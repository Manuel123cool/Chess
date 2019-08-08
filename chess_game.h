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
