#pragma once

namespace core
{
	namespace fs
	{
		class FileSystem : std::map<std::string, std::string>
		{
		public:
			FileSystem(const std::string& dataFolder);
			~FileSystem();

			FileSystem(const FileSystem& fs) = delete;

		public:
			bool Init();

		private:
			bool ReadDir(const std::string& dir);

		private:
			const std::string m_dataFolder;
		};
	}
}