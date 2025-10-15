#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <utility>  // for std::pair

class Player {
 private:
  char _color;  // 'B' or 'W'
  std::vector<std::pair<char, int>> _valid_moves;  // stores possible moves

 public:
  Player(const char& color);
  char get_color() const;
};

#endif // PLAYER_HPP

