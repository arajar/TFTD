#pragma once

//////////////////////////////////////////////////////////////////////////

class GameConfig
{
public:
	typedef std::map<int, int> ScoreMap;

public:
	GameConfig(const std::string& configFile);
	virtual ~GameConfig();

public:
	bool Init();

public:
	const std::string& GetPath() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	const std::vector<std::string>& GetTiles() const;
	const std::string& GetBackground() const;

	const std::string& GetFontName() const;
	int GetFontSize() const;

	int GetTileSize() const;
	int GetNumRows() const;
	int GetNumCols() const;
	const vec2i& GetGameplayArea() const;
	uint GetGameTime() const;
	int GetMinSequence() const;

	const ScoreMap& GetScoreMap() const;
	const std::vector<vec2f> GetDynamitePath() const;

private:
	const std::string m_configFile;

	std::string m_pathToGfx;

	int m_windowWidth;
	int m_windowHeight;

	std::string m_fontName;
	int m_fontSize;
	std::vector<std::string> m_tiles;
	std::string m_backgroundImage;

	int m_tileSize;
	int m_columns;
	int m_rows;
	vec2i m_gameplayArea;
	uint m_time;
	int m_minSequence;
	ScoreMap m_scores;
	
	std::vector<vec2f> m_dynamitePath;
};

//////////////////////////////////////////////////////////////////////////

