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
        joueurs.push_back(Joueur(i,0, 0, 0)); //ajoute a la fin du vector
      //gerer la couleur 
    }
}

Jeu::Jeu(int nb_j): nb_Joueur(nb_j){
   
    for (int i=0;i<nb_j; i++)
    {
        joueurs.push_back(Joueur(i,0, 0, 0));      //gerer la couleur 
    }
}

Jeu::~Jeu(){} //Plus besoin de delete[] car 'vector' gere la mem automatiquement

void Jeu::AffichageLimiteTerrain_SDL(int x, int y)
{
    for(int i=0; i<x; i++)
    {
        cout<<"-";
    }
    cout<<endl;

    for (int i=0; i<y; i++)
    {
        cout<<"|";
        for(int j=0; j<x-2; j++)
        {
            cout<<" ";
        }
        cout<<"|"<<endl;
    }

    for(int i=0; i<x; i++)      
    {
        cout<<"-";
    }
    cout<<endl;
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
