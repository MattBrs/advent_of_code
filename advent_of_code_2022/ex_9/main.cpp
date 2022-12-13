#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

vector<string> split_string(string original_string, string separator);
void print_matrix(const vector<vector<bool>> &matrix);
int execute_moves(vector<vector<bool>> &matrix,
                  const vector<pair<string, int>> &moves);
void move_to(int &head_col, int &head_row, string direction);
void move_tail(const int &head_col, const int &head_row, int &tail_col,
               int &tail_row, const int &old_head_col, const int &old_head_row);

int main() {
  ifstream in("input.txt");
  vector<pair<string, int>> moves;
  int max_size = 0;

  while (!in.eof()) {
    string buffer;
    getline(in, buffer);

    vector<string> splitted_buffer = split_string(buffer, " ");
    moves.push_back({splitted_buffer[0], stoi(splitted_buffer[1])});
    max_size = max(max_size, stoi(splitted_buffer[1]) + 1);
  }

  vector<vector<bool>> visit_matrix(max_size * 100,
                                    vector<bool>(max_size * 100));
  // print_matrix(visit_matrix);

  cout << "moves: " << execute_moves(visit_matrix, moves) << endl;

  // print_matrix(visit_matrix);

  in.close();
  return 0;
}

vector<string> split_string(string original_string, string separator) {
  vector<string> splitted_string;
  int split_to = original_string.find(separator);

  if (separator == "" || split_to == -1) {
    splitted_string.push_back(original_string);
    return splitted_string;
  }

  while (original_string.size() > 0) {
    split_to = original_string.find(separator);

    if (split_to == -1) {
      splitted_string.push_back(original_string);
      return splitted_string;
    }

    string substr = original_string.substr(0, split_to);
    original_string.erase(0, split_to + 1);
    splitted_string.push_back(substr);
  }

  return splitted_string;
}

void print_matrix(const vector<vector<bool>> &matrix) {
  for (auto row : matrix) {
    for (auto item : row) {
      cout << item << " ";
    }

    cout << endl;
  }
}

int execute_moves(vector<vector<bool>> &matrix,
                  const vector<pair<string, int>> &moves) {

  int places_visited_count = 0;

  vector<pair<int, int>> rope_knots(10,
                                    {(matrix.size()) / 2, (matrix.size()) / 2});

  for (auto move : moves) {
    for (int i = 0; i < move.second; ++i) {

      vector<pair<int, int>> old_pos = rope_knots;
      int old_head_row = rope_knots[0].first;
      int old_head_col = rope_knots[0].second;

      move_to(rope_knots[0].second, rope_knots[0].first, move.first);

      for (int j = 0; j < rope_knots.size(); ++j) {

        move_tail(rope_knots[j].second, rope_knots[j].first,
                  rope_knots[j + 1].second, rope_knots[j + 1].first,
                  old_pos[j].second, old_pos[j].first);

        cout << "knot: " << j + 1 << " col: " << rope_knots[j + 1].second
             << "  row: " << rope_knots[j + 1].first << endl;
        if (!matrix[rope_knots[j + 1].first][rope_knots[j + 1].second]) {
          matrix[rope_knots[j + 1].first][rope_knots[j + 1].second] = true;
          places_visited_count++;
        }
      }
    }
  }

  return places_visited_count;
}

void move_tail(const int &head_col, const int &head_row, int &tail_col,
               int &tail_row, const int &old_head_col,
               const int &old_head_row) {
  // int distance = floor(
  //     sqrt(pow((head_col - tail_col), 2) + pow((head_row - tail_row), 2)));
  int distance_col = abs(head_col - tail_col);
  int distance_row = abs(head_row - tail_row);
  // cout << head_row << " " << head_col << endl;
  // cout << tail_row << " " << tail_col << endl;

  if (distance_col > 1 || distance_row > 1) {
    // cout << "entering" << endl;
    tail_row = old_head_row;
    tail_col = old_head_col;
  }
}

void move_to(int &head_col, int &head_row, string direction) {
  // to do
  if (direction == "R") {
    head_col++;
    return;
  }

  if (direction == "L") {
    head_col--;
    return;
  }

  if (direction == "U") {
    head_row--;
    return;
  }

  head_row++;
}
