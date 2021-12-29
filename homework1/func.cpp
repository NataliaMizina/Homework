#include <iostream>
#include <fstream>
#include "func.h"
#include <cmath>
#include <cfloat>

int MoveForward(double h, Speed &speed, const Partition *partitions, int currentDotX, int numberOfPartitions,
                int startingPartition) {
    double DotXatFreeFall = GetXofFreeFall(h, speed, currentDotX, true);
    //std::cout << "DotXatFreeFall: " << DotXatFreeFall << std::endl;

    if (DotXatFreeFall <= partitions[0].x)
    {
        return 0;  // недолёт до первой перегородки
    }
    else
    {
        int i = startingPartition;
        while (i<numberOfPartitions && DotXatFreeFall >= partitions[i].x)
        {
            double DotYatPartition = getDotYatPartition(partitions[i].x, h, speed, currentDotX);
            //std::cout << "dot Y at partition[" << i + 1 << "]: " << DotYatPartition << std::endl;
            if (partitions[i].h>=DotYatPartition) {
                //std::cout << "partition [" << i + 1 << "].h = " << partitions[i].h << ": HIT" << std::endl;

                if (startingPartition==i)  // если startingPartition не 0, значит точка летит вперёд
                      return startingPartition;                      //  после отскока назад, и если при этом она ударилась
                                                                     // о следующую перегородку после той от которой отскочила,
                                                                     // то она уже не выберется из пространства между этими перегородками

                //----------------------------------------------------------
                Speed speedNew;
                speedNew.vx=-1*speed.vx;
                speedNew.vy=speed.vy-(g/speed.vx*partitions[i].x);

                int answer = MoveBack(partitions, i, partitions[i].x, DotYatPartition, speedNew, numberOfPartitions);
                return answer;
                //----------------------------------------------------------
            }
            //else
                //std::cout << "partition [" << i + 1 << "].h = " << partitions[i].h << ": jumped over" << std::endl;
            i++;
        }
        return i;

    }
}


int MoveBack(const Partition *partitions, int i, double XofHitPartition, double DotYatPartition, Speed &speed,
             int numberOfPartitions) {
    double DotXatFreeFallBack = GetXofFreeFall(DotYatPartition, speed, XofHitPartition, false);
    //std::cout << "DotXatFreeFallBack: " << DotXatFreeFallBack << std::endl;

    if (DotXatFreeFallBack > partitions[i-1].x) {
        return i;
    }
    else {
        int j = i-1;
        while (j>=0 && DotXatFreeFallBack <= partitions[j].x) {
            double DotYatPartitionBack = getDotYatPartition(partitions[j].x, DotYatPartition, speed,
                                                            XofHitPartition);
            //std::cout << "dot Y at partition[" << j + 1 << "] back: " << DotYatPartitionBack << std::endl;
            if (partitions[j].h >= DotYatPartitionBack) {
                //std::cout << "partition [" << j + 1 << "].h = " << partitions[j].h << ": HIT" << std::endl;
                if (j==i-1) return j+1; // если точка на пути назад ударилась об предыдущую перегородку, она уже никуда не вылетит
                //----------------------------------------------------------
                Speed speedNew;
                speedNew.vx=-1*speed.vx;
                speedNew.vy=speed.vy-(g/speed.vx*partitions[j].x);

                int answer = MoveForward(DotYatPartitionBack, speedNew, partitions, partitions[j].x, numberOfPartitions,j+1);
                return answer;
                //----------------------------------------------------------
            } //else
                //std::cout << "partition [" << j + 1 << "].h = " << partitions[j].h << ": jumped over" << std::endl;
            j--;
        }
        return j+1;
    }
}

double getDotYatPartition(double partitionX, double h, Speed speed, double previousDotX) {
    double DotYatPartition;
    double A;
    double B;
    double C;

    A= calculateA(speed);
    B= calculateB(speed);
    C= calculateC(h);

    DotYatPartition = A*pow(partitionX-previousDotX,2)+B*(partitionX-previousDotX)+C;
    return DotYatPartition;
}

double GetXofFreeFall(double h, Speed speed, double currentDotX, bool right) {
    double A;
    double B;
    double C;
    double D;

    A = calculateA(speed);
    B = calculateB(speed);
    C = calculateC(h);
    D= pow(B, 2) - 4 * A * C;
    if (D < 0) throw std::runtime_error("Discriminant is less than 0. No solution");

    double x1 = ((-1*B + sqrt(D)) / (2 * A))+currentDotX;
    double x2 = ((-1*B - sqrt(D)) / (2 * A))+currentDotX;

    if (right)
        if (x1>currentDotX) return x1; else return x2;
    else
        if (x1<currentDotX) return x1; else return x2;

}

double calculateC(double h) {
    double c;
    c = h;
    //std::cout << "   C: " << c << std::endl;
    return c;
}

double calculateB(const Speed &speed) {
    double b;
    b= speed.vy / speed.vx;
    //std::cout << "   B: " << b << std::endl;
    return b;
}

double calculateA(const Speed &speed) {
    double a;
    double a_znamenatel = 2 * (pow(speed.vx, 2) + pow(speed.vy, 2));
    double a_chislitel =  g*(1+(pow(speed.vy,2)/pow(speed.vx,2)));
    a=   -1 * a_chislitel / a_znamenatel;
    //std::cout << "   A: " << a << std::endl;
    return a;
}

int readNumberOfPartitions(char *path) {
    int lines=0;

    std::ifstream in(path);
    if(in.is_open())
    {
        double num;
        in >> num;
        while(!in.eof())
        {
            double firstnum = DBL_MAX ; double secondnum = DBL_MAX;
            in >> firstnum >> secondnum;
            if (firstnum!=DBL_MAX && secondnum!=DBL_MAX) lines++;
        }
        in.close();
        return lines-1;
    }
    else
    {
        throw std::runtime_error("No file!");
    }
}


Partition* readFile(char *path, double &h0, Speed &speed, int partitionsNumber) {

    std::ifstream in(path);
    if(in.is_open())
    {
        in >> h0;
        in >> speed.vx >> speed.vy;

        Partition* partitions = new Partition[partitionsNumber];

        int i=0;
        while(!in.eof())
        {
            Partition inPoint;
            in >> inPoint.x >> inPoint.h;
            partitions[i] = inPoint;
            i++;
        }

        return partitions;

    }
    else {
        throw std::runtime_error("No file!");
    }

}

