#include <iostream>
#include "SetByCriteria.h"
#include "SetByString.h"

int main()
{
    SetByString s(1000, "1 5 9");
    s.print();
    s.setAt(1, '0');
    s.print();


    SetByCriteria s2(11, [](unsigned i) {return i % 2 == 0; });

    s2.print();
}
