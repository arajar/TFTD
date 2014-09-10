#pragma once

namespace editor
{
	struct TileSurface
	{
		explicit TileSurface(const std::string& name);
		std::string imgName;
		core::Image* image;

		ID(TileSurface);
	};

	typedef std::vector<TileSurface*> TileSurfaceList;

	class Tileset
	{
	public:
		explicit Tileset(const std::string& file);
		virtual ~Tileset();

	public:
		bool Init();

	public:
		TileSurfaceList GetTiles() const;

	protected:
		const std::string m_fileName;
		TileSurfaceList m_surfaces;
	};
}