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

#include "play_by_rules.h"
#include <iostream>

void PlayByRules::setPlayByRulesPointer(Chessboard *chessboard)
{
    m_chessboard = chessboard;
}

bool PlayByRules::checkValidClicking(int pos)
{
    bool isOn = m_chessboard->getFigureAssets(pos).isOn;
    bool colorEqualPlaying = m_chessboard->getFigureAssets(pos).white == m_chessboard->checkWhiteIsPlaying();
    if (isOn && colorEqualPlaying)
        return true;
    else
        return false;
}

bool PlayByRules::validMove(int from, int to)
{
    if (m_chessboard->getCurrentPlayerIsUp() && Chessboard::FARMER == m_chessboard->getFigureAssets(from).figure)
        return checkValidMoveFarmerUp(from, to);

    if (m_chessboard->getCurrentPlayerIsUp() && checkCastlingUp(from, to))
        return checkCastlingUp(from, to);

    if (checkCastling(from, to))
        return  checkCastling(from, to);

    switch (m_chessboard->getFigureAssets(from).figure)
    {
        case Chessboard::FARMER:
            return checkValidMoveFarmer(from, to);
            break;
        case Chessboard::TOWER:
            return checkValidMoveTower(from, to);
            break;
        case Chessboard::RUNNER:
            return checkValidMoveRunner(from, to);
            break;
        case Chessboard::QUEEN:
            return checkValidMoveQueen(from, to);
            break;
        case Chessboard::KING:
            return checkValidMoveKing(from, to);
            break;
        case Chessboard::HORS:
            return checkValidMoveHors(from, to);
    }
    return true;
}

bool PlayByRules::checkValidMoveFarmer(int from, int to)
{
    bool biggerSmallerFirstRow = from > 47 && from < 56;
    bool upToTwoTimes = (to == from - 8 || to == from - 8 * 2);

    bool isntFigure = (!m_chessboard->getFigureAssets(to).isOn && !m_chessboard->getFigureAssets(from - 8).isOn);

    if (biggerSmallerFirstRow && upToTwoTimes && isntFigure)
        return true;

    bool oneTime = (to == from - 8);
    if (!biggerSmallerFirstRow && oneTime && isntFigure)
        return true;

    bool oneTimeLeftRight = (to == from - 7 || to == from - 9);

    for (int i{7}; i < 64; i += 8)
    {
        if (from == i && to == from - 7)
        {
            return false;
        }
        if (from == i - 7 && to == from - 9)
        {
            return false;
        }
    }

    bool isCounterPlayer;
    if (m_chessboard->getFigureAssets(to).isOn)
        isCounterPlayer = (m_chessboard->checkWhiteIsPlaying() != m_chessboard->getFigureAssets(to).white);
    else
        isCounterPlayer = false;

    if (oneTimeLeftRight && isCounterPlayer)
        return true;

    return false;
}

bool PlayByRules::checkValidMoveFarmerUp(int from, int to)
{
    bool biggerSmallerFirstRow = from > 7 && from < 16;
    bool downToTwoTimes = (to == from + 8 || to == from + 8 * 2);

    bool isntFigure = (!m_chessboard->getFigureAssets(to).isOn && !m_chessboard->getFigureAssets(from + 8).isOn);

    if (biggerSmallerFirstRow && downToTwoTimes && isntFigure)
        return true;

    bool oneTime = (to == from + 8);
    if (!biggerSmallerFirstRow && oneTime && isntFigure)
        return true;

    bool oneTimeLeftRight = (to == from + 7 || to == from + 9);

    for (int i{7}; i < 64; i += 8)
    {
        if (from == i && to == from + 9)
        {
            return false;
        }
        if (from == i - 7 && to == from + 7)
        {
            return false;
        }
    }

    bool isCounterPlayer;
    if (m_chessboard->getFigureAssets(to).isOn)
        isCounterPlayer = (m_chessboard->checkWhiteIsPlaying() != m_chessboard->getFigureAssets(to).white);
    else
        isCounterPlayer = false;

    if (oneTimeLeftRight && isCounterPlayer)
        return true;

    return false;
}

