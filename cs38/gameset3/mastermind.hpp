//
//  mastermind.hpp
//  gameset3
//
//  Created by Will Hoback on 7/11/19.
//  Copyright © 2019 Will Hoback. All rights reserved.
//

#ifndef mastermind_hpp
#define mastermind_hpp

#include <stdio.h>
#include <array>
#include <algorithm>
#include <string>

constexpr int MAX_GUESSES = 7;
// set to 1 to show the answer
constexpr int DEBUG_MODE = 1;
constexpr auto MASTERMIND_TITLE =
R"(
 _      ____  ____  _____  _____ ____  _      _  _      ____  _
/ \__/|/  _ \/ ___\/__ __\/  __//  __\/ \__/|/ \/ \  /|/  _ \/ \
| |\/||| / \||    \  / \  |  \  |  \/|| |\/||| || |\ ||| | \|| |
| |  ||| |-||\___ |  | |  |  /_ |    /| |  ||| || | \||| |_/|\_/
\_/  \|\_/ \|\____/  \_/  \____\\_/\_\\_/  \|\_/\_/  \|\____/(_)
)";
typedef enum color {
    blue,
    red,
    purple,
    orange,
    brown,
    green,
} color;

std::array<std::string, 6> const colorstrings{"blue", "red", "purple", "orange", "brown", "green",};

void Mastermind();
void generateRandomAnswer(std::array<int, 4> &ans);
void populateGuess(std::array<int, 4> &guess, const int round);
void displayUserGuess(const std::array<int, 4> &guess);
void generateClue(const std::array<int, 4> &guess, const std::array<int, 4> &ans, std::array<std::string, 4> &clue);
void displayClue(std::array<std::string, 4> &clue);
void displayAnswer(const std::array<int, 4> &answer);
void setLevel(int &level);
bool isWinner(const std::array<int, 4> &userGuess, const std::array<int, 4> &answer);
#endif /* mastermind_hpp */
