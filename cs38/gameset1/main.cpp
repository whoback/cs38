/*
 Game Project Week 1
 main.cpp
 Will Hoback
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

// keep it neat and forward declare our functions
int makeRandNum(int mod);
void playFortuneTeller();
int shellPrompt(int guess);
int isWinner(int box, int guess);
void playShellGame();
void printShellStatus(int status);


// the whole world
int main(int argc, const char * argv[]) {
    
    // playFortuneTeller();
    
     playShellGame();
    
    return 0;
}


/**
 Generates a random number and constrains to a range using modulo
 
 @param mod the value of modulo to use or how many numbers are possible?
 @return a random number % param value
 */
int makeRandNum(int mod)
{
    //use current time as seed for random generator
    std::srand(static_cast<unsigned int>(std::time(0)));
    int randNum = std::rand() % mod;
    
    return randNum;
}

/**
 The game of Fortune Teller.
 
 */
void playFortuneTeller()
{
    std::cout << "What is your burning question? > ";
    std::string placeholder;
    std::getline(std::cin, placeholder);
    
    int answer = makeRandNum(6);
    
    std::cout << "\nThe fortune teller has answered: ";
    switch (answer) {
        case 0:
            std::cout << "Not in your lifetime!" << std::endl;
            break;
        case 1:
            std::cout << "Maybe next week!" << std::endl;
            break;
        case 2:
            std::cout << "Yes!" << std::endl;
            break;
        case 3:
            std::cout << "Reply hazy, try again." << std::endl;
            break;
        case 4:
            std::cout << "Signs point to yes." << std::endl;
            break;
        case 5:
            std::cout << "Very doubtful." << std::endl;
            break;
        case 6:
            std::cout << "You may rely on it." << std::endl;
        default:
            std::cout << "The fortune teller had another call please try again later..." << std::endl;
            break;
    }
    
}

/**
 Prompts player to guess where the shell is.
 
 @param guess the game starts with this = 0 and we replace with input
 @return the player's guess we assume it is 1 - 5
 */

int shellPrompt(int guess)
{
    std::cout << "Where is the shell? Choose box 1-5 > ";
    std::cin >> guess;
    return guess;
}

/**
 Checks to see if the user's guess matches the which box the shell is in.
 Originally a bool but moved to int to support additional status messages.
 
 @param box the value of the box with the shell
 @param guess the value of the user's guess
 @return 1 if winner 2 if not
 */

int isWinner(int box, int guess)
{
    if(guess == box)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

/**
 Prints specific game messages based on a status.
 
 @param status the status to print
 */
void printShellStatus(int status)
{
    if (status == 1)
    {
        std::cout << "Correct!" << std::endl;
    }
    if (status == 2)
    {
        std::cout << "That is incorrect." << std::endl;
    }
    if (status == 3)
    {
        std::cout << "You may try again." << std::endl;
    }
}

/**
 The Shell game.
 */
void playShellGame()
{
    // create and store which box shell is in 1 - 5
    int boxWithShell = makeRandNum(5);
    
    int userGuess = 0;
    int numberOfGuesses = 1;
    
    while(numberOfGuesses < 3)
    {
        // prompt user where is the shell
        userGuess = shellPrompt(userGuess);
        // check if we won
        if(isWinner(boxWithShell, userGuess) == 1)
        {
            // if we won tell the user
            printShellStatus(1);
            break;
        }
        else
        {
            // if we didn't tell them
            printShellStatus(2);
            // can they guess again?
            if(numberOfGuesses == 1)
            {
                printShellStatus(3);
                numberOfGuesses++;
            }
            else
            {
                // if not game over.
                break;
            }
            
        }
    }
}
