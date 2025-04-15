#include <iostream>
#include "Joueur.h"
#include <cassert>

using namespace std;

<<<<<<< HEAD
	Joueur::Joueur(): id(1), nbpionarrives(0), a_gagner(false)
	{
		for(unsigned int i=0; i<4; i++){
			tab[i]=Pion(i); //cree 4 pions avec un identifiant unique
		}

=======
Joueur::Joueur(): id(1), nbpionarrives(0), a_gagner(false)
{
	for(unsigned int i=0; i<4; i++){
		tab[i]=new Pion(i); //cree 4 pions avec un identifiant unique
>>>>>>> 72ea47a634b2c832c08041ff2d67195a8de42ea6
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
<<<<<<< HEAD
		couleur.setColor(r,v,b); //correctement initialise
		for (unsigned int i=0; i<4; i++){
			tab[i] = Pion(i);  
=======
		delete tab[i];
		tab[i]=nullptr;  
	}
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

Pion* Joueur::GetPion(int indice){ //recuperation du pion on en as besoin dans Jeu 
	if(indice <0 && indice >=4){
		return tab[indice]; //return 1 ptr vers le pion demande
	}else{
		return nullptr; //return nullptr if invalide index
	}
}

vector<Pion*> Joueur::GetPionsEnJeu(){
	vector<Pion*> pions_en_jeu; //init du vecteur qui contiendra les pions en jeu

	for(int i=0; i<4; i++){
		if(!tab[i]->GetEstArrive() && tab[i]->GetEstSorti()){
			pions_en_jeu.push_back(tab[i]); //ajoute le pion s'il est sorti mais pas arrive dans le tableau
>>>>>>> 72ea47a634b2c832c08041ff2d67195a8de42ea6
		}
	}
	return pions_en_jeu;
}

bool Joueur::Joueur_Gagnant()
{
	if(getNbpionArrives()==4)
	{
<<<<<<< HEAD
=======
		a_gagner=true;
	}else{
		a_gagner=false;
>>>>>>> 72ea47a634b2c832c08041ff2d67195a8de42ea6
	}
	return a_gagner;
}

float Joueur::GetXPion(int id_pion)
{
	return tab[id_pion]->GetCoordoneeXPoule();
}

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
=======
float Joueur::GetYPion(int id_pion)
{
	return tab[id_pion]->GetCoordoneeYPoule();
}
>>>>>>> 72ea47a634b2c832c08041ff2d67195a8de42ea6

void Joueur::RemplirCoordonneePoule(float cx, float cy)
{
	tab[0]->CoordonneesPionPoule(cx, cy);
	tab[1]->CoordonneesPionPoule(cx+2, cy);
	tab[2]->CoordonneesPionPoule(cx, cy-2);
	tab[3]->CoordonneesPionPoule(cx+2, cy-2);
}