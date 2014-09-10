#include "core.h"
#include "Tileset.h"
#include "pugixml.hpp"

namespace editor
{
	TileSurface::TileSurface(const std::string& name)
		: imgName(name)
		, image(nullptr)
	{
		image = core::ContentManager::GetInstance()->Get<core::Image>(imgName);
	}

	Tileset::Tileset(const std::string& file)
		: m_fileName(file)
	{
	}

	Tileset::~Tileset()
	{
		for (TileSurface* surf : m_surfaces)
		{
			delete surf->image;
		}
	}

	bool Tileset::Init()
	{
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(m_fileName.c_str());

		if (result.status == pugi::status_ok)
		{
			for (pugi::xml_node surfaceNode = doc.child("resources").child("surfaces").child("surface"); surfaceNode; surfaceNode = surfaceNode.next_sibling())
			{
				auto name = surfaceNode.attribute("image").value();
				m_surfaces.push_back(new TileSurface(name));
			}

			return true;
		}

		return false;
	}

	TileSurfaceList Tileset::GetTiles() const
	{
		return m_surfaces;
	}
}