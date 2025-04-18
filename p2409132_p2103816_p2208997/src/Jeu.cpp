#include "Jeu.h"
#include <iostream>
#include <cassert>

using namespace std;

Jeu::Jeu(): nb_Joueur(4)
{
    //int nb_Joueur=4;
    etat = ATTENTE_LANCER_DE;
    De de;
    joueur_actuel = 0;
    

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



    joueurs[0]->RemplirCoordonneePoule(1.75, 12.5);  //rouge
    joueurs[1]->RemplirCoordonneePoule(1.75, 3.5);  //vert
    joueurs[2]->RemplirCoordonneePoule(10.75, 3.5); //jaune
    joueurs[3]->RemplirCoordonneePoule(10.75, 12.5); //bleu


    for(int i=0; i<5; i++){
        chemin[i]={6, (13-i)};
    }
    //for(int i=10; i>5; i--){
        //chemin[i]={(10-i), 8};
    //}
    for(int i=5; i<=10; i++)   //me
    {
        chemin[i]={(10-i), 8};
    }
    chemin[11]={0, 7};
    /*for(int i=12; i<18; i++){
        chemin[i]={(12-i), 6};
    }*/
    for(int i=12; i<18; i++)
    {
        chemin[i]={(i-12), 6};
    }
    for(int i=23; i>=18; i--){
        chemin[i]={6, (23-i)};
    }
    chemin[24]={7, 0};
    for(int i=25; i<31; i++){
        chemin[i]={8, (i-25)};
    }
    for(int i=31; i<37; i++){   //////10 11 12 13
        chemin[i]={(i-22), 6};
    }
    chemin[37]={14, 7};
    for(int i=38; i<44; i++){
        chemin[i]={(52-i), 8};
    }
    for(int i=44; i<50; i++){
        chemin[i]={8, (i-35)};
    }
    chemin[50]={7, 14};
    chemin[51]={6, 14};
    chemin[52]={6, 13};

    for(int i=0; i<6; i++){
        zone_Gagnante_R[i]={7, (13-i)};
    }
    for(int i=0; i<6; i++){
        zone_Gagnante_J[i]={7, (i+1)};
    }
    for(int i=0; i<6; i++){
        zone_Gagnante_V[i]={(i+1), 7};
    }
    for(int i=0; i<6; i++){
        zone_Gagnante_B[i]={(13-i), 7};
    }

    //le tableau des coord de depart de chaque pion des chaque joueur
    LesCasesDepart[0]=chemin[0];
    LesCasesDepart[1]=chemin[13];
    LesCasesDepart[2]=chemin[26];
    LesCasesDepart[3]=chemin[39];
    //les case de depart de chaque joueur
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
/*
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

*/
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

        /*for(int i=0; i<nb_Joueur; i++){
            Gerer_Tour(*joueurs[i]);  //on passe par reference
        }*/

        if(joueurs_gagnants.size()==(static_cast<long unsigned int>(nb_Joueur)-1))
        {
            continu=false;
        }
    }while(continu);


}


pair<int, int> Jeu::GetCoordonnes(int index) const{
    return chemin[index];
}

pair<int, int> Jeu::GetZoneGagnateRouge(int index) const{
    return zone_Gagnante_R[index];
}


Joueur* Jeu::GetJoueur(unsigned int id) const
{
    assert(id<4);
    return joueurs[id];
}

De& Jeu::GetDe()
{
    return de;
}


void Jeu::Gerer_Tour(Joueur & j, bool & sortir_pion, bool & lancer_de)
{
    //pair<int,int> cordoDepart = LesCasesDepart[j.getId()];

    //if(de.GetVal()==6 && (j.GetNbpionArrives()<4|| (sortir_pion)) )
    if (sortir_pion)// && de.GetVal()==6)
    {
        cout<<"sortir_pion"<<endl;
        j.SortirPionBase(make_pair(10,10));
    }else{
        //deplacement
        //collision
    }
    sortir_pion=false;
    lancer_de = false; 
}
/*
void Jeu::Gerer_Jeu (bool &lancer_de, bool &sortir_pion)
{
    if(lancer_de)
    {
        
        //for(int i=4; i<nb_Joueur; i++)
        //{
            Gerer_Tour(*joueurs[0], sortir_pion, lancer_de);
        //}
    }
    
   if(lancer_de || sortir_pion)
   {
    cout<<"de a ete lancer et sortir pion: "<<sortir_pion<<endl;
    Gerer_Tour(*joueurs[0], sortir_pion, lancer_de);  
   }
   //Gerer_Tour(*joueurs[1], sortir_pion);
}*/

