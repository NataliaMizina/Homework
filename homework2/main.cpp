#include <iostream>
#include "func.h"



int main(int argc, char** argv) {
    if (argc == 2) {
        //std::cout << "file name: " << argv[1] << std::endl;
    }
    else
    {
        std::cout << "no arguments, or more than expected";
        return -1;
    }

    double h0;
    Speed speed;
    Partition* partitions;
    const int startingDotX = 0;

    int numberOfPartitions;
    numberOfPartitions = readNumberOfPartitions(argv[1]);

    if (numberOfPartitions>0) {
       //std::cout << "numberOfPartitions: " << numberOfPartitions << std::endl;

        partitions = readFile(argv[1], h0, speed, numberOfPartitions);
       //std::cout << "h0: " << h0 << "   speed.vx: " << speed.vx << "   speed.vy: " << speed.vy << std::endl;


/*        for (int i=0;i<numberOfPartitions;i++)
            std::cout << "partitions["<< i+1 << "].x: " << partitions[i].x << "   partitions[" << i+1 << "].h: " << partitions[i].h << std::endl;
        std::cout << "---------------------------------------" << std::endl;*/

        int answer = MoveForward(h0, speed, partitions, startingDotX, numberOfPartitions, 0);

        //std::cout << "================================" << std::endl;
        //std::cout << "Dot landed in section: ";
        std::cout << answer << std::endl;
        //std::cout << "================================" << std::endl;

    }
    else
    {
        std::cout << "0";
    }
    return 0;
}







