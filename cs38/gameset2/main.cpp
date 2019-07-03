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
int main(int argc, const char * argv[]) {
    std::string wordToGuess = randomAccessLibrary(lib);
    std::cout << wordToGuess << std::endl;
    return 0;
}


