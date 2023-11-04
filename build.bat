@echo off
set WorkingDir=%~dp0

REM Clean up old generated files.
for /r "%WorkingDir%" %%f in (*.a) do (
    REM echo Deleting "%%f"
    del "%%f"
)

REM Main script
for /D %%G in ("%WorkingDir%Libs\*") do (
    REM echo Entering %%G
    for %%f in (%%G\*.def) do (
        echo Building %%~nf
        echo lib %%~nG
        REM echo path %%G
        call :BuildLibrary "%%~nG" "%%~nf" "%%G"
    )
)

pause
goto :EOF

REM Function to perform the external commands
:BuildLibrary
set LibraryName=%1
set StubName=%2
set OutDir=%3
set StubDir=%OutDir%\\%StubName%
set SDKPath=%SCE_ORBIS_SDK_DIR%\host_tools\bin\

python "%WorkingDir%Scripts\emd_maker.py" %StubDir%.def 

"%SDKPath%orbis-clang.exe" -Wall -D__LIB__ -fno-builtin -O2 -Wno-return-type -c %StubDir%.c -o %StubDir%.c.o
"%SDKPath%orbis-clang.exe" -Wall -D__LIB__ -D__ASM__ -c %StubDir%.S -o %StubDir%.S.o
"%SDKPath%orbis-ld.exe" --oformat=prx --prx-stub-output-dir=%OutDir%\..\..\ --Map=%StubDir%.map -o %LibraryName%.sprx %StubDir%.c.o %StubDir%.S.o %StubDir%.emd

REM Rename all the stubs
ren %OutDir%\..\..\%StubName%_stub.a %StubName%_gen_stub.a
ren %OutDir%\..\..\%StubName%_stub_weak.a %StubName%_gen_stub_weak.a

REM Clean up.
del %OutDir%\..\..\%LibraryName%.sprx
for /R %OutDir% %%f in (*) do (if not "%%~xf"==".def" del "%%~f")

REM Return from the function
goto :EOF
