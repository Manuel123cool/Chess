#include "chessboard.h"
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
namespace MyRandom
{
	std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
}

void Chessboard::drawChessBoard()
{
    for (auto &rect : m_rect)
        m_window.draw(rect);
}

void Chessboard::updateChessboard()
{
    drawChessBoard();
    drawChessFigures();
}


Chessboard::Chessboard(sf::RenderWindow &window) : m_window(window)
{
    bool white = true;
    for (int j{0}; j < 8; ++j)
    {
        for (int i{0}; i < 8; ++i)
        {
            int index = j * 8 + i;
            m_rect[index].setSize(sf::Vector2f(112.5, 112.5));
            m_rect[index].setPosition(sf::Vector2f(i * 112.5, 20 + j * 112.5));
            if (white)
            {
                m_rect[index].setFillColor(sf::Color(255, 255, 204));
                white = false;
            }
            else
            {
                m_rect[index].setFillColor(sf::Color(255, 153, 0));
                white = true;
            }
        }
        if (white)
            white = false;
        else
            white = true;
    }

    if (!m_texture.loadFromFile("1280px-Chess_Pieces_Sprite.svg.png"))
    {
        std::cerr << "Error loading texure\n";
    }
}

void Chessboard::drawChessFigure(int x, int y, Figures figures, bool white, bool rotateToUp)
{
    float posX = -5.f + 112.5 * x;
    float posY =  20.f + 112.5 * y;
    float spriteX = 219 * static_cast<int>(figures);
    float spriteY = 213.5;
    if (white)
        spriteY = 0;

    switch (figures)
    {
        case KING:
            posX = -7.f + 112.5 * x;
            break;
        case QUEEN:
            posX = -5.f + 112.5 * x;
            break;
        case RUNNER:
            posX = -2.f + 112.5 * x;
            break;
        case HORS:
            posX = 1.f + 112.5 * x;
            break;
        case TOWER:
            posX = 6.f + 112.5 * x;
            break;
        case FARMER:
            posX = 11.f + 112.5 * x;
            break;
    }

    sf::Sprite sprite;
    sprite.setTexture(m_texture);
    sprite.setTextureRect(sf::IntRect(spriteX, spriteY, 195, 213.5));
    sprite.setPosition(sf::Vector2f(posX, posY));
    sprite.setScale(sf::Vector2f(0.6, 0.53));

    if (rotateToUp)
    {
        sprite.setRotation(180.f);
        switch (figures)
        {
            case KING:
                posX = 7.f + 112.5 * x + 112.5;
                break;
            case QUEEN:
                posX = 5.f + 112.5 * x + 112.5;
                break;
            case RUNNER:
                posX = 2.f + 112.5 * x + 112.5;
                break;
            case HORS:
                posX = -1.f + 112.5 * x + 112.5;
                break;
            case TOWER:
                posX = -6.f + 112.5 * x + 112.5;
                break;
            case FARMER:
                posX = -11.f + 112.5 * x + 112.5;
                break;
        }
        sprite.setPosition(sf::Vector2f(posX, posY + 112.5));
    }

    m_window.draw(sprite);
}

void Chessboard::setChessFigure(int pos, Figures figure, bool white, bool rotateToUp)
{
    m_figureAssets[pos].figure = figure;
    m_figureAssets[pos].white = white;
    m_figureAssets[pos].rotateToUp = rotateToUp;
    m_figureAssets[pos].isOn = true;
}

void Chessboard::deleteChessFigure(int pos)
{
    m_figureAssets[pos].isOn = false;
}

int Chessboard::getRandomNumber(int min, int max)
{
	std::uniform_int_distribution<> die(min, max); // we can create a distribution in any function that needs it
	return die(MyRandom::mersenne); // and then generate a random number from our global generator
}

void Chessboard::drawChessFigures()
{
    int countY = 0;
    for (int i{0}; i < 64; i += 8)
    {
        for (int j{0}; j < 8; ++j)
        {
            if (m_figureAssets[i+j].isOn)
                drawChessFigure(j, countY, m_figureAssets[i+j].figure, m_figureAssets[i+j].white, m_figureAssets[i+j].rotateToUp);
        }
        countY++;
    }
}

