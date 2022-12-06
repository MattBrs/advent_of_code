/*
  given some elves carrying some calories,
  find the amount of calories of the elf with the most calories.
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  vector<int> elves_calories;
  int current_elf_calories = 0;

  ifstream in("input.txt");

  while (!in.eof()) {
    string temp;

    getline(in, temp, '\n');
    if (temp.length() > 0) {
      current_elf_calories += stoi(temp);
      continue;
    }

    if (temp.length() <= 0) {
      elves_calories.push_back(current_elf_calories);
      current_elf_calories = 0;
    }
  }

  sort(elves_calories.begin(), elves_calories.end(), greater<>());

  int top_three_elves_calories_count =
      elves_calories[0] + elves_calories[1] + elves_calories[2];

  cout << top_three_elves_calories_count << endl;
  in.close();
  return 0;
}
