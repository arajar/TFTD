#include "core.h"
#include "Scene.h"

namespace core
{
	Scene::Scene()
		: m_isDirty(false)
	{

	}

	Scene::~Scene()
	{
		m_renderables.clear();
	}

	void Scene::Render()
	{
		for (auto renderable : m_renderables)
		{
			//renderable->Render();
		}
	}

	void Scene::Update(sf::Time deltaTime)
	{
		if (m_isDirty)
		{
			SortByLayer();
		}
	}

	bool Scene::Add(IRenderable* renderable)
	{
		auto found = std::find(m_renderables.begin(), m_renderables.end(), renderable);
		if (found == m_renderables.end())
		{
			m_renderables.push_back(renderable);
			m_isDirty = true;
		}

		return m_isDirty;
	}

	bool Scene::Remove(IRenderable* renderable)
	{
		auto found = std::find(m_renderables.begin(), m_renderables.end(), renderable);
		if (found != m_renderables.end())
		{
			m_renderables.erase(found);
			m_isDirty = true;
		}
	
		return m_isDirty;
	}

	void Scene::SortByLayer()
	{
		auto sort = [](const IRenderable* r1, const IRenderable* r2)
		{
			return r1->GetLayer() > r2->GetLayer();
		};

		std::sort(m_renderables.begin(), m_renderables.end(), sort);

		m_isDirty = false;
	}
}