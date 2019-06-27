#include <iostream>
#include <stdlib.h>
#include <time.h>   
#include <string>

#include "percolation.h"


void trimLeft(std::string& str) {
    size_t pos = str.find_first_not_of(" ");
    if( pos != std::string::npos)
        str = str.substr(pos);
}

int main(int argc, char* argv[]) {

    std::string countLine;
    int count = 0;
    if(std::getline(std::cin, countLine)) 
        count = atoi(countLine.c_str());
    else 
        return 1;

    std::string line;
    Percolation percol(count);
    while(std::getline(std::cin, line)) {
        trimLeft(line);
        if(line.empty())
            continue;
        size_t pos = line.find_first_of(" ");
        if(pos != std::string::npos) {
            int i = std::stoi(line.substr(0, pos));
            int j = std::stoi(line.substr(pos + 1));
            percol.open(i, j);

        }
    }                
    
    auto resultMsg = percol.percolates() ? "system percolates" : "system does not percolate";
    std::cout << resultMsg << std::endl;

    return 0;
}
