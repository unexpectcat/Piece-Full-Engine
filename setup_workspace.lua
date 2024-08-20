-- premake5.lua
workspace "sausage_project"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "kubykEngine"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"


include "Engine/setup_engine_project.lua"
include "Game/setup_game_project.lua"