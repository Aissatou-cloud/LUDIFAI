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

	Pion* GetPion(int indice){ //recuperation du pion on en as besoin dans Jeu 
		if(indice <0 && indice >=4){
			return tab[indice]; //return 1 ptr vers le pion demande
		}else{
			return nullptr; //return nullptr if invalide index
		}
	}

	vector<Pin*> GetPionsEnJeu(){
		vector<Pion*> pions_en_jeu; //init du vecteur qui contiendra les pions en jeu

		for(int i=0; i<4; i++){
			if(!tab[i]->GetEstArrive() && tab[i]->GetEstSorti()){
				pions_en_jeu.push_back(tab[i]); //ajoute le pion s'il est sorti mais pas arrive dans le tableau
			}
		}
		return pions_en_jeu;
	}

