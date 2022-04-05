workspace "Flick"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Flick/vendor/GLFW/include"
IncludeDir["Glad"] = "Flick/vendor/Glad/include"
IncludeDir["ImGui"] = "Flick/vendor/imgui"
IncludeDir["glm"] = "Flick/vendor/glm"
IncludeDir["stb_image"] = "Flick/vendor/stb_image"

group "Dependencies"
	include "Flick/vendor/GLFW"
	include "Flick/vendor/Glad"
	include "Flick/vendor/imgui"

group ""

project "Flick"
	location "Flick"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fipch.h"
	pchsource "Flick/src/fipch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/src/Flick",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FI_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		filter "configurations:Debug"
			defines "FI_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "FI_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "FI_DIST"
			runtime "Release"
			optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Flick/vendor/spdlog/include",
		"Flick/src",
		"Flick/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Flick"
	}

	filter "system:windows"
		systemversion "latest"

		filter "configurations:Debug"
			defines "FI_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "FI_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "FI_DIST"
			runtime "Release"
			optimize "on"

project "Flick-Editor"
	location "Flick-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Flick/vendor/spdlog/include",
		"Flick/src",
		"Flick/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Flick"
	}

	filter "system:windows"
		systemversion "latest"

		filter "configurations:Debug"
			defines "FI_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "FI_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "FI_DIST"
			runtime "Release"
			optimize "on"