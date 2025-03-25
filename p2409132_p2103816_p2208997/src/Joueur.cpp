#include <iostream>
#include "Joueur.h"

using namespace std;

	Joueur::Joueur(): id(1), nbpionarrives(0), a_gagner(false)
	{
		for(unsigned int i=0; i<4; i++){
			tab[i]=new Pion(i); //cree 4 pions avec un identifiant unique
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

