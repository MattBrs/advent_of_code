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
    stack<string> &directory_stack, map<string, long long> &directories_info,
    string &current_path);
void go_back_one_dir_and_update(stack<string> &directory_stack,
                                map<string, long long> &directories_info,
                                string &current_path);
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

long long count_root_size(const map<string, long long> directory_info) {
  long long count = 0;
  for (auto item : directory_info) {
    if (item.first.find("/", 1) == string::npos && item.first.size() > 1) {
      cout << "counting: " << item.first << " " << item.second << endl;
      count += item.second;
    }
  }

  return count;
}

int main() {
  ifstream in("input.txt");
  stack<string> directory_stack = {};
  map<string, long long> directories_info;
  string current_path = "";
  directories_info["/"] = 0;
  long long max_size_counter = 0;
  long long current_folder_counter = 0;
  const long long MAX_SIZE = 70000000;
  const long long MINIMUM_SIZE = 30000000;
  long long root_file_size = 0;

  while (!in.eof()) {
    string buffer;
    getline(in, buffer);

    // cout << current_path << endl;

    if (buffer == "") {
      break;
    }

    vector<string> splitted_buffer = split_string(buffer, " ");

    if (splitted_buffer[1] == "ls" || splitted_buffer[0] == "dir") {
      continue;
    }

    if (splitted_buffer[1] == "cd") {

      if (current_folder_counter > 0) {
        // cout << "checking if " << directory_stack.top() << " is present"
        //      << endl;
        //
        // cout << directories_info.count(directory_stack.top()) << endl;
        if (current_path == "/") {
          root_file_size = current_folder_counter;
        }

        directories_info[current_path] = current_folder_counter;
        current_folder_counter = 0;
      }

      if (splitted_buffer[2] == "..") {

        go_back_one_dir_and_update(directory_stack, directories_info,
                                   current_path);

        continue;
      }

      if (splitted_buffer[2] == "/") {

        // empty_stack_and_update_directories(directory_stack, directories_info,
        // current_path);
        current_path = "/";
        directory_stack = {};
        directory_stack.push("/");
        continue;
      }

      directory_stack.push(splitted_buffer[2]);
      if (current_path != "/") {
        current_path += "/";
      }

      current_path += splitted_buffer[2];
      directories_info[current_path] = 0;
      continue;
    }

    long long file_size = stoll(splitted_buffer[0]);
    current_folder_counter += file_size;
  }

  if (current_folder_counter > 0) {
    directories_info[directory_stack.top()] = current_folder_counter;
    current_folder_counter = 0;
  }
  go_back_one_dir_and_update(directory_stack, directories_info, current_path);
  //  empty_stack_and_update_directories(directory_stack, directories_info,
  //                                     current_path);
  //  cout << directories_info["/"] << endl;

  long long size_to_free =
      MINIMUM_SIZE -
      (MAX_SIZE - (count_root_size(directories_info) + root_file_size));
  long long found_size = MAX_SIZE;

  for (auto item : directories_info) {
    cout << item.first << " -> " << item.second << endl;
    if (item.second >= size_to_free) {
      found_size = min(found_size, item.second);
    }
  }

  cout << "root size: " << count_root_size(directories_info) + root_file_size
       << endl;
  cout << size_to_free << endl;
  cout << found_size << endl;
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
    stack<string> &directory_stack, map<string, long long> &directories_info,
    string &current_path) {
  while (!directory_stack.empty() && directory_stack.top() != "/") {
    go_back_one_dir_and_update(directory_stack, directories_info, current_path);
  }
}

void go_back_one_dir_and_update(stack<string> &directory_stack,
                                map<string, long long> &directories_info,
                                string &current_path) {
  string last_folder = current_path;

  int index = current_path.size() - directory_stack.top().size();
  index = index - 1 == 0 ? index : index - 1;

  current_path.erase(index);
  cout << "returning to:" << current_path << "  from: " << last_folder << endl;
  directory_stack.pop();

  directories_info[current_path] += directories_info[last_folder];
}
