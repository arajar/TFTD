#pragma once

namespace core
{
	struct WindowEvent
	{
		explicit WindowEvent(sf::RenderWindow* window)
		{
			this->window = window;
		}

		sf::Event event;
		sf::RenderWindow* window;
	};
}