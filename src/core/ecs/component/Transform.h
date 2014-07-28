#pragma once

#include "IComponent.h"

namespace core
{
	class Transform : public ecs::Component
	{
	public:
		Transform();
		Transform(const glm::vec3& pos);
		Transform(const glm::vec3& pos, const glm::vec3& scale);
		Transform(const glm::vec3& pos, const glm::vec3& scale, const glm::quat& rotation);

	public:
		virtual void Update(Uint32 deltaTime) override {};

	public:
		const glm::vec3& GetPosition();
		const glm::vec3& GetScale();
		const glm::quat& GetRotation();

		void SetPosition(const glm::vec3& pos);
		void SetScale(const glm::vec3& scale);
		void SetRotation(const glm::quat& rotation);

	private:
		const glm::mat4 GetTransform();

	private:
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::quat m_rotation;
	};

}