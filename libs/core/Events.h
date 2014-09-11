#pragma once

namespace core
{
	struct WindowEvent
	{
		explicit WindowEvent(sf::RenderWindow* window, sf::View& gameView, sf::RenderTarget& target)
			: window(window)
			, gameView(gameView)
			, target(target)
		{}

		sf::Event event;
		sf::RenderWindow* window;
		sf::View& gameView;
		sf::RenderTarget& target;
	};
}