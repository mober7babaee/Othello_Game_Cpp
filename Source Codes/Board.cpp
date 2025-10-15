#include "Board.hpp"
#include <stdexcept>

Board::Board() : _state(BOARD_SIZE, std::vector<char>(BOARD_SIZE, '.')) {}

void Board::reset() {
    for (auto& row : _state) {
        std::fill(row.begin(), row.end(), '.');
    }
    _state[3][3] = 'W';
    _state[3][4] = 'B';
    _state[4][3] = 'B';
    _state[4][4] = 'W';
}

void Board::display_board() const {
    std::cout << " ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << " " << COLUMN_LABELS[i];
    }
    std::cout << "\n";

    for (int r = 0; r < BOARD_SIZE; ++r) {
        std::cout << r + 1 << " ";
        for (int c = 0; c < BOARD_SIZE; ++c) {
            std::cout << _state[r][c] << " ";
        }
        std::cout << "\n";
    }
}

void Board::get_scores(int& black_score, int& white_score) const {
    black_score = white_score = 0;
    for (const auto& row : _state) {
        for (char cell : row) {
            if (cell == 'B') ++black_score;
            else if (cell == 'W') ++white_score;
        }
    }
}

bool Board::inside_bounds(const char& y, const int& x) const {
    return (y >= 'A' && y < COLUMN_LABELS[BOARD_SIZE] && x > 0 && x <= BOARD_SIZE);
}

bool Board::is_unoccupied(const char& y, const int& x) const {
    return _state[x - 1][y - 'A'] == '.';
}

void Board::place_piece(const char& y, const int& x, const char& color) {
    if (!inside_bounds(y, x)) {
        throw std::out_of_range("Invalid board coordinates");
    }
    else if (!is_unoccupied(y, x)) {
        throw std::invalid_argument("Cell already occupied");
    }
    else if (!valid_move(y, x, color)) {
        throw std::invalid_argument("Invalid move: no flips possible");
    }
    else {
    _undo.push(_state);
    int row = x - 1;
    int col = y - 'A';
    _state[row][col] = color;
    apply_flips(row, col, color);
    }
}



bool Board::valid_move(const char& y, const int& x, const char& color) const {
    if (!inside_bounds(y, x) || !is_unoccupied(y, x)) return false;

    char opponent = (color == 'B') ? 'W' : 'B';
    int row = x - 1, col = y - 'A';
    for (const auto& d : MOVE_DIRS) {
        int c_row = row + d[0], c_col = col + d[1];
        if (c_row < 0 || c_row >= BOARD_SIZE || c_col < 0 || c_col >= BOARD_SIZE) continue;
        if (_state[c_row][c_col] != opponent) continue;

        c_row += d[0]; c_col += d[1];
        while (c_row >= 0 && c_row < BOARD_SIZE && c_col >= 0 && c_col < BOARD_SIZE) {
            if (_state[c_row][c_col] == '.') break;
            if (_state[c_row][c_col] == color) return true;
            c_row += d[0]; c_col += d[1];
        }
    }
    return false;
}

void Board::apply_flips(const int& row, const int& col, const char& color) {
    char opponent = (color == 'B') ? 'W' : 'B';
    for (const auto& d : MOVE_DIRS) {
        int c_row = row + d[0], c_col = col + d[1];
        std::vector<std::pair<int,int>> flips;

        while (c_row >= 0 && c_row < BOARD_SIZE && c_col >= 0 && c_col < BOARD_SIZE) {
            if (_state[c_row][c_col] == '.') break;
            if (_state[c_row][c_col] == opponent) {
                flips.push_back(std::make_pair(c_row, c_col));
            }
            if (_state[c_row][c_col] == color) {
                for (auto& pos : flips) {
                    _state[pos.first][pos.second] = color;
                }
                break;
            }
            c_row += d[0]; c_col += d[1];
        }
    }
}

void Board::save_to_stream(std::ofstream& ofs) const {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            ofs << _state[i][j];
            if (j < BOARD_SIZE - 1) ofs << " ";
        }
        ofs << "\n";
    }
}

void Board::load_from_stream(std::ifstream& ifs) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (!(ifs >> _state[i][j])) {
                throw std::runtime_error("Failed to read board data");
            }
        }
    }
}

bool Board::undo() {
    if (_undo.empty()) return false;
    _redo.push(_state);
    _state = _undo.top();
    _undo.pop();
    return true;
}

bool Board::redo() {
    if (_redo.empty()) return false;
    _undo.push(_state);
    _state = _redo.top();
    _redo.pop();
    return true;
}
