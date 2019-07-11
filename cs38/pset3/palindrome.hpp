//
//  palindrome.hpp
//  pset3
//
//  Created by Will Hoback on 7/11/19.
//  Copyright © 2019 Will Hoback. All rights reserved.
//

#ifndef palindrome_h
#define palindrome_h
#include <stdio.h>
#include <cstddef>
#include <iostream>
#include <cstring>
#include <cctype>

void Pdrome();
char* cleanText( char* str );
char* reverseText( char* str1,  char* str2);
bool isPalindrome( char* str);
#endif /* palindrome_h */
