#pragma once

#include "resources\IResource.h"

class Image;
class Font;

namespace core
{
	class ContentManager : public Singleton<ContentManager>
	{
	public:
		ContentManager(SDL_Renderer* renderer, const std::string& pathToContent);
		virtual ~ContentManager();

	public:
		template<class Resource>
		Resource* Get(const std::string& name);

		void Unload();

	public:
		SDL_Renderer* GetRenderer() const;

	private:
		SDL_Renderer* m_renderer;
		const std::string m_pathToContent;

		std::map<std::string, IResource*> m_resources;
	};
}

// Template functions implementations
#include "ContentManager.inl"
