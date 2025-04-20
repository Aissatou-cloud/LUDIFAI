#include "AffichageSDL.h"
#include <iostream>

using namespace std;

int main()
{
    srand(time(NULL));
    AffichageSDL sj;
    
    Jeu J;
    J.GetJoueur(0)->SetType(HUMAIN);
    J.GetJoueur(1)->SetType(IA);      // IA ici
    J.GetJoueur(2)->SetType(HUMAIN);
    J.GetJoueur(3)->SetType(HUMAIN);

    sj.SdlBoucle(J);

    return 0;
}