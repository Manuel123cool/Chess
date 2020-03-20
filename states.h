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
