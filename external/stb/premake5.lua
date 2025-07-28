project "stb"
    kind "Utility"  -- Header-only library
    language "C++"
    staticruntime "on"

    targetdir ("%{wks.location}/binaries/" .. outputdir .. "/Breakout")
    objdir ("%{wks.location}/intermediate/" .. outputdir .. "/Breakout")

    files {
        "include/stb/stb_image.h",
    }

    includedirs {
        "include",
    }

    filter "system:windows"
        defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "architecture:x86_64"
        defines { "STBI_SSE2" } -- Enable SSE2 optimizations