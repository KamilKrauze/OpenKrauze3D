workspace "OpenKrauzeEngine"
    architecture "x64"
    configurations { "Debug", "Release" }

project "OpenKrauzeEngine"
    location "src"
    kind "ConsoleApp"
    language "C++"
    
    targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    files { 
        "./src/**.h",
        "./src/**.hpp",
        "./src/**.c",
        "./src/**.cpp"
    }

    includedirs {
        -- Project source code
        "./src/Public/",
        "./src/Private/",
        
        -- Thirdparty
        "./thirdparty/include/"
    }

    libdirs {
        "./thirdparty/lib/"
    }

-- Windows system

    filter "system:windows"
        system "windows"
        cppdialect "C++17"
        systemversion "latest"
        flags { "MultiProcessorCompile" }

-- Linux system
    filter "system:linux"
        system "linux"
        cppdialect "gnu++17"
        buildoptions { "-fopenmp" }
        links { "omp", "glfw", "GL", "m", "X11", "pthread", "Xi", "Xrandr", "dl" }

-- Build configurations
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"