#pragma once

namespace core
{
	class Image : public IResource, public IDrawable
	{
	public:
		Image(const std::string& name, SDL_Renderer* renderer);
		virtual ~Image();

	public: // IResource interface
		virtual bool Load() override;
		virtual ResourceType GetType() override;

	public: // IDrawable interface
		virtual vec2i GetSize() override;
		virtual SDL_Texture* GetTexture() override;
		virtual void Render() override;

	private:
		const std::string m_name;

		int m_width;
		int m_height;

		SDL_Texture* m_texture;
	};
}