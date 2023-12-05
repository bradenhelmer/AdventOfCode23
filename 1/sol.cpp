// Advent of Code 2023 Day 1 - C++
// Braden Helmer
#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main(void) {

  std::ifstream puzzleInput("input.txt");
  const std::map<std::string, int> nums = {
      {"one", '1'},   {"two", '2'},   {"three", '3'},
      {"four", '4'},  {"five", '5'},  {"six", '6'},
      {"seven", '7'}, {"eight", '8'}, {"nine", '9'},
  };

  int sum = 0;
  std::string currentLine;
  while (getline(puzzleInput, currentLine)) {
    char digits[2] = {'a', 'a'};
    for (int idx = 0; digits[0] == 'a'; idx++) {
      if (isdigit(currentLine[idx])) {
        digits[0] = currentLine[idx];
        break;
      }
      for (const auto &num : nums) {
        if (*(num.first.begin()) == currentLine[idx]) {
          std::string str = currentLine.substr(idx, num.first.size());
          if (!num.first.compare(str)) {
            digits[0] = num.second;
            break;
          }
        }
      }
    }

    for (int idx = currentLine.size() - 1; digits[1] == 'a'; idx--) {
      if (isdigit(currentLine[idx])) {
        digits[1] = currentLine[idx];
        break;
      }

      for (const auto &num : nums) {
        if (*(num.first.rbegin()) == currentLine[idx]) {
          if ((int)(idx - (num.first.size()- 1)) >= 0) {
            std::string str = currentLine.substr(idx - (num.first.size() - 1),
                                                 num.first.size());
            if (!num.first.compare(str)) {
              digits[1] = num.second;
              break;
            }
          }
        }
      }
    }

    sum += std::stoi(std::string(digits));
  }
  std::cout << sum << '\n';
  puzzleInput.close();

  return EXIT_SUCCESS;
}
