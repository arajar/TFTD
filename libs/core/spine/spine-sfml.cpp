#include "core.h"

#include <spine/spine-sfml.h>
#include <spine/extension.h>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#ifndef SPINE_MESH_VERTEX_COUNT_MAX
#define SPINE_MESH_VERTEX_COUNT_MAX 1000
#endif

void _spAtlasPage_createTexture(spAtlasPage* self, const char* path)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(path)) return;
	texture->setSmooth(true);
	self->rendererObject = texture;
	sf::Vector2u size = texture->getSize();
	self->width = size.x;
	self->height = size.y;
}

void _spAtlasPage_disposeTexture(spAtlasPage* self)
{
	delete static_cast<sf::Texture*>(self->rendererObject);
}

char* _spUtil_readFile(const char* path, int* length)
{
	return _readFile(path, length);
}

namespace spine
{
	SkeletonDrawable::SkeletonDrawable(spSkeletonData* skeletonData, spAnimationStateData* stateData)
		: timeScale(1)
		, vertexArray(new sf::VertexArray(sf::Triangles, skeletonData->bonesCount * 4))
		, worldVertices(0)
	{
		spBone_setYDown(true);
		worldVertices = MALLOC(float, SPINE_MESH_VERTEX_COUNT_MAX);
		skeleton = spSkeleton_create(skeletonData);

		ownsAnimationStateData = stateData == 0;
		if (ownsAnimationStateData)
		{
			stateData = spAnimationStateData_create(skeletonData);
		}

		state = spAnimationState_create(stateData);

		m_debugText.setFont(core::Engine::DEBUG_FONT);
		m_debugText.setCharacterSize(13);
	}

	SkeletonDrawable::~SkeletonDrawable()
	{
		delete vertexArray;
		FREE(worldVertices);
		spAnimationState_dispose(state);
		if (ownsAnimationStateData)
		{
			spAnimationStateData_dispose(state->data);
		}

		spSkeleton_dispose(skeleton);
	}

	void SkeletonDrawable::Update(sf::Time deltaTime)
	{
		spSkeleton_update(skeleton, deltaTime.asSeconds());
		spAnimationState_update(state, deltaTime.asSeconds() * timeScale);
		spAnimationState_apply(state, skeleton);
		spSkeleton_updateWorldTransform(skeleton);
	}

	void SkeletonDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		vertexArray->clear();
		states.blendMode = sf::BlendAlpha;

