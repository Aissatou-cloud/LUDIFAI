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

void De::LancerDe()
{
    val = rand()%6+1;
}

int De::GetVal() const
{
    return val;
}

