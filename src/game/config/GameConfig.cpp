#include "pch.h"
#include "GameConfig.h"

//////////////////////////////////////////////////////////////////////////

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

//////////////////////////////////////////////////////////////////////////

std::vector<std::string> split(const std::string &s, char delim) 
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

//////////////////////////////////////////////////////////////////////////

GameConfig::GameConfig(std::string configFile)
	: std::map<std::string, ConfigData>()
	, m_configFile(configFile)
{
}

//////////////////////////////////////////////////////////////////////////

GameConfig::~GameConfig()
{
}

//////////////////////////////////////////////////////////////////////////

bool GameConfig::Init()
{
	clear();
	return Deserialize();
}

//////////////////////////////////////////////////////////////////////////

bool GameConfig::Save()
{
	return Serialize();
}

//////////////////////////////////////////////////////////////////////////

bool GameConfig::Serialize()
{
	std::ofstream file(m_configFile);
	if (file.is_open())
	{
		file.clear();
		std::string line = "";

		std::string temp = "";
		std::string sect = "";

		for (auto& it : *this)
		{
			auto splitted = split(it.first, '.');
			std::string key = it.first;
			if (splitted.size() == 2)
			{
				sect = splitted[0];
				key = splitted[1];
			}

			if (temp != sect)
			{
				file << "[" << sect << "]\n";
				temp = sect;
			}

			line = key;
			line += "=";
			line += it.second;
			line += "\n";

			file << line;
		}

		file.close();
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////

bool GameConfig::Deserialize()
{
	std::ifstream file(m_configFile);
	if (file.is_open())
	{
		std::string section = "";

		while (!file.eof())
		{
			std::string line = "";
			std::getline(file, line);

			if (line[0] == ';')
			{
				continue;
			}

			if (line[0] == '[')
			{
				section = line;
				section = section.substr(1, section.size() - 2);
				continue;
			}

			auto splitted = split(line, '=');
			if (splitted.size() == 2)
			{
				std::string key = splitted[0];
				if (!section.empty())
				{
					key = section + "." + key;
				}

				(*this)[key] = splitted[1];
			}
		}

		file.close();
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
