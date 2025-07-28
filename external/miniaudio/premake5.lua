project "MiniAudio"
    kind "None"  -- Header-only library
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/binaries/" .. outputdir .. "/Breakout")
    objdir ("%{wks.location}/intermediate/" .. outputdir .. "/Breakout")    

    files {
        "include/miniaudio/**.h"
    }
    
    includedirs {
        "include"
    }
