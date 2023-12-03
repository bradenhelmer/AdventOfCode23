// Advent of Code 2023 Problem 1 - C++
// Braden Helmer
#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main(void) {

  std::ifstream puzzleInput("input.txt");
  std::string currentLine;

  int idSum = 0, gameCount = 0;

  while (getline(puzzleInput, currentLine)) {
    gameCount++;
    bool possible = 1;
    std::string trimmed = currentLine.substr(currentLine.find(':') + 2);
    std::map<char, int> fewest = {
        {'r', 0},
        {'g', 0},
        {'b', 0},
    };

    for (int curr = 0; curr < trimmed.size(); curr++) {
      int num;
      if (isdigit(trimmed[curr])) {
        int end = trimmed.find(' ', curr);
        num = std::stoi(trimmed.substr(curr, end));
        do {
          curr++;
        } while (!isalpha(trimmed[curr]));
        char color = trimmed[curr];
        fewest[color] = (num > fewest[color]) * num +
                        (num <= fewest[color]) * fewest[color];
      }
    }
    idSum += (fewest['r'] * fewest['g'] * fewest['b']);
  }
  std::printf("Sum: %d\n", idSum);
  puzzleInput.close();
  return EXIT_SUCCESS;
}
