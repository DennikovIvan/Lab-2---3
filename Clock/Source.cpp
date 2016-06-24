#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

const int screenWidth = 800;
const int screenHeight = 600;
const float PI = 3.1415927f;
const int clockCircleSize = 250;
const int clockCircleThickness = 2;
int x, y;
float angle = 0.0;

//прототипы
void createDots(sf::CircleShape *dot, sf::Vector2f windowCenter);
void setCircle(sf::CircleShape *circle, int PointCount, int outTick, sf::Color color, int isFilled, float X, float Y);
void setStrelki(sf::RectangleShape **strel, sf::Vector2f center);

void createDots(sf::CircleShape *dot, sf::Vector2f windowCenter)
{
	//настройка точек
	for (int i = 0; i<60; i++)
	{
		x = int((clockCircleSize - 10) * cos(angle));
		y = int((clockCircleSize - 10) * sin(angle));
		if (i % 5 == 0)
			dot[i] = sf::CircleShape(3);
		else
			dot[i] = sf::CircleShape(1);
		setCircle(&dot[i], 12, 1, sf::Color::Blue, 1, x + windowCenter.x, y + windowCenter.y);
		angle = angle + ((2 * PI) / 60);
	}
}

void setCircle(sf::CircleShape *circle, int PointCount, int outTick, sf::Color color, int isFilled, float X, float Y)
{
	//настройка кругов
	(*circle).setPointCount(PointCount);
	(*circle).setOutlineThickness(outTick);
	(*circle).setOutlineColor(color);
	if (isFilled)
		(*circle).setFillColor(color);
	(*circle).setOrigin((*circle).getGlobalBounds().width / 2, (*circle).getGlobalBounds().height / 2);
	(*circle).setPosition(X,Y);
}

void setStrelki(sf::RectangleShape **strel, sf::Vector2f center)
{
	//настройка стрелок
	for (int i=0;i<3;i++)
	{
		(*strel[i]).setFillColor(sf::Color::Black);
		(*strel[i]).setOrigin((*strel[i]).getGlobalBounds().width / 2, (*strel[i]).getGlobalBounds().height - 25);
		(*strel[i]).setPosition(center);
	}
}

int main()
{
	//устанавливаем уровень сглаживания
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//создаем окно приложения
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Analog Clock", sf::Style::Close, settings);
	float windowX = window.getSize().x;
	float windowY = window.getSize().y;

	//Определяем центр окна
	sf::Vector2f windowCenter = sf::Vector2f(windowX / 2.0f, windowY / 2.0f);

	//создаем точки
	sf::CircleShape dot[60];
	createDots(dot,windowCenter);

	//создаем внешний контур
	sf::CircleShape clockCircle(clockCircleSize);

	//настраиваем внешний контур
	setCircle(&clockCircle,100, clockCircleThickness, sf::Color::Black,0, windowX / 2 + clockCircleThickness, windowY / 2 + clockCircleThickness);

	//создаем центральный круг
	sf::CircleShape centerCircle(10);

	//настраиваем центральный круг
	setCircle(&centerCircle, 100, 1, sf::Color::Red,1, windowX / 2, windowY / 2);

	//создаем стрелки
	sf::RectangleShape hourHand(sf::Vector2f(5, 180));
	sf::RectangleShape minuteHand(sf::Vector2f(3, 240));
	sf::RectangleShape secondsHand(sf::Vector2f(2, 250));

	//массив стрелок
	sf::RectangleShape *strelki[3];
	strelki[0] = &hourHand;
	strelki[1] = &minuteHand;
	strelki[2] = &secondsHand;

	//настройка стрелок
	setStrelki(strelki, windowCenter);

	//задний фон часов
	sf::Texture clockImage;
	if (!clockImage.loadFromFile("C:/Workshpase/Clock/fon.jpg"))
	{
		return EXIT_FAILURE;
	}
	clockCircle.setTexture(&clockImage);
	clockCircle.setTextureRect(sf::IntRect(40, 0, 500, 500));	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

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
