/*
 Problem Set Week 2
 main.cpp
 Will Hoback
 */
#include <iostream>

int opAndIfPractice();

int main() {
    // insert code here...
    std::cout << "Hello, World!\n";
    opAndIfPractice();
    return 0;
}

int opAndIfPractice()
{
//    Create three variables: x, y, z, all integers and a double called d.
    int x, y, z;
    double d;
    //Set x and y to 10
    x = 10;
    y = 10;
    //Add one to x using the = and + operators.
    x = x + 1;
    std::cout << "x=" << x << std::endl;
    //Add one to x using the ++ operator. Display
    x++;
    std::cout << "x=" << x << std::endl;
    //Add one to x using the += operator. Display
    x += 1;
    std::cout << "x=" << x << std::endl;
    //Set y to 4 and z to 8. Divide z by y and store the result in x.  Display
    y = 4;
    z = 8;
    x = z / y;
    std::cout << "x=" << x << std::endl;
    //Divide y by z and store the result in d. Display.
    d = y / z;
    std::cout << "d=" << d << std::endl;
    //If x is greater than 0, add 10 to x. Display x.
    if(x > 0)
    {
        x += 10;
        std::cout << x << std::endl;
    }
    //If x is greater than 0 and y is less than 10, add 1 to d.  Display x, y, d
    if(x > 0 && y < 10)
    {
        d++;
        std::cout << "x=" << x << std::endl;
        std::cout << "y=" << y << std::endl;
        std::cout << "d=" << d << std::endl;
    }
    //If x is greater than 0 or y is less than 10, add 1 to d.  Display x, y, d
    if(x > 0 || y < 10)
    {
        d++;
        std::cout << "x=" << x << std::endl;
        std::cout << "y=" << y << std::endl;
        std::cout << "d=" << d << std::endl;
    }
    return 0;
}
