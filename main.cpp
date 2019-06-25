//
//  main.cpp
//  pset1
//
#include <iostream>
#include <string>

// part 1 define vars
int ageOfCat = 7;
float gradeAvgOfStudent = 92.5;
int numOfJellyBeansInTub = 399;
bool doEatPizza = true;
int maxPeopleAllowed = 250;

// store person and address information
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
    std::string hotdogItem = "Hotdog";
    float hotdogCost = 3.50;
    int hotdogQuantity = 0;
    std::string friesItem = "Fries";
    float friesCost = 2.50;
    int friesQuantity = 0;
    std::string sodaItem = "Soda";
    float sodaCost = 1.25;
    int sodaQuantity = 0;
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

void orderHotdog(struct newOrder x)
{
    // Hotdogs cost $3.50, fries cost $2.50 and soda costs $1.25.  You must also include a meals tax of 6.25%
    // get basic order fino
    
    // calc subtotal
    // calc tax amount
    // calc total order
}

void orderCalc(struct newOrder x)
{
    
}

int main(int argc, const char * argv[]) {
    struct nameAndAddress userInfo;
    struct newOrder order;
    populateNameAndAddress(userInfo);
    
    
    
    return 0;
}
