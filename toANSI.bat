@echo off

set FILES= src\main.cc src\field.h src\field.cc src\arrangement_validity.h src\arrangement_validity.cc src\game_process.h src\game_process.cc src\draw.h


for %%a in (%FILES%) do (
	call :convert2ansi %%a
)
echo:
echo Press any key to continue
pause > NUL
goto :eof


:convert2ansi <FILE>
set FILE=%~1
echo | set /p dummyName="%FILE%... "
IF NOT EXIST %FILE% (
	echo no such file
	goto :eof
)
iconv -f utf-8 -t windows-1251 %FILE% > SomeNameThatIWouldNeverCallAFileInAProject.cpp 2> NUL
IF ERRORLEVEL 1 (
	del SomeNameThatIWouldNeverCallAFileInAProject.cpp
	echo already in ANSI
) ELSE (
	copy SomeNameThatIWouldNeverCallAFileInAProject.cpp %FILE% > NUL
	del SomeNameThatIWouldNeverCallAFileInAProject.cpp
	echo converted to ANSI
)
goto :eof


