project "spdlog"
    kind "None"  -- Header-only library
    language "C++"
    cppdialect "C++11"
    staticruntime "on"

    targetdir ("%{wks.location}/binaries/" .. outputdir .. "/Breakout")
    objdir ("%{wks.location}/intermediate/" .. outputdir .. "/Breakout")
    
    files {
        "include/spdlog/**.h",
    }
    
    includedirs {
        "include",
    }

    filter "action:vs*"
        defines { "_CRT_SECURE_NO_WARNINGS" }