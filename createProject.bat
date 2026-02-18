@echo off
premake\windows\premake5 --file=premake.lua vs2022
echo Build files generated!
premake5 export-compile-commands
echo "Exported compile-commands complete!"
pause

