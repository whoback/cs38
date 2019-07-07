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

constexpr auto HANGMAN_STATE_INIT =
R"(
WELCOME TO HANGMAN
IF YOU PICK THE WRONG LETTER 6 TIMES
OUR FRIEND HERE DIES... GOOD LUCK!

  +---+
  |   |
      |
      |
      |
      |
=========

)";

constexpr auto HANGMAN_STATE_1 =
R"(
CAREFUL... ONLY 5 MORE TO GO...
  +---+
  |   |
  O   |
      |
      |
      |
=========

)";
constexpr auto HANGMAN_STATE_2 =
R"(
YOU REALLY SHOULD TRY HARDER! 4 LEFT.
  +---+
  |   |
  O   |
  |   |
      |
      |
=========

)";
constexpr auto HANGMAN_STATE_3 =
R"(
OK. STOP FOOLING AROUND. DOWN TO 3 AND LIVES ARE AT STAKE!
  +---+
  |   |
  O   |
 /|   |
      |
      |
=========

)";
constexpr auto HANGMAN_STATE_4 =
R"(
2 TO GO AND EVEN I'M SWEATING NOW...
  +---+
  |   |
  O   |
 /|\  |
      |
      |
=========

)";
constexpr auto HANGMAN_STATE_5 =
R"(
ONLY 1 MORE CHANCE...THE END IS NEAR I REALLY HOPE YOU KNOW THE WORD!
  +---+
  |   |
  O   |
 /|\  |
 /    |
      |
=========

)";
constexpr auto HANGMAN_STATE_FINAL =
R"(
WELL...BETTER HIM THAN US RIGHT?
  +---+
  |   |
  O   |
 /|\  |
 / \  |
      |
=========
GAME OVER...

)";

std::string generateRandomWordFromLibrary(std::vector<std::string> lib);
std::string changeToUnderscores(std::string str);
bool letterIsInWord(std::string word, std::string letter);
bool letterAlreadyUsed(std::string letterToGuess, std::vector<std::string> usedLetters);
std::string getUserGuess(std::string letterToGuess);
bool hasUserGuessedAllLetters(std::vector<int> positions, std::string wordToGuess);
void printWinningMessage();
void initWordToGuessMessage(std::string underscore);
bool doesUserWantToGuessWholeWord();
std::string getUserWholeWordGuess();
void printUsedLetters(std::vector<std::string> usedLetters);
void printCurrentState(int badGuesses);
static void printRoundInfo(const std::string &underscore, const std::vector<std::string> &usedLetters);
static void printEndOfGameStats(int badGuesses, int goodGuesses, const std::vector<std::string> &usedLetters);


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

int main(int argc, const char * argv[]) {
    // vars for gameplay
    int goodGuesses = 0;
    int badGuesses = 0;
    
    std::string letterToGuess;
    std::vector<int> positions;
    std::vector<std::string> usedLetters;
    
    
    // generate a word for the user and change it to ___s
    std::string wordToGuess = generateRandomWordFromLibrary(lib);
    std::string underscore = changeToUnderscores(wordToGuess);
    
    // print our hangman state
    printCurrentState(badGuesses);
    // print the word as underscores for the user
    initWordToGuessMessage(underscore);
    // game logic
    while(badGuesses < 6)
    {
        // get user input
        letterToGuess = getUserGuess(letterToGuess);
        
        // compare letter -> word and it is in the word and hasn't already been used

        if(letterIsInWord(wordToGuess, letterToGuess) && !letterAlreadyUsed(letterToGuess, usedLetters))
        {
            
            usedLetters.push_back(letterToGuess);
            for(int i = 0; i < wordToGuess.length(); i++)
            {
                if(wordToGuess.at(i) == letterToGuess.at(0))
                {
                    positions.push_back(i);
                    underscore.at(i) = letterToGuess.at(0);
                }
            }
            
            // check if winner
            if(hasUserGuessedAllLetters(positions, wordToGuess))
            {
                goodGuesses++; // for the last count
                printWinningMessage();
                printEndOfGameStats(badGuesses, goodGuesses, usedLetters);
                break;
            }
            // end of a round so increment guess counter, output updated underscores and used letters
            goodGuesses++;
            
            std::cout << "\033[3;42;30mGood guess!\033[0m\t\t" << std::endl;
            printRoundInfo(underscore, usedLetters);
            
            // ask user if they want to guess the entire word
            if(doesUserWantToGuessWholeWord())
            {
                // if they do see if the word they enter matches
                std::string userWholeWordGuess;
                userWholeWordGuess = getUserWholeWordGuess();
                if(userWholeWordGuess == wordToGuess)
               {
                   goodGuesses++;
                   printWinningMessage();
                   printEndOfGameStats(badGuesses, goodGuesses, usedLetters);
                   break;
               }
                else{
                    std::cout << "\x1B[31mBaaaad Guessss\033[0m\t\t" << std::endl;
                    badGuesses++;
                    printRoundInfo(underscore, usedLetters);
                }
                
            }
            
        }
        // we had a bad guess
        else
        {
            std::cout << "\x1B[31mBaaaad Guessss\033[0m\t\t" << std::endl;
            if(!letterAlreadyUsed(letterToGuess, usedLetters))
            {
                usedLetters.push_back(letterToGuess);
            }
            badGuesses++;
            if (badGuesses == 6) {
                printCurrentState(badGuesses);
                printEndOfGameStats(badGuesses, goodGuesses, usedLetters);
                break;
            }
            printCurrentState(badGuesses);
            printRoundInfo(underscore, usedLetters);
        }
    }
    
    return 0;
}

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


