#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void read_crates_from_string(vector<pair<string, int>> &crates,
                             int &current_line_crate_count, string buffer);
void read_moves_from_string(string buffer);
void put_crates_on_stacks(const vector<pair<string, int>> &crates,
                          vector<stack<string>> &crate_stacks);
void change_crate_stack(const int &crates_to_move, const int &starting_stack,
                        const int &arriving_stack,
                        vector<stack<string>> &crate_stacks);
void read_top_crates(const vector<stack<string>> crate_stacks);
void read_stack(stack<string> stack_to_read) {
  while (!stack_to_read.empty()) {
    cout << stack_to_read.top() << "  ";
    stack_to_read.pop();
  }

  cout << endl;
}

int main(int argc, char const *argv[]) {
  ifstream in("input.txt");
  vector<pair<string, int>> crates;
  int stack_count = 0;

  bool is_crate_row = true;
  while (!in.eof() &&
         is_crate_row) { // stop reading crates if cannot find anymore
    string buffer;
    int current_line_crate_count = 0;

    getline(in, buffer);

    is_crate_row = buffer.find("[") != -1;

    if (is_crate_row) {
      read_crates_from_string(
          crates, current_line_crate_count,
          buffer); // if there is a crate in the string, read.
      stack_count = max(stack_count, current_line_crate_count);
      continue;
    }
  }

  vector<stack<string>> crate_stacks(stack_count + 1);
  put_crates_on_stacks(crates, crate_stacks);

  while (!in.eof()) {
    string buffer;

    int crates_to_move_count;
    int starting_stack;
    int arriving_stack;

    in >> buffer;
    in >> buffer;

    if (buffer == "") {
      break;
    }

    crates_to_move_count = stoi(buffer);

    in >> buffer;
    in >> buffer;
    starting_stack = stoi(buffer) - 1;

    in >> buffer;
    in >> buffer;
    arriving_stack = stoi(buffer) - 1;
    change_crate_stack(crates_to_move_count, starting_stack, arriving_stack,
                       crate_stacks);
  }
  read_top_crates(crate_stacks);
  in.close();
  return 0;
}

void read_crates_from_string(vector<pair<string, int>> &crates,
                             int &current_line_crate_count, string buffer) {
  while (buffer.size() > 0) {
    int distance = buffer.find("[");

    if (distance == -1) {
      break;
    }
    string current_crate = buffer.substr(distance, distance + 3);
    buffer.erase(0, distance + 4);

    if (current_crate.size() > 4) {
      current_crate = current_crate.erase(0, current_crate.find("["));
      current_crate = current_crate.erase(current_crate.find(']') + 1,
                                          current_crate.size());
    }

    current_line_crate_count += (distance / 4);

    int crate_stacks_position = current_line_crate_count;
    crates.push_back({current_crate, crate_stacks_position});
    current_line_crate_count++;
  }
}

void read_moves_from_string(string buffer) {
  while (buffer.size() > 0) {
  }
}

void put_crates_on_stacks(const vector<pair<string, int>> &crates,
                          vector<stack<string>> &crate_stacks) {
  for (int i = crates.size() - 1; i >= 0; i--) {
    crate_stacks[crates[i].second].push(crates[i].first);
  }
}

void change_crate_stack(const int &crates_to_move, const int &starting_stack,
                        const int &arriving_stack,
                        vector<stack<string>> &crate_stacks) {
  stack<string> moved_crates;

  for (int i = 0; i < crates_to_move; i++) {
    moved_crates.push(crate_stacks[starting_stack].top());

    crate_stacks[starting_stack].pop();
  }

  while (!moved_crates.empty()) {
    crate_stacks[arriving_stack].push(moved_crates.top());
    moved_crates.pop();
  }
}

void read_top_crates(const vector<stack<string>> crate_stacks) {
  for (auto item : crate_stacks) {
    if (!item.empty()) {
      cout << item.top() << " ";
    }
  }

  cout << endl;
}
