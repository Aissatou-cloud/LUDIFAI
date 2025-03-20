#include <iostream>
#include "Joueur.h"

using namespace std;

	Joueur::Joueur(): id(1), nbpionarrives(0) 
	{
		for(unsigned int i=0; i<4; i++){
			tab[i]=new Pion(i+1); //cree 4 pions avec un identifiant unique
		}
	}

	Joueur::Joueur(unsigned int ident, unsigned char r, unsigned char v, unsigned char b):id(ident), nbpionarrives(0)
	{
		couleur.setColor(r,v,b); //correctement initialise
		for (unsigned int i=0; i<4; i++){
			tab[i] = new Pion(i+1);  
		}
	}

	Joueur::~Joueur()
	{
		/*for (unsigned int i = 0; i < 4; ++i) 
		{
			delete tab[];  
		}*/
	}

	int Joueur:: getId()const{
		return id;
	}

	int Joueur::getNbpionArrives()
	{
		return nbpionarrives;
	}

	Color Joueur:: getCouleur() const {return couleur ;}

