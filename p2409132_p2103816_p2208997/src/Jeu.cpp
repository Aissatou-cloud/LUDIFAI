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

Pion* ChoisirPion(vector<Pion*> PionsEnJeu, Joueur &joueur ){
    if(PionsEnJeu.size== 1){ //si un seul pion en jeu, le return
        return PionsEnJeu[0]; 
    }

    cout<<"Choississez 1 pion à déplacer (1-4): ";
    int choix;
    cin>>choix;

    while(choix < 1 || choix > 4 ||
         !joueur.GetPion(choix -1)->GetEstSorti() || joueur.GetPion(choix -1)->GetEstArrive()){
            cout<<"choix de pon invalide.Reessayer !";
            cin>>choix;
    }

    return joeur.GetPion(choix -1);
}

void DeplacerPion(Pion* pion, int val-de){
    pion->SeDeplace(val_de);
    cout<<"le pion "<< pion->GetId()<< "avance de " <<val_de <<"cases." <<endl;
}


void VerifierCollision(Pion* pion_deplace, Joueur &joueur_actuel){
    for(int i=0; i<joueurs.size(); i++){
        Joueur& autre_joueur = *joueurs[i];   //Utlisation de la boucle 

        if(autre_joueur.getId() !=joueur_actuel.getId()){
            for(int j=0; j<4; j++){
                if(autre_joueur.GetPion(i)->GetI() == pion_deplace->GetI()){
                    autre_joueur.GetPion(i)->RetournerBase();
                    cout << "Le pion adverse "<< autre_joueur.GetPion(i)->GetI()
                    <<" retourne àa la base"<<endl;   
                }
            }
        }
    }

}

void VerifierArrivee(Pion* pion, Joueur &joueur){
    if(pion.GetI() >= 56){ //si 5- est la derniere cas
        joueur.nbpionarrives ++; //on increment le nbpionarrive
        cout<<"Le pion " <<pion->GetId()<<" du joueur "<<joueur.GetId()<< " est arrive "<<endl;

    }
}

void Jeu::Gerer_Tour(Joueur &joueur){
    cout<<"Tour du joueur: "<< joueur.getID()<<"!"<<endl;
    
    //1.lancé du dé
    int val_de=LanceDe();


    // recuperer les pions en jeu
    vector<Pion*> pions_en_jeu=RecupererPonsEnJeu(joueur);

    //gerer le cas ou aucun pion n'est sur le plateau
    if(pions_en_jeu.empty()){
        if(GererEntreeJeu(joueur, val_de)) return ;
        return ;
    }

    //choisir un pion à deplacer
    Pion* pion_choisi=ChoisiPion(pions_en_jeu, joueur);
    
    //deplacer le pion
    DeplacerPion(pion_choisi, val_de);

    //verifier les collisions
    VerifierCollisions(pion_choisi,joueur);

    //veifier si un pion a atteint l'arrivee
    VerifierArrivee(pion_choisi, joueur);

    cout <<"Fin du tour du joueur " <<joueur.getId() <<ensl;



}

