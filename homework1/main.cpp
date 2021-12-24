#include "func.h"
#include <climits>
using namespace std;


int main()
{
    int n = 0;
    try
    {
        Point* points = readFile("in.txt", n);

        int maxLeftX=0;
        int maxLeftY=0;
        int maxRightX=0;
        int maxRightY=0;

        if (n>1)
        {
            Answer res = firstVar(points, n);
            maxLeftX =res.left.x;
            maxLeftY =res.left.y;
            maxRightX =res.right.x;
            maxRightY =res.right.y;
        }

        cout << "max left: " << maxLeftX<< ' ' << maxLeftY << '\n' <<
             "max right: " << maxRightX << ' ' << maxRightY << endl;

        delete points;
    }
    catch(std::runtime_error err)
    {
        cout << err.what() << endl;
    }

    cin.clear();
    cin.ignore(INT_MAX, '\n');

    return 0;
}
