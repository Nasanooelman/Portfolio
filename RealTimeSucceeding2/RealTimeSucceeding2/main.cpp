#include "GameState.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Real Time Succeeding!");
	sf::View view2(sf::Vector2f(1000, 1000), sf::Vector2f(1000, 1000));
	sf::CircleShape shape(100.f);

	shape.setFillColor(sf::Color::Green);

	GameState* testLevel = new GameState;
	
	sf::Clock FPSclock;
	FPSclock.restart();
	int time = 0;


	while (window.isOpen())
	{
		
		//window.setView(view2);
		time++;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		testLevel->updateState(&window);
		if (FPSclock.getElapsedTime() >= sf::seconds(1))
		{
			if (time > 500)
			{
				std::cout << "The current FPS is " <<std::to_string(time) << std::endl;
				time = 0;
				FPSclock.restart();
				
			}
		}
	}

	delete testLevel;
	DRAW.DeleteThis();
	MAP.DeleteThis();
	return 0;

	
}