buildpath = "%{cfg.platform}.%{cfg.buildcfg}.%{cfg.architecture}"

workspace "B"
    
    architecture "x64"
	startproject "B"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

project "B"
    location "B"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin/" .. buildpath .. "/%{prj.name}")
    objdir ("%{wks.location}/bin/int/" .. buildpath .. "/%{prj.name}")

    pchheader "bpch.h"
	pchsource "B/src/bpch.cpp"

    files {
        "B/src/**.cpp",
        "B/src/**.h"
    }

    includedirs {
        "B/src"
    }