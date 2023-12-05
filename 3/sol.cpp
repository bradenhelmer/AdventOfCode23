// Advent of Code 2023 Problem 3 - C++
// Braden Helmer
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<std::vector<char>> CharBuf;

bool isSymbol(char c) { return !isdigit(c) && c != '.'; }

void part1(CharBuf &engineSchematic) {
  int sum = 0;
  for (int row = 0; row < engineSchematic.size(); row++) {
    for (int col = 0; col < engineSchematic[row].size(); col++) {
      if (isdigit(engineSchematic[row][col])) {
        int start = col;
        do {
          col++;
        } while (isdigit(engineSchematic[row][col]));
        std::string num(engineSchematic[row].begin() + start,
                        engineSchematic[row].begin() + col);
        bool validNum = 0;
        for (int check = (start > 0 ? start - 1 : start);
             check < (col < engineSchematic[row].size() ? col + 1 : col);
             check++) {
          // Lateral top and bottom;
          if (row > 0) {
            validNum |= isSymbol(engineSchematic[row - 1][check]);
          }
          if (row < engineSchematic.size() - 1) {
            validNum |= isSymbol(engineSchematic[row + 1][check]);
          }
          // Check ends
          if (start > 0) {
            validNum |= isSymbol(engineSchematic[row][start - 1]);
          }
          if (col < engineSchematic[row].size() - 1) {
            validNum |= isSymbol(engineSchematic[row][col]);
          }
        }
        sum += validNum * std::stoi(num);
      }
    }
  }

  std::printf("Part 1: %d\n", sum);
}

