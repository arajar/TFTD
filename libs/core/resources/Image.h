#pragma once

namespace core
{
	class Image : public IResource, public IRenderable
	{
	public:
		explicit Image(const std::string& name);
		virtual ~Image();

	public: // IResource interface
		virtual bool Load() override;
		virtual ResourceType GetType() override;

	public: // IRenderable interface
		virtual void Render(sf::RenderTarget& target) override;

	public: // ITransform interface
		virtual void SetPosition(const glm::vec3& position) override;

	private:
		const std::string m_name;
		sf::Sprite m_sprite;
		sf::Texture m_tex;
	};
}