#include <iostream>
#include "NVector.h"

using namespace std;

int main()
{
    NVector v(4);
    cin >> v;

    NVector v2(4);
    cin >> v;

    NVector result = v + v2;

    cout << result << endl;
}