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

Jeu::~Jeu()
{
    for (Joueur * joueur: joueurs)
    {
        delete joueur;
    }
} //Plus besoin de delete[] car 'vector' gere la mem automatiquement, pour chq joueur du vector on delete

void Jeu::AffichageLimiteTerrain_SDL(int x, int y, char t[4])
{
for (int i = 0; i < y; i++)  
	{
		for (int j = 0; j < x; j++) 
		{
			if (i == 0 || i == y - 1)   
				std::cout << "-";
			else if (j == 0 || j == x - 1) 
				std::cout << "|";
			else if (j<=2 && i<=2)
				std::cout<<t[1];
			else if (i >= y - 3 && j >= x - 3)
				std::cout<<t[2];
			else if (i<=2 && j>=27)
				std::cout<<t[3];
			else if (j<=2 && i>=12)
				std::cout<<t[0];
            else if (
                ((i == 5 || i == 9) && (j <= 10 || j >= 20)) ||  
                ((j == 10 || j == 20) && (i <= 5 || i >= 9)) ||  
                ((i == 1 || i == y - 2) && j >= 10 && j <= 20) ||  
                ((j == 1 || j == x - 1 || j == x - 2) && i >= 5 && i <= 9))
				std::cout<<"*";
			else 
				std::cout << ".";  
		}	std::cout <<std::endl; 
	}
}

int Jeu::LancerDe(unsigned int id_joueur){
    int val_de=de.GetVal();
    cout<<"le joueur: "<<joueurs[id_joueur]->getId()<< "a lance le de : "<<val_de<< endl;
    return val_de;
}

vector<Pion*> Jeu:: RecupDesPionsEnJeu(Joueur &joueur){
    vector<Pion*> pionsEnjeu;
    for(int i=0; i<4; i++){
        Pion * pion = joueur.GetPion(i);    //recupère les pions, tu peux pas utiliser tab direct

        if(!pion->GetEstArrive() && pion->GetEstSorti()){
            pionsEnjeu.push_back(joueur.GetPion(i));
        }
    }
    return pionsEnjeu;
}

bool Jeu::GererEntreeJeu(Joueur &joueur, int val_de){
    if (val_de==6){
        //chercher un pion qui n'est pas encore sorti
        for(int i=0; i<4; i++){
            Pion* pion_sorti=joueur.GetPion(i);
            if(!pion_sorti->GetEstSorti()){ //si le pion n'est pas sorti
                pion_sorti->SortirBase();
                cout<<"le joueur: "<< joueur.getId() <<" a fait sortir un pion" <<endl;
                return true;
            }

        }
        
    }
    cout<<"Aucun pion en jeu(no 6)"<<endl;
    return false;
}

Pion* Jeu::ChoisirPion(vector<Pion*> PionsEnJeu, Joueur &joueur ){
    if(PionsEnJeu.size()== 1){ //si un seul pion en jeu, le return
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

    return joueur.GetPion(choix -1);
}

void Jeu::DeplacerPion(Pion* pion, int val_de){
    pion->SeDeplace(val_de);
    cout<<"le pion "<< pion->GetId()<< "avance de " <<val_de <<"cases." <<endl;
}


void Jeu::VerifierCollision(Pion* pion_deplace, Joueur &joueur_actuel){
    for(size_t i=0; i<joueurs.size(); i++){     // ici i de type size_t type entier non signé pour représenter taille des objets en mémoire,
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

void Jeu::VerifierArrivee(Pion* pion, Joueur &joueur){
    if(pion->GetId() >= 56){ //si 5- est la derniere cas
        joueur.IncrementerNbPionArrive(); //on increment le nbpionarrive, impossible de faire nbpionarrivee ++ car membre privee
        cout<<"Le pion " <<pion->GetId()<<" du joueur "<<joueur.getId()<< " est arrive "<<endl;

    }
}

void Jeu::Gerer_Tour(Joueur &joueur){
    cout<<"Tour du joueur: "<< joueur.getId()<<"!"<<endl;
    
    //1.lancé du dé
    int val_de=LancerDe(joueur.getId());


    // recuperer les pions en jeu
    vector<Pion*> pions_en_jeu=RecupDesPionsEnJeu(joueur);

    //gerer le cas ou aucun pion n'est sur le plateau
    if(pions_en_jeu.empty()){
        if(GererEntreeJeu(joueur, val_de)) return ;
        return ;
    }

    //choisir un pion à deplacer
    Pion* pion_choisi=ChoisirPion(pions_en_jeu, joueur);
    
    //deplacer le pion
    DeplacerPion(pion_choisi, val_de);

    //verifier les collisions
    VerifierCollision(pion_choisi,joueur);

    //veifier si un pion a atteint l'arrivee
    VerifierArrivee(pion_choisi, joueur);

    cout <<"Fin du tour du joueur " <<joueur.getId() <<endl;

}

void Jeu::Demarer_Jeu(char tab[4])
{
    
    int taille_x, taille_y;         //taille plateau
    taille_x = 30;    //affichage a part 
    taille_y = 15;

    AffichageLimiteTerrain_SDL(taille_x, taille_y, tab);


    cout<<"Le jeu commence avec: "<< nb_Joueur<< "joueurs" <<endl;

    //Affichage des joueurs et leur couleurs
    for( int i=0; i< nb_Joueur; i++){
        cout<<"Player: "<<joueurs[i]->getId()<< " -Color: ( "
        <<(int)joueurs[i]->getCouleur().getR()<<", " 
        <<(int)joueurs[i]->getCouleur().getV()<<", " 
        <<(int)joueurs[i]->getCouleur().getB()<<" )"<<endl;

    }
    
    bool continu;
    continu= true;
    do{

        for(int i=0; i<nb_Joueur; i++){
            Gerer_Tour(*joueurs[i]);  //on passe par reference
        }

        if(joeur)
    }


}

