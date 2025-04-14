#ifndef AFFICHAGESDL_H
#define AFFICHAGESDL_H

#include <stdlib.h>
#include <filesystem>

#include <SDL2/SDL.h>           //affichage graphique   
//#include <SDL2/SDL_image.h>     //charger des images
//#include <SDL2/SDL_ttf.h>  

#include "Image.h"
#include "De.h"

/**
 * 
 */
class AffichageSDL
{
private:
    SDL_Window *m_window;  ///<Fenetre de la SDL
    SDL_Renderer *m_renderer; ///< Moteur du rendu graphique
    TTF_Font *m_font; ///< Police de texte
    TTF_Font *m_font_j1; //Police de texte
    TTF_Font *m_font_j2; //Police de texte
    TTF_Font *m_font_j3; //Police de texte
    TTF_Font *m_font_j4; //Police de texte
    Image m_plateau; ///< image du plateau
    Image m_faces_de[6]; ///<image du dé
    Image m_de_inter[5]; ///image intermediaire du dé
    Image m_tab_pion[4]; ///< image des pions 
    

    /**
     * @brief fonction qui gere l'affichage
     * @param de_lancer si le dé a ete lancer
     * @param de de du jeu 
     */
    void SdlAff(bool de_lancer, De de);

public:
    /**
     * @brief Initialise SDL et charge les ressources(Constructeur)
     */
    AffichageSDL(); 
    /**
     * @brief (Destructeur) libere de la memoire allouee
     */
    ~AffichageSDL();

    /**
     * @brief Boucle principale qui gere les evenements du jeu
     */
    void SdlBoucle();
};


#endif

