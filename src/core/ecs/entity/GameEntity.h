#pragma once

#include "Entity.h"

namespace core
{
	class Transform;

	class GameEntity : public ecs::Entity
	{
	public:
		GameEntity(const std::string& name);
		virtual ~GameEntity();

	public:
		virtual void Init() override;
		virtual void Update(Uint32 deltaTime) override;

	public:
		void SetPosition(const glm::vec3& pos);
		void SetScale(const glm::vec3& scale);
		void SetRotation(const glm::quat& rotation);

		const glm::vec3 GetPosition();
		const glm::vec3 GetScale();
		const glm::quat GetRotation();

	protected:
		Transform* m_transform;
	};
}