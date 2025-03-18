#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur
{
	private:
    	int id;
    	int nbpionarrives;
    	Pion * tab[4];  
    	Color couleur; 	
    public:
    	Joueur();
    	Joueur(int indent);
    	int getNbpionArrives();
    	~Joueur();
};

#endif

