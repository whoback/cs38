//
//  hotdog.hpp
//  pset3
//
//  Created by Will Hoback on 7/11/19.
//  Copyright © 2019 Will Hoback. All rights reserved.
//

#ifndef hotdog_hpp
#define hotdog_hpp

#include <stdio.h>
#include <array>

void Hotdog();
void displayMenu();
void getOrderItem(std::array<int, 3> &quants);
void displayOrderAmounts(std::array<int, 3> &quants);
float calculateSubtotal(std::array<int, 3> &quants, std::array<const float, 3> &price);
float calculateDiscount(float subtotal);
float calculateTax(float subtotal);
std::string formatDollarOutput(double amt);
#endif /* hotdog_hpp */
