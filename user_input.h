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
