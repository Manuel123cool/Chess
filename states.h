#pragma once
#include <iostream>

class Manu;
class TwoPlayer;
class OnePlayer;

class States
{
private:
    States *m_baseStates;
public:
    virtual void update() {};
    virtual States* currentState(Manu *manu, TwoPlayer *twoPlayer, OnePlayer *onePlayer) {return m_baseStates;};
    void changeState(Manu *manu, TwoPlayer *twoPlayer, OnePlayer *onePlayer);
    States* getState();
    virtual ~States() {};
    States(Manu *manu);
    States();
};
