#ifndef PLATEAU_H
#define PLATEAU_H
#include "Joueur.h"


/**
 * @class Plateau
 * @brief une classe qui gere le plateau du jeu
 */
class Plateau{
private:
    unsigned char chemin_commun[52]; ///<chemin commun a tus les pions (0 à 52)
    unsigned char chemin_arrivee[4][5]; ///<Zones d'arrivée spécifiques à chaque jour(indices 52 a 57)
    Joueur tab_joueur[4]; ///<tableau de 4 joueurs

public:
    /**
     * @brief constructeur de la classe Plateau
     */
    Plateau();

    /**
     *@brief Acces
     */
    Joueur * getJouer(); //Acces aux joueurs
    unsigned char getCaseCommun(unsigned chra index) const ; //Lire une case du chemin commun
    unsigned char getCaseArrivee(int joueur, unsigned char index) const ; //lire une case d'arrivee

    void afficherPlateau(); //Pour afficher le plateau en mode console

};



#endif