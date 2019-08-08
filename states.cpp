#include "states.h"
#include "manu.h"

void States::changeState(Manu *manu, TwoPlayer *twoPlayer, OnePlayer *onePlayer)
{
    m_baseStates = m_baseStates->currentState(manu, twoPlayer, onePlayer);
}

States* States::getState()
{
    return m_baseStates;
}

States::States(Manu *manu) : m_baseStates(manu)
{

}

States::States()
{
}
