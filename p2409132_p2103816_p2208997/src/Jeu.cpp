#include "Jeu.h"
#include <iostream>

using namespace std;

Jeu::Jeu(): nb_Joueur(4)
{
    //int nb_Joueur=4;
    De de;
    /*Comme on a un vector de joeur on aura pas besoin d'allouer et desallouer dynmiquement
    car vector le gere automatiquemnt pour nous
    et aussi VECTOR nous permet d'ajouter(PUSH.BACK) ou de retirer des joueurs avec ces methodes
    sans se soucier de la taille du tab 
     */
    for (int i=0;i<nb_Joueur; i++)
    {
        joueurs.push_back(new Joueur(i,0, 0, 0)); //ajoute a la fin du vector
      //gerer la couleur 
    }
}

Jeu::Jeu(int nb_j): nb_Joueur(nb_j){
   
    for (int i=0;i<nb_j; i++)
    {
        joueurs.push_back(new Joueur(i,0, 0, 0));      //gerer la couleur 
    }
}

Jeu::~Jeu(){
    for(int i; i<nb_Joueur; i++){
        delete Joueur;
    }
} //Plus besoin de delete[] car 'vector' gere la mem automatiquement

void Jeu::AffichageLimiteTerrain_SDL(int x, int y)
{
	for (int i = 0; i < y; i++)  
	{
		for (int j = 0; j < x; j++) 
		{
			if (i == 0 || i == y - 1)   
				cout << "-";
			else if (j == 0 || j == x - 1) 
				cout << "|";
			else if (j<=2 && i<=2)
				cout<<"r";
			else if (i >= y - 3 && j >= x - 3)
				cout<<"b";
			else if (i<=2 && j>=27)
				cout<<"v";
			else if (j<=2 && i>=12)
				cout<<"n";
			else if ((i==5 && j<=10) || (i==5 && j>=20) || 
			(i==9 && j<=10) || (i==9 && j>=20) || (j==10 && i<=5) 
			|| (j==10 && i>=10) || (i==1 && j>=10 && j<=20) || 
			(i==y-2 && j>=10 && j<=20) || 
			(i==1 && j>=10 && j<=20) || 
			(j==1 && i>=5 && i<=9) || (j==x-1 && i>=5 && i<=9) 
			|| (j==20 && (i>=9 || i<=5) ) || (j==x-2 && i>=5 && i<=9))
				cout<<"*";
			else 
				cout << ".";  
		}
		cout << endl; 
	}
}
void Jeu::Demarer_Jeu(){
    
    int taille_x, taille_y;         //taille plateau
    taille_x = 30;    //affichage a part 
    taille_y = 15;

    AffichageLimiteTerrain_SDL(taille_x, taille_y);


    cout<<"Le jeu commence avec: "<< nb_Joueur<< "joueurs" <<endl;

    //Affichage des joueurs et leur couleurs
    for( int i=0; i< nb_Joueur; i++){
        cout<<"Player: "<<joueurs[i].getId()<< " -Color: ( "
        <<(int)joueurs[i].getCouleur().getR()<<", " 
        <<(int)joueurs[i].getCouleur().getV()<<", " 
        <<(int)joueurs[i].getCouleur().getB()<<" )"<<endl;

    }

}

int Jeu::LancerDe(){
    int val_de=Get.Val();
    cout<<"le joueur: "<<joueur.getID()<< "a lance le de : "<<val_de<< endl;
    return val_de;
}

vector<Pion*> Jeu:: RecupDesPionsEnJeu(Joueur &joueur){
    vector<Pion*> pionsEnjeu;
    for(int i=0; i<4; i++){
        if(!tab[i]->GetEstArrive() && tab[i]->GetEstSorti()){
            pionsEnJeu.push_back(joueur.GetPion(i));
        }
    }
    return pionsEnJeu;
}

bool GererEntreeJeu(Joueur &joueur, int val_de){
    if(val_de==6){
        //chercher un pion qui n'est pas encore sorti
        for(int=0; i<4; i++){
            Pion* pion_sorti=joueur.GetPion(i);
            if(!pion_sorti.GetEstSorti()){ //si le pion n'est pas sorti
                pion_sorti.SortirBase();
                cout<<"le joueur: "<< joueur.getID() <<" a fait sortir un pion" <<endl;
                return true;
            }

        }
        
    }
    cout<<<"Aucun pion en jeu(no 6)"<<endl;
    return false;
}


/*void Jeu::Gerer_Tour(Joueur &joueur){
    cout<<"Tour du joueur: "<< joueur.getID()<<"!"<<endl;
    
    //1.lancé du dé
    int val_de=Get.Val();
    cout<<"le joueur: "<<joueur.getID()<< "a lance le de : "<<val_de<< endl;


    //Deplacemnt du pion
    vector<Pion*> pions_en_jeu;
    for(int=0; i<4; i++){
        Joue
    }



}*/

