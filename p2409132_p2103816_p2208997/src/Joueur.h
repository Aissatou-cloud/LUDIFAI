#ifndef JOUEUR_H
#define JOUEUR_H
#include "Pion.h"
#include "Color.h"

class Joueur
{
	private:
    	unsigned int id;
    	int nbpionarrives;
    	Pion * tab[4];  
    	Color couleur; 	
    public:
    	Joueur();
		Joueur(unsigned int indent,unsigned char r, unsigned char v, unsigned char b);
		~Joueur();
		int getId() const;
		Color getCouleur() const ;
    	int getNbpionArrives();
    	
};

#endif
