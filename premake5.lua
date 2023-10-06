workspace "Media_Player"
	architecture "x64"

	configurations {
		"Debug"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDirs = {}
includeDirs["FMOD"] = "%{prj.name}/vendor/FMOD/include"
includeDirs["SPDLOG"] = "%{prj.name}/vendor/spdlog/include"
includeDirs["GLFW"] = "%{prj.name}/vendor/GLFW/include"
includeDirs["DearImGUI"] = "%{prj.name}/vendor/DearImGUI/include"

project "Media_Player"
	location "Media_Player"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp" 

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/src",
		"%{includeDirs.FMOD}",
		"%{includeDirs.SPDLOG}",
		"%{includeDirs.GLFW}",
		"%{includeDirs.DearImGUI}"
	}

	libdirs {
		"%{prj.name}/vendor/FMOD/lib",
		"%{prj.name}/vendor/GLFW/bin/Debug-windows-x86_64/GLFW"
	}

	links {
		"fmod_vc.lib",
		"fmodL_vc.lib",
		"GLFW"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		runtime "Debug"
		systemversion "latest"

		defines { }

		postbuildcommands {
			('{COPY} "../Media_Player/vendor/FMOD/lib/fmod.dll" "../bin/Debug-windows-x86_64/Media_Player"')
		}

	filter "configurations:Debug"
		symbols "On"