/*
void Jeu::Gerer_Jeu(bool & lancer_de, bool &sortir_pion)
{
    if(lancer_de) de.LancerDe();
    

    if(sortir_pion)
    {
        cout<<"sorti du pion"<<endl;
        joueurs[0]->SortirPionBase(make_pair(10,10));    
        //lancer_de=false;
        sortir_pion = false;
    }else{
        //lancer_de=false;
        sortir_pion = false;
        
        //delacement et collisison
    }
    

}




void Jeu::VerifierCollision(Pion* pion_deplace, Joueur &joueur_actuel){

    int case_joueur_actuel =(IdVersCase(joueur_actuel) +(static_cast<int>(pion_deplace->SGetI()) -1)) % 52;


    for(size_t i=0; i<joueurs.size(); i++){     // ici i de type size_t type entier non signé pour représenter taille des objets en mémoire,
        Joueur& autre_joueur = *joueurs[i];   //Utlisation de la boucle 

        if(autre_joueur.getId() !=joueur_actuel.getId()){
            for(int j=0; j<4; j++){
                int case_autre_joueur =(IdVersCase(autre_joueur) +(static_cast<int>(autre_joueur.GetPion(j)->GetI()) -1)) % 52;

                if(case_autre_joueur == case_joueur_actuel){
                    autre_joueur.GetPion(j)->RetournerBase();
                    cout << "Le pion adverse "<< autre_joueur.GetPion(j)->GetId()
                    <<" retourne àa la base"<<endl;   
                }
            }
        }
    }

}*/


/*void Jeu::DeplacerPion(Pion* pion, int val_de){
    pion->SetI(val_de);
    cout<<"le pion "<< pion->GetId()<< "avance de " <<val_de <<"cases." <<endl;
}*/

EtatJeu Jeu::GetEtat() const
{
    return etat;
}

void Jeu::SetEtat(EtatJeu etat_jeu)
{
    etat = etat_jeu;
}


pair<int,int> Jeu::GetChemin(int i)
{
    return chemin[i];
}

int Jeu::GetJoueurActuel() const
{
    return joueur_actuel;
}

void Jeu::SetJoueurActuel(int i)
{
    joueur_actuel = i;
}

int  Jeu:: IdVersCase(Joueur &j) const{
    switch(j.getId()){
        case 0:
            return case_Depart_R;
        case 1:
             return case_Depart_V;
        
        case 2:
            return case_Depart_J;
            
        case 3:
            return case_Depart_B;
            
        default:
            cout <<"Valeur inattendu "<<endl;
            return -1;
            
            
    }

}

//FONCTIONS VERIFIERCOLLISIONS
void Jeu::VerifierCollision(Pion &pion_deplace, Joueur &joueur_actuel)
{
	int tab_case_special[4]={0,13,26,39}; // case special ou on ne peux pas supprimer de pion on a aussi les cases en couleurs
	cout<<"--------------collision"<<endl;
	int case_joueur_actuel = (IdVersCase(joueur_actuel) + pion_deplace.GetI() ) % 52;
	cout << "Case actuelle du joueur " << joueur_actuel.getId() << " : " << case_joueur_actuel<<" a fait tant de pas "<< (static_cast<int>(pion_deplace.GetI()))<< endl;
	for(size_t i=0; i<joueurs.size(); i++) // boucle pour parcourir les joueurs
	{ 
		Joueur& autre_joueur = *joueurs[i]; // recuperation des joueurs
		cout<<"Checkons avec le joueur :"<<autre_joueur.getId()<<endl;
		if (joueur_actuel.getId()!=autre_joueur.getId()) // on ne doit pas comparer avec lui meme
		{	
			for (int j = 0; j < 4; j++) // boucle pour parcourir les pions
			{
				Pion& pion_autre_joueur = autre_joueur.GetPion(j); // on recupere un pion
				int case_autre_joueur = (IdVersCase(autre_joueur) + (pion_autre_joueur.GetI()-i)) % 52; // permet de transformer le nombre de pas en position dans le jeu
				cout << "  Pion " << j << " de l’adversaire est en case " << case_autre_joueur << endl;
				
				for (int c=0; c<4; c++) // parcours les cases speciales
				{
					if ((case_autre_joueur!=tab_case_special[c]) || (pion_autre_joueur.GetI()< 52)) // si case coloree ou special alors on fait rien
					{
						if (case_autre_joueur == case_joueur_actuel) // si meme endroit alors on fait retourner à la base
						{
							cout << ">>> COLLISION détectée ! Le pion adverse retourne à la base." << endl;
							pion_autre_joueur.RetournerBase();
							return;
						}
					}	
					else
					{
						cout<<"case special donc rien"<<endl;
					}
				}
			}
		}
	}
}

