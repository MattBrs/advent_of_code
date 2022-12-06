#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<pair<pair<int, int>, pair<int, int>>> elves_sections;
  ifstream in("input.txt");

  while (!in.eof()) {
    string buffer;
    string first_elf_sections("");
    string second_elf_sections("");

    string first_elf_first_section;
    string first_elf_second_section;
    string second_elf_first_section;
    string second_elf_second_section;

    in >> buffer;

    if (buffer == "") {
      break;
    }

    first_elf_sections = buffer.substr(0, buffer.find(","));
    second_elf_sections =
        buffer.substr(buffer.find(",") + 1, buffer.size() + 1);

    first_elf_first_section =
        first_elf_sections.substr(0, first_elf_sections.find("-"));
    first_elf_second_section = first_elf_sections.substr(
        first_elf_sections.find("-") + 1, first_elf_sections.size() + 1);
    second_elf_first_section =
        second_elf_sections.substr(0, second_elf_sections.find("-"));
    second_elf_second_section = second_elf_sections.substr(
        second_elf_sections.find("-") + 1, second_elf_sections.size() + 1);

    elves_sections.push_back(
        {{stoi(first_elf_first_section), stoi(first_elf_second_section)},
         {stoi(second_elf_first_section), stoi(second_elf_second_section)}});
  }

  int count_overlappings = 0;
  for (auto elves_pair : elves_sections) {
    if (elves_pair.first.first <= elves_pair.second.first &&
        elves_pair.first.second >= elves_pair.second.second) {
      count_overlappings++;
      continue;
    }

    if (elves_pair.first.first >= elves_pair.second.first &&
        elves_pair.first.second <= elves_pair.second.second) {
      count_overlappings++;
      continue;
    }

    if (elves_pair.first.second >= elves_pair.second.first &&
        elves_pair.first.first <= elves_pair.second.first) {
      count_overlappings++;
      continue;
    }

    if (elves_pair.first.first <= elves_pair.second.second &&
        elves_pair.first.second >= elves_pair.second.first) {
      count_overlappings++;
      continue;
    }
  }

  cout << count_overlappings << endl;
  in.close();
  return 0;
}
