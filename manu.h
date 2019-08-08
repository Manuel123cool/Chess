#pragma once
#include "states.h"
#include <SFML/Graphics.hpp>
#include "one_player.h"

class Manu : public States
{
public:
    enum State {ONE_PLAYER,TWO_PLAYER, MANU};
private:
    State m_state = MANU;
    sf::RectangleShape m_rect[2];
    sf::RenderWindow &m_window;
    void drawButtons();
    State selectButtons();
    void clicketButton(Manu::State state);
public:
    Manu(sf::RenderWindow &window);
    virtual void update() override;
    virtual States* currentState(Manu *manu, TwoPlayer *twoPlayer, OnePlayer *onePlayer) override;
};
