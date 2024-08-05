-- premake5.lua
workspace "knu_proj"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "kubykEngine"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"


include "Engine/setup_project.lua"