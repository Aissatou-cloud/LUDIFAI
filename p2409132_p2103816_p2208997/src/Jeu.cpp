#include "Jeu.h"
#include <iostream>

using namespace std;

Jeu::Jeu(): nb_Joueur(4)
{
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
}

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



int Jeu::JoueurLanceDe(unsigned int id_joueur, De de) //ok : a ne pas toucher
{
	cout<<"-----------------lancerdee"<<endl;
    de.LancerDe();
    cout<<"le joueur "<<joueurs[id_joueur]->getId()<< " a tire le "<<de.GetVal()<< endl;
    return de.GetVal();
}

void Jeu:: RecupDesPionsEnJeu(Joueur &joueur, Pion pionsenjeu[4], bool &vide) //Non utilisable pour l'instant
{
    cout<<"-----------------RecupDesPionsEnJeu"<<endl;
    vide=true;
    int index=0;
    cout<<"vide ? [0/1]: "<<vide<<endl;
    for(int i=0; i<4; i++)
    {
        Pion pion = joueur.GetPion(i);  //recupère les pions, tu peux pas utiliser tab direct
    
        if(!pion.GetEstArrive() && pion.GetEstSorti())
        {
            pionsenjeu[index] = pion; 
            index++; 
            vide=false;
        }     
    }
}

bool Jeu::GererEntreeJeu(Joueur &joueur, int val_de) 
{
    cout<<"-----------------GererEntreeJeu"<<endl;
    if (val_de==6)
    {
        cout<<"entree de jeu ou sortie de pion ? [e/s]"<<endl;

        for(int i=0; i<4; i++)
        {
            Pion pion_sorti=joueur.GetPion(i);
            cout << "Vérifi du pion " << i << endl;

            if (not (pion_sorti.GetEstSorti())) 
            {
                joueur.GetPion(i).SortirBase();
                return true;
            }
        }
    }
    cout << "Tous les pions sont déjà sortis." << endl;
    return false;
}
bool Jeu::Pionsjouables(Joueur &joueur, int val_de)
{
	cout<<"---------------pions jouables"<<endl;
	for (int i = 0; i < 4; i++)
	{	
		Pion p = joueur.GetPion(i);
		if ((p.GetEstSorti() && (!p.GetEstArrive())) || (!p.GetEstSorti() && (val_de == 6)))
		{
			cout<<"Il existe au moins pion valide"<<endl;
			return true;
		}	
			
	}
	cout<<"Il n'y a pas de pion valide"<<endl;
	return false;
}

Pion& Jeu::ChoisirPion(Joueur &joueur, int val_de) //ok
{
    cout<<"-------------choisirpion"<<endl;
    int choix;  // Initialisation à une valeur invalide
    bool choixnonval = true;
    // Afficher les pions validereturn joueur.GetPion(choix);s
    for (int i = 0; i < 4; i++)
	{
        Pion p = joueur.GetPion(i);
        if ((p.GetEstSorti() && (!p.GetEstArrive())) || (!p.GetEstSorti() && (val_de == 6))) {
            cout << "Pion " << i << " : valide";
        } else {
            cout << "Pion " << i << " : non valide";
        }
		cout <<" sortie ? "<< p.GetEstSorti()<<" arrivee ? "<<p.GetEstArrive()<<endl;
    }
    
	while (choixnonval)
	{	
		cout<<"choix (0-3) : "<<endl;
		cin>>choix;
		if (choix<=3 && choix>=0)
		{
            
			Pion &p = joueur.GetPion(choix);
			if ((p.GetEstSorti() && (!p.GetEstArrive())) || (!p.GetEstSorti() && (val_de == 6)))
			{
				cout << "Pion " << choix << " : valide" << endl;
				return joueur.GetPion(choix);
			}
            choixnonval=false;
		}
	}
    return joueur.GetPion(choix);
}

void Jeu::DeplacerPion(Pion &pion, int val_de) //ok
{
	cout<<"----------deplacerpion"<<endl;
	int avance = val_de;

    if (!pion.GetEstSorti()) 
	{
        avance = 1; // il commence tout juste, donc 1 seule case et on le sort de la base
        pion.SortirBase();
    }
	else
	{
		pion.SeDeplace(avance); // sinon on avance de n du de
	}
    cout<<"le pion "<< pion.GetId()<< " avance de " <<avance <<"cases." <<endl;
}

