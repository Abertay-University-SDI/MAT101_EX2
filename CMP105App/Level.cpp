#include "Level.h"
#include <Windows.h>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	play = true;

	rocketTexture.loadFromFile("gfx/rocket.png");
	rocket.setInput(in);
	rocket.setRenderWindow(hwnd);
	rocket.setSize(sf::Vector2f(100, 100));
	rocket.setOrigin(rocket.getSize().x/2.0f, rocket.getSize().y/2.0f);
	rocket.setRotation(90);
	rocket.setPosition(0, 300);
	rocket.setTexture(&rocketTexture);
	rocket.setText(&text);

	if (!font.loadFromFile("font/arial.ttf"))
	{
		// something went wrong
		MessageBox(NULL, L"Font failed to load", L"Error", MB_OK);
	}

	//drag = false;

	// Create a text
	text.setString("Hello world");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	//text.setPosition(10, 10);
	text.setFillColor(sf::Color::Red);


}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	//The class that provides access to the keyboard state is sf::Keyboard.It only contains one function, isKeyPressed, which checks the current state of a key(pressed or released).It is a static function, so you don't need to instanciate sf::Keyboard to use it.
		//This function directly reads the keyboard state, ignoring the focus state of your window.This means that isKeyPressed may return true even if your window is inactive.
	if (input->isKeyJustDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();
	}
	if (input->isKeyJustDown(sf::Keyboard::Return))
	{
		
		play = !play;
	}
}

// Update game objects
void Level::update(float dt)
{
	if (play)
	{
		rocket.update(dt);
		std::string xpos = std::to_string(sf::Mouse::getPosition(*window).x);
		std::string ypos = std::to_string(sf::Mouse::getPosition(*window).y);
		text.setString("Mouse: " + xpos + ", " + ypos);
	}
}

// Render level
void Level::render()
{
	beginDraw();
	rocket.Draw();
	window->draw(text);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}