//
//  hotdog.cpp
//  pset3
//
//  Created by Will Hoback on 7/11/19.
//  Copyright © 2019 Will Hoback. All rights reserved.
//

#include "hotdog.hpp"
#include <array>
#include <iostream>
#include <iomanip>
#include <algorithm>

// hotdogs, fries, soda
std::array<const float, 3> itemPrice{3.50, 2.50, 1.25};
std::array<int, 3> itemQuantity{0,0,0};

void Hotdog()
{
    int sent = 0;
    do {
        getOrderItem(itemQuantity);
        displayOrderAmounts(itemQuantity);
        std::cout << "Continue ordering (yes or no): " << std::endl;
        std::string confirmation;
        std::cin >> confirmation;
        if(confirmation == "no")
        {
            sent = 1;
        }
        
    } while(sent == 0);
    
    float subtotal = calculateSubtotal(itemQuantity, itemPrice);
    std::string fmtsubtotal = formatDollarOutput(subtotal);
    float discount = calculateDiscount(subtotal);
    std::string fmtdiscount = formatDollarOutput(discount);
    float tax = calculateTax(subtotal);
    std::string fmttax = formatDollarOutput(tax);
    float total = subtotal - discount + tax;
    std::string fmttotal = formatDollarOutput(total);
    
    std::cout << "Subtotal: " << " $" << fmtsubtotal << std::endl;
    std::cout << "Discount: " << " $" << fmtdiscount << std::endl;
    std::cout << "Tax: " << "      $" << fmttax << std::endl;
    std::cout << "Total: " << "    $" << fmttotal << std::endl;
    
}


/**
 displays the menu to the user and then takes in a quantity for each item selected

 @param quants array of quantities of each item
 */
void getOrderItem(std::array<int, 3> &quants)
{
    displayMenu();
    int choice;
    std::cin >> choice;
    
    int orderAmount = 0;
    if(choice == 1)
    {
        std::cout << "How many orders of hotdog do you want?" << std::endl;
        std::cin >> orderAmount;
        quants.at(0) += orderAmount;
        
    }
    if(choice == 2)
    {
        std::cout << "How many orders of fries do you want?" << std::endl;
        std::cin >> orderAmount;
        quants.at(1) += orderAmount;
    }
    if(choice == 3)
    {
        std::cout << "How many orders of soda do you want?" << std::endl;
        std::cin >> orderAmount;
        quants.at(2) += orderAmount;
    }
    
}

/**
 Displays the menu to the user
 */
void displayMenu()
{
    std::cout << "Choose next item (order by item number)\n";
    std::cout<< "1: hotdog\n2: fries\n3: soda\n";
}

/**
 Displays the current item amounts in the order

 @param quants an array of quantities of each of our items
 */
void displayOrderAmounts(std::array<int, 3> &quants)
{
    std::cout<< "Your order\n";
    std::cout<< "hotdog: " << quants.at(0) << "\n";
    std::cout<< "fries: " << quants.at(1) << "\n";
    std::cout<< "soda: " << quants.at(2) << "\n";
}

/**
 Calculate the subtotal of the order

 @param quants quantities of our orders as an array of ints
 @param price price of our items as an array of const floats
 @return a float of the sum of all items * their price
 */
float calculateSubtotal(std::array<int, 3> &quants, std::array<const float, 3> &price)
{
    float hotdogs = quants.at(0) * price.at(0);
    float fries = quants.at(1) * price.at(1);
    float soda = quants.at(2) * price.at(2);
    float sub = hotdogs + fries + soda;
    return sub;
}

/**
 calculates a 10% discount if the subtotal is >= 20.00

 @param subtotal current subtotal as a float
 @return the amount of the discount either 10% of the subtotal or zero
 */
float calculateDiscount(float subtotal)
{
    if(subtotal >= 20)
    {
        return subtotal * .10;
    }
    return 0;
}
float calculateTax(float subtotal)
{
    return subtotal * 0.0625;
}

/**
 Takes a float amount and formats it to be xx.xx for currency use.

 @param amt amount of money as a float
 @return a string formatted as xx.xx
 */
std::string formatDollarOutput(double amt)
{
    std::string orig = std::to_string(amt);
    std::string search = ".";
    auto pos = orig.find_first_of(search);
    auto end = orig.size();
    orig.erase(pos+3, end);
    
    return orig;
}
