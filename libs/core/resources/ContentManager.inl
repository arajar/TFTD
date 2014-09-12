#include "ContentManager.h"
#include "resources\Image.h"

namespace core
{
	template<class Resource>
	Resource* ContentManager::Get(const std::string& name)
	{
		if (m_resources[name] != nullptr)
		{
			return static_cast<Resource*>(m_resources[name]);
		}

		std::string path = m_fs[name];

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