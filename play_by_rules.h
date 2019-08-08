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
