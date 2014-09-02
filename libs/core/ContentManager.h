#pragma once

#include "resources\IResource.h"
#include "filesystem\FileSystem.h"

namespace core
{
	class Image;

	class ContentManager : public Singleton<ContentManager>
	{
	public:
		ContentManager(SDL_Renderer* renderer, FileSystem& fs);
		virtual ~ContentManager();

	public:
		template<class Resource>
		Resource* Get(const std::string& name);
		
		template<>
		Image* Get(const std::string& name);

		void Unload();

	public:
		SDL_Renderer* GetRenderer() const;

	private:
		SDL_Renderer* m_renderer;

		std::map<std::string, IResource*> m_resources;

	private:
		FileSystem& m_fs;
	};
}

// Template functions implementations
#include "ContentManager.inl"
