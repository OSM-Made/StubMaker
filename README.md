# StubMaker

Windows improvement of flatz's PS4 stub library maker. Creates linkable stub libraries that expose undocumented functions and internal APIs not available in the official PS4 SDK. Supports both standard and packed .prx formats where multiple libraries are combined into a single module.

## Requirements

- **Python 3.6+** (pathlib and modern syntax support required)
- **Sony PS4 SDK** with `SCE_ORBIS_SDK_DIR` environment variable set
- **Windows** (uses orbis-clang.exe and orbis-ld.exe from SDK)

## Setup

1. **Install Python 3.6 or higher**
   - Download from [python.org](https://www.python.org/downloads/)
   - Or use your preferred package manager

2. **Set SDK Environment Variable**
   - Ensure `SCE_ORBIS_SDK_DIR` is set to your Sony PS4 SDK installation path
   - Verify with: `echo %SCE_ORBIS_SDK_DIR%` (Command Prompt) or `$env:SCE_ORBIS_SDK_DIR` (PowerShell)

3. **Verify SDK Tools**
   - The build script requires `orbis-clang.exe` and `orbis-ld.exe` in `%SCE_ORBIS_SDK_DIR%\host_tools\bin\`

## Usage

Run the build script:

```bash
python build.py
```

The script will:
1. Clean up any existing `.a` files
2. Process all `.def` definition files in the `Libs/` directory
3. Generate assembly (`.S`), C (`.c`), and export metadata (`.emd`) files
4. Compile and link stub libraries using the Orbis SDK toolchain
5. Output all generated stub libraries to the `Build/` directory

### Output

Built stub libraries will be located in:
```
Build/
├── <stub_name>_gen_stub.a
└── <stub_name>_gen_stub_weak.a
```

You can now link your projects against these stubs for enhanced functionality.

## Project Structure

```
StubMaker/
├── build.py              # Main build script (replaces build.bat + emd_maker.py)
├── Include/              # C/C++ header files for exposed APIs
│   ├── Defs/             # Definition headers with constants and enums
│   │   ├── AppMessagingDefs.h
│   │   ├── KernelExtDefs.h
│   │   └── ...
│   ├── AppMessaging.h    # App messaging system functions
│   ├── KernelExt.h       # Extended kernel functions
│   ├── mdbg.h            # Debug functions
│   ├── NetExt.h          # Network extensions
│   └── ...               # Additional library headers
├── Libs/                 # Library definition files (.def)
│   ├── libSceNet/
│   │   └── libSceNet.def
│   ├── libkernel/
│   │   └── libkernel.def
│   ├── libSceSystemService/  # Example: packed .prx with multiple libs
│   │   ├── libSceAppMessaging.def
│   │   ├── libSceSystemService.def
│   │   └── ...
│   └── ...
└── Build/                # Output directory for built stub libraries
    ├── <stub_name>_gen_stub.a
    └── <stub_name>_gen_stub_weak.a
```

## Credits

Credits to [flatz](https://github.com/flatz) for the original [ps4_stub_lib_maker_v2](https://github.com/flatz/ps4_stub_lib_maker_v2) project. This is a Windows-compatible port with build process improvements.
