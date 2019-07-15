//
//  main.cpp
//  pset4


#include <iostream>

class Money{
public:
    int dollars;
    int cents;
};

int* makeFibSeries(int n)
{
    
    int *ptr_ret;
    // the c way
    //ptr_ret = (int *)malloc(sizeof(int) * n);
    // the c++ way
    ptr_ret = new int[n];
    // use pointer indexing not array indexing
    *(ptr_ret + 0) = 0;
    *(ptr_ret + 1) = 1;
    for(int i = 2; i < n; ++i)
    {
        *(ptr_ret + i) = *(ptr_ret + i-1) + *(ptr_ret + i-2);
    }
    
    return ptr_ret;
}
void fibPartOne()
{
    int fib[30];
    int *ptr_arr = fib;
    *(ptr_arr + 0) = 0;
    *(ptr_arr + 1) = 1;
    for(int i = 2; i < 30; ++i)
    {
        *(ptr_arr + i) = *(ptr_arr + i-1) + *(ptr_arr + i-2);
    }
    for(int x = 0; x < 30; ++x)
    {
        std::cout << *(ptr_arr + x) << std::endl;
    }
    
    
}

//Create a function called allocName. This function should take as input a first name and a last name.  It should then dynamically allocate a memory block to store the full name and return a pointer to the name.   In main(), call allocName, display the full name and then deallocate the memory block.
char* allocName(char* first, char* last)
{
    char* full;
    full = new char[strlen(first) + strlen(last) + 1];
    strcat(full, first);
    strcat(full, " ");
    strcat(full, last);
    return full;
}

//Create a structure or a class called Money that contains int members for dollars and cents. Create a function called addMoney() that takes three parameters:   a Money instance and an amount of dollars and cents to add (dollars and cents are separate  int’s) Create a function called showMoney() that displays a Money object as $d.cc In main() create some money, add $3.75 to it using addMoney, display the resulting amount using showMoney()
void addMoney(Money &m, const int dollars, const int cents)
{
    m.dollars = dollars;
    m.cents = cents;
}

void showMoney(const Money &m)
{
    std::cout << "$" << m.dollars << "." << m.cents << std::endl;
}

//Write a function called subString that returns a char *. It will take three input parameters: a char * and two int's: an index and howmany.   The function should return a substring that is formed from the index position of the input string for howmany characters or until the termination character (‘\0’) is encountered.   howmany should default to creating a substring that continues to the termination character.

char* subString(char* s, int index, int howmany = 0)
{
    // if user didn't provide us with a number of chars
    // default to finding the distance from index -> termination character
    if(howmany == 0)
    {
        howmany = 0;
        
        while (s[howmany] != '\0') {
            howmany++;
        }
        
        howmany = howmany - index;
        
    }
    
    //allocate space for new string based on howmany + 1 for null term
    char* ret = new char[howmany+1];
    
    
    for(int i = 0; i < howmany; i++)
    {
        ret[i] = s[index + i];
        
    }
    ret[howmany] = '\0';
    return ret;
}
int main(int argc, const char * argv[]) {
    
    //fibPartOne();
    // part 2
    //    int *make;
    //    int numToDisplay;
    //    std::cout << "How many numbers should I display: ";
    //    std::cin >> numToDisplay;
    //    make = makeFibSeries(numToDisplay);
    //    for(int x = 0; x < numToDisplay; ++x)
    //    {
    //        std::cout << *(make + x) << std::endl;
    //    }
    // allocName
    //    char first[5]  = "Will";
    //    char last[7] = "Hoback";
    //    char* full = allocName(first, last);
    //    std::cout << full << std::endl;
    //    delete full;
    
    // deallocation
    // c way
    // free(make);
    // c++ way
    // delete make;
    
    //    Money money;
    //    int d = 42;
    //    int c = 99;
    //    addMoney(money, d, c);
    //    showMoney(money);
    
    char s1[80] = "Hello There";
    char * s2 = subString(s1, 3);     // returns "lo There"
    
    std::cout << s2;
    //
    //
    //
    return 0;
}
