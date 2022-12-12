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

  vector<vector<bool>> visit_matrix(max_size, vector<bool>(max_size));
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
  int head_row = matrix.size() - 1;
  int head_col = 0;
  int tail_row = head_row;
  int tail_col = head_col;

  for (auto move : moves) {
    // cout << matrix[tail_row][tail_col] << endl;
    // cout << tail_row << " " << tail_col << endl;
    for (int i = 0; i < move.second; ++i) {
      // cout << tail_row << " " << tail_col << endl;
      // print_matrix(matrix);
      // cout << "moving: " << move.first << endl;

      int old_head_row = head_row;
      int old_head_col = head_col;

      move_to(head_col, head_row, move.first);
      move_tail(head_col, head_row, tail_col, tail_row, old_head_col,
                old_head_row);

      if (!matrix[tail_row][tail_col]) {
        matrix[tail_row][tail_col] = true;
        places_visited_count++;
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
