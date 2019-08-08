#include "manu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "two_player.h"
#include "one_player.h"

void Manu::update()
{
    drawButtons();
    clicketButton(selectButtons());
}

void Manu::drawButtons()
{
    sf::Font font;
    if (!font.loadFromFile("futura-normal_[allfont.de].ttf"))
    {
        std::cerr << "Error loading font\n";
    }
    sf::Text text;
    text.setFont(font);
    text.setString("PLAYER ONE:");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(105.f, 100.f));

    sf::Text text1;
    text1.setFont(font);
    text1.setString("PLAYER TWO:");
    text1.setCharacterSize(24);
    text1.setFillColor(sf::Color::Black);
    text1.setPosition(sf::Vector2f(105.f, 150.f));

    m_window.draw(m_rect[0]);
    m_window.draw(m_rect[1]);
    m_window.draw(text);
    m_window.draw(text1);
}

Manu::State Manu::selectButtons()
{
    sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);

    for (int i{0}; i < 2; ++i)
    {
        bool intersectY = (localPosition.y >= m_rect[i].getGlobalBounds().top &&
            localPosition.y <= m_rect[i].getGlobalBounds().top + m_rect[i].getGlobalBounds().height);

        bool intersectX = (localPosition.x >= m_rect[i].getGlobalBounds().left &&
            localPosition.x <= m_rect[i].getGlobalBounds().left + m_rect[i].getGlobalBounds().width);

        if (intersectY && intersectX)
        {
            m_rect[i].setOutlineColor(sf::Color::Magenta);
            m_rect[i].setOutlineThickness(3.f);
            if (i == 0)
                return ONE_PLAYER;
            else
                return TWO_PLAYER;
        }
        else
        {
            m_rect[i].setOutlineThickness(0);
        }
    }
    return MANU;
}

void Manu::clicketButton(Manu::State state)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_state = state;
    }
}

States* Manu::currentState(Manu *manu, TwoPlayer *twoPlayer, OnePlayer *onePlayer)
{
    switch (m_state)
    {
        case ONE_PLAYER:
            return onePlayer;
            break;
        case TWO_PLAYER:
            return twoPlayer;
            break;
        case MANU:
            return manu;
            break;
    }
}

Manu::Manu(sf::RenderWindow &window) : m_window(window)
{
    for (auto &rect : m_rect)
    {
        rect.setSize(sf::Vector2f(200.f, 30.f));
        rect.setFillColor(sf::Color::White);
    }
    m_rect[0].setPosition(sf::Vector2f(100.f, 100.f));
    m_rect[1].setPosition(sf::Vector2f(100.f, 150.f));
}
