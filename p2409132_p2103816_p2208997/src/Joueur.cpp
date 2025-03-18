#include <iostream>
#include "Joueur.h"

using namespace std;

Joueur::Joueur()
{
	id=0;
	nbpionarrives=0;
}

Joueur::Joueur(int ident, int r, int v, int b)
{
	id=ident;
	nbpionarrives=0;
	couleur=set_color(r,v,b);
	Pion * tab[4];
	for (i=0; i<4;i++)
	{
		tab[0] = new Pion();  
	}
}

int Joueur::getNbpionArrives()
{
	return nbpionarrives;
}

Joueur::~Joueur()
{
	for (int i = 0; i < 4; ++i) 
	{
		delete tab[i];  
	}
}

