workspace "OpenGL_Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	IncludeDir = {}
IncludeDir["GLFW"] = "OpenGL_Engine/Dependencies/GLFW/include"
IncludeDir["GLAD"] = "OpenGL_Engine/Dependencies/GLAD/include"
IncludeDir["imgui"] = "OpenGL_Engine/Dependencies/imgui"

include "OpenGL_Engine/Dependencies/GLFW"
include "OpenGL_Engine/Dependencies/GLAD"
include "OpenGL_Engine/Dependencies/imgui"

	project "OpenGL_Engine"
		location "OpenGL_Engine"
		kind "SharedLib"
		language "C++"
	targetdir ("bin/%{prj.name}")	
	objdir ("bin-int/%{prj.name}")

	pchheader "gbpch.h"
	pchsource "OpenGL_Engine/src/gbpch.cpp"
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"

		}
		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/Dependencies/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.imgui}"
		}
		links
		{
			"GLFW",
			"GLAD",
			"imgui",
			"opengl32.lib"
			
		}
		filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
		"GB_PLATFORM_WINDOWS",
			"GB_BUILD_DLL"
		}
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/Sandbox")
		}

		filter "configurations:Debug"
		defines 
		{
		"GB_DEBUG",
		"GB_ENABLE_ASSERTS"
		}
		symbols "On"

		filter "configurations:Release"
		defines "GB_RELEASE"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleAPP"
	language "C++"

	targetdir ("bin/%{prj.name}")
	objdir("bin-int/%{prj.name}")
	files 
	{
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"OpenGL_Engine/Dependencies/spdlog/include",
		"OpenGL_Engine/src"
	}

	links
	{
	"OpenGL_Engine"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GB_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "GB_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GB_RELEASE"
		symbols "On"
