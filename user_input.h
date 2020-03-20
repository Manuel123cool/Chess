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
#include "chessboard.h"
#include "play_by_rules.h"

class UserInput
{
private:
    Chessboard *m_chessboard;
    PlayByRules *m_playByRules;
    sf::RenderWindow &m_window;
    struct PosPlusValid
    {
        int pos = 0;
        bool isValid = false;
    };
    PosPlusValid m_posPlusValid[100];
    int m_count = 0;
    bool m_isClicket = true;
protected:
    struct FromTo
    {
        int from = -1;
        int to = -1;
        bool isOn = false;
    };
    struct ClicketPos
    {
        bool on = false;
        int pos1 = -1;
        int pos2 = -1;
    };
    ClicketPos m_clicketPos;
    void setUserInputPointers(Chessboard *chessboard, PlayByRules *playByRules);
    ClicketPos getUserInupt();
public:
    UserInput(sf::RenderWindow &window);
};
