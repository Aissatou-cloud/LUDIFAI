#include "AffichageSDL.h"
#include <iostream>
#include <string>

using namespace std;

AffichageSDL::AffichageSDL(): m_window(nullptr), m_renderer(nullptr), m_font(nullptr), m_font_j1(nullptr), m_font_j2(nullptr), m_font_j3(nullptr), m_font_j4(nullptr)
{
    //Initialisation de la SDL
    //SDL_Rect r;     //a voir si on enleve
    //r.w = (w<0) ? m_surface->w      //...
    cout<<"SDL: init"<<endl;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout<<"Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //Initialisation de SDL_ttf pour l'affichage texte -> besoin pour les joueurs
    //si initialisation echoue -> quite
    cout<<"SDL_ttf: init"<<endl;
    if(TTF_Init()!=0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //Initialisation de SDL_image pour charger image (PNG, JPG)
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    cout<<"SDL_image: init"<<endl;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        cout<<"SDL_m_image could not initialize! SDL_m_image Error: "<<IMG_GetError()<<endl;
        SDL_Quit();
        exit(1);
    }

    //taille fenêtre
    int dimx, dimy;
    dimx = dimy = 1000;     //Largeur, Hauteur

    //SDL_WINDOWPOS_CENTERED : POSITION X (CENTRE SUR L'AXE X)
    //SDL_WINDOWPOS_CENTERED : POSITION Y (CENTRE SUR L'AXE Y)
    //"LUDO" : titre de la fenetre
    //SDL_WINDOW_SHOWN	: Affiche la fenêtre immédiatement après sa création
    //a voir si on garde SDL_WINDOW_RESIZABLE : Permet de redimensionner la fenêtre avec la souris
    m_window = SDL_CreateWindow("LUDO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(m_window == NULL)
    {
        cout<<"Erreur lors de la creation de la fenetre: "<<SDL_GetError()<<endl;
        SDL_Quit();
        exit(1);
    }

    /*index= -1 : laise SDL choisir automatiquement le meilleur GPU
    SDL_RENDERER_ACCELERATED : accceleration materielle 
    */
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    //Image plateau
    m_plateau.loadFromFile("data/plateau.png", m_renderer);
    /*m_tab_pion[0].loadFromFile("data/pion/rond_vert", m_renderer);        //vert, jaune bleu rouge
    m_tab_pion[1].loadFromFile("data/pion/rond_jaune", m_renderer);
    m_tab_pion[2].loadFromFile("data/pion/rond_bleu", m_renderer);
    m_tab_pion[3].loadFromFile("data/pion/rond_rouge", m_renderer);

    for(int i=0; i<6; i++)
    {
        string nom_fichier = "data/de/de_"+to_string(i)+".png";
        m_faces_de[i].loadFromFile(nom_fichier.c_str(), m_renderer);
    }

    for(int i=0; i<5; i++)
    {
        string nom_fichier2 ="data/de/de_int"+to_string(i)+".png";
        m_de_inter[i].loadFromFile(nom_fichier2.c_str(), m_renderer);
    }*/
}

//libere la meoire allouee
AffichageSDL::~AffichageSDL(){
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();

}

void AffichageSDL:: SdlAff(){
    
    // Remplir l'écran de blanc
    //SDL_SetRenderDrawColor : définit la couleur de fond du rendu
    //( 130, 140, 255, 255) : correspond a une teinte bleue
    // clair avec une opacite  maximale (255)
    SDL_SetRenderDrawColor(m_renderer, 130, 140, 255, 255);

    //efface l'ecran avec cette couleur :
    // IMPORTANT :pour ne pas supersposer l'ancien rendu avec
    // le nouveau
    SDL_RenderClear(m_renderer);

    // Affiche du texte
    //fonction definit dans classe image
    //m_font_im.draw(m_renderer, 320 - 50, 50, 100, 50);

    //2.Affichage du plateau 
    m_plateau.draw(m_renderer, 0, 0); //à haut en gauche

    /*3.affchage des pions de chaque joueur
    for(int j=0; j<nb_Joueur; j++){
        for(int i=0; i<4; i++){
            Pion* pion=joueur[j]->GetPion(i);

            //recuperer la case actuelle du pion
            unsigned char caseIndex= pion->GetI();

            //recuperer les coordonnees du pion
        }
    }*/


}

void AffichageSDL::SdlBoucle()
{
    SDL_Event events;   //Stocke les événements (clavier, souris, fermeture, etc.).
    bool quit = false;  //Contrôle la boucle (true = fin du programme).

    // tant que ce n'est pas la fin ...
    while (!quit)
    {

        // tant qu'il y a des evenements à traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events))  // vérifie s'il y a des événements à traiter.
        {                               //S'il y a un événement, il est stocké dans events.
            if (events.type == SDL_QUIT)
                quit = true; //Si l'utilisateur clique sur la croix de la fenêtre (SDL_QUIT),
                             // on met quit = true pour quitter la boucle.
            else if (events.type == SDL_KEYDOWN)        //si une touche est pressee (SDL_KEYDOWN ), on verifie laquelle
            {
                switch (events.key.keysym.scancode) // contient le code scancode de la touche qui a été pressée. 
                                                    //Le scancode est un identifiant numérique unique qui représente 
                                                    //chaque touche du clavier indépendamment de sa position sur le clavier 
                                                    //ou de la disposition du clavier.
                { 
                case SDL_SCANCODE_ESCAPE:       //scancode pour la touche Échap (Escape) sur le clavier.
                case SDL_SCANCODE_Q:            //Scancode pour la touche Q sur le clavier.
                    quit = true;
                    break;
                default:
                    break;
                }
            }
        }

        // on affiche le jeu sur le buffer caché
        SdlAff();   // maj du rendu , cette fonction efface et redessine les elements du jeu

        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(m_renderer);  //afiche le rendu (sinon les modifications ne sont pas visibles)
    }
}