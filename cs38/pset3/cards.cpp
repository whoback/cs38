//
//  cards.cpp
//  pset3
#include "cards.hpp"
#include <string>
#include <iterator>
#include <cstddef>
#include <random>
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
std::random_device r;
std::mt19937 gen(r());

void Card()
{
    std::vector<std::string> ranks {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    typedef enum suit {
        club,
        diamond,
        heart,
        spade,
    } suit;
    
    std::uniform_int_distribution<> ds(0, 3);
    std::uniform_int_distribution<> dr(0, 12);
    
    int c = ds(gen);
    int& cardsuit = c;
    std::string cardactual = ranks.at(dr(gen));
    std::string &cardrank = cardactual;
    
    
    dealACard(cardsuit, cardrank);
    
}


/**
 Deals a rand card when called

 @param cardsuit int from 0 - 3 representing card suits
 @param cardrank string of the value of our card
 @return an int representing the value of our card
 */
int dealACard(const int &cardsuit, const std::string &cardrank)
{
    int value = 0;
    if (cardrank == "Ace") value = 1;
    if (cardrank == "Jack" || cardrank == "Queen"  || cardrank == "King" || cardrank == "Ten" ) {
        value = 10;
    }
    if(cardrank == "Two") value = 2;
    if(cardrank == "Three") value = 3;
    if(cardrank == "Four") value = 4;
    if(cardrank == "Five") value = 5;
    if(cardrank == "Six") value = 6;
    if(cardrank == "Seven") value = 7;
    if(cardrank == "Eight") value = 8;
    if(cardrank == "Nine") value = 9;
    return value;
}
