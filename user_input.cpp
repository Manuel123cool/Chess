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

#include "user_input.h"
#include <iostream>

void UserInput::setUserInputPointers(Chessboard *chessboard, PlayByRules *playByRules)
{
    m_chessboard = chessboard;
    m_playByRules = playByRules;
}

UserInput::ClicketPos UserInput::getUserInupt()
{
    ClicketPos clicketPos;

    bool wasClicket = m_isClicket;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        m_isClicket = true;
    else
        m_isClicket = false;

    if (m_count >= 100)
        m_count = 0;

    if (m_isClicket && !wasClicket)
    {
        for (int i{0}; i < 64; ++i)
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);
            sf::FloatRect rect = m_chessboard->getGlobalBounds(i);

            bool intersectY = (localPosition.y >= rect.top &&
                localPosition.y <= rect.top + rect.height);

            bool intersectX = (localPosition.x >= rect.left &&
                localPosition.x <= rect.left + rect.width);

            if (intersectX && intersectY)
            {
                m_count++;
                m_posPlusValid[m_count].pos = i;
                m_posPlusValid[m_count].isValid = m_playByRules->checkValidClicking(i);

                if (!m_playByRules->checkValidClicking(i) && m_posPlusValid[m_count - 1].isValid)
                {
                    clicketPos.on = true;
                    clicketPos.pos1 = m_posPlusValid[m_count - 1].pos;
                    clicketPos.pos2 = i;
                    return clicketPos;
                }
            }
        }
    }
    clicketPos.on = false;
    return clicketPos;
}

UserInput::UserInput(sf::RenderWindow &window) : m_window(window)
{

}
