#include "chess_game.h"
#include "play_by_rules.h"
#include <iostream>
#include <string>
#include <chrono> 

void ChessGame::updateChessGame()
{
    if (m_once)
    {
        setUpChessFigures();
        m_once = false;
    }
    updateChessboard();

    setUserInputPointers(this, this);
    setPlayByRulesPointer(this);

    drawAndCheckRestartGame();
    drawPossibleMoves();

    ClicketPos clicketPos;
    clicketPos = getUserInupt();
    
    bool checkCheck{ checkIfGettingCheck(clicketPos.pos1, clicketPos.pos2, *this)};
    bool b_validMove{ validMove(clicketPos.pos1, clicketPos.pos2) }; 

    if (clicketPos.on && b_validMove && !checkCheck)
    {
        m_state = "";

        playFromTo(clicketPos.pos1, clicketPos.pos2);

        if (!checkIfCheckmate(clicketPos.pos2, *this))
            checkIfMakingCheck(clicketPos.pos2);

        rotateBoard();
    }

    drawState(m_state);
}

void ChessGame::checkIfMakingCheck(int to)
{
    int counterKingPos = -1;
    for (int i{0}; i < 64; ++i)
    {
        bool isCounterPlayer;
        if (getFigureAssets(i).isOn)
            isCounterPlayer = (checkWhiteIsPlaying() != getFigureAssets(i).white);
        else
            isCounterPlayer = false;

        if (KING == getFigureAssets(i).figure && isCounterPlayer && getFigureAssets(i).isOn)
        {
            counterKingPos = i;
        }
    }
    if (validMove(to, counterKingPos))
    {
        if (checkWhiteIsPlaying())
            m_state = "black is check";
        else
            m_state = "white is check";
    }

}

bool ChessGame::aFigureCanMoveToByCastling(int from, int to, Chessboard &chessboard, bool dontDraw)
{
    Chessboard chessboard1(chessboard, m_window);
    chessboard1.playFromTo(from, to);
    chessboard1.changeCurrentPlayed();

    PlayByRules playByRules(m_window);
    playByRules.setPlayByRulesPointer(&chessboard1);

    for (int i{0}; i < 64; ++i)
    {
        bool currentPlayed = chessboard1.checkWhiteIsPlaying() == chessboard1.getFigureAssets(i).white;
        if (currentPlayed && chessboard1.getFigureAssets(i).isOn && playByRules.validMove(i, to))
        {
            if (!dontDraw)
                m_state = "Invalid move: you getting check by moving this castling";
            return true;
        }
    }
    return false;
}

bool ChessGame::checkIfGettingCheck(int from, int to, Chessboard &chessboardArg, bool dontDraw)
{
    Chessboard chessboard(chessboardArg, m_window);
    chessboard.playFromTo(from, to);
    chessboard.changeCurrentPlayed();


    int counterKingPos = -1;
    for (int i{0}; i < 64; ++i)
    {
        bool isCounterPlayer;
        if (chessboard.getFigureAssets(i).isOn)
            isCounterPlayer = (chessboard.checkWhiteIsPlaying() != chessboard.getFigureAssets(i).white);
        else
            isCounterPlayer = false;

        if (KING == chessboard.getFigureAssets(i).figure && isCounterPlayer && chessboard.getFigureAssets(i).isOn)
        {
            counterKingPos = i;
            break;
        }
    }

    PlayByRules playByRules(m_window);
    playByRules.setPlayByRulesPointer(&chessboard);

    for (int i{0}; i < 64; ++i)
    {
        bool currentPlayed = chessboard.checkWhiteIsPlaying() == chessboard.getFigureAssets(i).white;
        if (currentPlayed && chessboard.getFigureAssets(i).isOn && playByRules.validMove(i, counterKingPos))
        {
            if (!dontDraw)
            {
                m_state = "Invalid move: you getting check";
            }
            return true;
        }
    }

    //if play down
    if (from == 60 && getFigureAssets(60).figure == KING && to == 62)
    {
        return aFigureCanMoveToByCastling(from, 61, chessboardArg, dontDraw) ||
            aFigureCanMoveToByCastling(from, 60, chessboardArg, dontDraw);
    }

    if (from == 60 && getFigureAssets(60).figure == KING && to == 58)
    {
        return aFigureCanMoveToByCastling(from, 59, chessboardArg, dontDraw) ||
            aFigureCanMoveToByCastling(from, 60, chessboardArg, dontDraw);
    }
    //if play up
    if (from == 4 && getFigureAssets(4).figure == KING && to == 6)
    {
        return aFigureCanMoveToByCastling(from, 5, chessboardArg, dontDraw) ||
            aFigureCanMoveToByCastling(from, 4, chessboardArg, dontDraw);
    }
    if (from == 4 && getFigureAssets(4).figure == KING && to == 2)
    {
        return aFigureCanMoveToByCastling(from, 3, chessboardArg, dontDraw) ||
            aFigureCanMoveToByCastling(from, 4, chessboardArg, dontDraw);
    }
   return false;
}

