#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

/// Board size (classic Othello)
constexpr int BOARD_SIZE = 8;

/// ANSI color codes (optional, for styling)
#define COLOR_RED "\033[31m"
#define COLOR_RESET "\033[0m"

/// Column labels (A–Z, but we only use A–H)
static const char COLUMN_LABELS[26] = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

/// Directions for flipping (8 neighbors)
static const int MOVE_DIRS[8][2] = {
    {-1,-1}, {-1,0}, {-1,1},
    {0,-1},          {0,1},
    {1,-1},  {1,0},  {1,1}
};

/// Quick filename check (must end with .oth)
inline bool valid_savefile_name(const std::string& filename) {
    return filename.size() > 4 &&
           filename.substr(filename.find_last_of('.') + 1) == "oth";
}

class Board {
 private:
  using Grid = std::vector<std::vector<char>>;
  Grid _state;
  std::stack<Grid> _undo;
  std::stack<Grid> _redo;

  bool inside_bounds(const char& y, const int& x) const;
  bool is_unoccupied(const char& y, const int& x) const;

 public:
  Board();

  void reset();
  void display_board() const;
  void get_scores(int& black_score, int& white_score) const;
  void place_piece(const char& y, const int& x, const char& color);
  bool valid_move(const char& y, const int& x, const char& color) const;
  void apply_flips(const int& row, const int& col, const char& color);
  void save_to_stream(std::ofstream& ofs) const;
  void load_from_stream(std::ifstream& ifs);
  bool undo();
  bool redo();
};

#endif  // __BOARD_HPP__

