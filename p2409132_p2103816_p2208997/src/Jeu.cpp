#include "Jeu.h"
#include <iostream>

using namespace std;

Jeu::Jeu()
{
    int nb_joueur=4;
    De de;
    Joueur * joueur = new Joueur[nb_joueur];

    for (int i=0;i<nb_joueur; i++)
    {
        joueur[i] = Joueur(i, 0, 0, 0);       //gerer la couleur 
    }
}

<<<<<<< HEAD


=======
Jeu::Jeu(int nb_j)
{
    De de;
    Joueur * joueurs = new Joueur[nb_j];

    for (int i=0;i<nb_j; i++)
    {
        joueurs[i] = Joueur(i, 0, 0, 0);       //gerer la couleur 
    }
}

Jeu::~Jeu()
{
    delete [] joueurs;
}

void Jeu::AffichageLimiteTerrain_SDL(int x, int y)
{
    for(int i=0; i<x; i++)
    {
        cout<<"-";
    }
    cout<<endl;

    for (int i=0; i<y; i++)
    {
        cout<<"|";
        for(int j=0; j<x-2; j++)
        {
            cout<<" ";
        }
        cout<<"|"<<endl;
    }

    for(int i=0; i<x; i++)      
    {
        cout<<"-";
    }
    cout<<endl;
}

void Jeu::Demarer_Jeu()
{
    int taille_x, taille_y;         //taille plateau
    taille_x = 30;    //affichage a part 
    taille_y = 15;

    AffichageLimiteTerrain_SDL(taille_x, taille_y);
}
>>>>>>> 62fb08fdc869c48bc8a4b4fff9da16f52991db60
