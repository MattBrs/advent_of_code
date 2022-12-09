#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ifstream in("input.txt");
  string elf_signal;

  in >> elf_signal;

  string start_of_packet_marker("");
  int i = 0;
  for (i = 0; i < elf_signal.size() && start_of_packet_marker.size() < 14;
       i++) {

    int char_pos = start_of_packet_marker.find(elf_signal[i]);
    if (char_pos == -1) {
      start_of_packet_marker += elf_signal[i];
      continue;
    }

    if (char_pos != -1) {
      start_of_packet_marker.erase(0, char_pos + 1);
      start_of_packet_marker += elf_signal[i];
      continue;
    }
  }

  cout << start_of_packet_marker << endl;
  cout << i << endl;
  in.close();
  return 0;
}
