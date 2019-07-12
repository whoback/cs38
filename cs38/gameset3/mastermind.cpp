//
//  mastermind.cpp
//  gameset3
//
//  Created by Will Hoback on 7/11/19.
//  Copyright © 2019 Will Hoback. All rights reserved.
//

#include "mastermind.hpp"
#include <array>
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>
std::array<int, 4> answer;
std::array<std::array<int, 7>, 4> guesses;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 generator (seed);

color colors;
void Mastermind()
{
    generateRandomAnswer(answer);
    for (auto i : answer){
        std::cout << i;
    }
    
}

void generateRandomAnswer(std::array<int, 4> &ans)
{
    
    for(int i = 0; i < ans.size(); i++)
    {
        auto g = generator();
        ans.at(i) = g%6;
    }
}
