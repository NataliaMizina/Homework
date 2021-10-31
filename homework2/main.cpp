#include <iostream>
#include "func.h"



int main(int argc, char** argv) {
    if (argc == 2) {
        std::cout << "file name: " << argv[1] << std::endl;
    }
    else
    {
        std::cout << "no arguments";
        return -1;
    }

    double h0;
    Speed speed;
    Partition* partitions;
    const int startingDotX = 0;

    int numberOfPartitions;
    numberOfPartitions = readNumberOfPartitions(argv[1]);

    if (numberOfPartitions>0) {

        

        partitions = readFile(argv[1], h0, speed, numberOfPartitions);
       

        int answer = MoveForward(h0, speed, partitions, startingDotX, numberOfPartitions, 0);


   
        std::cout << "Dot landed in section: " << answer << std::endl;
       

    }
    else
    {
        std::cout << "Not enough partitions in the file";
    }
    return 0;
}







