/*
 Problem Set Week 2
 main.cpp
 Will Hoback
 */
#include <iostream>
#include <string>
#include <sstream>
#include <ctype.h>


const float taxRate = 0.0625;

struct newOrder {
    
    const float hotdogCost = 3.50;
    float hotdogQuantity = 0;
    
    const float friesCost = 2.50;
    float friesQuantity = 0;
    
    const float sodaCost = 1.25;
    float sodaQuantity = 0;
    float tax = 0.0625;
    
    float subtotal = 0;
    float total = 0;
};

int opAndIfPractice();
float calcItemSubtoal(float cost, float quant);
float formatFloat(float num);
float calcOrderSubtotal(struct newOrder x);
void printOrder(struct newOrder a);
void orderHotdog(struct newOrder x);
void genFibSeq(int n);

int main() {
    
    //opAndIfPractice();
    //struct newOrder order;
    //orderHotdog(order);
    genFibSeq(10);
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


void genFibSeq(int n)
{
    int arr[30]= {0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,
        610,987,1597,2584,4181,6765,10946,17711,28657,46368,
        75025,121393,196418,317811,514229};
    
    int numToDisplay;
    std::string input;
    
    while((std::cout << "How many numbers should I display: ")
          && std::getline(std::cin, input))
    {
        std::istringstream is {input};
        if((is >> numToDisplay) && !(is >> input) && (numToDisplay <= 30) && (numToDisplay > 0))
        {
            break;
        }
        std::cerr << "Invalid input please try again." << std::endl;
    }
//    std::cin >> numToDisplay;
    for(int i = 0; i < numToDisplay; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}
/**
 Performs basic math to return subtotal of an item/quant pair
 
 @param cost the cost of an item
 @param quant the quantity of an item
 @return the product of cost and quant params
 */

float calcItemSubtoal(float cost, float quant)
{
    return cost * quant;
}


/**
 Used to format output to be no more than .xy decimal places
 
 @param num the number to format 123.4567
 @return the formatted number 123.45
 */
float formatFloat(float num)
{
    // conver to string
    std::string num_s = std::to_string(num);
    
    // find '.'
    std::size_t found;
    found=num_s.find('.');
    // this returns The position of the first character of the first match.
    //    If no matches were found, the function returns string::npos.
    if(found!=std::string::npos)
    {
        // if found resize string
        num_s.resize(found + 3);
    }
    
    return std::stof(num_s, nullptr);
}
/**
 Calculate a discount if our subtotal is >= $20.00
 
 @param sum the calculated sum of our subtotal
 @return either the sum + our discountAmount or just sum if < $20
 */
float calcDiscount(float sum)
{
    float discountAmount;
    discountAmount = sum * .10;
    return sum - discountAmount;
}
/**
 Group and sum our order items into a subtotal
 
 @param x a struct containing order data
 @return sum the formatted 123.12 sum of individual items
 */
float calcOrderSubtotal(struct newOrder x)
{
    // calc indiv item subtotals
    float dogs = calcItemSubtoal(x.hotdogCost, x.hotdogQuantity);
    float fries = calcItemSubtoal(x.friesCost, x.friesQuantity);
    float soda = calcItemSubtoal(x.sodaCost, x.sodaQuantity);
    
    // sum items together
    float sum = dogs + fries + soda;
    
    
    // format and return
    
    sum = formatFloat(sum);
    return sum;
    
}
/**
 Prints out order data formatted to spec
 
 @param a struct containing order data
 */
void printOrder(struct newOrder a)
{
    // print basic order info
    std::cout << "Your order:" << std::endl;
    std::cout << a.hotdogQuantity << " hotdogs" << std::endl;
    std::cout << a.friesQuantity << " fries" << std::endl;
    std::cout << a.sodaQuantity << " drinks" << std::endl;
    
    std::cout << "Subtotal: $" << a.subtotal << std::endl;
    std::cout << "Meals Tax (6.25%): "<< a.tax << std::endl;
    std::cout << "Total Due: $" << a.total << std::endl;
}

/**
 Prompts for input of a new order and saves data to a struct.
 Calcs subtotal / tax / total and calls printOrder()
 
 @param x a struct containing order data
 */
void orderHotdog(struct newOrder x)
{
    // Hotdogs cost $3.50, fries cost $2.50 and soda costs $1.25.  You must also include a meals tax of 6.25%
    // get basic order fino
    std::cout << "Welcome to Joe's" << std::endl;
    std::cout << "How many hotdogs: ";
    std::cin >> x.hotdogQuantity;
    std::cout << "How many fries: " ;
    std::cin >> x.friesQuantity;
    std::cout << "How many drinks: ";
    std::cin >> x.sodaQuantity;
    
    // check if there are no items in the order, let the user know and end the program.
    if(x.hotdogQuantity == 0 && x.friesQuantity == 0 && x.sodaQuantity ==0)
    {
        std::cout << "No items in this order!";
        return;
    }
    
    
    // calc subtotal = sum of all items price * quant
    x.subtotal = calcOrderSubtotal(x);
    // check for discount and apply
    if(x.subtotal > 20)
    {
        x.subtotal = calcDiscount(x.subtotal);
    }
    // calc tax amount
    x.tax = x.subtotal * taxRate;
    x.tax = formatFloat(x.tax);
    // calc total order
    x.total = x.subtotal + x.tax;
    x.total = formatFloat(x.total);
    
    // print order info back to user
    printOrder(x);
    
}
