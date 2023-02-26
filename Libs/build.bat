set WorkingDir=%~dp0

for /D %%G in ("%WorkingDir%*") do (
	echo Entering %%G
	for %%f in (%%G\*.def) do (
		echo Building %%~nf
		echo lib %%~nG
		makeStub.bat %%~nG %%~nf %%G
	)
)

pause
