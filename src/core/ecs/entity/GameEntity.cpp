#include "pch.h"
#include "GameEntity.h"

#include "Transform.h"

namespace core
{
	GameEntity::GameEntity(const std::string& name)
		: Entity(name)
		, m_transform(nullptr)
	{
	}

	GameEntity::~GameEntity()
	{
	}

	void GameEntity::Init()
	{
		this->AddComponent<Transform>();

		// Cache the transform
		m_transform = GetComponent<Transform>();
	}

	void GameEntity::Update(Uint32 deltaTime)
	{
		Entity::Update(deltaTime);
	}

	void GameEntity::SetPosition(const glm::vec3& pos)
	{
		m_transform->SetPosition(pos);
	}

	void GameEntity::SetScale(const glm::vec3& scale)
	{
		m_transform->SetScale(scale);
	}

	void GameEntity::SetRotation(const glm::quat& rotation)
	{
		m_transform->SetRotation(rotation);
	}

	const glm::vec3 GameEntity::GetPosition()
	{
		return m_transform->GetPosition();
	}

	const glm::vec3 GameEntity::GetScale()
	{
		return m_transform->GetScale();
	}

	const glm::quat GameEntity::GetRotation()
	{
		return m_transform->GetRotation();
	}
}