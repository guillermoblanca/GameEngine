workspace "OpenGL_Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
IncludeDir["GLFW"] = "OpenGL_Engine/Dependencies/GLFW/include"
IncludeDir["GLAD"] = "OpenGL_Engine/Dependencies/GLAD/include"
IncludeDir["imgui"] = "OpenGL_Engine/Dependencies/imgui"
IncludeDir["glm"] = "OpenGL_Engine/Dependencies/glm"

include "OpenGL_Engine/Dependencies/GLFW"
include "OpenGL_Engine/Dependencies/GLAD"
include "OpenGL_Engine/Dependencies/imgui"


	project "OpenGL_Engine"
		location "OpenGL_Engine"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

	targetdir ("bin/".. outputdir .."/%{prj.name}")	
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gbpch.h"
	pchsource "OpenGL_Engine/src/gbpch.cpp"
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/Dependencies/glm/glm/**.hpp",
			"%{prj.name}/Dependencies/glm/glm/**.inl",	
		}
		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/Dependencies/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.imgui}",
			"%{IncludeDir.glm}",
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
		systemversion "latest"

		defines
		{
			"GB_PLATFORM_WINDOWS",
			"GB_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines 
		{
		"GB_DEBUG",
		"GB_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "on"

		filter "configurations:Release"
		defines "GB_RELEASE"
		runtime "Release"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleAPP"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .."/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	files 
	{
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"OpenGL_Engine/Dependencies/spdlog/include",
		"OpenGL_Engine/src",
		"%{IncludeDir.glm}",
		"OpenGL_Engine/Dependencies"
	}

	links
	{
	"OpenGL_Engine",
	}
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GB_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "GB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GB_RELEASE"
		runtime "Release"
		optimize "on"
