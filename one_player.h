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

#pragma once
#include "chess_game.h"
#include "states.h"
#include <SFML/Graphics.hpp>
#include "computer.h"

class OnePlayer : public ChessGame, public States, public Computer
{
private:
    bool backToManu();
    sf::RenderWindow &m_window;
    sf::Font m_font;
    bool m_once = true;
    bool whiteIsHuman;
    bool gameOver = false;
public:
    OnePlayer(sf::RenderWindow &window);
    virtual void update() override;
    virtual States* currentState(Manu *manu, TwoPlayer *twoPlayer, OnePlayer *onePlaye) override;
};