bool PlayByRules::checkValidMoveTower(int from, int to)
{
    bool breakForDirection[4] = {0};
    bool breakLoop = false;

    bool waitNextRound[4] = {0};

    int wasPos[4];
    for (auto &elem : wasPos)
        elem = from;

    int nextPos[4] = {0};
    while (!breakLoop)
    {
        nextPos[0] = wasPos[0] - 8;
        nextPos[1] = wasPos[1] - 1;
        nextPos[2] = wasPos[2] + 8;
        nextPos[3] = wasPos[3] + 1;

        for (int i{7}; i < 64; i += 8)
        {

            if (wasPos[1] == i - 7)
                breakForDirection[1] = true;

            if (wasPos[3] == i)
                breakForDirection[3] = true;
        }

        for (int i{0}; i < 8; i++)
        {
            if (wasPos[0] == i)
                breakForDirection[0] = true;

            if (wasPos[2] == i + 56)
                breakForDirection[2] = true;
        }

        for (int i{0}; i < 4; ++i)
        {
            if (waitNextRound[i])
            {
                breakForDirection[i] = true;
                waitNextRound[i] = false;
            }

        }

        for (int i{0}; i < 4; ++i)
        {
            bool isCounterPlayer = false;
            int pos = nextPos[i];
            if (m_chessboard->getFigureAssets(pos).isOn)
                isCounterPlayer = (m_chessboard->checkWhiteIsPlaying() != m_chessboard->getFigureAssets(pos).white);


            if (m_chessboard->getFigureAssets(pos).isOn && !isCounterPlayer)
            {
                breakForDirection[i] = true;
            }

            if (isCounterPlayer)
            {
                waitNextRound[i] = true;
            }
        }

        for (int i{0}; i < 4; ++i)
        {
            if (!breakForDirection[i])
                if (nextPos[i] == to)
                    return true;
        }

        for (int i{0}; i < 4; ++i)
            wasPos[i] = nextPos[i];

        int countBreak = 0;
        for (int i{0}; i < 4; ++i)
        {
            if (breakForDirection[i])
                countBreak++;
        }
        if (countBreak == 4)
            breakLoop = true;
    }

    return false;
}

bool PlayByRules::checkValidMoveRunner(int from, int to)
{
    bool breakForDirection[4] = {0};
    bool isSeT[4] = {0};
    bool breakLoop = false;

    bool waitNextRound[4] = {0};

    int wasPos[4];
    for (auto &elem : wasPos)
        elem = from;

    int nextPos[4] = {0};
    while (!breakLoop)
    {
        nextPos[0] = wasPos[0] - 9;
        nextPos[1] = wasPos[1] - 7;
        nextPos[2] = wasPos[2] + 7;
        nextPos[3] = wasPos[3] + 9;

        for (int i{7}; i < 64; i += 8)
        {
            for (int j{0}; j < 4; ++j)
            {
                if (wasPos[j] == i - 7)
                {
                    breakForDirection[j] = true;
                    if (from == i - 7 && !isSeT[j])
                    {
                        breakForDirection[j] = false;
                        if (j == 0 || j == 2)
                        {
                            isSeT[j] = true;
                            breakForDirection[j] = true;
                        }
                    }
                }
                if (wasPos[j] == i)
                {
                    breakForDirection[j] = true;
                    if (from == i && !isSeT[j])
                    {
                        breakForDirection[j] = false;
                        if (j == 1 || j == 3)
                        {
                            isSeT[j] = true;
                            breakForDirection[j] = true;
                        }
                    }
                }

            }
        }

        for (int i{0}; i < 8; i++)
        {
            for (int j{0}; j < 4; ++j)
            {
                if (wasPos[j] == i)
                {
                    breakForDirection[j] = true;
                    if (from == i && !isSeT[j])
                    {
                        breakForDirection[j] = false;
                        if (j == 0 || j == 1)
                        {
                            isSeT[j] = true;
                            breakForDirection[j] = true;
                        }
                    }
                }

                if (wasPos[j] == i + 56)
                {
                    breakForDirection[j] = true;
                    if (from == i + 56 && !isSeT[j])
                    {
                        breakForDirection[j] = false;
                        if (j == 2 || j == 3)
                        {
                            isSeT[j] = true;
                            breakForDirection[j] = true;
                        }
                    }
                }
            }
        }

        for (int i{0}; i < 4; ++i)
        {
            if (waitNextRound[i])
            {
                breakForDirection[i] = true;
                waitNextRound[i] = false;
            }
        }

        for (int i{0}; i < 4; ++i)
        {
            bool isCounterPlayer = false;
            int pos = nextPos[i];
            if (m_chessboard->getFigureAssets(pos).isOn)
                isCounterPlayer = (m_chessboard->checkWhiteIsPlaying() != m_chessboard->getFigureAssets(pos).white);


            if (m_chessboard->getFigureAssets(pos).isOn && !isCounterPlayer)
            {
                breakForDirection[i] = true;
            }

            if (isCounterPlayer)
            {
                waitNextRound[i] = true;
            }
        }

        for (int i{0}; i < 4; ++i)
        {
            if (!breakForDirection[i])
                if (nextPos[i] == to)
                    return true;
        }

        for (int i{0}; i < 4; ++i)
            wasPos[i] = nextPos[i];

        int countBreak = 0;
        for (int i{0}; i < 4; ++i)
        {
            if (breakForDirection[i])
                countBreak++;
        }
        if (countBreak == 4)
            breakLoop = true;
    }

    return false;
}

