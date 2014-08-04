#include "pch.h"
#include "FileSystem.h"
#include "tinydir.h"

namespace core
{
	FileSystem::FileSystem(const std::string& folder)
	{
		m_folders.push_back(folder);
	}

	bool FileSystem::Init()
	{
		if (!m_folders.empty())
		{
			Refresh();
			return true;
		}

		return false;
	}

	void FileSystem::Refresh()
	{
		clear();

		for (const auto& folder : m_folders)
		{
			ReadFolder(folder);
		}
	}

	bool FileSystem::AddFolder(const std::string& folder)
	{
		auto found = std::find(m_folders.begin(), m_folders.end(), folder);
		if (found != m_folders.end())
		{
			m_folders.push_back(folder);
			return true;
		}

		return false;
	}

	bool FileSystem::RemoveFolder(const std::string& folder)
	{
		auto found = std::find(m_folders.begin(), m_folders.end(), folder);
		if (found != m_folders.end())
		{
			m_folders.erase(found);
			Refresh();
			return true;
		}

		return false;
	}

	void FileSystem::ReadFolder(const std::string& dir)
	{
		tinydir_dir d;
		tinydir_open(&d, dir.c_str());

		while (d.has_next)
		{
			tinydir_file file;
			tinydir_readfile(&d, &file);

			if (file.is_dir && strcmp(file.name, ".") && strcmp(file.name, ".."))
			{
				ReadFolder(file.path);
			}
			else
			{
				if (strcmp(file.name, ".") && strcmp(file.name, ".."))
				{
					(*this)[file.name] = file.path;
				}
			}

			tinydir_next(&d);
		}

		tinydir_close(&d);
	}
}