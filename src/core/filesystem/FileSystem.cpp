#include "pch.h"
#include "FileSystem.h"
#include "tinydir.h"

namespace core
{
	namespace fs
	{
		FileSystem::FileSystem(const std::string& dataFolder)
			: m_dataFolder(dataFolder)
		{

		}

		FileSystem::~FileSystem()
		{

		}

		bool FileSystem::Init()
		{
			return ReadDir(m_dataFolder);
		}

		bool FileSystem::ReadDir(const std::string& dir)
		{
			tinydir_dir d;
			tinydir_open(&d, dir.c_str());

			while (d.has_next)
			{
				tinydir_file file;
				tinydir_readfile(&d, &file);

				if (file.is_dir && strcmp(file.name, ".") && strcmp(file.name, ".."))
				{
					ReadDir(file.path);
				}
				else
				{
					(*this)[file.name] = file.path;
				}

				tinydir_next(&d);
			}

			tinydir_close(&d);

			return true;
		}

	}
}