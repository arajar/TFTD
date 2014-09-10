-------------------------------------------------------------------------------
-- 
-------------------------------------------------------------------------------

include "../tools/premake/common/"

-------------------------------------------------------------------------------

solution "Tesseract"

	math.randomseed(string.hash(solution().name))
  	startproject "Tesseract"
	addCommonConfig()

	configuration "Debug"
		targetsuffix "-d"

-------------------------------------------------------------------------------

	local LIBS      = "../libs/"
	local BUILD_DIR = "../build/".._OPTIONS["arch"].."/"

	local CORE      = LIBS.."core"
	local SFML      = LIBS.."sfml"
	local GLM	    = LIBS.."glm"
	local IMGUI     = LIBS.."imgui"
	local GLEW      = LIBS.."glew-1.10.0"
	local PUGIXML   = LIBS.."pugixml"
	local SPINE     = LIBS.."spine"

-------------------------------------------------------------------------------
	
	defines "GLEW_STATIC"
	defines "SFML_STATIC"

-------------------------------------------------------------------------------

project "sfml"
	targetdir(BUILD_DIR)
	kind "StaticLib"
	language "C++"

	includedirs
	{
		SFML.."/include/",
		SFML.."/src/",
		SFML.."/extlibs/headers/AL",
		SFML.."/extlibs/headers/jpeg",
		SFML.."/extlibs/headers/libsndfile/windows",
		SFML.."/extlibs/headers/libfreetype/windows",
		GLEW.."/include",
	}

	files
	{
		SFML.."/src/SFML/Audio/*.cpp",
		SFML.."/src/SFML/Graphics/*.cpp",
		SFML.."/src/SFML/Main/*.cpp",
		SFML.."/src/SFML/Network/*.cpp",
		SFML.."/src/SFML/System/*.cpp",
		SFML.."/src/SFML/Window/*.cpp",
		SFML.."/src/SFML/Network/Win32/*.cpp",
		SFML.."/src/SFML/System/Win32/*.cpp",
		SFML.."/src/SFML/Window/Win32/*.cpp",
	}

	libdirs
	{
		BUILD_DIR,
		SFML.."/extlibs/libs-msvc/" .. _OPTIONS["arch"],
		GLEW.."/lib/" .. _OPTIONS["arch"],
	}

	links
	{
		"glew32s.lib",
		"freetype",
		"jpeg",
		"openal32",
		"sndfile",
		"winmm",
	}

	configuration "Debug"
		defines { "_DEBUG" }

	configuration "Release"
		defines { "NDEBUG" }

-------------------------------------------------------------------------------

project "pugixml"
	targetdir(BUILD_DIR)
	kind "StaticLib"
	language "C++"

	files
	{
		PUGIXML.."/src/pugixml.hpp",
		PUGIXML.."/src/pugiconfig.hpp",
		PUGIXML.."/src/pugixml.cpp"
	}

	configuration "Debug"
		defines { "_DEBUG" }

	configuration "Release"
		defines { "NDEBUG" }

-------------------------------------------------------------------------------

project "spine"
	targetdir(BUILD_DIR)
	kind "StaticLib"
	language "C"

	files
	{
		SPINE.."/src/",
		SPINE.."/src/**",
		SPINE.."/include/**",
	}

	includedirs
	{
		SPINE.."/include",
	}

	configuration "Debug"
		buildoptions { "/MDd" }

	configuration "Release"
		buildoptions { "/MD" }

-------------------------------------------------------------------------------

project "core"
	targetdir(BUILD_DIR)
	kind "StaticLib"

	files 
	{
		CORE.."/**",
	}

	includedirs 
	{
		CORE.."/",
		CORE.."/**",
		GLM.."/glm",
		IMGUI,
		GLEW.."/include",
		PUGIXML.."/src",
		SFML.."/include",
		SPINE.."/include",
	}

	libdirs 
	{ 
		GLEW.."/lib/" .. _OPTIONS["arch"],
		BUILD_DIR,

	}

	links
	{
		"glew32s.lib",
		"opengl32",
		"imgui",
		"pugixml",
		"spine",
		"sfml",
		"jpeg",
		"freetype",
	}

	configuration "Debug"
		buildoptions { "/MDd" }

	configuration "Release"
		buildoptions { "/MD" }

-------------------------------------------------------------------------------

project "imgui"
	targetdir(BUILD_DIR)
	kind "StaticLib"

	files
	{
		IMGUI .. "/**",
	}

	includedirs
	{
		IMGUI,
	}

	excludes 
	{
		IMGUI.."/examples",
		IMGUI.."/examples/**",
		IMGUI.."/web",
		IMGUI.."/web/**",
	}

	configuration "Debug"
		buildoptions { "/MDd" }
		defines
		{
			"_DEBUG",
			"_SCL_SECURE_NO_WARNINGS",
			"_CRT_SECURE_NO_WARNINGS",
		}

	configuration "Release"
		buildoptions { "/MD" }
		defines
		{
			"NDEBUG",
			"_SECURE_SCL=0",
			"_SECURE_SCL_THROWS=0",
			"_SCL_SECURE_NO_WARNINGS",
			"_CRT_SECURE_NO_WARNINGS",
		}

-------------------------------------------------------------------------------

project "Tesseract"

	targetdir("../release/" )
	kind "ConsoleApp"
	pchheader "pch.h"
	pchsource "../src/pch.cpp"
	debugdir("$(TargetDir)")

	files 
	{
		"../src/**",
	}

	includedirs 
	{
		"../src/",
		"../src/**",
		CORE,
		GLM.."/glm",
		IMGUI,
		GLEW.."/include",
		SFML.."/include",
		SPINE.."/include",
	}

	libdirs 
	{ 
		SFML.."/extlibs/libs-msvc/" .. _OPTIONS["arch"],
		GLEW.."/lib/" .. _OPTIONS["arch"],
		BUILD_DIR,
	}

	links
	{
		"glew32s.lib",
		"opengl32",
		"imgui",
		"core",
		"sfml",
		"pugixml",
		"freetype",
		"jpeg",
		"winmm",
		"spine",
	}

	-- Copy the needed dlls to the output dir
	postbuildcommands
	{
		"echo Copying dlls...",
		"robocopy $(SolutionDir)../../"..SFML.."/bin/" .. _OPTIONS["arch"] .. "/ $(TargetDir)  /XO /NJH /NP > log.txt",
		"exit 0",
	}

	targetname( "Tesseract" .. _OPTIONS["arch"])

	configuration "Debug"
		buildoptions { "/MDd" }

	configuration "Release"
		buildoptions { "/MD" }

---------------------------------------------------------------------------

