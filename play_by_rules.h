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

class PlayByRules
{
private:
    Chessboard *m_chessboard;
    bool checkValidMoveFarmer(int form, int to);
    bool checkValidMoveFarmerUp(int form, int to);
    bool checkValidMoveTower(int form, int to);
    bool checkValidMoveRunner(int form, int to);
    bool checkValidMoveQueen(int from, int to);
    bool checkValidMoveKing(int from , int to);
    bool checkValidMoveHors(int from, int to);
    bool checkCastling(int from, int to);
    bool checkCastlingUp(int from, int to);
    sf::RenderWindow &m_window;
    int m_posCurrentClicket = -1;
    void drawPoint(int pos);
    bool m_isClicket = false;
protected:
    void setPLayByRulesToDefault();
    void drawPossibleMoves(bool twoPlayer = false, bool whiteIsHuman = false);
public:
    bool validMove(int form, int to);
    void setPlayByRulesPointer(Chessboard *chessboard);
    bool checkValidClicking(int pos);
    PlayByRules(sf::RenderWindow &window);
};
