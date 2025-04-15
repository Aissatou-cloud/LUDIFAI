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
		tab[i] = new Pion(i);  
	}
}

Joueur::~Joueur()
{
	for (unsigned int i = 0; i < 4; i++) 
	{
		couleur.setColor(r,v,b); //correctement initialise
		for (unsigned int i=0; i<4; i++){
			tab[i] = Pion(i);  
		}
	}
	return pions_en_jeu;
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

float Joueur::GetXPion(int id_pion) const
{
	assert( id_pion>=0);
	assert( id_pion<4);
	assert( tab[ id_pion]);
	return tab[id_pion]->GetCoordoneeXPoule();
}

<<<<<<< HEAD
<<<<<<< HEAD
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

float Joueur::GetYPion(int id_pion) const

{
	assert( id_pion>=0);
	assert( id_pion<4);
	assert( tab[ id_pion]);
	return tab[id_pion]->GetCoordoneeYPoule();
}


void Joueur::RemplirCoordonneePoule(float cx, float cy)
{
	assert( tab[0]);
	assert( tab[1]);
	assert( tab[2]);
	assert( tab[3]);
	tab[0]->CoordonneesPionPoule(cx, cy);
	tab[1]->CoordonneesPionPoule(cx+1.75, cy);
	tab[2]->CoordonneesPionPoule(cx, cy-1.75);
	tab[3]->CoordonneesPionPoule(cx+1.75, cy-1.75);
}