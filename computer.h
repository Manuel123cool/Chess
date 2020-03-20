/*  Konklusion_cms: open source blog manager
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
#include "chess_game.h"

class Computer
{
private:
    PlayByRules *m_playByRules;
    Chessboard *m_chessBoard;
    ChessGame *m_chessGame;
    int getRandomNumber(int min, int max);
    struct Move
    {
        int from = -1;
        int to = -1;
        int index = 0;
    };
    Move* getAllPosMoves(Move *move, Chessboard *chessboard);
    Move playRandom(Move *move, Chessboard *chessboard);
    sf::RenderWindow &m_window;
    int evaluation(Chessboard *chessboard);
    Move playWithEvaluation(Chessboard *chessboard);
    Move playMinimax();
    int minimax(int deph, int dephNumber, Chessboard &chessboard, bool computerIsPlaying, int alpha, int beta);
    int m_countMinimaxPos = 0;
    bool m_whiteIsHuman;
protected:
    void setUpComputer(PlayByRules *playByRules, Chessboard *chessBoard, ChessGame *chessGame, bool whiteIsHuman);
    bool computerPLay();
public:
    Computer(sf::RenderWindow &window);
};