void Jeu::VerifierCollision(Pion pion_deplace, Joueur &joueur_actuel) 
{
    cout<<"--------------verif collision"<<endl;
    for (int i=0; i<joueurs.size(); i++)
    {     
        Joueur& autre_joueur = *joueurs[i];   //Utlisation de la boucle 

        if(autre_joueur.getId() !=joueur_actuel.getId())
        {
            for(int j=0; j<4; j++)
            {
                if(autre_joueur.GetPion(i).GetI() == pion_deplace.GetI())
                {
                    autre_joueur.GetPion(i).RetournerBase();
                    cout << "Le pion adverse "<< autre_joueur.GetPion(i).GetI()<<" retourne à la base"<<endl;   
                }
            }
        }
    }
}

void Jeu::VerifierArrivee(Pion pion, Joueur &joueur) //ok
{
    cout<<"-------------verif arrive"<<endl;
    if(pion.GetId() >= 56)
    { //si 5- est la derniere cas
        joueur.IncrementerNbPionArrive(); //on increment le nbpionarrive, impossible de faire nbpionarrivee ++ car membre privee
        cout<<"Le pion " <<pion.GetId()<<" du joueur "<<joueur.getId()<< " est arrive "<<endl;
    }
}

void Jeu::Gerer_Tour(Joueur &joueur)
{
    
    if(joueur.Joueur_Gagnant())
    {
        cout<<"Le joueur "<< joueur.getId()<< "a deja gagné !" <<endl;
        return ; 
    }

    if(joueur.Joueur_Gagnant()==false)
    {
        cout<<"*******************************************Tour du joueur : "<< joueur.getId()<<" ! "<<endl;
        int val_de=0;
        De de;
        val_de=JoueurLanceDe(joueur.getId(), de);

		if (Pionsjouables(joueur,val_de))
		{
			cout<<"On a des pions jouables donc on choisie : "<<endl;
			Pion& pion_choisi=ChoisirPion(joueur, val_de);
			cout<<"deplacement"<<endl;
			DeplacerPion(pion_choisi, val_de);
			
			
			
			VerifierArrivee(pion_choisi, joueur);

			//verifier les collisions sssi le pion n'a pas atteint l'arrivee
			if (not(pion_choisi.GetEstArrive()))
			{
			   VerifierCollision(pion_choisi,joueur);
			}
			
			//verifier si le joueur a gagne apres son move
			if(joueur.Joueur_Gagnant())
			{
				joueurs_gagnants.push_back(&joueur);        //passe l'adresse 
			}			
		}
        cout <<"Fin du tour du joueur " <<joueur.getId() <<endl;        
    }
}


void Jeu::Demarer_Jeu(char tab[4])
{
    cout<<"demarage_jeu"<<endl;
    int taille_x, taille_y;         //taille plateau
    taille_x = 30;    //affichage a part 
    taille_y = 15;
	bool continu;
    continu= true;
	
    AffichageLimiteTerrain_SDL(taille_x, taille_y, tab);

    cout<<"Le jeu commence avec: "<< nb_Joueur<< "joueurs" <<endl;

    //Affichage des joueurs et leur couleurs
    for( int i=0; i< nb_Joueur; i++)
	{
        cout<<"Player: "<<joueurs[i]->getId()<< " -Color: ( "
        <<(int)joueurs[i]->getCouleur().getR()<<", " 
        <<(int)joueurs[i]->getCouleur().getV()<<", " 
        <<(int)joueurs[i]->getCouleur().getB()<<" )"<<endl;
    }
    
    do{
        for(int i=0; i<nb_Joueur; i++){
            Gerer_Tour(*joueurs[i]);  //on passe par reference
        }

        if(joueurs_gagnants.size()==(static_cast<long unsigned int>(nb_Joueur)-1))
        {
            continu=false;
        }
    } while(continu);
}

