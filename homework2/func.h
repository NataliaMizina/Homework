#include <iostream>

const double g = 9.81;

struct Speed {
    double vx;
    double vy;
};

struct Partition {
    double x;
    double h;
};

int MoveForward(double h, Speed &speed, const Partition *partitions, int currentDotX, int numberOfPartitions,
                int startingPartition);
int MoveBack(const Partition *partitions, int i, double XofHitPartition, double DotYatPartition, Speed &speed,
             int numberOfPartitions);
double calculateC(double h);
double calculateB(const Speed &speed);
double calculateA(const Speed &speed);
double getDotYatPartition(double partitionX, double h, Speed speed, double previousDotX);
double GetXofFreeFall(double h, Speed speed, double currentDotX, bool right);
int readNumberOfPartitions(char *string);
Partition* readFile(char *path, double &h0, Speed &speed, int partitionsNumber);
