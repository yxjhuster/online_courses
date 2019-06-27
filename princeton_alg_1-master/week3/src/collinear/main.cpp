#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>

#include "collinear.h"


using PointsList = std::list<my::Point>;


void testAlgorithm(const PointsList& points) {

    std::list<my::Segment> res;
    my::findCollinearBruteForce(points.begin(), points.end(), std::back_inserter(res));
    printRange("result: ", res.begin(), res.end());

}

void trimLeft(std::string& str) {
    size_t pos = str.find_first_not_of(" ");
    if( pos != std::string::npos)
    str = str.substr(pos);
}

bool readDataFromFile(const char* fileName, std::list<my::Point>& pointList) {
    std::string line;
    std::ifstream f(fileName);

    if (f.is_open()) {
        // first line in file contains number of points in file
        auto pointCount = 0;
        if (getline(f, line)) {
            try {
                pointCount = std::stoi(line);
            } catch(...) {
                f.close();
                std::cerr << "faled to parse file - invalid data" << std::endl;
                return false;
            }
        }
        // read points and push them to back of the output list
        while (pointCount > 0 && getline(f, line)) {
            trimLeft(line);
            size_t pos = line.find_first_of(" ");
            if(pos != std::string::npos) {
                int x, y = 0;
                try {
                    x = std::stoi(line.substr(0, pos));
                    y = std::stoi(line.substr(pos + 1));
                } catch(...) {
                  f.close();
                  std::cerr << "faled to parse file - invalid data" << std::endl;
                  return false;
                }
                pointList.push_back(my::Point(x, y));
                pointCount--;
            }
        }

        if(pointCount != 0) {
            std::cerr << "faled to parse file - invalid data" << std::endl;
            return false;
        }

        f.close();
        return true;
    }

    std::cerr << "failed to open file" << std::endl;
    return false;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "invalid command line arguments" << std::endl;
        exit(1);
    }

    // list to hold input data from file
    std::list<my::Point> inputPoints;

    const char* fileName = argv[1];
    if(!readDataFromFile(fileName, inputPoints)) {
        std::cerr << "failed to read data from specified file" << std::endl;
        exit(1);
    }

    testAlgorithm(inputPoints);
    return 0;
}
