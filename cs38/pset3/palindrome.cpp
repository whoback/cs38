/*
Problem 2:  Palindrome
A palindrome is a sentence that reads the same forward and backward.
For example, “Madam I’m Adam”.  Note that you have to remove whitespace and
punctuation to make it work!

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
