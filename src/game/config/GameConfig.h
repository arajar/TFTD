#pragma once

//////////////////////////////////////////////////////////////////////////

struct ConfigData
{
	std::string m_data;

	operator int() const
	{
		return this->AsInt();
	}

	operator float() const
	{
		return this->AsFloat();
	}

	operator bool() const
	{
		return this->AsBool();
	}

	operator void() const
	{}

	operator std::string() const
	{
		return m_data;
	}

	int AsInt() const
	{
		return m_data.empty() ? -1 : std::stoi(m_data);
	}

	float AsFloat() const
	{
		return m_data.empty() ? -1.f : std::stof(m_data);
	}

	bool AsBool() const
	{
		return m_data == "true" ? true : false;
	}

	ConfigData()
		: m_data("") {}

	ConfigData(const std::string& data)
		: m_data(data) {}

	ConfigData(const char* data)
		: m_data(data) {}

	ConfigData(int data)
		: m_data(std::to_string(data)) {}

	ConfigData(float data)
		: m_data(std::to_string(data)) {}

	ConfigData(bool data)
	{
		if (data)
		{
			m_data = "true";
		}
		else
		{
			m_data = "false";
		}
	}
};

//////////////////////////////////////////////////////////////////////////

class GameConfig : public std::map < std::string, ConfigData >
{
public:
	GameConfig(std::string configFile);
	virtual ~GameConfig();

public:
	bool Init();
	bool Save();

protected:
	bool Serialize();
	bool Deserialize();

protected:
	const std::string m_configFile;

};

//////////////////////////////////////////////////////////////////////////

