@echo off
premake\windows\premake5.exe gmake2
premake\windows\premake5.exe export-compile-commands
pause

