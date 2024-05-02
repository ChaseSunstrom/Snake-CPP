workspace "Snake-CPP"
    architecture "x64"
    configurations {"Debug", "Release"}
    startproject "Snake-CPP"

project "Snake-CPP"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    cppdialect "C++20"

    files { "src/**.c", "src/**.h" }

    includedirs {
        "include/**"
    }

    libdirs {
        "lib/**"
    }

    links {
        "SDL2",
        "SDL2main"
    }

    postbuildcommands {
        "{COPY} %{wks.location}lib/DLLs/*.dll bin/%{cfg.buildcfg}"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        defines { "RELEASE", "NDEBUG" }
        optimize "Full"