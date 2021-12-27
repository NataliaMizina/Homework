#include "func.h"
#include <climits>

Answer firstVar(Point* input, int n)
{
    /* расстояние d = x*cos(a) + b*sin(a) ; x,y - точка, cos(a), sin(a) - компоненты нормали
    к направляющему вектору прямой разделяющей плооскость
    d > 0 - точка справа от прямой, d < 0 - точка слева*/
    double sin = -input[0].x/sqrt(input[0].x*input[0].x + input[0].y*input[0].y);
    double cos = input[0].y/sqrt(input[0].x*input[0].x + input[0].y*input[0].y);


    double maxRight = 0;
    Point maxRightPoint{0,0};

    double maxLeft = 0;
    Point maxLeftPoint{0,0};

    for (int i = 0; i < n; i++)
    {
        double dist = input[i].x*cos + input[i].y*sin;

        if (dist >= maxRight)
        {
            maxRight = dist;
            maxRightPoint = input[i];
        }
        else if (dist <= maxLeft)
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


