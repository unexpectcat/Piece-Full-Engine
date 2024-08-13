project "kubykEngine"
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
   "Source/**.py"
    }
   includedirs { 
    "$(SolutionDir)Engine\\Include\\assimp",
    "$(SolutionDir)Engine\\Include\\GL",
    "$(SolutionDir)Engine\\Include\\GLFW",
    "$(SolutionDir)Engine\\Include\\ImGui",
    "$(SolutionDir)Engine\\Include\\KHR",
    "$(SolutionDir)Engine\\Include\\Glad",
    "$(SolutionDir)Engine\\Include"
   }
   libdirs { "$(SolutionDir)Engine/Libraries" }
   

   
      
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
    
   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"
       debugenvs { "PATH=%PATH%;$(SolutionDir)\\Engine\\Binaries\\Debug" }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"
       debugenvs { "PATH=%PATH%;$(SolutionDir)\\App\\Build\\Binaries\\Release" }

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"
       debugenvs { "PATH=%PATH%;$(SolutionDir)\\App\\Build\\Binaries\\Dist" }