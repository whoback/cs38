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

constexpr int MAX_GUESSES = 7;

typedef enum color {
    blue,
    red,
    purple,
    orange,
    brown,
    green,
} color;



void Mastermind();
void generateRandomAnswer(std::array<int, 4> &ans);
#endif /* mastermind_hpp */
