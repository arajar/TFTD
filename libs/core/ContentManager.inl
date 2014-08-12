#include "ContentManager.h"

namespace core
{
	template<class Resource>
	Resource* ContentManager::Get(const std::string& name)
	{
		if (m_resources[name] != nullptr)
		{
			return static_cast<Resource*>(m_resources[name]);
		}

		std::string path = m_pathToContent;
		path += "gfx/";
		path += name;

		Resource* res = new Resource(path);
		try
		{
			res->Load();
		}
		catch (const core::GameException& ex)
		{
			std::cout << ex.what() << std::endl;
		}

		if (res)
		{
			m_resources[name] = res;
		}

		return res;
	}
}