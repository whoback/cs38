/*
Problem 2:  Palindrome
*/
#include "palindrome.hpp"

    
void Pdrome()
{
    char test1[] = "Are we not drawn onward, we few, drawn onward to new era?";
    char test2[] = "Doc, note, I Dissent. A fast never prevents a fatness. I diet on cod.";
    char test3[] = "God, Art! Name no pup “One Mantra Dog.”";
    char notP[] = "not A PAlindrome for sURE!";
    char notP2[] = "United States women's national soccer team won the world cup.";
    
    isPalindrome(test1);
    isPalindrome(test2);
    isPalindrome(test3);
    isPalindrome(notP);
    isPalindrome(notP2);
}

/**
 takes a string and removes all non alpha chars

 @param str a string to clean
 @return the cleaned string
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

/**
 takes two strings uses the first as the model to reverse

 @param str1 string to reverse
 @param str2 string to return in reverse order
 @return a copy of str1 in reverse order
 */
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

/**
 Checks to see if a given string is a palindrome

 @param str the string to check
 @return bool
 */
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
