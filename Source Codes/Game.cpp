#include "Game.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

Game::Game()
    : _players{ Player('B'), Player('W') },
      _currentPlayer(&_players[0]),
      _Bscore{0},
      _Wscore{0},
      _finished{false} {
          _board.reset();
      }

void Game::nextTurn() {
    _currentPlayer = (_currentPlayer == &_players[0]) ? &_players[1] : &_players[0];
    if (!hasValidMoves(_currentPlayer)) {
        _currentPlayer = (_currentPlayer == &_players[0]) ? &_players[1] : &_players[0];
        if (!hasValidMoves(_currentPlayer)) {
            _finished = true;
        }
    }
}

void Game::showCurrentTurn() const {
    std::cout << "Player Turn: " << _currentPlayer->get_color() << std::endl;
}

void Game::displayBoardState() {
    _board.display_board();
    _board.get_scores(_Bscore, _Wscore);

    if (!_finished) {
        showCurrentTurn();
    }

    std::cout << "Score - B: "<< _Bscore
              << " | W: "<< _Wscore << std::endl;

    if (_finished) {
        if (_Bscore > _Wscore) std::cout << "Winner: Black\n";
        else if (_Wscore > _Wscore) std::cout << "Winner: White\n";
        else std::cout << "Game ended in a draw!\n";
    }
}

void Game::resetGame() {
    _board.reset();
    _currentPlayer = &_players[0];
    _finished = false;
    displayBoardState();
}

void Game::makeMove(const char& y, const int& x) {
    _board.place_piece(y, x, _currentPlayer->get_color());
    nextTurn();
    displayBoardState();
}

void Game::saveGame(const std::string& fname) {
    std::ofstream out("saved/" + fname);
    if (!out) throw std::runtime_error("Could not open file for saving.");
    _board.save_to_stream(out);
    out << _currentPlayer->get_color() << "\n";
    out.close();
}

void Game::loadGame(const std::string& fname) {
    std::ifstream in("saved/" + fname);
    if (!in) throw std::runtime_error("Could not open file for loading.");
    _board.load_from_stream(in);

    char playerCol;
    if (!(in >> playerCol) || (playerCol != 'B' && playerCol != 'W')) {
        throw std::invalid_argument("Corrupted save file.");
    }
    _currentPlayer = (playerCol == 'B') ? &_players[0] : &_players[1];
    in.close();

    if (!hasValidMoves(_currentPlayer)) {
        _currentPlayer = (_currentPlayer == &_players[0]) ? &_players[1] : &_players[0];
        if (!hasValidMoves(_currentPlayer)) {
            _finished = true;
        }
    }
    displayBoardState();
}

bool Game::hasValidMoves(Player* player) {
    for (char y = 'A'; y< COLUMN_LABELS[BOARD_SIZE]; ++y) {
        for (int x = 1; x <= BOARD_SIZE; ++x) {
            if (_board.valid_move(y, x, player->get_color())) {
                return true;
            }
        }
    }
    return false;
}

void Game::undoLastMove() {
    if (_board.undo()) {
        nextTurn();
        displayBoardState();
    }
}

void Game::redoLastMove() {
    if (_board.redo()) {
        nextTurn();
        displayBoardState();
    }
}

void Game::handleCommand(const std::string& input_line) {
        std::istringstream iss(input_line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "new") {
            if (iss >> cmd) throw std::invalid_argument("Unexpected arguments.");
            resetGame();
        }

        else if (cmd == "place") {
            std::string token;
            if (!(iss >> token) || token.length() != 2 || (iss >> cmd))
                throw std::invalid_argument("Expected: place [Column][Row]");
            char y = std::toupper(token[0]);
            int x = token[1] - '0';
            makeMove(y, x);
        }

        else if (cmd == "save") {
            std::string filename;
            if (iss >> filename && !(iss >> cmd)) {
                if (!valid_savefile_name(filename)) throw std::invalid_argument("Use .oth extension.");
                saveGame(filename);
            } else {
                throw std::invalid_argument("Expected: save filename.oth");
            }
        }

        else if (cmd == "load") {
            std::string filename;
            if (iss >> filename && !(iss >> cmd)) {
                if (!valid_savefile_name(filename)) throw std::invalid_argument("Use .oth extension.");
                loadGame(filename);
            } else {
                throw std::invalid_argument("Expected: load filename.oth");
            }
        }
       else if (cmd == "undo") {
            if (iss >> cmd) {
                    throw std::invalid_argument("Invalid input format.");
            }
            undoLastMove();
        }
       else if (cmd == "redo") {
            if (iss >> cmd) {
                    throw std::invalid_argument("Invalid input format.");
            }
            redoLastMove();
        }
        else if (cmd == "exit") {
            if (iss >> cmd) throw std::invalid_argument("Unexpected arguments after exit.");
            std::exit(0);
        }

        else {
            throw std::invalid_argument("Unknown command: " + cmd);
        }

}


void Game::run() {
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        try {
            handleCommand(line);
        } catch (const std::exception& e) {
            std::cerr << COLOR_RED << e.what() << COLOR_RESET << std::endl;
            displayBoardState();
        }
    }
}