void part2(CharBuf &engineSchematic) {
  int sum = 0;
  for (int row = 0; row < engineSchematic.size(); row++) {
    for (int col = 0; col < engineSchematic[row].size(); col++) {
      if (engineSchematic[row][col] == '*') {

        // Column directions of possible numbers.
        int top = -1, bottom = -1, back = -1, front = -1, top2 = -1,
            bottom2 = -1;
        for (int numCheck = (col > 0 ? col - 1 : col);
             numCheck < (col < engineSchematic[row].size() ? col + 2 : col);
             numCheck++) {

          // Special 2 on top case
          if (row > 0 && !isdigit(engineSchematic[row - 1][col]) &&
              isdigit(engineSchematic[row - 1][col - 1]) &&
              isdigit(engineSchematic[row - 1][col + 1])) {
            top = col - 1;
            top2 = col + 1;
            break;
          }

          // Special 2 on bottom case
          if (row < engineSchematic.size() - 1 &&
              !isdigit(engineSchematic[row + 1][col]) &&
              isdigit(engineSchematic[row + 1][col - 1]) &&
              isdigit(engineSchematic[row + 1][col + 1])) {
            bottom = col - 1;
            bottom2 = col + 1;
            break;
          }

          // Look for a number on the top
          if (row > 0 && top == -1) {
            top +=
                (numCheck + 1) * !!isdigit(engineSchematic[row - 1][numCheck]);
          }
          // Look for number on the bottom
          if (row < engineSchematic.size() - 1 && bottom == -1) {
            bottom +=
                (numCheck + 1) * !!isdigit(engineSchematic[row + 1][numCheck]);
          }
          // Check ends
          if (col > 0 && back == -1) {
            back += (numCheck + 1) * !!isdigit(engineSchematic[row][col - 1]);
          }
          if (col < engineSchematic[row].size() - 1 && front == -1) {
            front += (col + 2) * !!isdigit(engineSchematic[row][col + 1]);
          }
        }
        // If the product of all the indices is greater than 1, we know that we
        // have 2 numbers. 1 and 3 would make the product negative, and none
        // would = 1.
        if ((top * bottom * front * back * top2 * bottom2) > 1) {
          int product = 1;
          if (top != -1) {
            std::pair<int, int> bounds = {top, top};
            do {
              bounds.first -=
                  !!isdigit(engineSchematic[row - 1][bounds.first - 1]);
              bounds.second +=
                  !!isdigit(engineSchematic[row - 1][bounds.second + 1]);
            } while (isdigit(engineSchematic[row - 1][bounds.first - 1]) ||
                     isdigit(engineSchematic[row - 1][bounds.second + 1]));

            std::string topNum(engineSchematic[row - 1].begin() + bounds.first,
                               engineSchematic[row - 1].begin() +
                                   bounds.second + 1);
            product *= std::stoi(topNum);
          }
          if (bottom != -1) {
            std::pair<int, int> bounds = {bottom, bottom};
            do {
              bounds.first -=
                  !!isdigit(engineSchematic[row + 1][bounds.first - 1]);
              bounds.second +=
                  !!isdigit(engineSchematic[row + 1][bounds.second + 1]);
            } while (isdigit(engineSchematic[row + 1][bounds.first - 1]) ||
                     isdigit(engineSchematic[row + 1][bounds.second + 1]));

            std::string bottomNum(
                engineSchematic[row + 1].begin() + bounds.first,
                engineSchematic[row + 1].begin() + bounds.second + 1);
            product *= std::stoi(bottomNum);
          }
          if (top2 != -1) {
            std::pair<int, int> bounds = {top2, top2};
            do {
              bounds.first -=
                  !!isdigit(engineSchematic[row - 1][bounds.first - 1]);
              bounds.second +=
                  !!isdigit(engineSchematic[row - 1][bounds.second + 1]);
            } while (isdigit(engineSchematic[row - 1][bounds.first - 1]) ||
                     isdigit(engineSchematic[row - 1][bounds.second + 1]));

            std::string top2Num(engineSchematic[row - 1].begin() + bounds.first,
                                engineSchematic[row - 1].begin() +
                                    bounds.second + 1);
            product *= std::stoi(top2Num);
          }
          if (bottom2 != -1) {
            std::pair<int, int> bounds = {bottom2, bottom2};
            do {
              bounds.first -=
                  !!isdigit(engineSchematic[row + 1][bounds.first - 1]);
              bounds.second +=
                  !!isdigit(engineSchematic[row + 1][bounds.second + 1]);
            } while (isdigit(engineSchematic[row + 1][bounds.first - 1]) ||
                     isdigit(engineSchematic[row + 1][bounds.second + 1]));

            std::string bottom2Num(
                engineSchematic[row + 1].begin() + bounds.first,
                engineSchematic[row + 1].begin() + bounds.second + 1);
            product *= std::stoi(bottom2Num);
          }
          if (front != -1) {
            std::pair<int, int> bounds = {front, front};
            do {
              bounds.second +=
                  !!isdigit(engineSchematic[row][bounds.second + 1]);
            } while (isdigit(engineSchematic[row][bounds.second + 1]));
            std::string frontNum(engineSchematic[row].begin() + bounds.first,
                                 engineSchematic[row].begin() + bounds.second +
                                     1);
            product *= std::stoi(frontNum);
          }
          if (back != -1) {
            std::pair<int, int> bounds = {back, back};
            do {
              bounds.first -= !!isdigit(engineSchematic[row][bounds.first - 1]);
            } while (isdigit(engineSchematic[row][bounds.first - 1]));
            std::string backNum(engineSchematic[row].begin() + bounds.first,
                                engineSchematic[row].begin() + bounds.second +
                                    1);
            product *= std::stoi(backNum);
          }
          sum += product;
        }
      }
    }
  }
  std::printf("Part 2: %d\n", sum);
}

int main(void) {

  std::ifstream puzzleInput("input.txt");
  std::string currentLine;

  // Read file into vector
  CharBuf engineSchematic;
  while (getline(puzzleInput, currentLine)) {
    std::stringstream ss(currentLine);
    std::vector<char> row;
    char curr;
    while (ss >> curr) {
      row.push_back(curr);
    }
    engineSchematic.push_back(row);
  }

  part1(engineSchematic);
  part2(engineSchematic);
  return EXIT_SUCCESS;
}
