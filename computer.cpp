#include "computer.h"
#include <iostream>
#include <random> // for std::mt19937
#include <ctime> // for std::time
namespace MyRandom1
{
	// Initialize our mersenne twister with a random seed based on the clock (once at system startup)
	std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
}

int Computer::getRandomNumber(int min, int max)
{
	std::uniform_int_distribution<> die(min, max); // we can create a distribution in any function that needs it
	return die(MyRandom1::mersenne); // and then generate a random number from our global generator
}

void Computer::setUpComputer(PlayByRules *playByRules, Chessboard *chessBoard, ChessGame *chessGame, bool whiteIsHuman)
{
    m_chessBoard = chessBoard;
    m_playByRules = playByRules;
    m_chessGame = chessGame;
    m_whiteIsHuman = whiteIsHuman;
}

bool Computer::computerPLay()
{
    Move move[200];
    Move move1;
    //move1 = playRandom(getAllPosMoves(move, m_chessBoard), m_chessBoard);
    //move1 = playWithEvaluation(m_chessBoard);
    move1 = playMinimax();

    if (move1.to == -1)
        return false;

    if (!m_chessGame->checkIfCheckmate(move1.to, *m_chessBoard))
        m_chessGame->checkIfMakingCheck(move1.to);
    else
        return true;

    return false;
}

Computer::Move* Computer::getAllPosMoves(Move *move, Chessboard *chessboard)
{
    PlayByRules playByRules(m_window);
    playByRules.setPlayByRulesPointer(chessboard);
    int index = 0;
    for (int i{0}; i < 64; ++i)
    {
        for (int j{0}; j < 64; ++j)
        {
            bool currentPlayed = chessboard->checkWhiteIsPlaying() == chessboard->getFigureAssets(i).white;
            if (chessboard->getFigureAssets(i).isOn && currentPlayed && playByRules.validMove(i, j) && !m_chessGame->checkIfGettingCheck(i, j, *chessboard, true))
            {
                move[index].from = i;
                move[index].to = j;
                index++;
            }
        }
    }

    for (int i{0}; i < 200; ++i)
        move[i].index = index;

    return move;
}

Computer::Move Computer::playRandom(Move *move, Chessboard *chessboard)
{
    if (move[0].index == 0)
    {
        Move move1;
        move1.from = -1;
        move1.to =  -1;

        return move1;
    }

    int randomNumber = getRandomNumber(0, move[0].index - 1);
    chessboard->playFromTo(move[randomNumber].from, move[randomNumber].to);

    Move move2;
    move2.from = move[randomNumber].from;
    move2.to =  move[randomNumber].to;

    return move2;

}

Computer::Computer(sf::RenderWindow &window) : m_window(window)
{

}

int Computer::evaluation(Chessboard *chessboard)
{
    int boardvalue = 0;
    for (int i{0}; i < 64; ++i)
    {
        if (chessboard->getFigureAssets(i).isOn)
        {
            if (chessboard->getFigureAssets(i).white != m_whiteIsHuman)
            {
                switch (chessboard->getFigureAssets(i).figure)
                {
                    case Chessboard::FARMER:
                        boardvalue += 10;
                        break;
                    case Chessboard::HORS:
                        boardvalue += 30;
                        break;
                    case Chessboard::RUNNER:
                        boardvalue += 30;
                        break;
                    case Chessboard::TOWER:
                        boardvalue += 50;
                        break;
                    case Chessboard::QUEEN:
                        boardvalue += 90;
                        break;
                }
            }
            else if (chessboard->getFigureAssets(i).white == m_whiteIsHuman)
            {
                switch (chessboard->getFigureAssets(i).figure)
                {
                    case Chessboard::FARMER:
                        boardvalue -= 10;
                        break;
                    case Chessboard::HORS:
                        boardvalue -= 30;
                        break;
                    case Chessboard::RUNNER:
                        boardvalue -= 30;
                        break;
                    case Chessboard::TOWER:
                        boardvalue -= 50;
                        break;
                    case Chessboard::QUEEN:
                        boardvalue -= 90;
                        break;
                }
            }
        }
    }

    return boardvalue;
}

