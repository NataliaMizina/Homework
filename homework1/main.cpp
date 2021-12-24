#include "func.h"
#include <climits>

using namespace std;


int main()
{
    int n = 0;
    try
    {
        dot* dots = readFile("in.txt", n);
        ans result = solution(dots, n);

        cout << "Leftmost: " << result.left.x << ' ' << result.left.y << '\n' <<
             "Rightmost: " << result.right.x << ' ' << result.right.y << endl;

        delete dots;
    }
    catch(std::runtime_error err)
    {
        cout << err.what() << endl;
    }

    cin.clear();
    cin.ignore(INT_MAX, '\n');

    return 0;
}
