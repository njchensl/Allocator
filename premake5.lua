workspace "Allocator"
    architecture "x64"
    startproject "Allocator"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

vectorextensions "AVX2"
buildoptions {
    "/Qpar", "/Qpar-report:1", "/Qvec-report:1"
}

filter "configurations:Release"
    linkoptions {
        "/LTCG"
    }
filter "configurations:Dist"
    linkoptions {
        "/LTCG"
    }


project "Allocator"
    location "Allocator"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    filter "system:windows"
        systemversion "latest"


    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
        buildoptions {
            "/O2", "/Ob2", "/Ot", "/Oy", "/GT", "/GL"
        }

    filter "configurations:Dist"
        runtime "Release"
        optimize "on"
        buildoptions {
            "/O2", "/Ob2", "/Ot", "/Oy", "/GT", "/GL"
        }

