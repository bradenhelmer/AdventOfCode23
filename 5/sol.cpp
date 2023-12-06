// Advent of Code 2023 Problem 5 - C++
// Braden Helmer
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<long> Seeds;

void part1() {
  std::ifstream almanac("input.txt");
  std::string currentLine;

  // Get first line with seed numbers.
  getline(almanac, currentLine);
  currentLine = currentLine.substr(currentLine.find(':') + 2);
  std::istringstream seedStream(currentLine);
  std::string currentSeed;
  Seeds seedList;
  while (getline(seedStream, currentSeed, ' ')) {
    seedList.push_back(std::stol(currentSeed));
  }

  // Read rest of almanac
  while (getline(almanac, currentLine)) {
    // New mapping
    if (isalpha(currentLine[0])) {
      getline(almanac, currentLine);

      std::vector<bool> setFields(seedList.size());
      std::fill(setFields.begin(), setFields.end(), 0);

      // New Mapping set
      while (isdigit(currentLine[0])) {
        int idx = 0;
        std::vector<long> mapping;
        std::string currentMapNum;
        std::istringstream mappingStream(currentLine);
        while (getline(mappingStream, currentMapNum, ' ')) {
          mapping.push_back(std::stol(currentMapNum));
        }

        for (int i = 0; i < seedList.size(); i++) {
          if (seedList[i] >= mapping[1] &&
              seedList[i] < (mapping[1] + mapping[2]) && !setFields[i]) {
            seedList[i] = (mapping[0] + (seedList[i] - mapping[1]));
            setFields[i] = 1;
          }
        }
        getline(almanac, currentLine);
      }
    }
  }

  std::printf("The lowest seed location is: %ld\n",
              *std::min_element(seedList.begin(), seedList.end()));
}

void part2();

int main(void) {

  part1();

  return EXIT_SUCCESS;
}