void PlayByRules::drawPossibleMoves(bool twoPlayer, bool whiteIsHuman)
{
    bool wasClicket = m_isClicket;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        m_isClicket = true;
    else
        m_isClicket = false;

    if (twoPlayer && m_chessboard->checkWhiteIsPlaying() != whiteIsHuman)
        m_isClicket = false;

    if (m_isClicket && !wasClicket)
    {
        for (int i{0}; i < 64; ++i)
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);
            sf::FloatRect rect = m_chessboard->getGlobalBounds(i);

            bool intersectY = (localPosition.y >= rect.top &&
                localPosition.y <= rect.top + rect.height);

            bool intersectX = (localPosition.x >= rect.left &&
                localPosition.x <= rect.left + rect.width);

            if (intersectX && intersectY)
            {
                if (checkValidClicking(i))
                {
                    m_posCurrentClicket = i;
                }
                else
                {
                    m_posCurrentClicket = -1;
                }
            }
        }
    }

    for (int i{0}; i < 64; ++i)
    {
        if (m_posCurrentClicket != -1)
        {
            if (validMove(m_posCurrentClicket, i))
            {
                drawPoint(i);
            }
        }
    }

}

void PlayByRules::drawPoint(int pos)
{
    int row = 0;
    for (int j{0}; j < 64; j += 8)
    {
        for (int i{0}; i < 8; ++i)
        {
            if (i+j == pos)
            {
                sf::CircleShape circle(10.f);
                circle.setFillColor(sf::Color::Green);
                float x = 112 * i+ 50;
                float y = 112 * row + 70;
                circle.setPosition(sf::Vector2f(x, y));
                m_window.draw(circle);
                return;
            }
        }
        row++;
    }
}

bool PlayByRules::checkValidMoveQueen(int from, int to)
{
    return checkValidMoveTower(from, to) || checkValidMoveRunner(from, to);
}

bool PlayByRules::checkValidMoveKing(int from, int to)
{
    bool leftRightForward = (to == from - 7 || to == from - 9);
    bool leftRightBackwards = (to == from + 7 || to == from + 9);
    bool leftRight = (to == from - 1 || to == from + 1);
    bool forwardBackward = (to == from - 8 || to == from + 8);

    bool isCounterPlayer;
    if (m_chessboard->getFigureAssets(to).isOn)
        isCounterPlayer = (m_chessboard->checkWhiteIsPlaying() != m_chessboard->getFigureAssets(to).white);
    else
        isCounterPlayer = false;

    for (int i{7}; i < 64; i += 8)
    {
        if (from == i && ((to == from - 7) || (to == from + 9) || (to == from + 1)))
        {
            return false;
        }
        if (from == i - 7 && ((to == from + 7) || (to == from - 9) || (to == from - 1)))
        {
            return false;
        }
    }

    if ((leftRight || leftRightBackwards || leftRightForward || forwardBackward) && !m_chessboard->getFigureAssets(to).isOn)
        return true;

    if ((leftRight || leftRightBackwards || leftRightForward || forwardBackward) && isCounterPlayer)
        return true;

    return false;
}

