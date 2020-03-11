#include "one_player.h"
#include "manu.h"
#include "chessboard.h"
#include "chess_game.h"
#include "one_player.h"

class States;

void OnePlayer::update()
{
    if (m_once)
    {
        setUpChessFigures();
        m_once = false;
        whiteIsHuman = checkWhiteIsPlaying();
        if (!whiteIsHuman)
            changeCurrentPlayed();
    }
    updateChessboard();

    setUserInputPointers(this, this);
    setPlayByRulesPointer(this);
    setUpComputer(this, this, this, whiteIsHuman);

    if (drawAndCheckRestartGame())
    {
        whiteIsHuman = !whiteIsHuman;
        if (!whiteIsHuman)
            changeCurrentPlayed();

        gameOver = false;
    }

    drawPossibleMoves(true, whiteIsHuman);

    ClicketPos clicketPos;
    clicketPos = getUserInupt();

    if (clicketPos.on && validMove(clicketPos.pos1, clicketPos.pos2) &&
        !checkIfGettingCheck(clicketPos.pos1, clicketPos.pos2, *this) && checkWhiteIsPlaying() == whiteIsHuman && !gameOver)
    {
        m_state = "";

        playFromTo(clicketPos.pos1, clicketPos.pos2);

        if (!checkIfCheckmate(clicketPos.pos2, *this))
            checkIfMakingCheck(clicketPos.pos2);
        else
            gameOver = true;

        changeCurrentPlayed();
    }

    if (checkWhiteIsPlaying() != whiteIsHuman && !gameOver)
    {
        m_state = "";

        if (computerPLay())
            gameOver = true;

        changeCurrentPlayed();
    }

    drawState(m_state);
}

States* OnePlayer::currentState(Manu *manu, TwoPlayer *twoPlayer, OnePlayer *onePlayer)
{
    if (backToManu())
        return manu;
    return onePlayer;
}

bool OnePlayer::backToManu()
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(100.f, 20.f));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(sf::Vector2f(0.f, 0.f));

    sf::Text text1;
    text1.setFont(m_font);
    text1.setString("Manu:");
    text1.setCharacterSize(18);
    text1.setFillColor(sf::Color::Black);
    text1.setPosition(sf::Vector2f(5.f, 0.f));

    sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);

    bool intersectY = (localPosition.y >= rect.getGlobalBounds().top &&
        localPosition.y <= rect.getGlobalBounds().top + rect.getGlobalBounds().height);

    bool intersectX = (localPosition.x >= rect.getGlobalBounds().left &&
        localPosition.x <= rect.getGlobalBounds().left + rect.getGlobalBounds().width);

    bool manu = false;
    if (intersectY && intersectX)
    {
        rect.setOutlineColor(sf::Color::Magenta);
        rect.setOutlineThickness(3.f);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            manu = true;
        }
    }
    else
    {
        rect.setOutlineThickness(0);
    }
    m_window.draw(rect);
    m_window.draw(text1);
    return manu;
}

OnePlayer::OnePlayer(sf::RenderWindow &window) : m_window(window), ChessGame(window), Computer(window)
{
    if (!m_font.loadFromFile("futura-normal_[allfont.de].ttf"))
    {
        std::cerr << "Error loading font\n";
    }
}

