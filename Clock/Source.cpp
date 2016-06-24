////////////////////////////////////////////////////////////
// Headers:
// ctime for getting system time and
// cmath for sin and cos functions
////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////

const int screenWidth = 800;
const int screenHeight = 600;
const float PI = 3.1415927f;
const int clockCircleSize = 250;
const int clockCircleThickness = 2;
int x, y;
float angle = 0.0;

void createDots(sf::CircleShape * dot, sf::Vector2f windowCenter)
{
	for (int i = 0; i<60; i++)
	{
		x = float((clockCircleSize - 10) * cos(angle));
		y = float((clockCircleSize - 10) * sin(angle));
		if (i % 5 == 0)
			dot[i] = sf::CircleShape(3);
		else
			dot[i] = sf::CircleShape(1);
		dot[i].setFillColor(sf::Color::Black);
		dot[i].setOrigin(dot[i].getGlobalBounds().width / 2, dot[i].getGlobalBounds().height / 2);
		dot[i].setPosition(x + windowCenter.x, y + windowCenter.y);
		angle = angle + ((2 * PI) / 60);
	}
}

void setStrelki(sf::RectangleShape * strel, sf::Vector2f center)
{
	for (int i=0;i<3;i++)
	{
		strel[i].setFillColor(sf::Color::Black);
		strel[i].setOrigin(strel[i].getGlobalBounds().width / 2, strel[i].getGlobalBounds().height - 25);
		strel[i].setPosition(center);
	}
}



int main()
{
	// Set multisampling level
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Analog Clock", sf::Style::Close, settings);
	float windowX = window.getSize().x;
	float windowY = window.getSize().y;
	// Define windowCenter which gets the center of the window here, right after creating window
	sf::Vector2f windowCenter = sf::Vector2f(windowX / 2.0f, windowY / 2.0f);
	// Create a list for clock's dots
	sf::CircleShape dot[60];
	createDots(dot,windowCenter);
	// Create outline of the clock
	sf::CircleShape clockCircle(clockCircleSize);

	clockCircle.setPointCount(100);
	clockCircle.setOutlineThickness(clockCircleThickness);
	clockCircle.setOutlineColor(sf::Color::Black);
	clockCircle.setOrigin(clockCircle.getGlobalBounds().width / 2, clockCircle.getGlobalBounds().height / 2);
	clockCircle.setPosition(windowX / 2 + clockCircleThickness, windowY / 2 + clockCircleThickness);

	// Crate another circle for center
	sf::CircleShape centerCircle(10);

	centerCircle.setPointCount(100);
	centerCircle.setFillColor(sf::Color::Red);
	centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
	centerCircle.setPosition(windowCenter);

	// Create hour, minute, and seconds hands
	sf::RectangleShape hourHand(sf::Vector2f(5, 180));
	sf::RectangleShape minuteHand(sf::Vector2f(3, 240));
	sf::RectangleShape secondsHand(sf::Vector2f(2, 250));
	// массив стрелок
	sf::RectangleShape strelki[3];
	strelki[0] = hourHand;
	strelki[1] = minuteHand;
	strelki[2] = secondsHand;
	//настройка стрелок
	setStrelki(strelki, windowCenter);

	// Create clock background
	sf::Texture clockImage;
	if (!clockImage.loadFromFile("C:/Workshpase/Clock/fon.jpg"))
	{
		return EXIT_FAILURE;
	}

	clockCircle.setTexture(&clockImage);
	clockCircle.setTextureRect(sf::IntRect(40, 0, 500, 500));

	

	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Get system time
		std::time_t currentTime = std::time(NULL);

		struct tm * ptm = localtime(&currentTime);

		hourHand.setRotation(ptm->tm_hour * 30 + (ptm->tm_min / 2));
		minuteHand.setRotation(ptm->tm_min * 6 + (ptm->tm_sec / 12));
		secondsHand.setRotation(ptm->tm_sec * 6);

		// Clear the window
		window.clear(sf::Color::White);
		window.draw(clockCircle);
		for (int i = 0; i<60; i++)
		{
			window.draw(dot[i]);
		}
		window.draw(hourHand);
		window.draw(minuteHand);
		window.draw(secondsHand);
		window.draw(centerCircle);
		window.display();
	}

	return EXIT_SUCCESS;
}
