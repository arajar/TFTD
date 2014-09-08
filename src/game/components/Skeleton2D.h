#pragma once

#include "components/Renderable.h"
#include "components/Updatable.h"
#include "spine/spine-sfml.h"

namespace ecs
{
	class Skeleton2D : public ecs::Renderable
	{
	public:
		Skeleton2D();
		virtual ~Skeleton2D();

	public:
		bool Init(const std::string& name, const std::string& atlasName, const std::string& jsonName);
		void SetSkin(const std::string& name);
		void SetAnimation(const std::string& animName);
		spSlot* GetSlot(const std::string& slot);
		bool Attach(const std::string& slotName, const std::string& object);
		void Scale(const sf::Vector2f& scale);

	public:
		virtual void Update(sf::Time deltaTime);

		virtual void Render(sf::RenderTarget& tex) override;
		virtual void RenderDebug(sf::RenderTarget& tex) override;
		virtual void SetPosition(const glm::vec3& pos) override;

	public:
		void SetCallback(std::function<void(spAnimationState* state, int trackIndex, spEventType type, spEvent* event, int loopCount)> callback);

	protected:
		spine::SkeletonDrawable* m_skeleton;
		const std::string m_name;

	private:
		std::function<void(spAnimationState* state, int trackIndex, spEventType type, spEvent* event, int loopCount)> m_callback;

	};
}