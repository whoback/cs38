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
#include <set>
#include <algorithm>
#include <string>
#include <iostream>
std::array<int, 4> answer;

unsigned seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
std::mt19937 generator (seed);
int level;

void Mastermind()
{
    setLevel(level);
    generateRandomAnswer(answer);
    if(DEBUG_MODE)
    {
        
        for(int i = 0; i < answer.size(); i++)
        {
            std::cout << colorstrings.at(answer.at(i)) << " ";
        }
        std::cout << std::endl;
    }
    int x = 0;
    while(x < MAX_GUESSES)
    {
        std::array<int, 4> userGuess;
        populateGuess(userGuess);
        displayUserGuess(userGuess);
        std::array<std::string, 4> clue;

        generateClue(userGuess, answer, clue);
        displayClue(clue);
        if(isWinner(userGuess, answer))
        {
            std::cout << "You won!" << std::endl;
            break;
        }
        x++;
    }
    std::cout << "Game over!" << std::endl;
    displayAnswer(answer);
    
}

void generateRandomAnswer(std::array<int, 4> &ans)
{
    std::set<int> temp;
    for(int i = 0; i < ans.size(); i++)
    {
        auto g = generator() % 6;
        auto res = temp.insert(g);
        if(level == 1)
        {
            while(res.second == false)
            {
                g = generator() % 6;
                
                res = temp.insert(g);
                
            }
            ans.at(i) = g;
        }
        ans.at(i) = g;
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

void displayUserGuess(const std::array<int, 4> &guess)
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
    if(guess == ans)
    {
        clue.fill("black peg");
    }
    
    for(int i = 0; i < ans.size(); i++)
    {
        if(std::find(ans.begin(), ans.end(), guess.at(i)) != ans.end())
        {
            clue.at(i) = "white peg";
        }
        if(guess.at(i) == ans.at(i))
        {
            clue.at(i) = "black peg";
        }
    }
}
void displayClue(const std::array<std::string, 4> &clue)
{
    std::cout << "Your clue: ";
    for(int i = 0; i < clue.size(); i++)
    {
        std::cout << clue.at(i) << " ";
    }
    std::cout << std::endl;
}
void displayAnswer(const std::array<int, 4> &answer)
{
    std::cout << "The answer is: ";
    for(int i = 0; i < answer.size(); i++)
    {
        std::cout << colorstrings.at(answer.at(i)) << " ";
    }
    std::cout << std::endl;
}
void setLevel(int &level)
{
    std::cout << "What level do you want to play? Easy (1) / Hard (2):  ";
    std::cin >> level;
}
bool isWinner(const std::array<int, 4> &userGuess, const std::array<int, 4> &answer)
{
    if(userGuess == answer)
        return true;
    else
        return false;
}
