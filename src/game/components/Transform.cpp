#include "pch.h"
#include "Transform.h"

namespace ecs
{
	Transform::Transform()
		: m_position(0.0f)
		, m_scale(1.0f)
		, m_rotation(glm::quat())
	{
	}

	Transform::Transform(const glm::vec3& pos)
		: m_position(pos)
		, m_scale(1.0f)
		, m_rotation(glm::quat())
	{
	}

	Transform::Transform(const glm::vec3& pos, const glm::vec3& scale)
		: m_position(pos)
		, m_scale(scale)
		, m_rotation(glm::quat())
	{
	}

	Transform::Transform(const glm::vec3& pos, const glm::vec3& scale, const glm::quat& rotation)
		: m_position(pos)
		, m_scale(scale)
		, m_rotation(rotation)
	{
	}

	const glm::vec3& Transform::GetPosition()
	{
		return m_position;
	}

	const glm::vec3& Transform::GetScale()
	{
		return m_scale;
	}

	const glm::quat& Transform::GetRotation()
	{
		return m_rotation;
	}

	void Transform::SetPosition(const glm::vec3& pos)
	{
		m_position = pos;
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_scale = scale;
	}

	void Transform::SetRotation(const glm::quat& rotation)
	{
		m_rotation *= rotation;
	}

	const glm::mat4 Transform::GetTransform()
	{
		glm::mat4 transform;
		transform = glm::translate(transform, m_position);
		transform *= glm::toMat4(m_rotation);
		transform = glm::scale(transform, m_scale);

		return transform;
	}
}