		sf::Vertex vertices[4];
		sf::Vertex vertex;
		for (int i = 0; i < skeleton->slotsCount; ++i)
		{
			spSlot* slot = skeleton->drawOrder[i];
			spAttachment* attachment = slot->attachment;
			if (!attachment)
			{
				continue;
			}

			sf::Texture* texture = 0;
			if (attachment->type == SP_ATTACHMENT_REGION)
			{
				spRegionAttachment* regionAttachment = reinterpret_cast<spRegionAttachment*>(attachment);
				texture = static_cast<sf::Texture*>(static_cast<spAtlasRegion*>(regionAttachment->rendererObject)->page->rendererObject);
				spRegionAttachment_computeWorldVertices(regionAttachment, slot->bone, worldVertices);

				sf::Uint8 r = static_cast<sf::Uint8>(skeleton->r * slot->r * 255);
				sf::Uint8 g = static_cast<sf::Uint8>(skeleton->g * slot->g * 255);
				sf::Uint8 b = static_cast<sf::Uint8>(skeleton->b * slot->b * 255);
				sf::Uint8 a = static_cast<sf::Uint8>(skeleton->a * slot->a * 255);

				sf::Vector2u size = texture->getSize();
				vertices[0].color.r = r;
				vertices[0].color.g = g;
				vertices[0].color.b = b;
				vertices[0].color.a = a;
				vertices[0].position.x = worldVertices[SP_VERTEX_X1];
				vertices[0].position.y = worldVertices[SP_VERTEX_Y1];
				vertices[0].texCoords.x = regionAttachment->uvs[SP_VERTEX_X1] * size.x;
				vertices[0].texCoords.y = regionAttachment->uvs[SP_VERTEX_Y1] * size.y;

				vertices[1].color.r = r;
				vertices[1].color.g = g;
				vertices[1].color.b = b;
				vertices[1].color.a = a;
				vertices[1].position.x = worldVertices[SP_VERTEX_X2];
				vertices[1].position.y = worldVertices[SP_VERTEX_Y2];
				vertices[1].texCoords.x = regionAttachment->uvs[SP_VERTEX_X2] * size.x;
				vertices[1].texCoords.y = regionAttachment->uvs[SP_VERTEX_Y2] * size.y;

				vertices[2].color.r = r;
				vertices[2].color.g = g;
				vertices[2].color.b = b;
				vertices[2].color.a = a;
				vertices[2].position.x = worldVertices[SP_VERTEX_X3];
				vertices[2].position.y = worldVertices[SP_VERTEX_Y3];
				vertices[2].texCoords.x = regionAttachment->uvs[SP_VERTEX_X3] * size.x;
				vertices[2].texCoords.y = regionAttachment->uvs[SP_VERTEX_Y3] * size.y;

				vertices[3].color.r = r;
				vertices[3].color.g = g;
				vertices[3].color.b = b;
				vertices[3].color.a = a;
				vertices[3].position.x = worldVertices[SP_VERTEX_X4];
				vertices[3].position.y = worldVertices[SP_VERTEX_Y4];
				vertices[3].texCoords.x = regionAttachment->uvs[SP_VERTEX_X4] * size.x;
				vertices[3].texCoords.y = regionAttachment->uvs[SP_VERTEX_Y4] * size.y;

				vertexArray->append(vertices[0]);
				vertexArray->append(vertices[1]);
				vertexArray->append(vertices[2]);
				vertexArray->append(vertices[0]);
				vertexArray->append(vertices[2]);
				vertexArray->append(vertices[3]);

			}
			else if (attachment->type == SP_ATTACHMENT_MESH)
			{
				spMeshAttachment* mesh = reinterpret_cast<spMeshAttachment*>(attachment);
				if (mesh->verticesCount > SPINE_MESH_VERTEX_COUNT_MAX)
				{
					continue;
				}

				texture = static_cast<sf::Texture*>(static_cast<spAtlasRegion*>(mesh->rendererObject)->page->rendererObject);
				spMeshAttachment_computeWorldVertices(mesh, slot, worldVertices);

				sf::Uint8 r = static_cast<sf::Uint8>(skeleton->r * slot->r * 255);
				sf::Uint8 g = static_cast<sf::Uint8>(skeleton->g * slot->g * 255);
				sf::Uint8 b = static_cast<sf::Uint8>(skeleton->b * slot->b * 255);
				sf::Uint8 a = static_cast<sf::Uint8>(skeleton->a * slot->a * 255);
				vertex.color.r = r;
				vertex.color.g = g;
				vertex.color.b = b;
				vertex.color.a = a;

				sf::Vector2u size = texture->getSize();
				for (int i = 0; i < mesh->trianglesCount; ++i)
				{
					int index = mesh->triangles[i] << 1;
					vertex.position.x = worldVertices[index];
					vertex.position.y = worldVertices[index + 1];
					vertex.texCoords.x = mesh->uvs[index] * size.x;
					vertex.texCoords.y = mesh->uvs[index + 1] * size.y;
					vertexArray->append(vertex);
				}

			}
			else if (attachment->type == SP_ATTACHMENT_SKINNED_MESH)
			{
				spSkinnedMeshAttachment* mesh = reinterpret_cast<spSkinnedMeshAttachment*>(attachment);
				if (mesh->uvsCount > SPINE_MESH_VERTEX_COUNT_MAX)
				{
					continue;
				}

				texture = static_cast<sf::Texture*>(static_cast<spAtlasRegion*>(mesh->rendererObject)->page->rendererObject);
				spSkinnedMeshAttachment_computeWorldVertices(mesh, slot, worldVertices);

				sf::Uint8 r = static_cast<sf::Uint8>(skeleton->r * slot->r * 255);
				sf::Uint8 g = static_cast<sf::Uint8>(skeleton->g * slot->g * 255);
				sf::Uint8 b = static_cast<sf::Uint8>(skeleton->b * slot->b * 255);
				sf::Uint8 a = static_cast<sf::Uint8>(skeleton->a * slot->a * 255);
				vertex.color.r = r;
				vertex.color.g = g;
				vertex.color.b = b;
				vertex.color.a = a;

				sf::Vector2u size = texture->getSize();
				for (int i = 0; i < mesh->trianglesCount; ++i)
				{
					int index = mesh->triangles[i] << 1;
					vertex.position.x = worldVertices[index];
					vertex.position.y = worldVertices[index + 1];
					vertex.texCoords.x = mesh->uvs[index] * size.x;
					vertex.texCoords.y = mesh->uvs[index + 1] * size.y;
					vertexArray->append(vertex);
				}
			}

			if (texture)
			{
				// SMFL doesn't handle batching for us, so we'll just force a single texture per skeleton.
				states.texture = texture;

				sf::BlendMode blend = slot->data->additiveBlending ? sf::BlendAdd : sf::BlendAlpha;
				if (states.blendMode != blend)
				{
					target.draw(*vertexArray, states);
					vertexArray->clear();
					states.blendMode = blend;
				}
			}
		}

		target.draw(*vertexArray, states);
	}

	void SkeletonDrawable::drawDebug(sf::RenderTarget& target)
	{
		sf::VertexArray lines(sf::LinesStrip, skeleton->slotsCount);

		for (int i = 0; i < skeleton->slotsCount; ++i)
		{
			spSlot* slot = skeleton->drawOrder[i];
			m_debugText.setString(slot->bone->data->name);
			m_debugText.setPosition(sf::Vector2f(slot->bone->worldX + skeleton->x, slot->bone->worldY + skeleton->y));
			target.draw(m_debugText);

			lines[i].position = sf::Vector2f(slot->bone->worldX + skeleton->x, slot->bone->worldY + skeleton->y);
		}

		target.draw(lines);
	}
}
