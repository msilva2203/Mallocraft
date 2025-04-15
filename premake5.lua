workspace "Mallocraft"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

-- the general output directory for each project
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories
include_dirs = {}
include_dirs["glfw"] = "Source/ThirdParty/glfw/include"
include_dirs["glad"] = "Source/ThirdParty/glad/include"
include_dirs["stb_image"] = "Source/ThirdParty/stb_image/include"
include_dirs["glm"] = "Source/ThirdParty/glm"

-- premake includes
include "Source/ThirdParty/glfw"
include "Source/ThirdParty/glad"

project "Mallocraft"
    --location "./"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("Binaries/" .. outputdir)
    objdir ("Intermediate/" .. outputdir)

    files
    {
        "Source/Game/**.h",
        "Source/Game/**.cpp",
        "Source/ThirdParty/stb_image/src/*.cpp"
    }

    includedirs
    {
        "Source/Game/",
        "%{include_dirs.glfw}",
        "%{include_dirs.glad}",
        "%{include_dirs.stb_image}",
        "%{include_dirs.glm}"
    }

    links
    {
        "glfw",
        "glad"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "MALLOCRAFT_PLATFORM_WINDOWS"
        }

        links
        {
            "opengl32.lib"
        }

    filter "system:linux"
        pic "on"
        systemversion "latest"

        defines
        {
            "MALLOCRAFT_PLATFORM_LINUX"
        }

        links
        {
            "glfw",
            "GL",
            "X11",
            "pthread",
            "dl",
            "Xrandr",
            "Xi"
            --"Xxf86vm"
        }

    filter "configurations:Debug"
        defines "MALLOCRAFT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "MALLOCRAFT_RELEASE"
        runtime "Release"
        symbols "on"
        optimize "on"

    filter "configurations:Distribution"
        defines "MALLOCRAFT_DISTRIBUTION"
        runtime "Release"
        symbols "off"
        optimize "on"

    buildoptions "/utf-8"
