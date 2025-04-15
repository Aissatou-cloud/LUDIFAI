#include <iostream>
#include "Joueur.h"
#include <cassert>

using namespace std;

	Joueur::Joueur(): id(1), nbpionarrives(0), a_gagner(false)
	{
		for(unsigned int i=0; i<4; i++){
			tab[i]=Pion(i); //cree 4 pions avec un identifiant unique
		}

	}

	Joueur::Joueur(unsigned int ident, unsigned char r, unsigned char v, unsigned char b):id(ident), nbpionarrives(0)
	{
		couleur.setColor(r,v,b); //correctement initialise
		for (unsigned int i=0; i<4; i++){
			tab[i] = Pion(i);  
		}
	}

	Joueur::~Joueur()
	{
	}

	int Joueur:: getId()const{
		return id;
	}

	int Joueur::getNbpionArrives()
	{
		return nbpionarrives;
	}

	void Joueur::IncrementerNbPionArrive()
	{
		nbpionarrives++;
	}

	Color Joueur:: getCouleur() const {return couleur ;}

	Pion& Joueur::GetPion(int indice)
	{
		assert(indice >=0 && indice <=3);
		return tab[indice];
		
	}

	void Joueur::GetPionsEnJeu(Pion pions_en_jeu[4])
	{
		int index=0;
		for(int i=0; i<4; i++){
			if(!tab[i].GetEstArrive() && tab[i].GetEstSorti())
			{
				pions_en_jeu[index]=tab[i];
				index++;
			}
		}
	}

	bool Joueur::Joueur_Gagnant()
	{
		if(getNbpionArrives()==4)
		{
			a_gagner=true;
		}else{
			a_gagner=false;
		}
		return a_gagner;
	}

