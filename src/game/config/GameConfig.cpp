#include "pch.h"
#include "GameConfig.h"
#include <fstream>
#include "jsonxx.h"

//////////////////////////////////////////////////////////////////////////

GameConfig::GameConfig(const std::string& configFile)
: m_configFile(configFile)
, m_pathToGfx("")
, m_windowWidth(0)
, m_windowHeight(0)
, m_tiles()
, m_backgroundImage("")
, m_gameplayArea(0, 0)
, m_time(60)
, m_minSequence(3)
{

}

//////////////////////////////////////////////////////////////////////////

GameConfig::~GameConfig()
{

}

//////////////////////////////////////////////////////////////////////////

bool GameConfig::Init()
{
	bool initialized = false;

	std::ifstream is(m_configFile);
	if (is.is_open())
	{
		jsonxx::Object doc;
		doc.parse(is);

		if (doc.has<jsonxx::Object>("data"))
		{
			jsonxx::Object data = doc.get<jsonxx::Object>("data");

			// Gfx path
			m_pathToGfx = data.get<std::string>("path");

			// Window width
			m_windowWidth = static_cast<int>(data.get<jsonxx::Number>("window_width"));
			
			// Window height
			m_windowHeight = static_cast<int>(data.get<jsonxx::Number>("window_height"));
			
			// Tiles
			jsonxx::Array tileConfig = data.get<jsonxx::Array>("tiles");
			for (const auto& in : tileConfig.values())
			{
				m_tiles.push_back(in->get<std::string>());
			}

			// Tile Size
			m_tileSize = static_cast<int>(data.get<jsonxx::Number>("tileSize"));

			// Background image
			m_backgroundImage = data.get<jsonxx::Object>("background").get<std::string>("img");

			// Font name
			m_fontName = data.get<std::string>("font");

			// Font size
			//m_fontSize = static_cast<int>(data.get<jsonxx::Number>("fontSize"));

			// Dynamite path points
			jsonxx::Array dynamite = data.get<jsonxx::Array>("dynamite");
			for (const auto& in : dynamite.values())
			{
				auto val = in->get<jsonxx::Object>();
				vec2f pos;
				pos.first = static_cast<float>(val.get<jsonxx::Number>("x"));
				pos.second = static_cast<float>(val.get<jsonxx::Number>("y"));

				m_dynamitePath.push_back(pos);
			}
		}

		// Gameplay area
		if (doc.has<jsonxx::Object>("gameplay"))
		{
			jsonxx::Object ga = doc.get<jsonxx::Object>("gameplay");
			m_rows = static_cast<int>(ga.get<jsonxx::Object>("grid").get<jsonxx::Number>("rows"));
			m_columns = static_cast<int>(ga.get<jsonxx::Object>("grid").get<jsonxx::Number>("columns"));

			m_gameplayArea.first = static_cast<int>(ga.get<jsonxx::Object>("area").get<jsonxx::Number>("x"));
			m_gameplayArea.second = static_cast<int>(ga.get<jsonxx::Object>("area").get<jsonxx::Number>("y"));

			m_time = static_cast<uint>(ga.get<jsonxx::Number>("time"));
			m_minSequence = static_cast<int>(ga.get<jsonxx::Number>("minSequence"));
		}

		// Score configuration
		if (doc.has<jsonxx::Object>("score"))
		{
			jsonxx::Object score = doc.get<jsonxx::Object>("score");
			int val = static_cast<int>(score.get<jsonxx::Number>("3tiles"));
			m_scores[3] = val;
			val = static_cast<int>(score.get<jsonxx::Number>("4tiles"));
			m_scores[4] = val;
			val = static_cast<int>(score.get<jsonxx::Number>("5tiles"));
			m_scores[5] = val;
		}

		initialized = true;
		is.close();
	}

	return initialized;
}

//////////////////////////////////////////////////////////////////////////

const std::string& GameConfig::GetPath() const
{
	return m_pathToGfx;
}

//////////////////////////////////////////////////////////////////////////

int GameConfig::GetWindowWidth() const
{
	return m_windowWidth;
}

//////////////////////////////////////////////////////////////////////////

int GameConfig::GetWindowHeight() const
{
	return m_windowHeight;
}

//////////////////////////////////////////////////////////////////////////

const std::vector<std::string>& GameConfig::GetTiles() const
{
	return m_tiles;
}

//////////////////////////////////////////////////////////////////////////

const std::string& GameConfig::GetBackground() const
{
	return m_backgroundImage;
}

//////////////////////////////////////////////////////////////////////////

const std::string& GameConfig::GetFontName() const
{
	return m_fontName;
}

//////////////////////////////////////////////////////////////////////////

int GameConfig::GetFontSize() const
{
	return m_fontSize;
}

//////////////////////////////////////////////////////////////////////////

int GameConfig::GetTileSize() const
{
	return m_tileSize;
}

//////////////////////////////////////////////////////////////////////////

int GameConfig::GetNumRows() const
{
	return m_rows;
}

//////////////////////////////////////////////////////////////////////////

int GameConfig::GetNumCols() const
{
	return m_columns;
}

//////////////////////////////////////////////////////////////////////////

const vec2i& GameConfig::GetGameplayArea() const
{
	return m_gameplayArea;
}

//////////////////////////////////////////////////////////////////////////

uint GameConfig::GetGameTime() const
{
	return m_time * 1000;
}

//////////////////////////////////////////////////////////////////////////

int GameConfig::GetMinSequence() const
{
	return m_minSequence;
}

//////////////////////////////////////////////////////////////////////////

const GameConfig::ScoreMap& GameConfig::GetScoreMap() const
{
	return m_scores;
}

//////////////////////////////////////////////////////////////////////////

const std::vector<vec2f> GameConfig::GetDynamitePath() const
{
	return m_dynamitePath;
}

//////////////////////////////////////////////////////////////////////////
