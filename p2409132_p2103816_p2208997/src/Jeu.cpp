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
    for(int i=0; i<5; i++){
        chemin[i]={6*40, (13-i)*40};
    }
    for(int i=10; i>=5; i--){
        chemin[i]={(10-i)*40, 8*40};
    }
    chemin[11]={0, 7*40};
    for(int i=12; i<18; i++){
        chemin[i]={(12-i)*40, 6*40};
    }
    for(int i=23; i>=18; i--){
        chemin[i]={6*40, (23-i)*40};
    }
    chemin[24]={7*40, 0};
    for(int i=25; i<31; i++){
        chemin[i]={8*40, (i-25)*40};
    }
    for(int i=31; i<37; i++){
        chemin[i]={(i-12)*40, 6*40};
    }
    chemin[37]={14*40, 7*40};
    for(int i=38; i<44; i++){
        chemin[i]={(52-i)*40, 8*40};
    }
    for(int i=44; i<50; i++){
        chemin[i]={8*40, (i-35)*40};
    }
    chemin[50]={7*40, 14*40};
    chemin[51]={6*40, 14*40};
    chemin[52]={6*40, 13*40};

    for(int i=0; i<6; i++){
        zone_Gagnante_R[i]={7*40, (13-i)*40};
    }
    for(int i=0; i<6; i++){
        zone_Gagnante_J[i]={7*40, (i+1)*40};
    }
    for(int i=0; i<6; i++){
        zone_Gagnante_V[i]={(i+1)*40, 7*40};
    }
    for(int i=0; i<6; i++){
        zone_Gagnante_B[i]={(13-i)*40, 7*40};
    }

    case_Depart_R=0;
    case_Depart_V=13;
    case_Depart_J=26;
    case_Depart_B=39;
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

int Jeu::JoueurLanceDe(unsigned int id_joueur, De de){
    de.LancerDe();
    cout<<"le joueur: "<<joueurs[id_joueur]->getId()<< "a lance le de : "<<de.GetVal()<< endl;
    return de.GetVal();
}

vector<Pion*> Jeu:: RecupDesPionsEnJeu(Joueur &joueur){
    vector<Pion*> pionsEnjeu;
    for(int i=0; i<4; i++){
        Pion * pion = joueur.GetPion(i);    //recupère les pions, tu peux pas utiliser tab direct

        if(pion != nullptr && !pion->GetEstArrive() && pion->GetEstSorti()){
            pionsEnjeu.push_back(pion);
        }
    }
    return pionsEnjeu;
}

bool Jeu::GererEntreeJeu(Joueur &joueur, int val_de){
    //val_de = de.GetVal();
    if (val_de==6){
        //chercher un pion qui n'est pas encore sorti
        for(int i=0; i<4; i++){
            Pion* pion_sorti=joueur.GetPion(i);
            if(pion_sorti != nullptr && !pion_sorti->GetEstSorti()){ //si le pion n'est pas sorti
                pion_sorti->SortirBase();
                cout<<"le joueur: "<< joueur.getId() <<" a fait sortir un pion" <<endl;
                cout << "Statut après sortie : " << pion_sorti->GetEstSorti() << endl;  // Vérifie si c'est bien true
                return true;
            }

        }
        
    }
    //cout<<"Aucun pion en jeu(no 6)"<<endl;
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
    pion->SetI(val_de);
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
    //pour debuguer
    if(joueur.Joueur_Gagnant()){
        cout<<"Le joueur "<< joueur.getId()<< "a deja gagné !" <<endl;
        return ; 
    }

    if(joueur.Joueur_Gagnant()==false)
    {
        cout<<"Tour du joueur: "<< joueur.getId()<<"!"<<endl;
        
       //Recup les pions en jeu avant de lancer le dé
       vector<Pion*> pions_en_jeu=RecupDesPionsEnJeu(joueur);

        //1.lancé du dé
        int val_de=0;
        De de;
        val_de=JoueurLanceDe(joueur.getId(), de);

        //2.si aucun pio n'est en jeu, essayer de faire entrer un pion

        //gerer le cas ou aucun pion n'est sur le plateau
        if(pions_en_jeu.empty()){
            //val_de=JoueurLanceDe(joueur.getId(), de);
            if(GererEntreeJeu(joueur, val_de)){
                cout<<"Un pion du joueur " <<joueur.getId()<< " est entré en jeu "<<endl;
                return ; //fin du tour si un pion a éte mis en jeu

            }else{
                cout<<"Aucun pion ne peut entrer en jeu.Fin du tour joueur "<<joueur.getId()<< endl;
                return ; //fin du tour si aucun pion ne peut entrer en jeu
            }
          
        }

        //choisir un pion à deplacer
        Pion* pion_choisi=ChoisirPion(pions_en_jeu, joueur);
        if(!pion_choisi){
            cout<<"Aucun pion valide selectionne" <<endl;
            return;
        }

        //deplacer le pion
        DeplacerPion(pion_choisi, val_de);

        //veifier si un pion a atteint l'arrivee avant de verifier la collision
        VerifierArrivee(pion_choisi, joueur);

        //verifier les collisions sssi le pion n'a pas atteint l'arrivee
        if(!pion_choisi->GetEstArrive()){
            VerifierCollision(pion_choisi,joueur);
        }
        
        //verifier si le joueur a gagne apres son move
        if(joueur.Joueur_Gagnant())
        {
            joueurs_gagnants.push_back(&joueur);        //passe l'adresse 
        }

        cout <<"Fin du tour du joueur " <<joueur.getId() <<endl;        
    }

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

        if(joueurs_gagnants.size()==(static_cast<long unsigned int>(nb_Joueur)-1))
        {
            continu=false;
        }
    }while(continu);


}


pair<int, int> Jeu::  GetCoordonnes(int index) const{
    return chemin[index];
}

pair<int, int> Jeu:: GetZoneGagnateRouge(int index) const{
    return zone_Gagnante_R[index];
}

Joueur* Jeu:: GetJoueur(int id) {    
    return joueurs[id];
}