void Chessboard::setUpChessFigures(bool restart)
{
    static bool first = true;
    static bool white1;
    static bool white2;
    if (first && !restart)
    {
        if (1 == getRandomNumber(1, 2))
        {
            white1 = true;
            white2 = false;
            m_whiteIsPlaying = false;
        }
        else
        {
            white1 = false;
            white2 = true;
            m_whiteIsPlaying = true;
        }
        first = false;
    }
    else if (restart)
    {
        if (m_whiteIsPlaying)
        {
            if (!getCurrentPlayerIsUp())
            {
                m_whiteIsPlaying = false;
                white1 = true;
                white2 = false;
            }
            else
            {
                m_whiteIsPlaying = false;
                white1 = false;
                white2 = true;
            }
        }
        else
        {
            white1 = false;
            white2 = true;
            if (!getCurrentPlayerIsUp())
            {
                m_whiteIsPlaying = true;
                white1 = false;
                white2 = true;
            }
            else
            {
                m_whiteIsPlaying = true;
                white1 = true;
                white2 = false;
            }
        }
    }

    for (int i(8); i < 16; ++i)
    {
        setChessFigure(i, FARMER, white1, true);
        setChessFigure(i + 40, FARMER, white2, false);
    }

    setChessFigure(0, TOWER, white1, true);
    setChessFigure(7, TOWER, white1, true);
    setChessFigure(1, HORS, white1, true);
    setChessFigure(6, HORS, white1, true);
    setChessFigure(2, RUNNER, white1, true);
    setChessFigure(5, RUNNER, white1, true);
    setChessFigure(3, QUEEN, white1, true);
    setChessFigure(4, KING, white1, true);

    setChessFigure(56, TOWER, white2, false);
    setChessFigure(63, TOWER, white2, false);
    setChessFigure(57, HORS, white2, false);
    setChessFigure(62, HORS, white2, false);
    setChessFigure(58, RUNNER, white2, false);
    setChessFigure(61, RUNNER, white2, false);
    setChessFigure(59, QUEEN, white2, false);
    setChessFigure(60, KING, white2, false);

}

sf::FloatRect Chessboard::getGlobalBounds(int index)
{
    return m_rect[index].getGlobalBounds();
}

Chessboard::FigureAssets Chessboard::getFigureAssets(int index)
{
    return m_figureAssets[index];
}

void Chessboard::playFromTo(int from, int to)
{
    FigureAssets figureAssets;
    figureAssets = getFigureAssets(from);
    deleteChessFigure(from);
    if (figureAssets.isOn)
    {
        if (figureAssets.figure == KING && checkWhiteIsPlaying())
            m_kingOrTowerWasPlayed.whiteKingMoved = true;
        else if (figureAssets.figure == KING && !checkWhiteIsPlaying())
            m_kingOrTowerWasPlayed.blackKingMoved = true;
        else if (figureAssets.figure == TOWER && (from == 63 || from == 7) && checkWhiteIsPlaying())
            m_kingOrTowerWasPlayed.rightWhiteTowerMoved = true;
        else if (figureAssets.figure == TOWER && (from == 0 || from == 56) && checkWhiteIsPlaying())
            m_kingOrTowerWasPlayed.leftWhiteTowerMoved = true;
        else if (figureAssets.figure == TOWER && (from == 0 || from == 56) && !checkWhiteIsPlaying())
            m_kingOrTowerWasPlayed.leftBlackTowerMoved = true;
        else if (figureAssets.figure == TOWER && (from == 7 || from == 63) && !checkWhiteIsPlaying())
            m_kingOrTowerWasPlayed.rightBlackTowerMoved = true;

        if (from == 60 && figureAssets.figure == KING && to == 62)
        {
            FigureAssets figureAssets1;
            figureAssets1 = getFigureAssets(63);
            deleteChessFigure(63);
            setChessFigure(61, figureAssets1.figure, figureAssets1.white, figureAssets1.rotateToUp);
        }

        if (from == 60 && figureAssets.figure == KING && to == 58)
        {
            FigureAssets figureAssets1;
            figureAssets1 = getFigureAssets(56);
            deleteChessFigure(56);
            setChessFigure(59, figureAssets1.figure, figureAssets1.white, figureAssets1.rotateToUp);
        }

        //when playing up
        if (from == 4 && figureAssets.figure == KING && to == 6)
        {
            FigureAssets figureAssets1;
            figureAssets1 = getFigureAssets(7);
            deleteChessFigure(7);
            setChessFigure(5, figureAssets1.figure, figureAssets1.white, figureAssets1.rotateToUp);
        }

        if (from == 4 && figureAssets.figure == KING && to == 2)
        {
            FigureAssets figureAssets1;
            figureAssets1 = getFigureAssets(0);
            deleteChessFigure(0);
            setChessFigure(3, figureAssets1.figure, figureAssets1.white, figureAssets1.rotateToUp);
        }

        deleteChessFigure(to);
        setChessFigure(to, figureAssets.figure, figureAssets.white, figureAssets.rotateToUp);
    }
}

