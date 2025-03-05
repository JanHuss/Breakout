#define MINIAUDIO_IMPLEMENTATION
#include <SFML/Graphics.hpp>
#include "miniaudio.h"
#include "Engine.h"
#include "RealVoicePool.h"
#include "VirtualVoicePool.h"

#include "GameManager.h"
#include <iostream>

RealVoicePool* RealVoicePool::instance = 0;
VirtualVoicePool* VirtualVoicePool::instance = 0;

int main()
{
    Engine audioEngine;
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Breakout");
    GameManager gameManager(&window, &audioEngine);
    gameManager.initialize();

    sf::Clock clock;
    float deltaTime;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        deltaTime = clock.restart().asSeconds();

        gameManager.update(deltaTime);
        window.clear();
        gameManager.render();
        window.display();
        audioEngine.run(deltaTime);
    }

    return 0;
}
