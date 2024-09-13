project "myGame"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"
   
   files { "Source/**.h",
   "Source/**.cpp",
   "Source/**.c",
   "Source/**.fs",
   "Source/**.vs",
   "Source/**.py",
        -- Add ImGui source files here
        "$(SolutionDir)Include/ImGui/imgui.cpp",
        "$(SolutionDir)Include/ImGui/imgui_draw.cpp",
        "$(SolutionDir)Include/ImGui/imgui_tables.cpp",
        "$(SolutionDir)Include/ImGui/imgui_widgets.cpp",
        "$(SolutionDir)Include/ImGui/imgui_impl_glfw.cpp",
        "$(SolutionDir)Include/ImGui/imgui_impl_opengl3.cpp",

        -- Add Sausage Engine Files
        "$(SolutionDir)Engine/Source/glad.c",
        "$(SolutionDir)Engine/Source/Tabs/SceneWindow.h",
        "$(SolutionDir)Engine/Source/Tabs/SceneWindow.cpp",
        "$(SolutionDir)Engine/Source/Objects/trinagle.h",
        "$(SolutionDir)Engine/Source/Objects/triangle.cpp"

        -- "$(SolutionDir)Engine/Source/**.c",
        -- "$(SolutionDir)Engine/Source/**.fs",
        -- "$(SolutionDir)Engine/Source/**.vs",
        -- "$(SolutionDir)Engine/Source/**.py"
    
    }
   includedirs { 
    "$(SolutionDir)Include\\assimp",
    "$(SolutionDir)Include\\GLM",
    "$(SolutionDir)Include\\GLFW",
    "$(SolutionDir)Include\\ImGui",
    "$(SolutionDir)Include\\KHR",
    "$(SolutionDir)Include\\Glad",
    "$(SolutionDir)Include\\linmath",
    "$(SolutionDir)Include"
   }
   libdirs { "$(SolutionDir)Libraries" }
   
      
   defines
   {
       "_CRT_SECURE_NO_WARNINGS"
   }


   targetdir ("$(SolutionDir)Game/Build/" .. OutputDir .. "/%{prj.name}")
   objdir ("$(SolutionDir)Game/Build/Intermediates/" .. OutputDir .. "/%{prj.name}")

   links {
   "glfw3.lib",
   "opengl32.lib",
   "user32.lib",
   "gdi32.lib",
   "shell32.lib",
   "assimp-vc143-mt.lib"
   }
   
   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }
    
   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"
       linkoptions { "/NODEFAULTLIB:MSVCRT.lib" }
       debugenvs { "PATH=%PATH%;$(SolutionDir)\\Binaries\\Debug" }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"
       linkoptions { "/NODEFAULTLIB:MSVCRT.lib" }
       debugenvs { "PATH=%PATH%;$(SolutionDir)\\Binaries\\Release" }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
       linkoptions { "/NODEFAULTLIB:MSVCRT.lib" }
       debugenvs { "PATH=%PATH%;$(SolutionDir)\\Binaries\\Dist" }