#include "pch.h"
#include "game\Game.h"

int main(int argc, char* argv[])
{
	Game g("Tesseract");
	if (g.Init())
	{
		g.Run();
	}
	return 0;
}