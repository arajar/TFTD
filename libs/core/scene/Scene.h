#pragma once

namespace core
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

	public:
		void Render();
		void Update(Uint32 deltaTime);

	public:
		bool Add(IRenderable* renderable);
		bool Remove(IRenderable* renderable);

	private:
		void SortByLayer();

	private:
		std::vector<IRenderable*> m_renderables;

		bool m_isDirty;
	};
}