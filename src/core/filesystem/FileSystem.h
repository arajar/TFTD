#pragma once

namespace core
{
	class FileSystem : public std::map < std::string, std::string >
	{
	public:
		FileSystem(const std::string& folder);
		virtual ~FileSystem() {};

		FileSystem(const FileSystem& fs) = delete;

	public:
		bool Init();
		void Refresh();
		bool AddFolder(const std::string& folder);
		bool RemoveFolder(const std::string& folder);

	private:
		void ReadFolder(const std::string& dir);

	private:
		std::vector<std::string> m_folders;
	};
}