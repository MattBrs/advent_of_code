/*
  given the enemy rock-paper-scissors choiches, calculate the total amount of
  points if you were to follow the guide (input). shapes points: rock -> 1,
  paper
  -> 2, scissors -> 3. round points: lost -> 0, draw -> 3, won -> 6
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  vector<pair<char, char>> guide_moves;

  ifstream in("input.txt");

  while (!in.eof()) {
    char enemy_move;
    char my_move;

    in >> enemy_move >> my_move;
    guide_moves.push_back({enemy_move, my_move});
  }

  guide_moves.pop_back();

  int total_points = 0;
  for (auto round_moves : guide_moves) {
    int my_move_points = ((int)round_moves.second) - 87; // range [1, 3]
    int enemy_move_points = ((int)round_moves.first) - 64;
    int round_points = my_move_points - enemy_move_points;

    cout << my_move_points << " - " << enemy_move_points << endl;

    if (round_moves.second == 'Y') { // draw
      my_move_points = enemy_move_points;
      round_points = 3;
    } else if (round_moves.second == 'X') { // lose
      my_move_points = enemy_move_points - 1;

      if (my_move_points < 1) {
        my_move_points = 3;
      }
      round_points = 0;
    } else { // win
      my_move_points = enemy_move_points + 1;

      if (my_move_points > 3) {
        my_move_points = 1;
      }

      round_points = 6;
    }

    cout << round_points << endl << "---------" << endl;

    total_points += my_move_points + round_points;
  }
  cout << total_points << endl;

  in.close();
  return 0;
}
