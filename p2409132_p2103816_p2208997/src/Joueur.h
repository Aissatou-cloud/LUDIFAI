#ifndef JOUEUR_H
#define JOUEUR_H
#include <vector>
#include "Pion.h"
#include "Color.h"

using namespace std;

class Joueur
{
	private:
    	unsigned int id;
    	int nbpionarrives;
    	Pion tab[4];  
    	Color couleur; 	
		bool a_gagner;
    public:
    	Joueur();
		//Joueur(const Joueur& j) : 
		Joueur(unsigned int indent,unsigned char r, unsigned char v, unsigned char b);
		~Joueur();
		unsigned int getId() const;
		Color getCouleur() const ;
    	int getNbpionArrives() const;
		void IncrementerNbPionArrive();
		Pion& GetPion(int indice); //recuperation du pion
		void GetPionsEnJeu(Pion pions_en_jeu[4]);  //recuperation du tableau statique de pions qui sont en jeu
		bool Joueur_Gagnant();

		float GetXPion(int id_pion) const;
		float GetYPion(int id_pion) const;
		
		void RemplirCoordonneePoule(float cx, float cy);
};

#endif
