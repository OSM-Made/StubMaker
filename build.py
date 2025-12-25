#!/usr/bin/env python3

import os
import sys
import re
import subprocess
import shutil
from pathlib import Path
from typing import List, Tuple

# Configuration
WORKING_DIR = Path(__file__).parent.resolve()
LIBS_DIR = WORKING_DIR / "Libs"
BUILD_DIR = WORKING_DIR / "Build"
SDK_PATH_ENV = "SCE_ORBIS_SDK_DIR"


class EMDMaker:
    """Embedded Module Definition generator - parses .def files and generates stub files."""

    def __init__(self, def_file_path: Path):
        self.def_file_path = def_file_path
        self.def_file_path_wo_ext = def_file_path.with_suffix('')
        self.lib_name = def_file_path.stem

        self.fun_names: List[str] = []
        self.obj_names: List[str] = []
        self.tls_names: List[str] = []

    def parse_def_file(self):
        """Parse the .def file to extract functions, objects, and TLS variables."""
        if not self.def_file_path.is_file():
            raise FileNotFoundError(f"Definition file not found: {self.def_file_path}")

        marker = None
        marker_regexp = re.compile(r'^([A-Za-z0-9_]+)\s*:$', re.IGNORECASE)
        name_with_nid_regexp = re.compile(r'^([A-Za-z0-9_]+)\s*=\s*(0[xX][A-Fa-f0-9]+)\s*$')

        with open(self.def_file_path, 'r') as f:
            for line in f.readlines():
                line = line.rstrip('\r\n').strip()

                # Skip empty lines and comments
                if len(line) == 0 or line.startswith(';'):
                    continue

                # Check for section markers (fun:, obj:, tls:)
                matches = marker_regexp.match(line)
                if matches is not None:
                    marker = matches.group(1)
                    continue

                # Check for name with NID
                matches = name_with_nid_regexp.match(line)
                if matches is not None:
                    name, nid = matches.group(1), matches.group(2)
                    line = f'{name}__nid_{nid}'

                # Add to appropriate list based on current marker
                if marker == 'fun':
                    self.fun_names.append(line)
                elif marker == 'obj':
                    self.obj_names.append(line)
                elif marker == 'tls':
                    self.tls_names.append(line)

    def generate_asm_file(self):
        """Generate the .S assembly file."""
        asm_file_path = self.def_file_path_wo_ext.with_suffix('.S')

        # Remove existing file if present
        if asm_file_path.is_file():
            asm_file_path.unlink()

        with open(asm_file_path, 'w') as f:
            # Generate function stubs
            for name in self.fun_names:
                f.write(f'.global {name}\n')
                f.write(f'.type {name}, @function\n')
                f.write(f'{name}:\n')
                f.write('\tretq\n\n')

            f.write('\n')

            # Generate object stubs
            for name in self.obj_names:
                f.write(f'.global {name}\n')
                f.write(f'.type {name}, @object\n')
                f.write(f'{name}:\n')
                f.write('\t.byte 0\n\n')

    def generate_c_file(self):
        """Generate the .c file with TLS variables."""
        c_file_path = self.def_file_path_wo_ext.with_suffix('.c')

        # Remove existing file if present
        if c_file_path.is_file():
            c_file_path.unlink()

        with open(c_file_path, 'w') as f:
            # Generate TLS variables
            for name in self.tls_names:
                f.write(f'__thread char {name}[1];\n')

    def generate_emd_file(self):
        """Generate the .emd export metadata file."""
        emd_file_path = self.def_file_path_wo_ext.with_suffix('.emd')

        # Remove existing file if present
        if emd_file_path.is_file():
            emd_file_path.unlink()

        with open(emd_file_path, 'w') as f:
            f.write(f'Library: {self.lib_name} {{\n')
            f.write('\texport: {\n')

            # Write all exports
            for name in self.fun_names:
                f.write(f'\t\t{name}\n')
            for name in self.obj_names:
                f.write(f'\t\t{name}\n')
            for name in self.tls_names:
                f.write(f'\t\t{name}\n')

            f.write('\t}\n')
            f.write('}\n')

    def generate_all(self):
        """Generate all stub files from the .def file."""
        print(f"  Generating stubs for {self.lib_name}")
        self.parse_def_file()
        self.generate_asm_file()
        self.generate_c_file()
        self.generate_emd_file()


