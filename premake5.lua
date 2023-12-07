workspace "OpenKrauzeEngine"
    architecture "x64"
    
    configurations { "Debug", "Release" }

project "OpenKrauzeEngine"
    location "src"
    kind "ConsoleApp"
    language "C++"
    
    targetdir "bin/%{cfg.buildcfg}-${cfg.configurations}-${cfg.architecture}"

    files { 
        "./src/**.h",
        "./src/**.hpp",
        "./src/**.c",
        "./src/**.cpp"
    }

    includedirs {
        "./include/"
    }

    libdirs {
        "./lib/"
    }

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"