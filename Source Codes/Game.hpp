#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "Board.hpp"
#include "Player.hpp"

class Game {
private:
    Board _board;
    Player _players[2];
    Player* _currentPlayer;

    int _Bscore, _Wscore;
    bool _finished;

    void handleCommand(const std::string& input);
    void nextTurn();
    void showCurrentTurn() const;
    void displayBoardState();
    void resetGame();
    void makeMove(const char& y, const int& x);
    void saveGame(const std::string& fname);
    void loadGame(const std::string& fname);
    bool hasValidMoves(Player* player);
    void undoLastMove();
    void redoLastMove();

public:
    Game();
    void run();
};

#endif // GAME_HPP
