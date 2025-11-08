@echo off
setlocal ENABLEDELAYEDEXPANSION

rem ===== Настройки llvm-mingw =====
rem Релиз: 20251104, архив llvm-mingw-20251104-ucrt-x86_64.zip
set "LLVM_MINGW_VER=20251104"
set "LLVM_MINGW_ARCH=ucrt-x86_64"
set "LLVM_MINGW_FILE=llvm-mingw-%LLVM_MINGW_VER%-%LLVM_MINGW_ARCH%.zip"
set "LLVM_MINGW_DIR=llvm-mingw-%LLVM_MINGW_VER%-%LLVM_MINGW_ARCH%"

set "COMPILER_ROOT=%LOCALAPPDATA%\Programs"
set "COMPILER_HOME=%COMPILER_ROOT%\%LLVM_MINGW_DIR%"
set "CLANG=%COMPILER_HOME%\bin\clang++.exe"

set "PROJECT_DIR=%CD%"
set "SRC_DIR=%PROJECT_DIR%\src"
set "OUT_EXE=%PROJECT_DIR%\Sea-Battle.exe"

set "TMP_ZIP=%TEMP%\%LLVM_MINGW_FILE%"
set "DOWNLOAD_URL=https://github.com/mstorsjo/llvm-mingw/releases/download/%LLVM_MINGW_VER%/%LLVM_MINGW_FILE%"

echo [INFO] Project directory: %PROJECT_DIR%

rem ===== Проверка и установка компилятора =====
if not exist "%CLANG%" (
    echo [INFO] Compiler not found, installing to "%COMPILER_HOME%"

    if not exist "%COMPILER_ROOT%" mkdir "%COMPILER_ROOT%"
    if not exist "%COMPILER_HOME%" mkdir "%COMPILER_HOME%"

    rem ---- Проверка интернета ----
    echo [INFO] Checking internet connection...
    ping -n 1 github.com >nul 2>&1
    if errorlevel 1 (
        echo [ERROR] No internet or github.com unreachable.
        pause
		exit /b 1
    )

    echo [INFO] Downloading llvm-mingw: %DOWNLOAD_URL%

    rem ---- Сначала пробуем curl ----
    where curl >nul 2>&1
    if %ERRORLEVEL%==0 (
        echo [INFO] Using curl...
        curl -L "%DOWNLOAD_URL%" -o "%TMP_ZIP%"
    ) else (
        echo [INFO] curl not found, using PowerShell...
        powershell -NoLogo -ExecutionPolicy Bypass ^
          -Command "[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -Uri '%DOWNLOAD_URL%' -OutFile '%TMP_ZIP%'"
    )

    if errorlevel 1 (
        echo [ERROR] Failed to download llvm-mingw.
        echo         Try to open this URL in browser: %DOWNLOAD_URL%
        pause
		exit /b 1
    )

    echo [INFO] Extracting archive to "%COMPILER_ROOT%"...
    powershell -NoLogo -ExecutionPolicy Bypass ^
      -Command "Expand-Archive -LiteralPath '%TMP_ZIP%' -DestinationPath '%COMPILER_ROOT%' -Force; Remove-Item '%TMP_ZIP%'"

    if errorlevel 1 (
        echo [ERROR] Failed to extract archive.
		pause
        exit /b 1
    )
)

if not exist "%CLANG%" (
    echo [ERROR] clang++.exe still not found at "%CLANG%".
	pause
    exit /b 1
)

rem ===== Конвертация исходников из UTF-8 в Windows-1251 =====
echo [INFO] Converting UTF-8 sources in "%SRC_DIR%" to Windows-1251...
powershell -NoLogo -ExecutionPolicy Bypass -Command ^
  "$enc1251 = [System.Text.Encoding]::GetEncoding(1251); " ^
  "$utf8 = New-Object System.Text.UTF8Encoding($false, $true); " ^
  "Get-ChildItem -Path '%SRC_DIR%' -Include *.cc,*.h -Recurse | ForEach-Object { " ^
  "  $bytes = [System.IO.File]::ReadAllBytes($_.FullName); " ^
  "  $isUtf8 = $true; " ^
  "  try { $text = $utf8.GetString($bytes) } catch { $isUtf8 = $false } " ^
  "  if ($isUtf8) { [System.IO.File]::WriteAllText($_.FullName, $text, $enc1251) } " ^
  "}"

if errorlevel 1 (
    echo [ERROR] Failed to convert sources encoding.
    pause
    endlocal
    exit /b 1
)

rem ===== Компиляция =====
echo [INFO] Using compiler: "%CLANG%"
echo [INFO] Building src\*.cc -^> "%OUT_EXE%"

pushd "%SRC_DIR%"
"%CLANG%" -std=c++20 ^
	-Wall -Wextra -Wno-invalid-source-encoding -Wno-sign-compare -Wno-reorder-ctor -Wno-parentheses ^
	-g -O2 *.cc -static -o "%OUT_EXE%"
set "BUILD_RC=%ERRORLEVEL%"
popd

if not "%BUILD_RC%"=="0" (
    echo [ERROR] Compilation failed, errorlevel=%BUILD_RC%.
	pause
    exit /b 1
)

echo.
echo [OK] Build finished: "%OUT_EXE%"
pause
endlocal