void Jeu::Gerer_Jeu(int id_pion_deplacer)
{
    //for (int i=0; i<nb_joueur; i++) //pour faire un tour a tester
    int i_depart=0;  //ok
    int i_apres = 0;
    int case_depart = 0;  //ok
    int i_reel=0;   //ok
    int index_chemin = 0;    //ok


    switch (etat)
    {
        case ATTENTE_ACTION:
            break;

        case ATTENTE_LANCER_DE:
            de.LancerDe();
            cout<<"Joueur actuel: "<<joueur_actuel<<endl;
            cout << "Dé lancé, valeur = " << de.GetVal() << endl;
            etat = ATTENTE_ACTION;
            break;

        case ATTENTE_SORTIE_PION:
            if(de.GetVal()==6 && joueurs[GetJoueurActuel()]->GetNbpionArrives()<4)
            {
                cout << "Sortie de pion" << endl;
                cout << "le x et y de chemin[1]: ("<<chemin[0].first <<" ;" << chemin[0].second <<" )"<<endl;
                GetJoueur(joueur_actuel)->SortirPionBase(LesCasesDepart[joueur_actuel]);
                etat = FIN_TOUR;
                             
            }
            break;  
            
        case ATTENTE_DEPLACEMENT:
            //rajouter condition si pion est sorti
            i_depart = joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI();
            cout<<"I depart: "<<i_depart<<endl;
            case_depart = IdVersCase(*joueurs[joueur_actuel]);

            if(joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetEstSorti())
            {
                if(i_apres<59)   //a changer normalement c est l'indice de leur ancienne position dans le chemin
                {
                    joueurs[joueur_actuel]->DeplacerUnPion(id_pion_deplacer, de.GetVal());  //met a jour le i
                    cout<<"i apres deplacement: "<<joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI()<<endl;
                    int i_reel = joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI();
                    int index_chemin = (i_reel + case_depart) % 52;
        
                    cout << "i pion = " << i_reel << endl;
                    cout << "i chemin = " << index_chemin << endl;

                    joueurs[joueur_actuel]->SetXpion(id_pion_deplacer, chemin[index_chemin].first);
                    joueurs[joueur_actuel]->SetYpion(id_pion_deplacer, chemin[index_chemin].second);  

                }else{  //cas ou +val de depasse cases final on met direct le pion a la case final;

                    joueurs[joueur_actuel]->GetPion(id_pion_deplacer).ChangerI(58);  //met a jour le i
                    cout<<"i= "<<joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI()<<endl;
                    joueurs[joueur_actuel]->SetXpion(id_pion_deplacer, chemin[joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI()].first);   //a voir si pas 58
                    joueurs[joueur_actuel]->SetYpion(id_pion_deplacer, chemin[joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI()].second);                     
                }   
            }

            etat = FIN_TOUR;
            break;

        case FIN_TOUR:
            joueur_actuel = (joueur_actuel + 1)%4;
            cout << "Nouveau joueur : " << joueur_actuel << endl;
            etat = ATTENTE_LANCER_DE;
            break;
    
        
        default:     
            joueur_actuel = joueur_actuel + 1;
            break;
    }
}