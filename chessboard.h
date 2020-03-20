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
#include <SFML/Graphics.hpp>

class Chessboard
{
public:
    enum Figures
    {
        KING,
        QUEEN,
        RUNNER,
        HORS,
        TOWER,
        FARMER
    };
    struct KingOrTowerWasPlayed
    {
        bool blackKingMoved = false;
        bool whiteKingMoved = false;
        bool leftWhiteTowerMoved = false;
        bool rightWhiteTowerMoved = false;
        bool leftBlackTowerMoved = false;
        bool rightBlackTowerMoved = false;
    };
private:
    struct FigureAssets
    {
        Figures figure;
        bool white;
        bool rotateToUp = false;
        bool isOn = false;
    };
    bool m_whiteIsPlaying = true;
    FigureAssets m_figureAssets[64];
    void drawChessBoard();
    void drawChessFigure(int x, int y, Figures figures, bool white, bool rotateToUp);
    void drawChessFigures();
    int getRandomNumber(int min, int max);
    sf::RectangleShape m_rect[64];
    sf::RenderWindow &m_window;
    sf::Texture m_texture;
    void setChessFigure(int pos, Figures figures, bool white, bool rotateToUp);
    bool m_currentPlayerIsUp = false;
    KingOrTowerWasPlayed m_kingOrTowerWasPlayed;
protected:
    void deleteChessFigure(int pos);
    void setUpChessFigures(bool restart = false);
    void updateChessboard();
public:
    KingOrTowerWasPlayed getKingOrTowerWasPlayed();
    void setChessBoardToDefault();
    bool getCurrentPlayerIsUp();
    void changeCurrentPlayed();
    void rotateBoard();
    void playFromTo(int from, int to);
    Chessboard(sf::RenderWindow &window);
    sf::FloatRect getGlobalBounds(int index);
    FigureAssets getFigureAssets(int index);
    bool checkWhiteIsPlaying();
};
