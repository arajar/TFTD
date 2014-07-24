#pragma once

namespace core
{
	class Image : public IResource, public IRenderable
	{
	public:
		Image(const std::string& name, SDL_Renderer* renderer);
		virtual ~Image();

	public: // IResource interface
		virtual bool Load() override;
		virtual ResourceType GetType() override;

	private:
		const std::string m_name;

	};
}