workspace "Ancora"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	platforms
	{
		"linux",
		"windows"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Ancora/vendor/GLFW/include"

include "Ancora/vendor/GLFW"

project "Ancora"
	location "Ancora"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "aepch.h"
	pchsource "Ancora/src/aepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	excludes
	{
		"%{prj.name}/src/Platform/**.h",
		"%{prj.name}/src/Platform/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW"
	}

	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"

		links
		{
			"GL",
			"dl",
			"pthread"
		}

		files
		{
			"%{prj.name}/src/Platform/Linux/**.h",
			"%{prj.name}/src/Platform/Linux/**.cpp"
		}

		defines
		{
			"AE_PLATFORM_LINUX",
			"AE_BUILD_DLL"
		}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		links
		{
			"libopengl32.lib"
		}

		files
		{
			"%{prj.name}/src/Platform/Windows/**.h",
			"%{prj.name}/src/Platform/Windows/**.cpp"
		}

		defines
		{
			"AE_PLATFORM_WINDOWS",
			"AE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines 
		{
			"AE_DEBUG",
			"AE_ENABLE_ASSERTS"
		}
		symbols "On"

	filter "configurations:Release"
		defines "AE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "AE_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Ancora/vendor/spdlog/include",
		"Ancora/src"
	}

	links
	{
		"Ancora"
	}

	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"

		defines
		{
			"AE_PLATFORM_LINUX",
			"AE_BUILD_DLL"
		}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"AE_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines 
		{
			"AE_DEBUG",
			"AE_ENABLE_ASSERTS"
		}
		symbols "On"

	filter "configurations:Release"
		defines "AE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "AE_DIST"
		optimize "On"