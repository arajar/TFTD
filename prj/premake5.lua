-------------------------------------------------------------------------------
-- 
-------------------------------------------------------------------------------

include "../tools/premake/common/"

-------------------------------------------------------------------------------

solution "TFTD"

	math.randomseed(string.hash(solution().name))
  	startproject "TFTD"
	addCommonConfig()

-------------------------------------------------------------------------------

project "TFTD"

	local SDL_LIB = "SDL2-2.0.3"
	local SDL_MIX = "SDL2_mixer-2.0.0"
	local SDL_TTF = "SDL2_ttf-2.0.12"
	local SDL_IMG = "SDL2_image-2.0.0"

	uuid "BDF8292E-B782-41BC-966F-8F8DEF9F9D87"
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
		"../libs/"..SDL_LIB.."/include",
		"../libs/"..SDL_MIX.."/include",
		"../libs/"..SDL_TTF.."/include",
		"../libs/"..SDL_IMG.."/include",
	}

	libdirs 
	{ 
		"../libs/"..SDL_LIB.."/lib/" .. _OPTIONS["arch"],
		"../libs/"..SDL_MIX.."/lib/" .. _OPTIONS["arch"],
		"../libs/"..SDL_TTF.."/lib/" .. _OPTIONS["arch"],
		"../libs/"..SDL_IMG.."/lib/" .. _OPTIONS["arch"],
	}

	-- Copy the needed dlls to the output dir
	postbuildcommands
	{
		"echo Copying dlls...",
		"robocopy $(SolutionDir)../../../libs/"..SDL_LIB.."/bin/" .. _OPTIONS["arch"] .. "/ $(TargetDir)  /XO /NJH /NP > log.txt",
		"robocopy $(SolutionDir)../../../libs/"..SDL_MIX.."/bin/" .. _OPTIONS["arch"] .. "/ $(TargetDir)  /XO /NJH /NP > log.txt",
		"robocopy $(SolutionDir)../../../libs/"..SDL_TTF.."/bin/" .. _OPTIONS["arch"] .. "/ $(TargetDir)  /XO /NJH /NP > log.txt",
		"robocopy $(SolutionDir)../../../libs/"..SDL_IMG.."/bin/" .. _OPTIONS["arch"] .. "/ $(TargetDir)  /XO /NJH /NP > log.txt",
		"exit 0",
	}

	links
	{
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2test.lib",
		"SDL2_image.lib",
		"SDL2_mixer.lib",
		"SDL2_ttf.lib",
	}

	configuration "Debug"
		buildoptions { "/MDd" }
		targetname( "TFTD" .. _OPTIONS["arch"] .. "_d" )

	configuration "Release"
		buildoptions { "/MD" }
		targetname( "TFTD" .. _OPTIONS["arch"])

---------------------------------------------------------------------------