bool Chessboard::checkWhiteIsPlaying()
{
    return m_whiteIsPlaying;
}

void Chessboard::rotateBoard()
{
    FigureAssets lowerPart[64];
    FigureAssets higherPart[64];
    FigureAssets allPart[64];

    m_whiteIsPlaying = !m_whiteIsPlaying;

    for (int i{0}; i < 32; ++i)
        higherPart[i] = m_figureAssets[i];

    for (int i{32}; i < 64; ++i)
        lowerPart[i] = m_figureAssets[i];

    int row = 0;
    for (int i{0}; i < 64; i += 8)
    {
        for (int j{0}; j < 8; ++j)
        {
            int pos = ((7 - row) * 8) + j;
            if (lowerPart[pos].isOn)
                allPart[i+j] = lowerPart[pos];
            if (higherPart[pos].isOn)
                allPart[i+j] = higherPart[pos];
        }
        row++;
    }

    for (int i{0}; i < 64; ++i)
    {
        deleteChessFigure(i);
        if (allPart[i].isOn)
        {
            setChessFigure(i, allPart[i].figure, allPart[i].white, !allPart[i].rotateToUp);
        }
    }

     //rotate board
    static bool white = true;
    if (white == true)
    {
        white = false;
    }
    else
    {
        white = true;
    }

    for (int j{0}; j < 8; ++j)
    {
        for (int i{0}; i < 8; ++i)
        {
            int index = j * 8 + i;
            m_rect[index].setSize(sf::Vector2f(112.5, 112.5));
            m_rect[index].setPosition(sf::Vector2f(i * 112.5, 20 + j * 112.5));
            if (white)
            {
                m_rect[index].setFillColor(sf::Color(255, 255, 204));
                white = false;
            }
            else
            {
                m_rect[index].setFillColor(sf::Color(255, 153, 0));
                white = true;
            }
        }
        if (white)
            white = false;
        else
            white = true;
    }
}

void Chessboard::changeCurrentPlayed()
{
    if (!m_currentPlayerIsUp)
    {
        m_whiteIsPlaying = !m_whiteIsPlaying;
        m_currentPlayerIsUp = true;
    }
    else
    {
        m_whiteIsPlaying = !m_whiteIsPlaying;
        m_currentPlayerIsUp = false;
    }
}

bool Chessboard::getCurrentPlayerIsUp()
{
    return m_currentPlayerIsUp;
}

Chessboard::KingOrTowerWasPlayed Chessboard::getKingOrTowerWasPlayed()
{
    return m_kingOrTowerWasPlayed;
}

void Chessboard::setChessBoardToDefault()
{
    m_kingOrTowerWasPlayed.blackKingMoved = false;
    m_kingOrTowerWasPlayed.whiteKingMoved = false;
    m_kingOrTowerWasPlayed.leftBlackTowerMoved = false;
    m_kingOrTowerWasPlayed.leftWhiteTowerMoved = false;
    m_kingOrTowerWasPlayed.rightBlackTowerMoved = false;
    m_kingOrTowerWasPlayed.rightWhiteTowerMoved = false;
}

Chessboard::Chessboard(const Chessboard &chessboard, sf::RenderWindow &window) : m_window(window)
{
    m_whiteIsPlaying = chessboard.m_whiteIsPlaying;
    m_kingOrTowerWasPlayed = chessboard.m_kingOrTowerWasPlayed; 
    for (int i{ 0 }; i < 64; ++i)
        m_figureAssets[i] = chessboard.m_figureAssetsi[i];
}
