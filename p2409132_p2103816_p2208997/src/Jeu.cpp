#include "Jeu.h"
#include <iostream>

using namespace std;

Jeu::Jeu()
{
    int nb=4;
    De de;
    for (unsigned char i=0;i<4; i++)
    {
        Joueur = joueur(i, i*20, i *20, i *20);
    }
}
