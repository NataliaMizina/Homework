#include "func.h"

ans solution(dot* input, int n)
{
    /* расстояние d = x*cos(a) + b*sin(a) ; x,y - точка, cos(a), sin(a) - компоненты нормали
    к направляющему вектору прямой разделяющей плооскость
    d > 0 - точка справа от прямой, d < 0 - точка слева*/
    double sin = input[0].y/sqrt(input[0].x*input[0].x + input[0].y*input[0].y);
    double cos = input[0].x/sqrt(input[0].x*input[0].x + input[0].y*input[0].y);


    double Rightmost = 1;
    dot Rightmostdot{0,0};

    double Leftmost = 1;
    dot Leftmostdot{0,0};

    for (int i = 1; i < n; i++)
    {
        double temp = input[i].x*sin + input[i].y*(-cos);
        double cs = (input[i].x*cos+input[i].y*sin)/sqrt(input[i].x*input[i].x+input[i].y*input[i].y);


        if (cs <= Rightmost && temp >= 0)
        {
            Rightmost = cs;
            Rightmostdot = input[i];
        }
        else if (cs <= Leftmost && temp < 0)
        {
            Leftmost = cs;
            Leftmostdot = input[i];
        }
    }

    return ans {Leftmostdot, Rightmostdot};
}
dot* readFile(const char* path, int& n)
{
    const int MAX = 10;
    char buffer[MAX];
    std::ifstream in(path);
    if(in.is_open())
    {
        while(!in.eof())
        {
            in.getline(buffer, MAX);
            n++;
        }



        dot* dots = new dot[n];
        n = 0;
        in.seekg(0);
        while(!in.eof())
        {
            dot indot;
            in >> indot.x >> indot.y;
            dots[n] = indot;
            n++;
        }

        return dots;
    }
    else {
        throw std::runtime_error("No file!");
    }
}

