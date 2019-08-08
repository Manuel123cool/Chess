#pragma once
#include "chess_game.h"
#include "states.h"
#include <SFML/Graphics.hpp>

class TwoPlayer : public States, public ChessGame
{
private:
    bool backToManu();
    sf::RenderWindow &m_window;
    sf::Font m_font;
public:
    TwoPlayer(sf::RenderWindow &window);
    virtual void update() override;
    virtual States* currentState(Manu *manu, TwoPlayer *twoPlayer, OnePlayer *onePlaye) override;
};
