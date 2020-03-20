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
#include "user_input.h"
#include "play_by_rules.h"
#include <string>
#include <SFML/Graphics.hpp>

class ChessGame : protected Chessboard, protected UserInput, protected PlayByRules
{
private:
    sf::RenderWindow &m_window;
    bool checkCastling();
    void restartGame();
    sf::Font m_font;
    bool aFigureCanMoveToByCastling(int from, int to, Chessboard &chessboard, bool dontDraw = false);
    bool m_once = true;
protected:
    void updateChessGame();
    bool drawAndCheckRestartGame();
    std::string m_state;
public:
    void drawState(std::string state);
    bool checkIfCheckmate(int to, Chessboard &chessboard, bool dontDraw = false);
    void checkIfMakingCheck(int to);
    bool checkIfGettingCheck(int from, int to, Chessboard &chessboard, bool dontDraw = false);
    ChessGame(sf::RenderWindow &window);
};
