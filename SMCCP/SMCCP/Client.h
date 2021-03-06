#pragma once
#include "SFML.h"
#include "Defines.h"

#include "TextBox.h"
#include "CheckBox.h"
#include "OwnButton.h"
#include "NamePrompt.h"

#include "util.h"

#include <iostream>
#include <string>

#include <vector>

#include <Windows.h>

#include "RSA.h"
#include "Protocol.h"

#include "InputCallbackHandler.h"

class Client : public InputCallbackHandler
{
public:
	enum class SetupResult
	{
		Default = -1,
		Done = 0,
		RetrySetup = 1,
		Close = 2,
		Error = 3,
	};

public:
#pragma region Con-/Destructor
	Client(bool pBlock, int pPort = 53000, sf::IpAddress address = sf::IpAddress::getPublicAddress());
	~Client();
#pragma endregion

private:
#pragma region Networking
	unsigned int port;
	std::string name;
	sf::IpAddress ip;

	sf::TcpSocket socket;

	sf::Packet sendData;
	sf::Packet receiveData;

	bool connected = true;
	bool block;

	void onServerDisconnect();

	std::string lastMsg;
	unsigned int maxMsgs = 15U;

	std::vector<sf::String> msgs;
#pragma endregion

public:
#pragma region Networking
	__declspec(deprecated) void SendString(sf::String msg);

	SetupResult Setup();

	bool isConnected() { return connected; }
	std::string getName() { return name; }
	sf::String getLastMsg() { return lastMsg; }
	unsigned int getPort() { return socket.getRemotePort(); }

	void Send(std::string msg, bool tagIncluded = false, bool encrypt = true);
#pragma endregion

private:
#pragma region Graphics
	sf::Text nameText;
	TextBox textBox;
	sf::Text msgText;

	CheckBox muteBox;

	OwnButton sendButton;

	void draw();
	void onEnter();
	void initGraphics();
#pragma endregion

public:
#pragma region Graphics
	//Displays message in messages feed (no name, etc.)
	void DisplayMessage(std::string message);
#pragma endregion

	//General
private:
#pragma region General
	bool running = true;
	bool muted;

	void update();
#pragma endregion

public:
#pragma region General
	void Run();
#pragma endregion

private:
#pragma region RSA
	RSA::Key key;
	RSA::PublicKey serverKey;

	//tries generating a key (filling variable key)
	//returns true if succesful
	bool GenerateKey(int max_errors = 5);
#pragma endregion

public:
#pragma region RSA

#pragma endregion

private:
#pragma region Callbacks
	void initCallbacks();
	//void cleanCallbacks();

	static const std::string sendButton_id;
#pragma endregion

public:
#pragma region Callbacks
	// Callback stuff
	virtual void LeftMCallback(int x, int y);
	virtual void CloseCallback();
	virtual void TextEnteredCallback(sf::Event::TextEvent text);
	virtual void LostFocusCallback();

	void buttonCallback(std::string id);
	OwnButton::buttonCallback bCallback =
		std::bind(&Client::buttonCallback, this,
			std::placeholders::_1);
#pragma endregion
};

