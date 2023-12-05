// Advent of Code 2023 Problem 4 - C++
// Braden Helmer
#include <cmath>
#include <fstream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<std::string> SCRATCH_CARDS;

void part1(SCRATCH_CARDS &scratchCards) {
  int pointTotal = 0;
  for (int card = 0; card < scratchCards.size(); card++) {
    int multiplier = -1;
    std::string trimmed =
        scratchCards[card].substr(scratchCards[card].find(':') + 2);
    int splitter = trimmed.find('|');
    std::string winningNums = trimmed.substr(0, splitter),
                givenNums = trimmed.substr(splitter + 2);

    // Create map for winning nums
    std::map<std::string, int> wNums;
    for (int curr = 0; curr < winningNums.size(); curr++) {
      if (isdigit(winningNums[curr])) {
        int start = curr;
        do {
          curr++;
        } while (isdigit(winningNums[curr]));
        std::string num(winningNums.begin() + start,
                        winningNums.begin() + curr);
        wNums[num] = 1;
      }
    }

    // Check given nums
    for (int curr = 0; curr < givenNums.size(); curr++) {
      if (isdigit(givenNums[curr])) {
        int start = curr;
        do {
          curr++;
        } while (isdigit(givenNums[curr]));
        std::string num(givenNums.begin() + start, givenNums.begin() + curr);
        multiplier += (wNums.find(num) != wNums.end());
      }
    }
    pointTotal += (multiplier > -1) * pow(2, multiplier);
  }
  std::printf("Part 1: %d\n", pointTotal);
}

void part2(SCRATCH_CARDS &scratchCards) {
  std::map<int, int> copyTable;
  // Populate copy table
  for (int card = 0; card < scratchCards.size(); card++) {
    copyTable[card + 1] = 1;
  }
  for (int card = 0; card < scratchCards.size(); card++) {
    for (int copy = 1; copy <= copyTable[card + 1]; copy++) {
      int multiplier = 0;
      std::string trimmed =
          scratchCards[card].substr(scratchCards[card].find(':') + 2);
      int splitter = trimmed.find('|');
      std::string winningNums = trimmed.substr(0, splitter),
                  givenNums = trimmed.substr(splitter + 2);

      // Create map for winning nums
      std::map<std::string, int> wNums;
      for (int curr = 0; curr < winningNums.size(); curr++) {
        if (isdigit(winningNums[curr])) {
          int start = curr;
          do {
            curr++;
          } while (isdigit(winningNums[curr]));
          std::string num(winningNums.begin() + start,
                          winningNums.begin() + curr);
          wNums[num] = 1;
        }
      }

      // Check given nums
      for (int curr = 0; curr < givenNums.size(); curr++) {
        if (isdigit(givenNums[curr])) {
          int start = curr;
          do {
            curr++;
          } while (isdigit(givenNums[curr]));
          std::string num(givenNums.begin() + start, givenNums.begin() + curr);
          multiplier += (wNums.find(num) != wNums.end());
        }
      }

      // Add copies
      for (int copied = 1; copied <= multiplier; copied++) {
        copyTable[card + copied + 1]++;
      }
    }
  }
  int totalCards =
      std::accumulate(copyTable.begin(), copyTable.end(), 0,
                      [](const int prev, const std::pair<int, int> &pair) {
                        return prev + pair.second;
                      });

  std::printf("Part 2: %d\n", totalCards);
}

int main(void) {
  std::ifstream input("input.txt");
  std::string currentLine;
  SCRATCH_CARDS cards;
  while (getline(input, currentLine)) {
    cards.push_back(currentLine);
  }

  part1(cards);
  part2(cards);
  return EXIT_SUCCESS;
}
