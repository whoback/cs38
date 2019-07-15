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
    std::cout << MASTERMIND_TITLE;
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
    int round = 1;
    while(round <= MAX_GUESSES)
    {
        std::array<int, 4> userGuess;
        populateGuess(userGuess, round);
        displayUserGuess(userGuess);
        std::array<std::string, 4> clue;

        generateClue(userGuess, answer, clue);
        displayClue(clue);
        if(isWinner(userGuess, answer))
        {
            std::cout << "You won!" << std::endl;
            break;
        }
        round++;
    }
    std::cout << "Game over!" << std::endl;
    displayAnswer(answer);
    
}

/**
 Generates random answers which correspond to our colors.
 checks the level set by the user and if 1 doesn't allow repeated colors
 if 2 allows repeats
 @param ans an array of ints to store our answer in
 */
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

/**
 Prompts the user to guess what color is in each slot
 Prints out helpful text such as the current round.
 @param guess array of ints containing user's guess
 @param round integer representing the current round
 */
void populateGuess(std::array<int, 4> &guess, int round)
{
    int userGuess;
    std::cout << "Round: #" << round << " ";
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

/**
 Prints out the user's last guess as actual strings converted from ints

 @param guess array of ints containing the user's guess
 */
void displayUserGuess(const std::array<int, 4> &guess)
{
    std::cout << "You guessed: ";
    for(int i = 0; i < guess.size(); i++)
    {
        std::cout << colorstrings.at(guess.at(i)) << " ";
    }
    std::cout << std::endl;
}


/**
 compares guess and ans arrays and fills the clue array with black peg or white peg clues
 if the color guess is in the answer -> white peg
 if the color guess is in the answer and the correct slot -> black peg

 @param guess array of ints containing user's guess
 @param ans array of ints containing answer values
 @param clue array of strings that will be printed for the user
 */
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

/**
 Displays the clues to the user after every round

 @param clue an array of strings only ever empty, black peg, or white peg
 */
void displayClue(std::array<std::string, 4> &clue)
{
    // if we're playing on hard shuffle the clues otherwise they conform to the slots
    if(level == 2)
    {
        std::shuffle(clue.begin(), clue.end(), generator);
    }
    std::cout << "Your clue: ";
    for(int i = 0; i < clue.size(); i++)
    {
        std::cout << clue.at(i) << " ";
    }
    std::cout << std::endl;
}

/**
 Displays the values in our answer array as strings of actual color names

 @param answer array of ints containing the answer
 */
void displayAnswer(const std::array<int, 4> &answer)
{
    std::cout << "The answer is: ";
    for(int i = 0; i < answer.size(); i++)
    {
        std::cout << colorstrings.at(answer.at(i)) << " ";
    }
    std::cout << std::endl;
}

/**
 Ask the user what level to play. Easy has no repeated colors where Hard allows repeats.

 @param level int representing the level choice
 */
void setLevel(int &level)
{
    std::cout << "What level do you want to play? Easy (1) / Hard (2):  ";
    std::cin >> level;
}

/**
 Checks to see if the user has won the game. If our guess array == our answer array
 then winner winner chicken dinner.

 @param userGuess an array of ints that has the user's guess
 @param answer an array of ints that is our answer
 @return bool
 */
bool isWinner(const std::array<int, 4> &userGuess, const std::array<int, 4> &answer)
{
    if(userGuess == answer)
        return true;
    else
        return false;
}