/**
 Returns true if the letter is found within the word
 
 @param word word to search
 @param letter letter to search for
 @return bool
 */
bool letterIsInWord(std::string word, std::string letter)
{
    if(word.find(letter) == std::string::npos)
    {
        return false;
    }
    return true;
}

/**
 Returns true if the letter has already been used
 
 @param letterToGuess the letter entered by the user
 @param usedLetters a vector of already entered letters
 @return bool
 */
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

/**
 Main intake of guesses from our user. Not much validation...

 @param letterToGuess string input via stdin which contains othe letter entered by the user
 @return a string containing the user entered letter
 */
std::string getUserGuess(std::string letterToGuess){
    while(true)
    {
        std::cout << "Guess a letter: ";
        std::getline(std::cin, letterToGuess);
    
        // only basic input checking assuming valid input per spec
        if(letterToGuess.length() < 2)
        {
            break;
        }
        std::cerr << "Invalid input please try again." << std::endl;
    }
    // deal with upcased characters
    letterToGuess = std::tolower(letterToGuess.at(0));
    return letterToGuess;
}

/**
 Checks to see if the user has guessed all the letters in the word or not

 @param positions a vector of ints which corresponds to the length of our word
 @param wordToGuess the word the user is trying to guess
 @return bool
 */
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
 
 */
void printWinningMessage()
{
    const char * wtext = R"(
    __      __  _                                       _
    \ \    / / (_)    _ _     _ _      ___      _ _    | |
     \ \/\/ /  | |   | ' \   | ' \    / -_)    | '_|   |_|
      \_/\_/  _|_|_  |_||_|  |_||_|   \___|   _|_|_   _(_)_
    _|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_| """ |
    "`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'
    )";
    
    
    std::cout << wtext << std::endl;

}

/**
 Prints out the word for the user to guess as underscores
 
 @param underscore the word to guess replaced with underscores
 */
void initWordToGuessMessage(const std::string &underscore)
{
    std::cout << "Your word to guess looks like: " << std::endl;
    
    std::cout << underscore << std::endl;
    std::cout << std::endl;
}

/**
 Returns true if the user wants to guess the entire word and false if not.
 
 @return bool
 */
bool doesUserWantToGuessWholeWord()
{
    std::cout << "Do you want to guess the whole word? Enter Y/N: ";
    std::string resp;
    std::getline(std::cin, resp);
    resp = std::tolower(resp.at(0));
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

/**
 Prints letters that have been guessed before.

 @param usedLetters is a vector of strings which is built up over time as the user enters guesses.
 */
void printUsedLetters(std::vector<std::string> usedLetters)
{
    for(std::string x : usedLetters)
    {
        std::cout << x << ',';
    };
    std::cout << std::endl;
}

/**
 This function prints the hangman ASCII art. Each is unique to a specific number of bad guesses.

 @param badGuesses an int corresponding to the number of incorrect guesses by the user
 */
void printCurrentState(int badGuesses)
{
    switch (badGuesses) {
        case 0:
            std::cout << HANGMAN_STATE_INIT;
            break;
        case 1:
            std::cout << HANGMAN_STATE_1;
            break;
        case 2:
            std::cout << HANGMAN_STATE_2;
            break;
        case 3:
            std::cout << HANGMAN_STATE_3;
            break;
        case 4:
            std::cout << HANGMAN_STATE_4;
            break;
        case 5:
            std::cout << HANGMAN_STATE_5;
            break;
        default: std::cout << HANGMAN_STATE_FINAL;
            break;
    }
    
}

/**
 This prints the newest version of a user's word to guess with all newly guessed letters included and the updated used letter table.

 @param underscore the updated string containing our letters and underscores
 @param usedLetters a vecctor of strings of used letters already guessed by the user
 */
static void printRoundInfo(const std::string &underscore, const std::vector<std::string> &usedLetters) {
    std::cout << "The word now looks like: " << std::endl;
    std::cout << underscore << " || Already used letters: ";
    printUsedLetters(usedLetters);
}

/**
 Prints end of game statistics for the user

 @param badGuesses number of incorrect guesses
 @param goodGuesses number of correct guesses
 @param usedLetters all the letters guessed
 */
static void printEndOfGameStats(int badGuesses, int goodGuesses, const std::vector<std::string> &usedLetters) {
    std::cout << "You guessed " << goodGuesses + badGuesses << " guesses this game." << std::endl;
    std::cout << goodGuesses << " of them were correct and " << badGuesses << " were incorrect." << std::endl;
    std::cout << "Look at all the letters you guessed!" << std::endl;
    printUsedLetters(usedLetters);
}
