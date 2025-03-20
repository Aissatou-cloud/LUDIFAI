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
        void Demarer_Jeu();

        /**
        * @brief gere les tours pour chaque joueur
        */
        void Gerer_Tour(Joueur & joueur);

        /**
        * @brief affiche le jeu sous la console 
        * @param j jeu 
        * @param t_x taille x de la fenetre
        * @param t_y taille y de la fenetre
        */
        void AffichageLimiteTerrain_SDL (int t_x, int t_y);
        int LancerDe();
        vector<Pion*> RecupDesPionsEnJeu(Joueur &joueur);
        bool GererEntreeJeu(Joueur &joueur, int val_de);
        Pion* ChoisirPion(vector<Pion*> PionsEnJeu, Joueur &joueur );
        void DeplacerPion(Pion* pion, int val-de);
        void VerifierCollision(Pion* pionDeplace, Joueur &joueurActuel);
        void VerifierArrivee(Pion* pion, Joueur &joueur);


};

#endif

