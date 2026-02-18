#!/bin/bash

premake5 gmake2
premake5 export-compile-commands
echo "Exported compile-commands complete!"

make config=debug -j$(nproc)
echo "Build complete!"

