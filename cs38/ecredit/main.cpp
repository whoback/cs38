// part 2 of the extra credit assignment
// will hoback
// goal is to read in ampie.txt, lowercase all words, remove all punc,
// count word frequency, sort by word frequency, and then display higher frequency
// to lower frequency words

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

int main(int argc, const char * argv[]) {
    //use map becuase it only allows one entry per word
    //int will count how many are in the song
    std::map<std::string, int> mapofwords;
    std::string fname = "ampie.txt";
    std::string str;
    std::fstream fs;
    
    //open our file
    fs.open(fname);
    //if we can read it
    if (fs.is_open()) {
        //read words into str
        while(fs >> str)
        {
            //remove anything thats not an alpha in str
            //having fun with lambda functions
            str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x){return !std::isalpha(x);}), str.end());
            
            //luckily no uppercases in middle of words so just set every first letter of str tolower
            char c = str.front();
            str.at(0) = std::tolower(c);
            
            //add str to our map OR if already added increment value
            // this works because of how map implements the []operator
            mapofwords[str]++;
        }
        
    }
    //close our file now that we're done
    fs.close();
    
    //vector of pairs of string,ints to hold our words and freqs
    std::vector<std::pair<std::string, int>> vecoffreqs;
    
    //loop over our map and add them to our vec
    for(auto x = mapofwords.begin(); x != mapofwords.end(); x++) {
        vecoffreqs.push_back(*x);
    }
    //sort our vec we want high frequency to low frequency
    //more lambda function fun
    std::sort(vecoffreqs.begin(), vecoffreqs.end(), [=](std::pair<std::string, int>& first, std::pair<std::string, int>& second)
              {
                  return first.second > second.second;
              });
    
    //print our vec
    for(auto i = 0; i < vecoffreqs.size(); i++)
    {
        std::cout << "Frequency of word: '" << vecoffreqs.at(i).first << "'" <<" --- " << vecoffreqs.at(i).second<< std::endl;
    }
    return 0;
}
