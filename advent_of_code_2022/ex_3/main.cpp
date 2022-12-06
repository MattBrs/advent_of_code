#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

string get_common_letters(string first_string, string second_string);
string get_common_letters(string first_string, string second_string, string third_string);
string remove_duplicates(string original_string);
int calculate_priority(string common_items);

int main () {
  vector<vector<string>> rucksack_list;
  string common_letters ("");

  ifstream in ("input.txt");
  
  while (!in.eof()) {
    vector<string> elf_group_rucksacks;
    string first_buffer;
    string second_buffer;
    string third_buffer;

    in >> first_buffer >> second_buffer >> third_buffer;
    elf_group_rucksacks.push_back(first_buffer);
    elf_group_rucksacks.push_back(second_buffer);
    elf_group_rucksacks.push_back(third_buffer);

    rucksack_list.push_back(elf_group_rucksacks);
  }

  for (auto group_rucksacs: rucksack_list) {
    common_letters += get_common_letters(group_rucksacs.at(0), group_rucksacs.at(1), group_rucksacs.at(2));
  }
  
  cout << "Priority: " << calculate_priority(common_letters) << endl;
  in.close();
  return 0;
}

string get_common_letters(string first_string, string second_string) {
  string intersection_string;
  sort(first_string.begin(), first_string.end());
  sort(second_string.begin(), second_string.end());
  
  set_intersection(first_string.begin(), first_string.end(), second_string.begin(), second_string.end(), back_inserter(intersection_string));
  
  return remove_duplicates(intersection_string);
}

string get_common_letters(string first_string, string second_string, string third_string) {
  string first_intersection = get_common_letters(first_string, second_string);
  string second_intersection = get_common_letters(first_string, third_string);
  string final_intersection;

  sort(first_intersection.begin(), first_intersection.end());
  sort (second_intersection.begin(), second_intersection.end());

  set_intersection(first_intersection.begin(), first_intersection.end(), second_intersection.begin(), second_intersection.end(), back_inserter(final_intersection));

  return final_intersection;
}

string remove_duplicates(string original_string) {
  char current_char = '\0';
  string modified_string ("");

  for (int i = 0; i < original_string.size(); i++) {
    if (current_char != original_string.at(i)) {
      current_char = original_string.at(i);
      modified_string.push_back(current_char);
    }
  }

  return modified_string;
}

int calculate_priority(string common_items) {
  int total_priorities_sum = 0;

  for (auto item: common_items) {
    int item_ascii_value = (int) item;
    
    if (item_ascii_value >= 65 && item_ascii_value <= 90) {
      total_priorities_sum += item_ascii_value - 38;
      continue;
    }

    if (item_ascii_value >= 61 && item_ascii_value <= 122) {
      total_priorities_sum += item_ascii_value - 96;
      continue;
    }
  }

  return total_priorities_sum;
}
