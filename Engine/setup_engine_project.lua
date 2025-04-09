project "sausageEngine"
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
   "Game/Source/**.h",
   "Game/Source/**.cpp",
   "Game/Source/**.c",
   "Game/Source/**.fs",
   "Game/Source/**.vs",
   "Game/Source/**.py",
        -- Add ImGui source files here
        "$(SolutionDir)Include/ImGui/**.cpp"
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


   targetdir ("$(SolutionDir)Engine/Build/" .. OutputDir .. "/%{prj.name}")
   objdir ("$(SolutionDir)Engine/Build/Intermediates/" .. OutputDir .. "/%{prj.name}")

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
    
   filter "configurations:DebugGameEditor"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"
       linkoptions { "/NODEFAULTLIB:MSVCRT.lib" }
       debugenvs { "PATH=%PATH%;$(SolutionDir)\\Binaries\\Debug" }


include "Game/setup_game_project.lua"