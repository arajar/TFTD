#include "pch.h"
#include "Skeleton2D.h"

namespace ecs
{
	Skeleton2D::Skeleton2D()
		: m_skeleton(nullptr)
		, m_name("")
	{

	}

	Skeleton2D::~Skeleton2D()
	{
		if (m_skeleton)
		{
			delete m_skeleton;
		}
	}

	bool Skeleton2D::Init(const std::string& name, const std::string& atlasName, const std::string& jsonName)
	{
		spAtlas* atlas = spAtlas_createFromFile(atlasName.c_str(), nullptr);
		spSkeletonJson* json = spSkeletonJson_create(atlas);
		spSkeletonData* skeletonData = spSkeletonJson_readSkeletonDataFile(json, jsonName.c_str());

		if (!skeletonData)
		{
			throw new core::GameException("Skeleton data not found");
		}

		spSkeletonJson_dispose(json);

		m_skeleton = new spine::SkeletonDrawable(skeletonData);
		m_skeleton->timeScale = 1;

		spSkeleton* skeleton = m_skeleton->skeleton;
		skeleton->flipX = false;
		skeleton->flipY = false;

		spSkeleton_setSkinByName(skeleton, name.c_str());
		spSkeleton_setSlotsToSetupPose(skeleton);

		spSkeleton_updateWorldTransform(skeleton);

		return true;
	}

	void Skeleton2D::SetSkin(const std::string& name)
	{
		spSkeleton_setSkinByName(m_skeleton->skeleton, name.c_str());
	}

	void Skeleton2D::SetAnimation(const std::string& animName)
	{
		spAnimationState_setAnimationByName(m_skeleton->state, 0, animName.c_str(), true);
	}

	spSlot* Skeleton2D::GetSlot(const std::string& slot)
	{
		return spSkeleton_findSlot(m_skeleton->skeleton, slot.c_str());
	}

	bool Skeleton2D::Attach(const std::string& slotName, const std::string& object)
	{
		return spSkeleton_setAttachment(m_skeleton->skeleton, slotName.c_str(), object.c_str()) == 0 ? false : true;
	}

	void Skeleton2D::Dettach(std::string const& slotName)
	{
		spSlot* slot = GetSlot(slotName.c_str());
		spSlot_setAttachment(slot, nullptr);
	}

	void Skeleton2D::Scale(const sf::Vector2f& scale)
	{
		m_skeleton->skeleton->root->scaleX = scale.x;
		m_skeleton->skeleton->root->scaleY = scale.y;
		spSkeleton_updateWorldTransform(m_skeleton->skeleton);
	}

	void Skeleton2D::Update(sf::Time deltaTime)
	{
		m_skeleton->Update(deltaTime);
	}

	void Skeleton2D::Render(sf::RenderTarget& tex)
	{
		tex.draw(*m_skeleton);
	}

	void Skeleton2D::RenderDebug(sf::RenderTarget& tex)
	{
		m_skeleton->drawDebug(tex);
	}

	void Skeleton2D::SetPosition(const glm::vec3& pos)
	{
		m_skeleton->skeleton->x = pos.x;
		m_skeleton->skeleton->y = pos.y;
	}
}