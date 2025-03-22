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

class Jeu
{
    private:
        int nb_Joueur;      ///nb de joueur 
        vector<Joueur*> joueurs; ///Tableau dyna de joueur
        //vector<Joueur> * joueurs;      ///creer tableau de nb Joueur présent
        De de;              ///le de du jeu 

    public:
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
        * @brief Demarer jeu place les pions et les joueurs pour le debut du jeu
        */
        void Demarer_Jeu(char tab[4]);

        /**
        * @brief gere les tours pour chaque joueur
        * @param joueur le joueur actuel 
		* @param tab de caractere (uniquement pour console)
        */
        void Gerer_Tour(Joueur & joueur);

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
        */
        int LancerDe();

        /**
        * @brief recupere le l'ensemble des pions qui sont deja en jeu d'un joueur
        * @param joueur le joueur
        */
        vector<Pion*> RecupDesPionsEnJeu(Joueur &joueur);

                
        /**
        * @brief gere l'entree du jeu c'est_à_dire la sortie d'un pion ou non par rapport a valeur du de
        * @param joueur le joueur
        * @param val_de la valeur du de
        */
        bool GererEntreeJeu(Joueur &joueur, int val_de);

        /**
        * @brief choisir la pion qui doit sortir 
        * @param PionsEnJeu un tableau de Pion en jeu du joueur
        * @param joueur le joueur
        */
        Pion* ChoisirPion(vector<Pion*> PionsEnJeu, Joueur &joueur );

        /**
        * @brief Deplace le pion sur le plateau 
        * @param pion 1 ptr sur Pion
        * @param val_de la valeur du de
        */
        void DeplacerPion(Pion* pion, int val_de);

        /**
        * @brief verifie la collision entre les autres pions des autres joeur et le joueur
        * @param pion_deplace 1 ptr sur Pion qui est le pion du joueur a deplacer
        * @param jouur_actuel le joueur qui joue le tour
        */
        void VerifierCollision(Pion* pion_deplace, Joueur &joueur_ctuel);

        /**
        * @brief verifie si le pion est arrive et incremente le nbponarives
        * @param pion 1 ptr sur Pion
        * @param joueur le joueur actuel
        */
        void VerifierArrivee(Pion* pion, Joueur &joueur);


};

#endif

