IncludeDir = {}
IncludeDir["GLFW"] = "Ancora/vendor/GLFW/include"
IncludeDir["Glad"] = "Ancora/vendor/Glad/include"
IncludeDir["ImGui"] = "Ancora/vendor/imgui"
IncludeDir["glm"] = "Ancora/vendor/glm"
IncludeDir["stb_image"] = "Ancora/vendor/stb_image"
IncludeDir["assimp"] = "Ancora/vendor/assimp/include"

include "Ancora/vendor/GLFW"
include "Ancora/vendor/Glad"
include "Ancora/vendor/imgui"
include "Ancora/vendor/assimp"

project "AncoraEngine"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	warnings "Default"
	-- warnings can take the values "Off", "Default", "Extra"

	targetdir ("bin/" .. outputdir .. "/Ancora")
	objdir ("bin-int/" .. outputdir .. "/Ancora")

	pchheader "aepch.h"
	pchsource "Ancora/src/aepch.cpp"

	files
	{
		"Ancora/src/**.h",
		"Ancora/src/**.cpp",
		"Ancora/vendor/stb_image/**.h",
		"Ancora/vendor/stb_image/**.cpp",
		"Ancora/vendor/glm/glm/**.hpp",
		"Ancora/vendor/glm/glm/**.inl"
	}

	excludes
	{
		"Ancora/src/Platform/**.h",
		"Ancora/src/Platform/**.cpp"
	}

	includedirs
	{
		"Ancora/src",
		"Ancora/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"assimp"
	}

	filter "system:linux"
		kind "SharedLib"

		defines
		{
			"AE_DYNAMIC_LINK"
		}

		links
		{
			"GL",
			"dl",
			"pthread"
		}

		files
		{
			"Ancora/src/Platform/Linux/**.h",
			"Ancora/src/Platform/Linux/**.cpp",
			"Ancora/src/Platform/OpenGL/**.h",
			"Ancora/src/Platform/OpenGL/**.cpp"
		}

		defines
		{
			"AE_PLATFORM_LINUX",
			"AE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "system:macosx"
		kind "SharedLib"

		defines
		{
			"AE_DYNAMIC_LINK"
		}

		links
		{
			"dl",
			"pthread"
		}

		files
		{
			"Ancora/src/Platform/Linux/**.h",
			"Ancora/src/Platform/Linux/**.cpp",
			"Ancora/src/Platform/OpenGL/**.h",
			"Ancora/src/Platform/OpenGL/**.cpp"
		}

		defines
		{
			"AE_PLATFORM_LINUX",
			"AE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "system:windows"
		systemversion "latest"
		kind "StaticLib"

		links
		{
			"opengl32.lib"
		}

		files
		{
			"Ancora/src/Platform/Windows/**.h",
			"Ancora/src/Platform/Windows/**.cpp",
			"Ancora/src/Platform/OpenGL/**.h",
			"Ancora/src/Platform/OpenGL/**.cpp"
		}

		defines
		{
			"AE_PLATFORM_WINDOWS",
			"AE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines
		{
			"AE_DEBUG",
			"AE_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AE_DIST"
		runtime "Release"
		optimize "on"
