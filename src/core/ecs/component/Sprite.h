#pragma once

#include "Component.h"

namespace core
{
	class Image;

	class Sprite : public ecs::Component
	{
	public:
		static std::string Type;

	public:
		Sprite(Image* image);
		virtual ~Sprite();

	public:
		virtual void OnTick(Uint32 deltaTime) {};

	private:
		Image* m_image;
	};
}
