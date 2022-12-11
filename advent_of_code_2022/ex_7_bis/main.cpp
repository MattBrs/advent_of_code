#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

vector<string> split_string(string original_string, string delimiter);
void print_vect(const vector<string> vector_to_print) {
  for (auto item : vector_to_print) {
    cout << item << " ";
  }

  cout << endl;
}
void empty_stack_and_update_directories(
    stack<string> &directory_stack, map<string, long long> &directories_info);
void go_back_one_dir_and_update(stack<string> &directory_stack,
                                map<string, long long> &directories_info);
void read_stack(stack<string> dir_stack) {
  while (!dir_stack.empty()) {
    cout << dir_stack.top() << " ";
    dir_stack.pop();
  }

  cout << endl;
}

string make_padding(int size) {
  string to_return("");

  for (int i = 0; i < size; i++) {
    to_return += " ";
  }

  return to_return;
}

int main() {
  ifstream in("input.txt");
  stack<string> directory_stack = {};
  map<string, long long> directories_info;

  long long max_size_counter = 0;
  long long current_folder_counter = 0;

  while (!in.eof()) {
    string buffer;
    getline(in, buffer);

    if (buffer == "") {
      break;
    }

    vector<string> splitted_buffer = split_string(buffer, " ");

    if (splitted_buffer[1] == "ls" || splitted_buffer[0] == "dir") {
      continue;
    }

    if (splitted_buffer[1] == "cd") {

      if (current_folder_counter > 0) {
        directories_info[directory_stack.top()] = current_folder_counter;
        current_folder_counter = 0;
      }

      if (splitted_buffer[2] == "..") {
        go_back_one_dir_and_update(directory_stack, directories_info);
        continue;
      }

      if (splitted_buffer[2] == "/") {

        empty_stack_and_update_directories(directory_stack, directories_info);
        directory_stack = {};
        directory_stack.push("/");
        continue;
      }

      directories_info[splitted_buffer[2]] = 0;
      directory_stack.push(splitted_buffer[2]);
      continue;
    }

    long long file_size = stoi(splitted_buffer[0]);
    // cout << "current folder: " << directory_stack.top() << endl;
    cout << make_padding(directory_stack.size() * 2)
         << "file: " << splitted_buffer[1] << endl;
    current_folder_counter += file_size;
    // cout << "folder size: " << current_folder_counter << endl;
    // cout << "-----------------" << endl;
  }

  if (current_folder_counter > 0) {
    directories_info[directory_stack.top()] = current_folder_counter;
    current_folder_counter = 0;
  }

  for (auto item : directories_info) {
    cout << item.first << " -> " << item.second << endl;
    if (item.second <= 100000) {
      max_size_counter += item.second;
    }
  }

  cout << max_size_counter << endl;
  in.close();
  return 0;
}

vector<string> split_string(string original_string, string delimiter) {
  vector<string> to_return;
  int trim_index = original_string.find(delimiter);

  if (delimiter == "" || trim_index == -1) {
    to_return.push_back(original_string);
    return to_return;
  }

  while (original_string.size() > 0) {
    trim_index = original_string.find(delimiter);

    if (trim_index == -1) {
      to_return.push_back(original_string);
      break;
    }

    string substr = original_string.substr(0, trim_index);
    original_string.erase(0, trim_index + 1);
    to_return.push_back(substr);
  }

  return to_return;
}

void empty_stack_and_update_directories(
    stack<string> &directory_stack, map<string, long long> &directories_info) {
  while (!directory_stack.empty() && directory_stack.top() != "/") {
    go_back_one_dir_and_update(directory_stack, directories_info);
  }
}

void go_back_one_dir_and_update(stack<string> &directory_stack,
                                map<string, long long> &directories_info) {
  string last_folder = directory_stack.top();
  directory_stack.pop();
  directories_info[directory_stack.top()] += directories_info[last_folder];
}
