//
//  main.cpp
//  pset1
//
#include <iostream>
#include <string>
#include <ctype.h>
// tax rate for our food order program
const float taxRate = 0.0625;

// part 1 define vars
int ageOfCat = 7;
float gradeAvgOfStudent = 92.5;
int numOfJellyBeansInTub = 399;
bool doEatPizza = true;
int maxPeopleAllowed = 250;

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
    // Display the order, the subtotal, the tax amount and the total.
    
    float subtotal = 0;
    float total = 0;
};


void populateNameAndAddress(nameAndAddress y)
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

float calcItemSubtoal(float cost, float quant)
{
    // basic math to return subtitle of an item/quant pair
    return cost * quant;
}

// format output to be no more than .xy decimal places

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


float calcOrderSubtotal(struct newOrder x)
{
    // calc indiv item subtotals
    float dogs = calcItemSubtoal(x.hotdogCost, x.hotdogQuantity);
    float fries = calcItemSubtoal(x.friesCost, x.friesQuantity);
    float soda = calcItemSubtoal(x.sodaCost, x.sodaQuantity);
    
    // sum items together
    float sum = dogs + fries + soda;
    
    // format and return
    return formatFloat(sum);
    
}

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

int main(int argc, const char * argv[]) {
    // initial structs
    struct nameAndAddress userInfo;
    struct newOrder order;

    populateNameAndAddress(userInfo);
    orderHotdog(order);



    
    return 0;
}
