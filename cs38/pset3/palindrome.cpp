/*
 Problem 2:  Palindrome
 A palindrome is a sentence that reads the same forward and backward.
 For example, “Madam I’m Adam”.  Note that you have to remove whitespace and
 punctuation to make it work!

 
 
 Create a function called isPalindrome() that takes a character array string as input and returns true/false to indicate whether the string is a palindrome. Use cleanText() and  reverseText() where appropriate.  Test your function within main().
 
 Ground Rules: You must use a character array (i.e., do not use the string class). The function must NOT display anything- it merely returns true or false. Test Cases:  Use the following test cases (which are all palindromes) – and make up two additional test cases of your own that are not palindromes. Are we not drawn onward, we few, drawn onward to new era? Doc, note, I Dissent. A fast never prevents a fatness. I diet on cod. God, Art! Name no pup “One Mantra Dog.”
 */

#include <stdio.h>
#include <cstddef>
#include <iostream>
#include <cstring>
#include <cctype>
#include "palindrome.h"

/**
 takes a character array string as input and modifies it such that all
 punctuation and whitespace are removed.

 @param str unmodified string
 
 */

char* cleanText(char* str)
{
    auto size = std::strlen(str);
    int j = 0;
    for(int i = 0; i < size; i++)
    {
        if(std::isalpha(str[i]))
        {
            str[j] = std::tolower(str[i]);
            
            j++;
        }
        
    }
    str[j] = '\0';
    return str;
}
//Create a function called reverseText() that takes two character array strings as parameters.  The first array is the ordinal string, the second will be the same text in reverse order.
//char* reverseText(char* str1, char* str2)
//{
//
//    return str1;
//
//}
//
//bool isPalindrome(std::string &str)
//{
//    std::string cleaned = cleanText(str);
//    std::string reversed = reverseText(str);
//    if(cleaned == reversed)
//    {
//        return true;
//    }
//    return false;
//}
