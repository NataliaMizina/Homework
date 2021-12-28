#include "func.h"
#include <climits>
Answer firstVar(Point* input, int n)
{

    double sin = -input[0].x;
    double cos = input[0].y;


    double maxRight = 1;
    Point maxRightPoint{1,1};

    double maxLeft = 1;
    Point maxLeftPoint{1,1};

    for (int i = 0; i < n; i++)
    {
        int delta = input[i].y*sin+input[i].x*(-cos);
        double dist = (input[i].y*cos-input[i].x*sin)/(sqrt(sin*sin+cos*cos)*sqrt(input[i].y*input[i].y+input[i].x*input[i].x));

        if (dist >= maxRight && delta >=0)
        {
            maxRight = dist;
            maxRightPoint = input[i];
        }
        else if (dist <= maxLeft && delta<0)
        {
            maxLeft = dist;
            maxLeftPoint = input[i];
        }
    }

    return Answer {maxLeftPoint, maxRightPoint};
}
Point* readFile(const char* path, int& n)
{

    std::ifstream in(path);
    if(in.is_open())
    {
        while(!in.eof())
        {
            int x = INT_MAX;  int y = INT_MAX;
            in >> x >> y;
            if (x!=INT_MAX && y!= INT_MAX) n++;
        }

        in.close();

        if (n<2) return nullptr;

        Point* points = new Point[n];
        int i = 0;
        in.open(path);
        while(!in.eof() && i<n)
        {
            Point inPoint;
            in >> inPoint.x >> inPoint.y;
            points[i] = inPoint;
            i++;
        }

        in.close();
        return points;
    }
    else {
        throw std::runtime_error("No file!");
    }
}
