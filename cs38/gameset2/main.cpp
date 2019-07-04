//
//  main.cpp
//  gameset2
//
//  Created by Will Hoback on 7/3/19.
//  Copyright © 2019 Will Hoback. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <sstream>

std::vector<std::string> lib = {
    "apple",
    "gnostic",
    "gossip",
    "grogginess",
    "haiku",
    "haphazard",
    "hangman",
    "baseball",
    "chocolate",
    "common",
    "bicycle",
    "zebra",
    "rainbow"
};
std::string randomAccessLibrary(std::vector<std::string> lib)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(lib.begin(), lib.end(), g);
    
    return lib.front();
}

std::string changeToUnderscores(std::string str)
{
    return str.replace(str.begin(), str.end(), str.length(), '_');
}

auto isLetterInWord(std::string word, std::string letter)
{
    
    if(word.find(letter) == std::string::npos)
    {
        return 1;
    }
    return 0;
}
std::string getUserGuess(std::string input, std::string letterToGuess){
    while((std::cout << "Guess a letter: ")
          && std::getline(std::cin, input))
    {
        std::istringstream is {input};
        if((is >> letterToGuess) && !(is >> input) && (letterToGuess.length() < 2))
        {
            break;
        }
        std::cerr << "Invalid input please try again." << std::endl;
        
    }
    // deal with upcased characters
    letterToGuess = std::tolower(letterToGuess[0]);
    return letterToGuess;
}

auto isWinner(std::vector<int> positions, std::string wordToGuess)
{
    if(positions.size() == wordToGuess.length())
    {
        return 0;
    }
    return 1;
}
int main(int argc, const char * argv[]) {
    
    // generate a word for the user and change it to ___s
    std::string wordToGuess = randomAccessLibrary(lib);
    std::string underscore = changeToUnderscores(wordToGuess);
    //int numberOfGuesses = 0;
    
    
    
    
    std::string input;
    std::string letterToGuess;
    std::vector<int> positions;
    
    std::cout << "Your word to guess is: " << std::endl;
    std::cout << wordToGuess << std::endl;
    std::cout << underscore << std::endl;
    while(true)
    {
        // get user input
        letterToGuess = getUserGuess(input, letterToGuess);
        // compare letter -> word
        if(isLetterInWord(wordToGuess, letterToGuess) != 1)
        {
            
            for(int i = 0; i < wordToGuess.length(); i++)
            {
                if(wordToGuess[i] == letterToGuess[0])
                {
                    positions.push_back(i);
                    underscore[i] = letterToGuess[0];
                }
            }
            std::cout << underscore << std::endl;
//            std::cout << "size of positions is: " << positions.size() << std::endl;
//            std::cout << "size of actual word : " << wordToGuess.length()<<std::endl;
            // check if winner
            if(isWinner(positions, wordToGuess) == 0)
            {
                std::cout << "Winner!" << std::endl;
                break;
            }
        }
        else
        {
            std::cout << "Oops try another guess!" << std::endl;
        }
    }
    
    return 0;
}


