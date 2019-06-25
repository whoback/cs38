//
//  main.cpp
//  gameset1

#include <iostream>
#include <cstdlib>
#include <string>


void playFortuneTeller()
{
    std::cout << "What is your burning question? > ";
    std::string placeholder;
    std::getline(std::cin, placeholder);
    std::srand(std::time(0)); //use current time as seed for random generator
    int answer = std::rand() % 6;
    
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

int main(int argc, const char * argv[]) {
    
    playFortuneTeller();
    
    return 0;
}