bool PlayByRules::checkValidMoveHors(int from, int to)
{
    int twoUpPos = from - 8 * 2;
    int twoDownPos = from + 8 * 2;
    int twoLeftPos = from - 2;
    int twoRightPos = from + 2;

    bool isCounterPlayer;
    if (m_chessboard->getFigureAssets(to).isOn)
        isCounterPlayer = (m_chessboard->checkWhiteIsPlaying() != m_chessboard->getFigureAssets(to).white);
    else
        isCounterPlayer = false;

    bool twoUpAndLeftRight = (to == twoUpPos - 1 || to == twoUpPos + 1);
    bool twoDownAndLeftRight = (to == twoDownPos - 1 || to == twoDownPos + 1);
    bool twoLeftAndLeftRight = (to == twoLeftPos - 8 || to == twoLeftPos + 8);
    bool twoRightAndLeftRight = (to == twoRightPos - 8 || to == twoRightPos + 8);

    for (int i{7}; i < 64; i += 8)
    {
        if ((from == i) && (twoRightAndLeftRight || to == twoDownPos + 1 || to == twoUpPos + 1))
        {
            return false;
        }
        else if ((from == i - 7) && (twoLeftAndLeftRight || to == twoDownPos - 1 || to == twoUpPos - 1))
        {
            return false;
        }
        else if ((from == i - 1) && (twoRightAndLeftRight))
        {
            return false;
        }
        else if ((from == i - 6) && (twoLeftAndLeftRight))
        {
            return false;
        }
    }

    if ((twoUpAndLeftRight || twoDownAndLeftRight || twoLeftAndLeftRight || twoRightAndLeftRight) && !m_chessboard->getFigureAssets(to).isOn)
        return true;

    if ((twoUpAndLeftRight || twoDownAndLeftRight || twoLeftAndLeftRight || twoRightAndLeftRight) && isCounterPlayer)
        return true;

    return false;
}
void PlayByRules::setPLayByRulesToDefault()
{
    m_posCurrentClicket = -1;
}

PlayByRules::PlayByRules(sf::RenderWindow &window) : m_window(window)
{

}

bool PlayByRules::checkCastling(int from, int to)
{
    // small castling
    bool rightTowerIsStanding = m_chessboard->getFigureAssets(63).figure == Chessboard::TOWER && m_chessboard->getFigureAssets(63).isOn;
    bool didNotMovedBlackAndRight = !m_chessboard->getKingOrTowerWasPlayed().rightBlackTowerMoved &&
        !m_chessboard->getKingOrTowerWasPlayed().blackKingMoved;
    bool noPosInCastlingBlackRight = !m_chessboard->getFigureAssets(62).isOn && !m_chessboard->getFigureAssets(61).isOn;
    bool rightPosInCastlingBlackRight = from == 60 && to == 62;
    if (didNotMovedBlackAndRight && !m_chessboard->checkWhiteIsPlaying() &&
        noPosInCastlingBlackRight && rightPosInCastlingBlackRight && rightTowerIsStanding)
        return true;

    bool didNotMovedWhiteAndRight = !m_chessboard->getKingOrTowerWasPlayed().whiteKingMoved &&
        !m_chessboard->getKingOrTowerWasPlayed().rightWhiteTowerMoved;
    bool noPosInCastlingWhiteRight = !m_chessboard->getFigureAssets(62).isOn && !m_chessboard->getFigureAssets(61).isOn;
    bool rightPosInCastlingWhiteRight = from == 60 && to == 62;
    if (didNotMovedWhiteAndRight && m_chessboard->checkWhiteIsPlaying() &&
        noPosInCastlingWhiteRight && rightPosInCastlingWhiteRight && rightTowerIsStanding)
        return true;

    //big castling
    bool leftTowerIsStanding = m_chessboard->getFigureAssets(56).figure == Chessboard::TOWER && m_chessboard->getFigureAssets(56).isOn;
    bool didNotMovedWhiteAndLeft = !m_chessboard->getKingOrTowerWasPlayed().whiteKingMoved &&
        !m_chessboard->getKingOrTowerWasPlayed().leftWhiteTowerMoved;
    bool noPosInCastlingWhiteLeft = !m_chessboard->getFigureAssets(59).isOn && !m_chessboard->getFigureAssets(58).isOn && !m_chessboard->getFigureAssets(57).isOn;
    bool rightPosInCastlingWhiteLeft = from == 60 && to == 58;
    if (didNotMovedWhiteAndLeft && m_chessboard->checkWhiteIsPlaying() &&
        noPosInCastlingWhiteLeft && rightPosInCastlingWhiteLeft && leftTowerIsStanding)
        return true;

    bool didNotMovedBlackAndLeft = !m_chessboard->getKingOrTowerWasPlayed().blackKingMoved &&
        !m_chessboard->getKingOrTowerWasPlayed().leftBlackTowerMoved;
    bool noPosInCastlingBlackLeft = !m_chessboard->getFigureAssets(59).isOn && !m_chessboard->getFigureAssets(58).isOn && !m_chessboard->getFigureAssets(57).isOn;
    bool rightPosInCastlingBlackLeft = from == 60 && to == 58;
    if (didNotMovedBlackAndLeft && !m_chessboard->checkWhiteIsPlaying() &&
        noPosInCastlingBlackLeft && rightPosInCastlingBlackLeft && leftTowerIsStanding)
        return true;

    return false;
}