class StubBuilder:
    """Builds stub libraries using the Orbis SDK toolchain."""

    def __init__(self):
        # Get SDK path from environment
        sdk_dir = os.environ.get(SDK_PATH_ENV)
        if not sdk_dir:
            raise EnvironmentError(
                f"{SDK_PATH_ENV} environment variable not set. "
                "Please set it to your Orbis SDK directory."
            )

        self.sdk_bin = Path(sdk_dir) / "host_tools" / "bin"
        self.orbis_clang = self.sdk_bin / "orbis-clang.exe"
        self.orbis_ld = self.sdk_bin / "orbis-ld.exe"

        # Verify tools exist
        if not self.orbis_clang.is_file():
            raise FileNotFoundError(f"orbis-clang not found at {self.orbis_clang}")
        if not self.orbis_ld.is_file():
            raise FileNotFoundError(f"orbis-ld not found at {self.orbis_ld}")

    def clean_old_files(self):
        """Clean up old generated .a files."""
        print("Cleaning up old .a files...")
        for a_file in WORKING_DIR.rglob("*.a"):
            print(f"  Deleting {a_file}")
            a_file.unlink()

    def build_library(self, library_name: str, stub_name: str, out_dir: Path) -> bool:
        """Build a single stub library."""
        print(f"\nBuilding {stub_name}")
        print(f"  Library: {library_name}")

        stub_dir = out_dir / stub_name
        stub_path_prefix = str(stub_dir)

        # Generate EMD files
        try:
            emd_maker = EMDMaker(stub_dir.with_suffix('.def'))
            emd_maker.generate_all()
        except Exception as e:
            print(f"  ERROR: Failed to generate EMD files: {e}")
            return False

        # Compile .c file
        c_file = stub_dir.with_suffix('.c')
        c_obj = Path(str(c_file) + '.o')

        try:
            print(f"  Compiling {c_file.name}")
            result = subprocess.run([
                str(self.orbis_clang),
                "-Wall",
                "-D__LIB__",
                "-fno-builtin",
                "-O2",
                "-Wno-return-type",
                "-c",
                str(c_file),
                "-o",
                str(c_obj)
            ], check=True, capture_output=True, text=True)
        except subprocess.CalledProcessError as e:
            print(f"  ERROR: Compilation of .c file failed")
            print(f"  {e.stderr}")
            return False

        # Compile .S file
        s_file = stub_dir.with_suffix('.S')
        s_obj = Path(str(s_file) + '.o')

        try:
            print(f"  Compiling {s_file.name}")
            result = subprocess.run([
                str(self.orbis_clang),
                "-Wall",
                "-D__LIB__",
                "-D__ASM__",
                "-c",
                str(s_file),
                "-o",
                str(s_obj)
            ], check=True, capture_output=True, text=True)
        except subprocess.CalledProcessError as e:
            print(f"  ERROR: Compilation of .S file failed")
            print(f"  {e.stderr}")
            return False

        # Link to create stub
        emd_file = stub_dir.with_suffix('.emd')
        map_file = stub_dir.with_suffix('.map')
        sprx_file = out_dir.parent.parent / f"{library_name}.sprx"

        try:
            print(f"  Linking")
            result = subprocess.run([
                str(self.orbis_ld),
                "--oformat=prx",
                f"--prx-stub-output-dir={out_dir.parent.parent}",
                f"--Map={map_file}",
                "-o",
                str(sprx_file),
                str(c_obj),
                str(s_obj),
                str(emd_file)
            ], check=True, capture_output=True, text=True)
        except subprocess.CalledProcessError as e:
            print(f"  ERROR: Linking failed")
            print(f"  {e.stderr}")
            return False

        # Ensure Build directory exists
        BUILD_DIR.mkdir(exist_ok=True)

        # Rename and move stub files to Build directory
        old_stub = out_dir.parent.parent / f"{stub_name}_stub.a"
        old_stub_weak = out_dir.parent.parent / f"{stub_name}_stub_weak.a"
        new_stub = BUILD_DIR / f"{stub_name}_gen_stub.a"
        new_stub_weak = BUILD_DIR / f"{stub_name}_gen_stub_weak.a"

        if old_stub.is_file():
            print(f"  Moving {stub_name}_stub.a to Build/{stub_name}_gen_stub.a")
            shutil.move(str(old_stub), str(new_stub))

        if old_stub_weak.is_file():
            print(f"  Moving {stub_name}_stub_weak.a to Build/{stub_name}_gen_stub_weak.a")
            shutil.move(str(old_stub_weak), str(new_stub_weak))

        # Clean up intermediate files
        print(f"  Cleaning up intermediate files")
        if sprx_file.is_file():
            sprx_file.unlink()

        # Remove all files in the stub directory except .def files
        for file in out_dir.iterdir():
            if file.is_file() and file.suffix != '.def':
                file.unlink()

        print(f"  ✓ Successfully built {stub_name}")
        return True

    def build_all(self):
        """Build all libraries found in the Libs directory."""
        if not LIBS_DIR.is_dir():
            print(f"ERROR: Libs directory not found at {LIBS_DIR}")
            return False

        # Clean old files first
        self.clean_old_files()

        # Create Build directory
        BUILD_DIR.mkdir(exist_ok=True)

        success_count = 0
        fail_count = 0

        # Iterate through library directories
        for lib_dir in sorted(LIBS_DIR.iterdir()):
            if not lib_dir.is_dir():
                continue

            library_name = lib_dir.name

            # Find all .def files in this library directory
            def_files = list(lib_dir.glob("*.def"))

            for def_file in def_files:
                stub_name = def_file.stem

                if self.build_library(library_name, stub_name, lib_dir):
                    success_count += 1
                else:
                    fail_count += 1

        print("\n" + "=" * 60)
        print(f"Build Summary:")
        print(f"  Success: {success_count}")
        print(f"  Failed:  {fail_count}")
        print(f"  Output:  {BUILD_DIR}")
        print("=" * 60)

        return fail_count == 0


def main():
    """Main entry point."""
    print("=" * 60)
    print("StubMaker Build Script")
    print("=" * 60)
    print()

    try:
        builder = StubBuilder()
        success = builder.build_all()

        if success:
            print("\n✓ Build completed successfully!")
            input("\nPress Enter to exit...")
            return 0
        else:
            print("\n✗ Build completed with errors.")
            input("\nPress Enter to exit...")
            return 1

    except Exception as e:
        print(f"\n✗ ERROR: {e}")
        import traceback
        traceback.print_exc()
        input("\nPress Enter to exit...")
        return 1


if __name__ == "__main__":
    main()
