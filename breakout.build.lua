workspace "Breakout"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    startproject "Breakout"
    buildoptions { "/utf-8" }

    -- Output directories
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "external/GLM"
    include "external/stb"
    include "external/SDL3"
group ""

project "Breakout"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"
    cppdialect "C++20"

    warnings "High"
    targetdir ("binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

    files {
        "assets/**",
        "source/**",
    }

    includedirs {
        "source/",
        "external/*/include",
    }

    libdirs {
        "external/SDL3/lib",
    }

    links {
        "SDL3.lib",
        "GLM",
        "stb",
    }

    postbuildcommands {
        "{COPY} %{wks.location}external/SDL3/lib/SDL3.dll %{wks.location}binaries/\"" .. outputdir .. "\"/%{prj.name}",
        "{COPY} %{wks.location}assets/** %{wks.location}binaries/\"" .. outputdir .. "\"/%{prj.name}/assets",
    }

    filter "configurations:Debug"
        defines { "_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "_NDEBUG" }
        runtime "Release"
        symbols "Off"
        optimize "Full"
