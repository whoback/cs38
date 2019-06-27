/*
 Problem Set Week 1
 main.cpp
 Will Hoback
 */
#include <iostream>
#include <string>
#include <ctype.h>

// part 1 define vars keep them out of global namespace
namespace PsetVariables {
    
    int ageOfCat = 7;
    float gradeAvgOfStudent = 92.5;
    int numOfJellyBeansInTub = 399;
    bool doEatPizza = true;
    int maxPeopleAllowed = 250;
}



// tax rate for our food order program
const float taxRate = 0.0625;


// store person and address information
// everything is a string for ease of use
struct nameAndAddress {
    std::string firstName;
    std::string lastName;
    std::string streetNumber;
    std::string streetName;
    std::string streetType;
    std::string city;
    std::string state;
    std::string zip;
};

// store hotdog order information
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

// keep it neat and forward declare our functions

void populateNameAndAddress(struct nameAndAddress y);
float calcItemSubtoal(float cost, float quant);
float formatFloat(float num);
float calcOrderSubtotal(struct newOrder x);
void printOrder(struct newOrder a);
void orderHotdog(struct newOrder x);


// run the show

int main(int argc, const char * argv[]) {
    // initial structs
    struct nameAndAddress userInfo;
    struct newOrder order;
    
    populateNameAndAddress(userInfo);
    orderHotdog(order);
    
    
    
    
    return 0;
}


/**
 Asks user for various information and stores it into a struct.
 Proceeds to print it out in a 3 line format.
 
 @param y a nameAndAddress struct for storing user input
 
 */
void populateNameAndAddress(struct nameAndAddress y)
{
    
    std::cout << "Please enter your first name: " << std::endl;
    std::getline(std::cin, y.firstName);
    std::cout << "Please enter your last name: " << std::endl;
    std::getline(std::cin, y.lastName);
    std::cout << "Please enter your street number: " << std::endl;
    std::getline(std::cin, y.streetNumber);
    std::cout << "Please enter your street name: " << std::endl;
    std::getline(std::cin, y.streetName);
    std::cout << "Please enter your street type: " << std::endl;
    std::getline(std::cin, y.streetType);
    std::cout << "Please enter your city: " << std::endl;
    std::getline(std::cin, y.city);
    std::cout << "Please enter your state: " << std::endl;
    std::getline(std::cin, y.state);
    std::cout << "Please enter your zip: " << std::endl;
    std::getline(std::cin, y.zip);
    
    //  print in 3 line format
    //    John Doe
    //    3 Main Street
    //    Anywhere, MA 02241
    std::cout << y.firstName << " " << y.lastName << std::endl;
    std::cout << y.streetNumber << " " << y.streetName << " " << y.streetType << std::endl;
    std::cout << y.city << "," << " " << y.state << " " << y.zip << std::endl;
    
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
    std::cout << "How many hotdogs: " <<std::endl;
    std::cin >> x.hotdogQuantity;
    std::cout << "How many fries: " <<std::endl;
    std::cin >> x.friesQuantity;
    std::cout << "How many drinks: " <<std::endl;
    std::cin >> x.sodaQuantity;
    
    
    
    
    // calc subtotal = sum of all items price * quant
    x.subtotal = calcOrderSubtotal(x);
    // calc tax amount
    x.tax = x.subtotal * taxRate;
    x.tax = formatFloat(x.tax);
    // calc total order
    x.total = x.subtotal + x.tax;
    x.total = formatFloat(x.total);
    
    // print order info back to user
    printOrder(x);
    
}