Computer::Move Computer::playWithEvaluation(Chessboard *chessboard)
{
    Move move;
    int movePointsScore = evaluation(chessboard);
    int index = 0;
    Move moveArray[200];

    bool evaluationChangend = false;
    int lastEvalutaion = evaluation(chessboard);

    bool breakLoop = false;

    PlayByRules playByRules(m_window);
    playByRules.setPlayByRulesPointer(chessboard);

    for (int i{0}; i < 64; ++i)
    {
        if (breakLoop)
            break;

        for (int j{0}; j < 64; ++j)
        {
            bool currentPlayed = chessboard->checkWhiteIsPlaying() == chessboard->getFigureAssets(i).white;
            if (chessboard->getFigureAssets(i).isOn && currentPlayed && playByRules.validMove(i, j) && !m_chessGame->checkIfGettingCheck(i, j, *chessboard, true))
            {
                Chessboard newChessboard(*chessboard);
                newChessboard.playFromTo(i, j);

                if (m_chessGame->checkIfCheckmate(j, newChessboard))
                {
                    move.from = i;
                    move.to = j;

                    breakLoop = true;
                    evaluationChangend = true;
                    break;
                }

                int evaluationVar = evaluation(&newChessboard);
                if (evaluationVar > movePointsScore)
                {
                    move.from = i;
                    move.to = j;

                    movePointsScore = evaluationVar;
                }

                moveArray[index].from = i;
                moveArray[index].to = j;
                index++;

                if (lastEvalutaion != evaluationVar)
                {
                    evaluationChangend = true;
                }
                lastEvalutaion = evaluationVar;
            }

        }
    }

    for (int i{0}; i < 200; ++i)
        moveArray[i].index = index;

    if (index == 0)
    {
        move.from = -1;
        move.to = -1;
        return move;
    }

    if (!evaluationChangend)
    {
        Move move1;
        move1 = playRandom(moveArray, m_chessBoard);
        return move1;
    }

    m_chessBoard->playFromTo(move.from, move.to);
    return move;
}

Computer::Move Computer::playMinimax()
{
    int alpha = -9000;
    int beta = 9000;
    m_countMinimaxPos = 0;
    Move moves[200];
    int deph = 3;
    getAllPosMoves(moves, m_chessBoard);
    struct MovePlusValue
    {
        int from = -1;
        int to = -1;
        int posValue = -9000;
    };
    MovePlusValue movePlusValue[200];

    for (int i{0}; i < moves[0].index; ++i)
    {
        Chessboard newChessboard(*m_chessBoard);
        newChessboard.playFromTo(moves[i].from, moves[i].to);
        if (m_chessGame->checkIfCheckmate(moves[i].to, newChessboard, true))
        {
            Move move;
            move.from = moves[i].from;
            move.to = moves[i].to;
            return move;
        }
        movePlusValue[i].posValue = minimax(deph, 1, newChessboard, false, alpha, beta);
        if(movePlusValue[i].posValue > alpha)
            alpha = movePlusValue[i].posValue;

        movePlusValue[i].from = moves[i].from;
        movePlusValue[i].to = moves[i].to;
    }

    MovePlusValue bestMove;

    Move moveRandom;
    bool evaluationChangend = false;
    int lastEvalutaion = movePlusValue[0].posValue;

    for (int i{0}; i < moves[0].index; ++i)
    {
        if (movePlusValue[i].posValue > bestMove.posValue)
            bestMove = movePlusValue[i];

        if (lastEvalutaion != movePlusValue[i].posValue)
        {
            evaluationChangend = true;
        }
        lastEvalutaion = movePlusValue[i].posValue;
    }

    if (!evaluationChangend)
    {
        Move move1;
        move1 = playRandom(moves, m_chessBoard);
        return move1;
    }

    Move move;
    move.from = bestMove.from;
    move.to = bestMove.to;
    m_chessBoard->playFromTo(bestMove.from, bestMove.to);
    return move;
}

int Computer::minimax(int deph, int dephNumber, Chessboard &chessboard, bool computerIsPlaying, int alpha, int beta)
{
    std::cout << "Positions: " << m_countMinimaxPos++ << "\n";
    if (deph == dephNumber)
        return evaluation(&chessboard);

    chessboard.changeCurrentPlayed();

    Move moves[200];
    getAllPosMoves(moves, &chessboard);

    if (computerIsPlaying)
    {
        int max = -9000;
        for (int i{0}; i< moves[0].index; ++i)
        {
            Chessboard newChessboard(chessboard);
            newChessboard.playFromTo(moves[i].from, moves[i].to);
            if (m_chessGame->checkIfCheckmate(moves[i].to, newChessboard, true))
                return 900;
            int minimaxVar = minimax(deph, dephNumber + 1, newChessboard, !computerIsPlaying, alpha, beta);
            if (minimaxVar > max)
                max = minimaxVar;
            alpha = max;
            if (beta <= alpha)
                break;
        }
        return max;
    }
    else
    {
        int min = 9000;
        for (int i{0}; i < moves[0].index; ++i)
        {
            Chessboard newChessboard(chessboard);
            newChessboard.playFromTo(moves[i].from, moves[i].to);
            if (m_chessGame->checkIfCheckmate(moves[i].to, newChessboard, true))
                return -900;
            int minimaxVar = minimax(deph, dephNumber + 1, newChessboard, !computerIsPlaying, alpha, beta);
            if (minimaxVar < min)
                min = minimaxVar;
            beta = min;
            if (beta <= alpha)
                break;
        }
        return min;
    }
}
