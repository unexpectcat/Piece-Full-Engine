package.path = package.path .. ";scripts/export-compile-commands/?.lua"
require("export-compile-commands")

workspace "SausageEngine"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
    startproject "SausageEngine"

outputdir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

project "SausageEngine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetname "SausageEngine"
    staticruntime "off"

    -- Unified paths using forward slashes
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files { 
        "src/**.h", "src/**.hpp",
        "src/**.cpp", "src/**.c",
        "src/**.fs", "src/**.vs",
        "include/imgui/**.cpp",
        "include/imgui/backends/**.cpp"
    }

    includedirs {
        "src",
        "include",
        "include/imgui",
        "include/imgui/backends"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS", "_CRT_SECURE_NO_WARNINGS" }
        buildoptions { "/EHsc" }
        -- Windows needs specific lib names
        links { "glfw3", "opengl32", "user32", "gdi32", "shell32", "assimp"}
        -- Change this to your actual local lib folder for Windows
        libdirs { "lib/windows" } 

    filter "system:linux"
        defines { "LINUX" }
        -- Linux finds these in /usr/lib automatically
        links { "glfw", "GL", "X11", "pthread", "dl", "m", "assimp" }

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        optimize "On"