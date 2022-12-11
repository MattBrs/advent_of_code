#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
  Node *parent;
  string name;
  int size;
  vector<Node *> children;
  bool is_folder;
};

typedef Node *tree;

tree init_tree();
tree find_node(const tree &root, string node_name);
tree find_node(const tree &root, tree node);
void insert_children(tree &root, const tree &children, const tree &parent);
tree execute_command(istream &in, tree &root, tree &curr_pos);
int calc_folders_size(tree &root);
int calc_sum_folder_size(tree &root, int &total_size);
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

int main() {
  ifstream in("input.txt");
  tree root = init_tree();
  tree curr_pos = root;

  while (!in.eof()) {
    string buffer;

    getline(in, buffer);

    if (buffer == "") {
      break;
    }

    vector<string> splitted_buffer = split_string(buffer, " ");

    if (splitted_buffer[1] == "cd") {
      // curr_pos = execute_command(in, root, curr_pos);
      cout << "bout to jump" << endl;
      if (splitted_buffer[2] == "/") {
        cout << "returning to root" << endl;
        curr_pos = root;
        continue;
      }

      if (splitted_buffer[2] == "..") {
        cout << "going up one" << endl;
        cout << "parent: " << curr_pos->parent->name;
        curr_pos = curr_pos->parent;
        continue;
      }

      cout << "finding: " << buffer << endl;
      tree node_found = find_node(root, buffer);
      cout << "going to: " << node_found->name << endl;

      curr_pos = node_found;
      continue;
    }

    if (splitted_buffer[1] == "ls") {
      getline(in, buffer);
      streampos old_pos = in.tellg();

      splitted_buffer = split_string(buffer, " ");

      while (splitted_buffer[0] != "$" && !in.eof()) {
        tree new_child = new Node;

        if (splitted_buffer[0] == "dir") {
          cout << splitted_buffer[1] << " is direcory" << endl;
          new_child->name = splitted_buffer[1];
          new_child->is_folder = true;
        } else {
          cout << "about to convert: " << splitted_buffer[0];
          new_child->size = stoi(splitted_buffer[0]);
          new_child->name = splitted_buffer[1];
          cout << "  size of file: " << splitted_buffer[1] << endl;
          new_child->parent = curr_pos;
          new_child->is_folder = false;
        }
        insert_children(curr_pos, new_child, curr_pos);
        // here i have a file
        old_pos = in.tellg();
        getline(in, buffer);
        splitted_buffer = split_string(buffer, " ");
      }

      in.seekg(old_pos);
      continue;
    }
  }

  calc_folders_size(root);

  int total_sum = 0;
  calc_sum_folder_size(root, total_sum);
  cout << "total sum: " << total_sum << endl;
  in.close();
  return 0;
}

tree execute_command(istream &in, tree &root, tree &curr_pos) {
  string buffer;
  in >> buffer;
  cout << "executing command" << endl;
  // ls command
  if (buffer.find("cd") == -1) {
    in >> buffer;
    streampos old_pos = in.tellg();

    while (buffer.find("$") == -1 && !in.eof()) {
      tree new_child = new Node;

      if (buffer.find("dir") != -1) {
        in >> buffer;
        cout << buffer << " is direcory" << endl;
        new_child->name = buffer;
        new_child->is_folder = true;
      } else {
        cout << "about to convert: " << buffer;
        new_child->size = stoi(buffer);
        in >> buffer;
        new_child->name = buffer;
        cout << "  size of file: " << buffer << endl;
        new_child->parent = curr_pos;
        new_child->is_folder = false;
      }
      insert_children(curr_pos, new_child, curr_pos);
      // here i have a file
      old_pos = in.tellg();
      in >> buffer;
    }

    in.seekg(old_pos);
    return curr_pos;
  }

  // cd command
  in >> buffer;
  cout << "bout to jump" << endl;
  if (buffer.compare("/") == 0) {
    cout << "returning to root" << endl;
    return root;
  }

  if (buffer.compare("..") == 0) {
    cout << "going up one" << endl;
    cout << "parent: " << curr_pos->parent->name;
    return curr_pos->parent;
  }

  cout << "finding: " << buffer << endl;
  tree node_found = find_node(root, buffer);
  cout << "going to: " << node_found->name << endl;

  return find_node(root, buffer);
}

void insert_children(tree &root, const tree &children, const tree &parent) {
  if (root == nullptr) {
    return;
  }

  tree found_parent = find_node(root, parent);

  if (found_parent != nullptr) {
    children->parent = found_parent;
    found_parent->children.push_back(children);
  }
}

tree find_node(const tree &root, tree node) {
  if (root == nullptr) {
    return nullptr;
  }

  if (root->name.compare(node->name) == 0) {
    return root;
  }

  for (auto tree_node : root->children) {
    tree found_node = find_node(tree_node, node);

    if (found_node != nullptr && found_node->name.compare(node->name) == 0) {
      return found_node;
    }
  }

  return nullptr;
}

tree find_node(const tree &root, string node_name) {
  cout << "im: " << root->name << endl;
  if (root == nullptr) {
    return nullptr;
  }

  cout << "wasnt null!" << endl;
  if (root->name.compare(node_name) == 0) {
    return root;
  }

  cout << "didnt found!" << endl;

  if (!root->is_folder) {
    return nullptr;
  }

  for (auto tree_node : root->children) {
    if (tree_node == nullptr || !tree_node->is_folder) {
      continue;
    }
    cout << "bout to find from: " << tree_node->name << endl;
    tree found_node = find_node(tree_node, node_name);
    cout << "found node: " << found_node->name << endl;
    if (found_node != nullptr && found_node->name.compare(node_name) == 0) {
      return found_node;
    }
  }

  return nullptr;
}

tree init_tree() {
  Node *new_node = new Node;
  new_node->parent = nullptr;
  new_node->name = "/";
  new_node->size = 0;
  new_node->is_folder = true;

  return new_node;
}

int calc_folders_size(tree &root) {
  if (root == nullptr) {
    return 0;
  }

  if (root->children.size() == 0) {
    return root->size;
  }

  for (auto child : root->children) {
    root->size += calc_folders_size(child);
  }

  return root->size;
}

int calc_sum_folder_size(tree &root, int &total_size) {
  if (root == nullptr) {
    return 0;
  }

  if (!root->is_folder) {
    return 0;
  }

  if (root->is_folder && root->size < 100000) {
    total_size += root->size;
  }

  for (auto node : root->children) {
    cout << "current file name and size: " << node->name << "  " << node->size
         << endl;
    calc_sum_folder_size(node, total_size);
  }

  return total_size;
}
