workspace "SausageEngine"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
    startproject "SausageEngine"

outputdir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

project "sausageEngine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
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
        "include/imgui/backends",
        "include/glad", -- Ensure Glad is found
        "include/glfw",
        "include/glm"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS", "_CRT_SECURE_NO_WARNINGS" }
        buildoptions { "/EHsc" }
        -- Windows needs specific lib names
        links { "glfw3", "opengl32", "user32", "gdi32", "shell32" }
        -- Change this to your actual local lib folder for Windows
        libdirs { "lib/windows" } 

    filter "system:linux"
        defines { "LINUX" }
        -- Linux finds these in /usr/lib automatically
        links { "glfw", "GL", "X11", "pthread", "dl", "m" }

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        optimize "On"