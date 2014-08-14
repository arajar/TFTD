-------------------------------------------------------------------------------
-- 
-------------------------------------------------------------------------------

include "../tools/premake/common/"

-------------------------------------------------------------------------------

solution "TFTD"

	math.randomseed(string.hash(solution().name))
  	startproject "terror"
	addCommonConfig()

-------------------------------------------------------------------------------

	local LIBS      = "../libs/"
	local BUILD_DIR = "../build/".._OPTIONS["arch"].."/"

	local CORE      = LIBS.."core"
	local SDL_LIB   = LIBS.."SDL2-2.0.3"
	local SDL_MIX   = LIBS.."SDL2_mixer-2.0.0"
	local SDL_TTF   = LIBS.."SDL2_ttf-2.0.12"
	local SDL_IMG   = LIBS.."SDL2_image-2.0.0"
	local GLM	    = LIBS.."glm"
	local IMGUI     = LIBS.."imgui"
	local GLEW      = LIBS.."glew-1.10.0"

-------------------------------------------------------------------------------
	
	defines "GLEW_STATIC"

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
		SDL_LIB.."/include",
		SDL_MIX.."/include",
		SDL_TTF.."/include",
		SDL_IMG.."/include",
		GLM.."/glm",
		IMGUI,
		GLEW.."/include",
	}

	libdirs 
	{ 
		SDL_LIB.."/lib/" .. _OPTIONS["arch"],
		SDL_MIX.."/lib/" .. _OPTIONS["arch"],
		SDL_TTF.."/lib/" .. _OPTIONS["arch"],
		SDL_IMG.."/lib/" .. _OPTIONS["arch"],
		GLEW.."/lib/" .. _OPTIONS["arch"],
		BUILD_DIR,
	}

	links
	{
		"glew32s.lib",
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2test.lib",
		"SDL2_image.lib",
		"SDL2_mixer.lib",
		"SDL2_ttf.lib",
		"Opengl32.lib",
		"imgui.lib"
	}

	configuration "Debug"
		buildoptions { "/MDd" }

	configuration "Release"
		buildoptions { "/MD" }

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

	configuration "Release"
		buildoptions { "/MD" }


project "terror"

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
		SDL_LIB.."/include",
		SDL_MIX.."/include",
		SDL_TTF.."/include",
		SDL_IMG.."/include",
		GLM.."/glm",
		IMGUI,
		GLEW.."/include",
	}

	libdirs 
	{ 
		SDL_LIB.."/lib/" .. _OPTIONS["arch"],
		SDL_MIX.."/lib/" .. _OPTIONS["arch"],
		SDL_TTF.."/lib/" .. _OPTIONS["arch"],
		SDL_IMG.."/lib/" .. _OPTIONS["arch"],
		GLEW.."/lib/" .. _OPTIONS["arch"],
		BUILD_DIR,
	}

	links
	{
		"glew32s.lib",
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2test.lib",
		"SDL2_image.lib",
		"SDL2_mixer.lib",
		"SDL2_ttf.lib",
		"Opengl32.lib",
		"imgui.lib"
	}

	-- Copy the needed dlls to the output dir
	postbuildcommands
	{
		"echo Copying dlls...",
		"robocopy $(SolutionDir)../../"..SDL_LIB.."/bin/" .. _OPTIONS["arch"] .. "/ $(TargetDir)  /XO /NJH /NP > log.txt",
		"robocopy $(SolutionDir)../../"..SDL_MIX.."/bin/" .. _OPTIONS["arch"] .. "/ $(TargetDir)  /XO /NJH /NP > log.txt",
		"robocopy $(SolutionDir)../../"..SDL_TTF.."/bin/" .. _OPTIONS["arch"] .. "/ $(TargetDir)  /XO /NJH /NP > log.txt",
		"robocopy $(SolutionDir)../../"..SDL_IMG.."/bin/" .. _OPTIONS["arch"] .. "/ $(TargetDir)  /XO /NJH /NP > log.txt",
		"exit 0",
	}

	links
	{
		"core.lib",
	}

	configuration "Debug"
		buildoptions { "/MDd" }
		targetname( "TFTD" .. _OPTIONS["arch"] .. "_d" )

	configuration "Release"
		buildoptions { "/MD" }
		targetname( "TFTD" .. _OPTIONS["arch"])

---------------------------------------------------------------------------

