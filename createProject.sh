#!/bin/bash

premake5 gmake
premake5 export-compile-commands


make config=debug -j$(nproc)

