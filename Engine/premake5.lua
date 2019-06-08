-- Shell Engine premake5.lua
workspace "Shell"
	architecture "x64"
	startproject "MainApp"
	configurations 
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.system}/%{cfg.buildcfg}-%{cfg.architecture}"

project "Shell"
	location "Shell"
	kind "SharedLib"
	language "C++"
	cppdialect "C++14"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/lib/spdlog/include"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SHELL_PLATFORM_WINDOWS",
			"SHELL_BUILD_DLL"
		}

		postbuildcommands
		{
			("IF NOT EXIST ../bin/" .. outputdir .. "/MainApp mkdir ../bin/" .. outputdir .. "/MainApp"),
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/MainApp/\"")
		}

	filter "configurations:Debug"
		defines "SHELL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SHELL_RELEASE"
		runtime "Release"
		optimize "on"

project "MainApp"
	location "MainApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++14"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Shell/lib/spdlog/include",
		"Shell/src",
		"Shell/lib"
	}

	links
	{
		"Shell"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SHELL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SHELL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SHELL_RELEASE"
		runtime "Release"
		optimize "on"
