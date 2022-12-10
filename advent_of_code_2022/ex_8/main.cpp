#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void print_matrix(const vector<vector<int>> &matrix);
int count_visible_trees(const vector<vector<int>> &tree_grid,
                        int &max_tree_score);
bool check_visible_from_top(const vector<vector<int>> &tree_grid,
                            const int &curr_height, const int &curr_col,
                            const int &curr_row, int &visible_trees);

bool check_visible_from_bottom(const vector<vector<int>> &tree_grid,
                               const int &curr_height, const int &curr_col,
                               const int &curr_row, int &visible_trees);

bool check_visible_from_left(const vector<vector<int>> &tree_grid,
                             const int &curr_height, const int &curr_col,
                             const int &curr_row, int &visible_trees);

bool check_visible_from_right(const vector<vector<int>> &tree_grid,
                              const int &curr_height, const int &curr_col,
                              const int &curr_row, int &visible_trees);

bool is_visible(const vector<vector<int>> &tree_grid, const int &curr_height,
                const int &curr_col, const int &curr_row,
                int &visible_tree_score);

int main() {
  ifstream in("input.txt");

  vector<vector<int>> tree_grid;
  while (!in.eof()) {

    string buffer;

    in >> buffer;

    if (tree_grid.size() < buffer.size()) {
      tree_grid.resize(buffer.size());
    }

    for (int i = 0; i < buffer.size(); i++) {
      tree_grid[i].push_back(buffer[i] - '0');
    }
  }

  int max_tree_score = 0;
  cout << "visible trees: " << count_visible_trees(tree_grid, max_tree_score)
       << endl;
  cout << "max tree score: " << max_tree_score << endl;

  in.close();
  return 0;
}

void print_matrix(const vector<vector<int>> &matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      cout << matrix[j][i] << " ";
    }

    cout << endl;
  }
}

int count_visible_trees(const vector<vector<int>> &tree_grid,
                        int &max_tree_score) {
  int visible_trees = 0;

  for (int i = 1; i < tree_grid.size() - 1; i++) {
    for (int j = 1; j < tree_grid[i].size() - 1; j++) {
      int curr_value = tree_grid[j][i];
      int local_tree_score = 0;

      if (is_visible(tree_grid, curr_value, j, i, local_tree_score)) {
        max_tree_score = max(max_tree_score, local_tree_score);
        visible_trees++;
      }
    }
  }

  return visible_trees + ((tree_grid.size() - 1) * 4);
}

bool check_visible_from_right(const vector<vector<int>> &tree_grid,
                              const int &curr_height, const int &curr_col,
                              const int &curr_row, int &visible_trees) {
  for (int i = curr_col + 1; i < tree_grid.size(); i++) {
    visible_trees++;

    if (tree_grid[i][curr_row] >= curr_height) {
      return false;
    }
  }

  return true;
}

bool check_visible_from_left(const vector<vector<int>> &tree_grid,
                             const int &curr_height, const int &curr_col,
                             const int &curr_row, int &visible_trees) {
  for (int i = curr_col - 1; i >= 0; i--) {
    visible_trees++;

    if (tree_grid[i][curr_row] >= curr_height) {
      return false;
    }
  }

  return true;
}

bool check_visible_from_bottom(const vector<vector<int>> &tree_grid,
                               const int &curr_height, const int &curr_col,
                               const int &curr_row, int &visible_trees) {
  for (int i = curr_row + 1; i < tree_grid.size(); i++) {
    visible_trees++;

    if (tree_grid[curr_col][i] >= curr_height) {
      return false;
    }
  }

  return true;
}

bool check_visible_from_top(const vector<vector<int>> &tree_grid,
                            const int &curr_height, const int &curr_col,
                            const int &curr_row, int &visible_trees) {
  for (int i = curr_row - 1; i >= 0; i--) {
    visible_trees++;

    if (tree_grid[curr_col][i] >= curr_height) {
      return false;
    }
  }
  return true;
}

bool is_visible(const vector<vector<int>> &tree_grid, const int &curr_height,
                const int &curr_col, const int &curr_row,
                int &visible_tree_score) {

  int visible_trees_top = 0;
  int visible_trees_bottom = 0;
  int visible_trees_right = 0;
  int visible_trees_left = 0;
  bool visible_from_top = check_visible_from_top(
      tree_grid, curr_height, curr_col, curr_row, visible_trees_top);

  bool visible_from_bottom = check_visible_from_bottom(
      tree_grid, curr_height, curr_col, curr_row, visible_trees_bottom);
  bool visible_from_right = check_visible_from_right(
      tree_grid, curr_height, curr_col, curr_row, visible_trees_right);
  bool visible_from_left = check_visible_from_left(
      tree_grid, curr_height, curr_col, curr_row, visible_trees_left);

  visible_tree_score = visible_trees_top * visible_trees_bottom *
                       visible_trees_left * visible_trees_right;

  return (visible_from_top || visible_from_bottom || visible_from_right ||
          visible_from_left);
}
