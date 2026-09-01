@echo off
setlocal

REM Arg1 optional: repo root (passed from UBT)
set REPO=%~1
if "%REPO%"=="" set REPO=%CD%

cd /d "%REPO%"

REM Only commit if there are changes
git status --porcelain >nul 2>&1
for /f %%i in ('git status --porcelain') do set HASCHANGES=1

if not defined HASCHANGES (
  echo No git changes; skipping commit.
  exit /b 0
)

set MSG=Auto-commit after build: %DATE% %TIME%
git add -A
git commit -m "%MSG%"

REM Optional push:
REM git push

endlocal
