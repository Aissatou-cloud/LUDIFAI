#ifndef JEU_H
#define JEU_H

#include <iostream>     //vector pour les tableaux dynamique
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
        vector<Joueur> * Joueur = new vector<Joueur> [nb_Joueur];        ///creer tableau de nb Joueur présent
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
        * @brief gere les tours pour chaque joueur
        */
        Gerer_Tour();

};

