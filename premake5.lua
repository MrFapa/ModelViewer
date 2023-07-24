workspace "ModelViewer"
    architecture "x64"
    configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "ModelViewer/Dependencies/GLFW/include"
IncludeDir["GLEW"] = "ModelViewer/Dependencies/glew-2.1.0/include"

LibDir = {}
LibDir["GLFW"] = "ModelViewer/Dependencies/GLFW/lib-vc2022"
LibDir["GLEW"] = "ModelViewer/Dependencies/glew-2.1.0/lib"
project "ModelViewer"
    location "ModelViewer"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/Dependencies/spdlog/src/*.cpp"
    }

    includedirs {
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLEW}",
        "%{prj.name}/Dependencies/spdlog/include"
    }

    libdirs {
        "%{LibDir.GLFW}",
        "%{LibDir.GLEW}"
    }

    links {
        "opengl32.lib",
        "glfw3_mt.lib",
        "glew32s.lib"
    }

    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"

    defines {
        "GLEW_STATIC"
    }

    filter "configurations:Debug"
        defines {
            "MV_DEBUG",
            "SPDLOG_COMPILED_LIB"   
        }
        symbols "On"

    filter "configurations:Release"
        defines "MV_RELEASE"
        optimize "On"
