#include "De.h"
#include <cstdlib>   //pour rand()


De::De()
{
    val = 1;
}

De::~De()
{
    val = 0;
}

int De::GetVal() const
{
    return rand()%7 + 1;
}