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
#include <string>
#include <iostream>
std::array<int, 4> answer;
std::array<int, 4> userGuess;
std::array<std::string, 4> clue;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 generator (seed);


void Mastermind()
{
    generateRandomAnswer(answer);
    
    populateGuess(userGuess);
    
    displayUserGuess(userGuess);
    generateClue(userGuess, answer, clue);
    displayClue(clue);
}

void generateRandomAnswer(std::array<int, 4> &ans)
{
    for(int i = 0; i < ans.size(); i++)
    {
        auto g = generator();
        ans.at(i) = g % 6;
    }
}

void populateGuess(std::array<int, 4> &guess)
{
    int userGuess;
    std::cout << "Time to guess!" << std::endl;
    std::cout << "Enter ";
    for(int a = 0; a < colorstrings.size(); a++)
    {
        std::cout << a << " for " << colorstrings.at(a) << ", ";
    }
    std::cout << std::endl;
    for(int i = 0; i < guess.size(); i++)
    {
        std::cout << "What color is in slot " << i+1 << ": ";
        std::cin >> userGuess;
        std::cout << std::endl;
        guess.at(i) = userGuess;
    }
    
}

void displayUserGuess(std::array<int, 4> &guess)
{
    std::cout << "You guessed: ";
    for(int i = 0; i < guess.size(); i++)
    {
        std::cout << colorstrings.at(guess.at(i)) << " ";
    }
    std::cout << std::endl;
}

void generateClue(std::array<int, 4> &guess, std::array<int, 4> &ans, std::array<std::string, 4> &clue)
{
    int j = 0;
    while(j < 4)
    {
        for(int i = 0; i < ans.size(); i++)
        {
            if(guess.at(j) == ans.at(i))
            {
                if(j == i)
                    clue.at(i) = "black";
                else clue.at(i) = "white";
            }
        }
        j++;
    }
    
}
void displayClue(std::array<std::string, 4> &clue)
{
    std::cout << "Your clue: ";
    for(int i = 0; i < clue.size(); i++)
    {
        std::cout << clue.at(i) << " ";
    }
    std::cout << std::endl;
}
