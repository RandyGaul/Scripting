-----------------------------------------------------------------
--                     Solution Settings                       --
-----------------------------------------------------------------
solution ( "../vs/scripting" )
  -- Different types of configurations for the solution
  configurations { "Debug", "Release" }

-----------------------------------------------------------------
--      This entire section belongs to a single project        --
-----------------------------------------------------------------
project ( "scripting" )
  language ( "C++" )
  kind ( "ConsoleApp" )
  location ( "../vs" )
  objdir ( "../objs" )
  targetdir ( "../bin" )
  libdirs { "../dependencies/" .. "**" }
  includedirs { "../dependencies/include", "../src/scripting/" }

  -- Types of files to include within this project
  files {
    "../src/scripting/**.h",
    "../src/scripting/**.hpp",
    "../src/scripting/**.cpp",
    "../src/scripting/**.c",
    "../src/scripting/**.txt",
    "../src/scripting/**.fx"
  }

  -- Debug Configuration Settings
  configuration "Debug"
    defines { "_DEBUG" }
    flags {
      "Symbols",
      "NoMinimalRebuild",
      "NoEditAndContinue",
      "FloatStrict",
      "StaticRuntime",
      "WinMain",
      "NoRTTI"
      }
      
    links {
    }
    
    pchheader ( "Precompiled.h" )
    pchsource ( "../src/scripting/Precompiled.c" )

    -- disable specific warnings:
    buildoptions { "/wd4100", "/wd4996", "/wd4201", "/wd4238", "/wd4800", "/wd4239", "/wd4505" }

  -- Release Configuration Settings
  configuration "Release"
    defines { "NDEBUG" }
    flags {
      "Symbols",
      "NoMinimalRebuild",
      "NoEditAndContinue",
      "FloatFast",
      "StaticRuntime",
      "WinMain",
      "OptimizeSpeed",
      "NoRTTI"
      }
      
    links {
    }
    
    pchheader ( "Precompiled.h" )
    pchsource ( "../src/scripting/Precompiled.c" )

    -- disable specific warnings:
    buildoptions { "/wd4100", "/wd4996", "/wd4201", "/wd4238", "/wd4800", "/wd4239", "/wd4505" }
