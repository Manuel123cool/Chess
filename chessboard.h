#pragma once
#include <SFML/Graphics.hpp>

class Chessboard
{
public:
    enum Figures
    {
        KING,
        QUEEN,
        RUNNER,
        HORS,
        TOWER,
        FARMER
    };
    struct KingOrTowerWasPlayed
    {
        bool blackKingMoved = false;
        bool whiteKingMoved = false;
        bool leftWhiteTowerMoved = false;
        bool rightWhiteTowerMoved = false;
        bool leftBlackTowerMoved = false;
        bool rightBlackTowerMoved = false;
    };
private:
    struct FigureAssets
    {
        Figures figure;
        bool white;
        bool rotateToUp = false;
        bool isOn = false;
    };
    bool m_whiteIsPlaying = true;
    FigureAssets m_figureAssets[64];
    void drawChessBoard();
    void drawChessFigure(int x, int y, Figures figures, bool white, bool rotateToUp);
    void drawChessFigures();
    int getRandomNumber(int min, int max);
    sf::RectangleShape m_rect[64];
    sf::RenderWindow &m_window;
    sf::Texture m_texture;
    void setChessFigure(int pos, Figures figures, bool white, bool rotateToUp);
    bool m_currentPlayerIsUp = false;
    KingOrTowerWasPlayed m_kingOrTowerWasPlayed;
protected:
    void deleteChessFigure(int pos);
    void setUpChessFigures(bool restart = false);
    void updateChessboard();
public:
    KingOrTowerWasPlayed getKingOrTowerWasPlayed();
    void setChessBoardToDefault();
    bool getCurrentPlayerIsUp();
    void changeCurrentPlayed();
    void rotateBoard();
    void playFromTo(int from, int to);
    Chessboard(sf::RenderWindow &window);
    Chessboard(const Chessboard &chessboard, sf::RenderWindow &window);
    sf::FloatRect getGlobalBounds(int index);
    FigureAssets getFigureAssets(int index);
    bool checkWhiteIsPlaying();
};
