//Create a class called Cypher with the following members:
//
//key   - an integer
//
//codedString    - a pointer to a dynamically allocated, null terminated (\0), array of char's
//
//default constructor   – set key to 0, sets codedString to nullptr
//
//parameterized constructor  - takes one parameter which is a file name. This constructor should do the following:
//
//open the file
//read the first line of the file and store  the value as a number in the key
//read the second line of the file in to a string called temp.  Allocate a block of char's big enough to hold the size of temp and point codedString to the new memory block.  Copy temp into the memory block.
//close the file
//copy constructor             – create a proper clone of the object
//
//destructor                            – delete any allocated memory
//
//getCode ();                            - return the codedString member as a string
//
//
//
//Be sure to designate private / public and const specifiers
//
//You may create additional methods or add code to main() if needed
//
//example code (this should be able to run given your class definition)
#include <iostream>
#include <fstream>


class Cypher
{
private:
    int key;
    char * codedString;
    
public:
    Cypher()
    {
        key = 0;
        codedString = nullptr;
    }
    Cypher(std::string fname)
    {
        std::string line;
        std::string temp;
        std::ifstream fs;
        fs.open(fname.c_str());
        int count = 0;
        while(std::getline(fs, line))
        {
            if(count == 0)
            {
                key = 1;
            }else
            {
                temp = line;
            }
            count++;
        }
        
        codedString = new char[temp.size()+1];
        for(int i = 0; i < temp.size(); i++)
        {
            codedString[i] = temp.at(i);
        }
        codedString[temp.size()+1] = '\0';
        fs.close();
    }
    Cypher(const Cypher& cyp)
    {
        key = cyp.key;
        codedString = cyp.codedString;
    }
    
    std::string getCode()
    {
        std::string ret;
        for(int i = 0; codedString[i] != '\0'; i++)
        {
            ret.push_back(codedString[i]);
        }
        
        return ret;
    }

};

int main(int argc, const char * argv[]) {
    Cypher c1;
    Cypher c2("codefile.txt");
    Cypher c3=c2;
    std::cout << c3.getCode() << std::endl;
    
    return 0;
}
