#ifndef JEU_H
#define JEU_H

#include <vector>
#include "Joueur.h"
#include "De.h"


using namespace std;

/**
* @class Jeu
* @brief Définit le jeu et le fait marcher 
*/
enum EtatJeu {      /// les etat du jeu
    ATTENTE_LANCER_DE,
    ATTENTE_ACTION,
    ATTENTE_SORTIE_PION,
    ATTENTE_DEPLACEMENT,
    FIN_TOUR
};

class Jeu
{
    private:
        EtatJeu etat;       ///<l'etat du jeu actuel
        int nb_Joueur;      ///<nb de joueur 
        int joueur_actuel; ///< le joueur actuel qui joue
        vector<Joueur*> joueurs; ///<Tableau dyna de joueur
        vector<Joueur*> joueurs_gagnants;   ///<tableau dynamique des joueurs gagnants
        //vector<Joueur> * joueurs;      ///<creer tableau de nb Joueur présent
        De de;              ///le de du jeu 
        pair<int, int> chemin[53]; ///< le chemin commun de tous les piosn 
        pair<int, int> zone_Gagnante_R[6]; ///< la partie gagnante du jRouge
        pair<int, int> zone_Gagnante_V[6]; ///< la partie gagnante du jVert
        pair<int, int> zone_Gagnante_J[6]; ///< la partie gagnante du jJaune
        pair<int, int> zone_Gagnante_B[6]; ///< la partie gagnante du jBleu
        pair<int, int> LesCasesDepart[4]; ///< le tab des cases de depart de chaque joueur dans le chemin
        int case_Depart_R; ///<la case de departRouge
        int case_Depart_V; ///<la case de departVert
        int case_Depart_J; ///<la case de departJaune
        int case_Depart_B; ///<la case de departBleu

        pair<float,float> coordo_poule[4];




    public:
        /**
         * @ initialise les elements du plateau
         */
        void InitialiserPlateau();
    
        /**
        * @brief Constructeur
        */
        Jeu();

        /**
        * @brief Autre constructeur qui prends en paramètre le nombre de joueur
        * @param nb_j nombre de joueur
        */
        Jeu(int nb_j);

        /**
        * @brief Destructeur
         */
        ~Jeu();

        /**
        * @brief retourne l'etat actuel du jeu
        */
        EtatJeu GetEtat() const;

        /**
        * @brief modifie l'etat
        * @param etat_jeu l etat du jeu
        */
        void SetEtat(EtatJeu etat_jeu);

        /**
        * @brief retourne les coordonnée d'un point du chemin
        * @param i indice du chemin 
        */

        /**
        * @brief retourne les coordonée de la poule d'un joueur
        * @param i index du joueur
         */
        pair<int, int> GetCoordoPoule(int i) const;

        /**
        * @brief remplie coordonnee de la poule d'un joueur
        * @param cx coordo x
        * @param cy coordo y
        */
        void SetCoordoPoule(int i, float cx, float cy);  //peut etre elle sert a rien 
        

        pair<int,int> GetChemin(int i);


        /**
        * @brief  Retourne le joueur actuel
        */
       int GetJoueurActuel() const ;

        /**
        * @brief Modifie le joueurs actuel
        * @param i indice du joueur 
        */
       void SetJoueurActuel(int i);


        /**
        * @brief Demarer jeu place les pions et les joueurs pour le debut du jeu
        */
        void Demarer_Jeu(char tab[4]);
    

        /**
        * @brief affiche le jeu sous la console 
        * @param j jeu 
        * @param t_x taille x de la fenetre
        * @param t_y taille y de la fenetre
        */
        void AffichageLimiteTerrain_SDL (int t_x, int t_y, char tab[4]);

        //methodes dont aura besoin Gerer_tour(Joueur &joueur)
                /**
        * @brief retourne la valeur lance du de
        * @param id_joueur joueur qui lance le dé
        * @param de de du jeu 
        */
        //int JoueurLanceDe(unsigned int id_joueur, De de);

        /**
        * @brief recupere le l'ensemble des pions qui sont deja en jeu d'un joueur
        * @param joueur le joueur
        */
        //void RecupDesPionsEnJeu(Joueur &joueur, Pion pionsenjeu[4], bool &vide);

                
        /**
        * @brief gere l'entree du jeu c'est_à_dire la sortie d'un pion ou non par rapport a valeur du de
        * @param joueur le joueur
        * @param val_de la valeur du de
        */
        //bool GererEntreeJeu(Joueur &joueur, int val_de);

        /**
        * @brief choisir le pion qui doit sortir 
        * @param choix un entier retournant le chois de l'utilisateur
        * @param joueur le joueur
        */
        //Pion& ChoisirPion(Joueur &joueur, int val_de);

        /**
        * @brief Deplace le pion sur le plateau 
        * @param pion 1 ptr sur Pion
        * @param val_de la valeur du de
        */
        //void DeplacerPion(Pion & pion, int val_de);

        /**
        * @brief verifie la collision entre les autres pions des autres joeur et le joueur
        * @param pion_deplace 1 ptr sur Pion qui est le pion du joueur a deplacer
        * @param jouur_actuel le joueur qui joue le tour
        */
        void VerifierCollision(Pion &pion_deplace, Joueur &joueur_actuel);

        /**
         * @brief renvoie le de du jeu
         */
        De& GetDe();

        /**
         * @brief renvoie le joueur d'identifiant en param
         * @param id l'identifiant du joueur
         */
        Joueur * GetJoueur(unsigned int id) const;

        /**
         * @brief verifie si le pion du joueur est arrive
         * @param pion le pion du joueur
         * @param joueur le joueur
         */
        void VerifierArrivee(Pion pion, Joueur &joueur);

        /**
         * @brief 
         */
		//bool Pionsjouables(Joueur &joueur, int val_de);
       

        //pair<int, int>  GetCoordonnes(int index) const;
        //pair<int, int>  GetZoneGagnateRouge(int index) const;

        /**
        * @brief gere les tours pour chaque joueur
        * @param j le joueur actuel 
		* @param sortir_pion si le joueur veut sortir un pion de la base
        * @param lancer_de 
        */
        void Gerer_Tour(Joueur & j, bool & sortir_pion, bool & lancer_de);

        /**
         * @brief Gère le jeu pour un tour
         * @param lancer_de si le dé a ete lancer
         * @param sortir_pion si on veut sortir un pion de la base
         */
        /*void Gerer_Jeu (bool &lancer_de, bool &sortir_pion);*/
        /**
         * @brief donne la case depart du pion en fonction de son id
         * @param j le joueur
         */
        int IdVersCase(Joueur &j) const;

        /**
         * @brief gere le logique du tour de l'IA 
         */
        void GererTourIA();

        /**
         * @brief Gere le jeu pour chaque tour
         * @param id_pion_deplacer id du pion a deplacer
         */
        void Gerer_Jeu (int id_pion_deplacer);

        /**
          * @brief  verifie si c'est IA qui joue ou HUMAIN
          */
        bool IAdoitJouer() const;
        /**
         * @brief teste toutes les fonctions de la classe
         */
        void testRegression();
};

#endif

