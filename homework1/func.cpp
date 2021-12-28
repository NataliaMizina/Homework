#include "func.h"
#include <climits>
Answer firstVar(Point* input, int n)
{

    double x0 = -input[0].x;
    double y0 = input[0].y;


    double maxRight = 0.7;
    Point maxRightPoint{0,0};

    double maxLeft = 0.7;
    Point maxLeftPoint{0,0};

    for (int i = 0; i < n; i++)
    {
        double delta = -x0*input[i].x+y0*input[i].y;
        double cos = (input[i].y*y0-input[i].x*x0)/(sqrt(x0*x0+y0*y0)*sqrt(input[i].y*input[i].y+input[i].x*input[i].x));

        if (cos >= maxRight && delta >=0 )
        {
            maxRight = cos;
            maxRightPoint = input[i];
        }
        else if (cos <= maxLeft && delta <0)
        {
            maxLeft = cos;
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
