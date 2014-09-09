
#pragma once

#include <spine/spine.h>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>

namespace spine
{
	class SkeletonDrawable : public sf::Drawable
	{
	public:
		spSkeleton* skeleton;
		spAnimationState* state;
		float timeScale;
		sf::VertexArray* vertexArray;

		explicit SkeletonDrawable(spSkeletonData* skeleton, spAnimationStateData* stateData = 0);
		~SkeletonDrawable();

	public:
		void Update(sf::Time deltaTime);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void drawDebug(sf::RenderTarget& target);

	private:
		bool ownsAnimationStateData;
		float* worldVertices;

		sf::Text m_debugText;
	};

}

