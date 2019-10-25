#pragma once
#include "SFML.h"
#include "curr.h"
#include "Defines.h"

#include "TextBox.h"
#include "CheckBox.h"
#include "OwnButton.h"

#include <iostream>
#include <string>

#include "InputHandler.h"

class StartMenu
{
public:
	enum Result
	{
		None = -2,
		Close = -1,
		Default = 0,
		Server = 1,
		Client = 2
	};

private:
	OwnButton serverButton;
	OwnButton clientButton;

	TextBox ipBox;
	sf::IpAddress adress;

	TextBox portBox;
	unsigned int port;

	Result returnVal = Result::None;

	void initCallbacks();

	static const std::string serverButton_id;
	static const std::string clientButton_id;

public:
	StartMenu();
	~StartMenu();

	const std::string callback_id;

	Result open();

	sf::IpAddress getIp() { return adress; }
	unsigned int getPort() { return port; }

	void leftMouseDown(int x, int y);
	void textEntered(sf::Event::TextEvent text);
	void close();

	void display();
	void nextWindow();
};

