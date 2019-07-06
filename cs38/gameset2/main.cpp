/*
 Game Project Week 2
 main.cpp
 Will Hoback
 */

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

/**
 Generate a random entry from our library of words

 @param lib a vector of strings
 @return a string that the user will end up guessing
 */
std::string generateRandomWordFromLibrary(std::vector<std::string> lib)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(lib.begin(), lib.end(), g);
    
    return lib.front();
}

/**
 This takes our word and replaces every character with an underscore

 @param str a string, this is the word that is being guessed by the user
 @return a new string of all underscores
 */
std::string changeToUnderscores(std::string str)
{
    return str.replace(str.begin(), str.end(), str.length(), '_');
}

bool letterIsInWord(std::string word, std::string letter)
{
    if(word.find(letter))
    {
        return true;
    }
    return false;
}

bool letterAlreadyUsed(std::string letterToGuess, std::vector<std::string> usedLetters)
{
    std::vector<std::string>::iterator itr = std::find(usedLetters.begin(), usedLetters.end(), letterToGuess);
    if(itr != usedLetters.end())
    {
        // has been used
        return true;
    }
    // has not been used
    return false;
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

bool hasUserGuessedAllLetters(std::vector<int> positions, std::string wordToGuess)
{
    if(positions.size() == wordToGuess.length())
    {
        return true;
    }
    return false;
}


/**
 Prints a message if the user has won the game

 @param goodGuesses numer of good guesses the user has currently
 @param badGuesses number of bad guesses the user has currently
 @param usedLetters vector of letters used in all guesses
 */
void printWinningMessage(int goodGuesses, int badGuesses, std::vector<std::string> usedLetters)
{
    const char * wtext = R"(
    __      __  _                                       _
    \ \    / / (_)    _ _     _ _      ___      _ _    | |
     \ \/\/ /  | |   | ' \   | ' \    / -_)    | '_|   |_|
      \_/\_/  _|_|_  |_||_|  |_||_|   \___|   _|_|_   _(_)_
    _|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_| """ |
    "`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'
    )";
 
    std::cout << "\n\n\n\n\n\n\n\n\n";
    std::cout << wtext << std::endl;
    std::cout << "You took " << goodGuesses + badGuesses << " guesses to get it right!" << std::endl;
    std::cout << goodGuesses << " of them were correct and " << badGuesses << " were incorrect!" << std::endl;
    std::cout << "Look at all the letters you guessed!" << std::endl;
    for(std::string x : usedLetters)
    {
        std::cout << x;
    };
}

/**
 Prints out the word for the user to guess as underscores

 @param underscore the word to guess replaced with underscores
 */
void initWordToGuessMessage(std::string underscore)
{
    std::cout << "Your word to guess is: " << std::endl;
    
    std::cout << underscore << std::endl;
}

/**
 Returns true if the user wants to guess the entire word and false if not.

 @return bool
 */
bool doesUserWantToGuessWholeWord()
{
    std::cout << "Do you want to guess the whole word? Enter Y for yes: ";
    std::string resp;
    std::getline(std::cin, resp);
    resp = std::tolower(resp[0]);
    if(resp == "y")
    {

        return true;
    }
    return false;
    
}

/**
 This function gets the user's guess of the entire word.

 @return a string containing the entered guess
 */
std::string getUserWholeWordGuess()
{
    std::cout << "Enter your guess: ";
    std::string guess;
    std::getline(std::cin, guess);
    
    return guess;
}

int main(int argc, const char * argv[]) {
    // vars for gameplay
    int goodGuesses = 0;
    int badGuesses = 0;
    std::string input;
    std::string letterToGuess;
    std::vector<int> positions;
    std::vector<std::string> usedLetters;
    
    
    // generate a word for the user and change it to ___s
    std::string wordToGuess = generateRandomWordFromLibrary(lib);
    std::string underscore = changeToUnderscores(wordToGuess);
    
    // print the word as underscores for the user
    initWordToGuessMessage(underscore);
  
    while(true)
    {
        // get user input
        letterToGuess = getUserGuess(input, letterToGuess);
        
        // compare letter -> word

        if(letterIsInWord(wordToGuess, letterToGuess) && !letterAlreadyUsed(letterToGuess, usedLetters))
        {
            
            usedLetters.push_back(letterToGuess);
            for(int i = 0; i < wordToGuess.length(); i++)
            {
                if(wordToGuess[i] == letterToGuess[0])
                {
                    positions.push_back(i);
                    underscore[i] = letterToGuess[0];
                }
            }
            
            // check if winner
            if(hasUserGuessedAllLetters(positions, wordToGuess))
            {
                goodGuesses++; // for the last count
                printWinningMessage(goodGuesses, badGuesses, usedLetters);
                break;
            }
            goodGuesses++;
            std::cout << underscore << std::endl;
            if(doesUserWantToGuessWholeWord())
            {
                
                std::string userWholeWordGuess;
                userWholeWordGuess = getUserWholeWordGuess();
                if(userWholeWordGuess == wordToGuess)
               {
                   goodGuesses++;
                   printWinningMessage(goodGuesses, badGuesses, usedLetters);
                   break;
               }
                
            }
            
        }
        else
        {
            if(letterAlreadyUsed(letterToGuess, usedLetters) != 0)
            {
                usedLetters.push_back(letterToGuess);
            }
            badGuesses++;
            std::cout << "Oops try another guess!" << std::endl;
        }
    }
    
    return 0;
}


