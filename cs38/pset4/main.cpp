//
//  main.cpp
//  pset4


#include <iostream>

int* makeFibSeries()
{
    int numToDisplay;
    std::cout << "How many numbers should I display: ";
    std::cin >> numToDisplay;
    int *ptr_ret = &numToDisplay;
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

int main(int argc, const char * argv[]) {

    // insert code here...
    std::cout << "Hello, World!\n";
    fibPartOne();
    return 0;
}



//std::vector<int> generateFibonacciSequence(int N)
//{
//    std::vector<int> vec;
//    std::pair<int, int> x = { 0, 1 };
//    for (int i = 0; i < N; ++i)
//    {
//        x = { x.second, x.first + x.second };
//        int single = x.first;
//        vec.push_back(single);
//    }
//    return vec;
//}
//
//void printFibonacciSequence(std::vector<int> sequence)
//{
//    std::cout << "Your sequence is: ";
//    for(int i = 0; i < sequence.size(); i++)
//    {
//        std::cout << sequence.at(i) << ", ";
//    }
//}
