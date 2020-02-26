#include <iostream>

#include <SFML/Graphics.hpp>
#include <iostream>
#include "chess_game.h"
#include "states.h"
#include "one_player.h"
#include "two_player.h"
#include "manu.h"


int main()
{
    int windowWidth = 900;
    int windowHeight = 920;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
        "Chess", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    OnePlayer onePlayer(window);
    TwoPlayer twoPlayer(window);

    Manu manu(window);
    States states(&manu);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        states.changeState(&manu, &twoPlayer, &onePlayer);
        states.getState()->update();

        window.display();
    }
    return 0;
}
