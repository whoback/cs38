//
//  main.cpp
//  pset3
//
//  Created by Will Hoback on 7/8/19.
//  Copyright © 2019 Will Hoback. All rights reserved.
//
#include "palindrome.h"
#include <iostream>
#include <string>
#include <iterator>
#include <cstddef>

int main(int argc, const char * argv[]) {
    char x[] = "Are we not drawn onward, we few, drawn onward to new era?";
    char y[] = "civic";
//    if(isPalindrome(x)) std::cout << x << std::endl;
//    if(isPalindrome(y)) std::cout << y << std::endl;
    
    cleanText(x);
    
    return 0;
}
