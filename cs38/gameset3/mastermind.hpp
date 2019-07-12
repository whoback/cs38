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
#include <string>

constexpr int MAX_GUESSES = 7;
constexpr int DEBUG_MODE = 1;

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
void populateGuess(std::array<int, 4> &guess);
void displayUserGuess(std::array<int, 4> &guess);
void generateClue(std::array<int, 4> &guess, std::array<int, 4> &ans, std::array<std::string, 4> &clue);
void displayClue(std::array<std::string, 4> &clue);
#endif /* mastermind_hpp */