bool PlayByRules::checkCastlingUp(int from, int to)
{
    // small castling
    bool rightTowerIsStanding = m_chessboard->getFigureAssets(7).figure == Chessboard::TOWER && m_chessboard->getFigureAssets(7).isOn;
    bool didNotMovedBlackAndRight = !m_chessboard->getKingOrTowerWasPlayed().rightBlackTowerMoved &&
        !m_chessboard->getKingOrTowerWasPlayed().blackKingMoved;
    bool noPosInCastlingBlackRight = !m_chessboard->getFigureAssets(6).isOn && !m_chessboard->getFigureAssets(5).isOn;
    bool rightPosInCastlingBlackRight = from == 4 && to == 6;
    if (didNotMovedBlackAndRight && !m_chessboard->checkWhiteIsPlaying() &&
        noPosInCastlingBlackRight && rightPosInCastlingBlackRight && rightTowerIsStanding)
        return true;

    bool didNotMovedWhiteAndRight = !m_chessboard->getKingOrTowerWasPlayed().whiteKingMoved &&
        !m_chessboard->getKingOrTowerWasPlayed().rightWhiteTowerMoved;
    bool noPosInCastlingWhiteRight = !m_chessboard->getFigureAssets(6).isOn && !m_chessboard->getFigureAssets(5).isOn;
    bool rightPosInCastlingWhiteRight = from == 4 && to == 6;
    if (didNotMovedWhiteAndRight && m_chessboard->checkWhiteIsPlaying() &&
        noPosInCastlingWhiteRight && rightPosInCastlingWhiteRight && rightTowerIsStanding)
        return true;

    //big castling
    bool leftTowerIsStanding = m_chessboard->getFigureAssets(0).figure == Chessboard::TOWER && m_chessboard->getFigureAssets(0).isOn;
    bool didNotMovedWhiteAndLeft = !m_chessboard->getKingOrTowerWasPlayed().whiteKingMoved &&
        !m_chessboard->getKingOrTowerWasPlayed().leftWhiteTowerMoved;
    bool noPosInCastlingWhiteLeft = !m_chessboard->getFigureAssets(3).isOn && !m_chessboard->getFigureAssets(2).isOn && !m_chessboard->getFigureAssets(1).isOn;
    bool rightPosInCastlingWhiteLeft = from == 4 && to == 2;
    if (didNotMovedWhiteAndLeft && m_chessboard->checkWhiteIsPlaying() &&
        noPosInCastlingWhiteLeft && rightPosInCastlingWhiteLeft && leftTowerIsStanding)
        return true;

    bool didNotMovedBlackAndLeft = !m_chessboard->getKingOrTowerWasPlayed().blackKingMoved &&
        !m_chessboard->getKingOrTowerWasPlayed().leftBlackTowerMoved;
    bool noPosInCastlingBlackLeft = !m_chessboard->getFigureAssets(3).isOn && !m_chessboard->getFigureAssets(2).isOn && !m_chessboard->getFigureAssets(1).isOn;
    bool rightPosInCastlingBlackLeft = from == 4 && to == 2;
    if (didNotMovedBlackAndLeft && !m_chessboard->checkWhiteIsPlaying() &&
        noPosInCastlingBlackLeft && rightPosInCastlingBlackLeft && leftTowerIsStanding)
        return true;

    return false;
}
