/*
Problem 2:  Palindrome
A palindrome is a sentence that reads the same forward and backward.
For example, “Madam I’m Adam”.  Note that you have to remove whitespace and
punctuation to make it work!

*/
#include "palindrome.hpp"

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
char* reverseText(char* str1, char* str2)
{
    auto size = std::strlen(str1);
    char cpy[size];
    std::strcpy(cpy, str1);
    
    auto j = size-1;
    for(int i = 0; i < size; i++)
    {
        str2[j] = cpy[i];
        j--;
    }
    str2[size] = '\0';
    return str2;
}

bool isPalindrome(char* str)
{
    cleanText(str);
    auto size = std::strlen(str);
    char cpy[size];
    
    char * r;
    r = reverseText(str, cpy);

    if(std::strcmp(r, str) == 0)
    {
        return true;
    }
    return false;
}