bool ChessGame::checkIfCheckmate(int to, Chessboard &chessboardArg, bool dontDraw)
{
    PlayByRules newPlayByRules(m_window);
    newPlayByRules.setPlayByRulesPointer(&chessboardArg);

    int counterKingPos = -1;
    for (int i{0}; i < 64; ++i)
    {
        bool isCounterPlayer;
        if (chessboardArg.getFigureAssets(i).isOn)
            isCounterPlayer = (chessboardArg.checkWhiteIsPlaying() != chessboardArg.getFigureAssets(i).white);
        else
            isCounterPlayer = false;

        if (KING == chessboardArg.getFigureAssets(i).figure && isCounterPlayer && chessboardArg.getFigureAssets(i).isOn)
        {
            counterKingPos = i;
        }
    }

    if (newPlayByRules.validMove(to, counterKingPos))
    {
        Chessboard chessboard(chessboardArg, m_window);
        chessboard.changeCurrentPlayed();

        PlayByRules playByRules(m_window);
        playByRules.setPlayByRulesPointer(&chessboard);

        int kingCanGoPos[8];
        for (auto &pos : kingCanGoPos)
            pos = -1;

        int index = 0;

        for (int i{0}; i <  64; ++i)
        {
            if (playByRules.validMove(counterKingPos, i))
            {
                kingCanGoPos[index] = i;
                index++;
            }
        }

        int count = 0;
        for (int i{0}; i < index; ++i)
        {
            Chessboard chessboard1(chessboardArg, m_window);
            chessboard1.playFromTo(counterKingPos, kingCanGoPos[i]);

            PlayByRules playByRules1(m_window);
            playByRules1.setPlayByRulesPointer(&chessboard1);

            for (int j{0}; j < 64; ++j)
            {
                bool currentPlayed = chessboard1.checkWhiteIsPlaying() == chessboard1.getFigureAssets(j).white;
                if (chessboard1.getFigureAssets(j).isOn && currentPlayed && playByRules1.validMove(j, kingCanGoPos[i]))
                {
                    count++;
                    break;
                }
            }
        }


        bool moveCanStopCheck = false;
        int newCounterKingPos = counterKingPos;
        for (int i{0}; i < 64; ++i)
        {
            if (moveCanStopCheck)
                break;

            for (int j{0}; j < 64; ++j)
            {
                if (moveCanStopCheck)
                    break;

                bool currentPlayed = chessboard.checkWhiteIsPlaying() == chessboard.getFigureAssets(i).white;

                if (!(chessboard.getFigureAssets(i).isOn && currentPlayed))
                    break;


                if (chessboard.getFigureAssets(i).isOn && currentPlayed && playByRules.validMove(i, j))
                {
                    Chessboard chessboard2(chessboardArg, m_window);
                    chessboard2.playFromTo(i, j);

                    if (KING == chessboard.getFigureAssets(i).figure)
                        newCounterKingPos = j;
                    else
                        newCounterKingPos = counterKingPos;

                    PlayByRules playByRules2(m_window);
                    playByRules2.setPlayByRulesPointer(&chessboard2);

                    int count1 = 0;
                    for (int k{0}; k < 64; ++k)
                    {
                        bool currentPlayed = chessboard2.checkWhiteIsPlaying() == chessboard2.getFigureAssets(k).white;
                        if (chessboard2.getFigureAssets(k).isOn && currentPlayed && playByRules2.validMove(k, newCounterKingPos))
                        {
                            break;
                        }
                        else
                        {
                            count1++;
                        }
                    }
                    if (count1 == 64)
                    {
                        moveCanStopCheck = true;
                        break;
                    }
                }
            }
        }

        if (count == index && !moveCanStopCheck)
        {
            if (!dontDraw)
            {
                if (chessboardArg.checkWhiteIsPlaying())
                {
                    m_state = "Black is checkmate";
                }
                else
                {
                    m_state = "White is checkmate";
                }

                if (chessboardArg.checkWhiteIsPlaying())
                {
                    m_state = "Black is checkmate";
                }
                else
                {
                    m_state = "White is checkmate";
                }
            }
            return true;
        }

    }

    return false;
}

void ChessGame::restartGame()
{
    for (int i{0}; i < 64; ++i)
        deleteChessFigure(i);

    setPLayByRulesToDefault();
    setChessBoardToDefault();

    setUpChessFigures(true);
    m_state = "";
}

bool ChessGame::drawAndCheckRestartGame()
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(100.f, 20.f));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(sf::Vector2f(103.f, 0.f));

    sf::Text text1;
    text1.setFont(m_font);
    text1.setString("restart");
    text1.setCharacterSize(18);
    text1.setFillColor(sf::Color::Black);
    text1.setPosition(sf::Vector2f(108.f, 0.f));

    sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);

    bool intersectY = (localPosition.y >= rect.getGlobalBounds().top &&
        localPosition.y <= rect.getGlobalBounds().top + rect.getGlobalBounds().height);

    bool intersectX = (localPosition.x >= rect.getGlobalBounds().left &&
        localPosition.x <= rect.getGlobalBounds().left + rect.getGlobalBounds().width);

    bool manu = false;
    bool restart = false;
    if (intersectY && intersectX)
    {
        rect.setOutlineColor(sf::Color::Magenta);
        rect.setOutlineThickness(3.f);

        static bool isClicket = true;
        bool wasClicket = isClicket;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            isClicket = true;
        else
            isClicket = false;

        if (isClicket && !wasClicket)
        {
            restartGame();
            restart = true;
        }
    }
    else
    {
        rect.setOutlineThickness(0);
    }
    m_window.draw(rect);
    m_window.draw(text1);
    return restart;
}

ChessGame::ChessGame(sf::RenderWindow &window) : m_window(window), Chessboard(window), UserInput(window), PlayByRules(window)
{
    if (!m_font.loadFromFile("futura-normal_[allfont.de].ttf"))
    {
        std::cerr << "Error loading font\n";
    }
}

void ChessGame::drawState(std::string state)
{
    sf::Text text1;
    text1.setFont(m_font);
    text1.setString(state);
    text1.setCharacterSize(18);
    text1.setFillColor(sf::Color::White);
    text1.setPosition(sf::Vector2f(208.f, 0.f));

    m_window.draw(text1);
}
