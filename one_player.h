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

