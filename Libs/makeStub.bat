set LibraryName=%1
set StubName=%2
set WorkingDir=%3
set OutDir=%4
set StubDir=%WorkingDir%\%StubName%
set SDKPath=%SCE_ORBIS_SDK_DIR%\host_tools\bin\

"C:\Python27\python.exe" "%~dp0\emd_maker.py" %StubDir%.def

"%SDKPath%orbis-clang.exe" -Wall -D__LIB__ -fno-builtin -O2 -Wno-return-type -c %StubDir%.c -o %StubDir%.c.o
"%SDKPath%orbis-clang.exe" -Wall -D__LIB__ -D__ASM__ -c %StubDir%.S -o %StubDir%.S.o
"%SDKPath%orbis-ld.exe" --oformat=prx --prx-stub-output-dir=%WorkingDir%\..\..\ --Map=%StubDir%.map -o %LibraryName%.sprx %StubDir%.c.o %StubDir%.S.o %StubDir%.emd

Rem Rename all the stubs
ren %WorkingDir%\..\..\%StubName%_stub.a %StubName%_gen_stub.a
ren %WorkingDir%\..\..\%StubName%_stub_weak.a %StubName%_gen_stub_weak.a

Rem Clean up.
del %WorkingDir%\..\%LibraryName%.sprx
for /R %WorkingDir% %%f in (*) do (if not "%%~xf"==".def" del "%%~f")
