#include "AffichageSDL.h"
#include <iostream>
using namespace std;

Affich




void AffichageSDL:: SdlAff(){
    //remplir l'ecran de blanc
    //SDL_SetRenderDrawColor: definit la couleur de fond du rendu
    SDL_SetRenderDrawColor(m_renderer,255, 255, 255, 255);

    //efface l'ecran avec cette couleur pour ne pas supersposer 
    //l'ancien rendu avec le nouveau
    SDL_RenderClear(m_renderer);

    /* A REVOIR POUR  m_font_im.draw*/

}




