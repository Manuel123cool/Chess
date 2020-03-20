/*  Chess: a simple chess AI
    Copyright (C) 2020  Manuel Maria Kümpel

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
