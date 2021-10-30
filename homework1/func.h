#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <exception>

struct dot{
    double x;
    double y;
};

struct ans
{
    dot left;
    dot right;
};

ans solution(dot* input, int n);
dot* readFile(const char* path, int& n);

