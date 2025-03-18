#ifndef JOUEUR_H
#define JOUEUR_H
#include "Pion.h"
#include "Color.h"

class Joueur
{
	private:
    	int id;
    	int nbpionarrives;
    	Pion * tab[4];  
    	Color couleur; 	
    public:
    	Joueur();
    	Joueur(int indent,int r, int v, int b);
    	int getNbpionArrives();
    	~Joueur();
};

#endif
