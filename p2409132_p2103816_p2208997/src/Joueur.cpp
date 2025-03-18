#include <iostream>
#include "Joueur.h"
#include "Pion.h"
using namespace std;

Joueur::Joueur()
{
	id=0;
	nbpionarrives=0;
}
Joueur::Joueur(int ident)
{
	id=ident;
	nbpionarrives=0;
}

int Joueur::getNbpionArrives()
{
	return nbpionarrives;
}

Color Joueur::setcouleurjoueur()
{
	couleur=set_color(r,v,b);
}

Joueur::~Joueur(){}

