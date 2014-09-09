#pragma once

#include "resources\IResource.h"
#include "filesystem\FileSystem.h"

namespace core
{
	class Image;

	class ContentManager : public Singleton<ContentManager>
	{
	public:
		explicit ContentManager(FileSystem& fs);
		virtual ~ContentManager();

	public:
		template<class Resource>
		Resource* Get(const std::string& name);
		
		template<>
		Image* Get(const std::string& name);

		void Unload();

	protected:
		std::map<std::string, IResource*> m_resources;

	private:
		FileSystem& m_fs;
	};
}

// Template functions implementations
#include "ContentManager.inl"
