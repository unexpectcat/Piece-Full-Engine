#!/bin/bash

premake5 gmake
premake5 export-compile-commands

read -p "Recreate include files? y/N: " answer
if [[ "$answer" =~ ^[Yy]$ ]]; then
    mkdir -p include/GLFW/
    cp ./vendor/glfw/include/GLFW/ ./include/GLFW/ -r

    mkdir -p include/imgui/
    cp vendor/imgui/imconfig.h include/imgui/
    cp vendor/imgui/imgui.cpp include/imgui/
    cp vendor/imgui/imgui.h include/imgui/
    cp vendor/imgui/imgui_demo.cpp include/imgui/
    cp vendor/imgui/imgui_draw.cpp include/imgui/
    cp vendor/imgui/imgui_internal.h include/imgui/
    cp vendor/imgui/imgui_tables.cpp include/imgui/
    cp vendor/imgui/imgui_widgets.cpp include/imgui/
    cp vendor/imgui/imstb_rectpack.h include/imgui/
    cp vendor/imgui/imstb_textedit.h include/imgui/
    cp vendor/imgui/imstb_truetype.h include/imgui/

    mkdir -p include/imgui/backends/
    cp vendor/imgui/backends/imgui_impl_glfw.cpp include/imgui/backends/
    cp vendor/imgui/backends/imgui_impl_glfw.h include/imgui/backends/
    cp vendor/imgui/backends/imgui_impl_opengl3.cpp include/imgui/backends/
    cp vendor/imgui/backends/imgui_impl_opengl3.h include/imgui/backends/
    cp vendor/imgui/backends/imgui_impl_opengl3_loader.h include/imgui/backends/

    mkdir -p include/glad2/
    cp vendor/glfw/deps/glad/gl.h include/glad2/gl.h
fi

make config=debug -j$(nproc)

