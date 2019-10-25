#pragma once
#include "TextBox.h"
#include "CheckBox.h"
#include "OwnButton.h"

#include "LogUtil.h"

#include "SFML.h"

class BaseUIWindow
{
protected:
	int baseWidth;
	int baseHeight;

	sf::RenderWindow window;
	sf::String title;

	BaseUIWindow(sf::String title);
	BaseUIWindow(unsigned int width, unsigned int height, sf::String title);
	~BaseUIWindow();

	int run();

	void display();
};

