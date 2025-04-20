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
    dimx = dimy = 600;     //Largeur, Hauteur

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
    assert( m_renderer);

    //Image plateau
    m_plateau.loadFromFile("data/plateau.png", m_renderer);

    //m_tab_pion[0].loadFromFile("data/pion/rond_rouge", m_renderer);        //vert, jaune bleu rouge
    /*m_tab_pion[1].loadFromFile("data/pion/rond_jaune", m_renderer);
    m_tab_pion[2].loadFromFile("data/pion/rond_bleu", m_renderer);
    m_tab_pion[3].loadFromFile("data/pion/rond_rouge", m_renderer);*/
    /*m_tab_pion[0].loadFromFile("data/pion/rond_vert.png", m_renderer);        //vert, jaune bleu rouge
    m_tab_pion[1].loadFromFile("data/pion/rond_jaune.png", m_renderer);
    m_tab_pion[2].loadFromFile("data/pion/rond_bleu.png", m_renderer);*/

    for(int i=0; i<4; i++)
    {
        m_pion_rouge[i].loadFromFile("data/pion/rond_rouge.png", m_renderer);
        m_pion_vert[i].loadFromFile("data/pion/rond_vert.png", m_renderer);
        m_pion_jaune[i].loadFromFile("data/pion/rond_jaune.png", m_renderer);
        m_pion_bleu[i].loadFromFile("data/pion/rond_bleu.png", m_renderer);
    }
   

    //de
    m_faces_de[0].loadFromFile("data/de/de_1.png", m_renderer);
    for(int i=2; i<=6; i++)
    {
        string nom_fichier = "data/de/de_"+to_string(i)+".png";
        m_faces_de[i-1].loadFromFile(nom_fichier.c_str(), m_renderer);
    }
    /*
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





void AffichageSDL:: SdlAff(bool de_lancer, De de, Jeu &Jeu){

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
    int dimx, dimy;
    SDL_GetWindowSize(m_window, &dimx, &dimy);
    m_plateau.draw(m_renderer, 0, 0, dimx, dimy); //à haut en gauche

    //Affiche les pions rouges
    //AffPionRouge(jeu);

    /*3.affchage des pions de chaque joueur
    for(int j=0; j<nb_Joueur; j++){
        for(int i=0; i<4; i++){
            Pion* pion=joueur[j]->GetPion(i);

            //recuperer la case actuelle du pion
            unsigned char caseIndex= pion->GetI();

            //recuperer les coordonnees du pion
        }
    }*/

    for (int i=0; i<4; i++)
    {
        //cout<<"Pion "<<i<<" X: "<<Jeu.GetJoueur(0)->GetPion(i).GetXPion()<<" Y: "<<Jeu.GetJoueur(0)->GetPion(i).GetYPion()<<endl;

        m_pion_rouge[i].draw(m_renderer, Jeu.GetJoueur(0)->GetPion(i).GetXPion()*40, Jeu.GetJoueur(0)->GetPion(i).GetYPion()*40, 30, 30);
        m_pion_vert[i].draw(m_renderer, Jeu.GetJoueur(1)->GetPion(i).GetXPion()*40, Jeu.GetJoueur(1)->GetPion(i).GetYPion()*40, 30, 30);
        m_pion_jaune[i].draw(m_renderer, Jeu.GetJoueur(2)->GetPion(i).GetXPion()*40, Jeu.GetJoueur(2)->GetPion(i).GetYPion()*40, 30, 30);
        m_pion_bleu[i].draw(m_renderer, Jeu.GetJoueur(3)->GetPion(i).GetXPion()*40, Jeu.GetJoueur(3)->GetPion(i).GetYPion()*40, 30, 30);

    }


    //affichage du dé si pas tirer
    m_faces_de[Jeu.GetDe().GetVal()-1].draw(m_renderer, dimx/2-35, dimy/2-37);
    //si tirer (pour l'instant sans prendre en compte le joueur pour test)
    if(de_lancer)
    {
        for(int i=0; i<6; i++)
        {
            m_faces_de[i].draw(m_renderer, dimx/2-35, dimy/2-37);
            SDL_RenderPresent(m_renderer);
            SDL_Delay(50);      //petite pause
        }
        cout<<Jeu.GetDe().GetVal()<<endl;
        m_faces_de[Jeu.GetDe().GetVal()-1].draw(m_renderer, dimx/2-35, dimy/2-37);
        de_lancer = false;
    }

}


void AffichageSDL::AnimerDeplacement (Jeu &Jeu, int joueur_actuel, int id_pion, int i_depart, int i_arrivee)
{
    int case_dep = Jeu.IdVersCase(*Jeu.GetJoueur(joueur_actuel));

    for(int i= i_depart +1; i<=i_arrivee; i++)
    {
        //Jeu.GetJoueur(joueur_actuel)->GetPion(id_pion).ChangerI(i);
        int index_chemin = (i + case_dep)%52;
        Jeu.GetJoueur(joueur_actuel)->SetXpion(id_pion, Jeu.GetChemin(index_chemin).first);
        Jeu.GetJoueur(joueur_actuel)->SetYpion(id_pion, Jeu.GetChemin(index_chemin).second);

        SdlAff(false, Jeu.GetDe(), Jeu);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(200);
    }


}







void AffichageSDL::SdlBoucle(Jeu &Jeu)
{
    SDL_Event events;
    bool quit = false;
    bool de_lancer_aff = false;
    cout<<"Le pion 0 de J0 a pour i= "<<Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(0).GetI()<<endl;

    while (!quit)
    {
        

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true;

            if (events.type == SDL_KEYDOWN)
            {
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    quit = true;
                    break;

                case SDL_SCANCODE_SPACE:
                    if (Jeu.GetEtat()==ATTENTE_LANCER_DE)
                    {
                        Jeu.Gerer_Jeu(0);   //changer?
                        de_lancer_aff = true;
                    }
                    break;

                case SDL_SCANCODE_RETURN:
                    if (Jeu.GetEtat() == ATTENTE_ACTION)
                    {
                        Jeu.SetEtat(ATTENTE_SORTIE_PION);
                        Jeu.Gerer_Jeu(0);   //changer?
                    }
                    break;

                case SDL_SCANCODE_1:         //pion avec id=0         
                    if(Jeu.GetEtat() == ATTENTE_ACTION)
                    {//a remplacer 0 par GetJoueur(joueur_actuel)
                        int i_depart = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(0).GetI();

                        Jeu.SetEtat(ATTENTE_DEPLACEMENT);
                        Jeu.Gerer_Jeu(0);

                        int i_arrivee = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(0).GetI();
                        AnimerDeplacement(Jeu, Jeu.GetJoueurActuel(), 0, i_depart, i_arrivee);  //premier 0 est le joueur a remplacer
                        //Jeu.VerifierCollision(joueurs[joueur_actuel]->GetPion(0), *joueurs[joueur_actuel]);
                        Jeu.VerifierCollision(Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(0), *Jeu.GetJoueur(Jeu.GetJoueurActuel()));
                    }
                    break;

                case SDL_SCANCODE_2:        //pion avzec id=1           
                    if(Jeu.GetEtat() == ATTENTE_ACTION)
                    {//a remplacer 0 par GetJoueur(joueur_actuel)
                        int i_depart = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(1).GetI();

                        Jeu.SetEtat(ATTENTE_DEPLACEMENT);
                        Jeu.Gerer_Jeu(1);

                        int i_arrivee = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(1).GetI();
                        AnimerDeplacement(Jeu, Jeu.GetJoueurActuel(), 1, i_depart, i_arrivee);  //premier 0 est le joueur a remplacer
                    }
                    break;

                case SDL_SCANCODE_3:        //pion avec id=2              
                    if(Jeu.GetEtat() == ATTENTE_ACTION)
                    {//a remplacer 0 par GetJoueur(joueur_actuel)
                        int i_depart = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(2).GetI();

                        Jeu.SetEtat(ATTENTE_DEPLACEMENT);
                        Jeu.Gerer_Jeu(2);

                        int i_arrivee = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(2).GetI();
                        AnimerDeplacement(Jeu, Jeu.GetJoueurActuel(), 2, i_depart, i_arrivee);  //premier 0 est le joueur a remplacer
                    }
                    break;

                case SDL_SCANCODE_4:        //pion avec id=3              
                    if(Jeu.GetEtat() == ATTENTE_ACTION)
                    {//a remplacer 0 par GetJoueur(joueur_actuel)
                        int i_depart = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(3).GetI();

                        Jeu.SetEtat(ATTENTE_DEPLACEMENT);
                        Jeu.Gerer_Jeu(3);

                        int i_arrivee = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(3).GetI();
                        AnimerDeplacement(Jeu, Jeu.GetJoueurActuel(), 3, i_depart, i_arrivee);  //premier 0 est le joueur a remplacer
                    }
                    break;

                case SDL_SCANCODE_N: 
                    Jeu.SetEtat(FIN_TOUR);
                    Jeu.Gerer_Jeu(0);

                    break;

                default:
                    //etat = ATTENTE_LANCER_DE;
                    break;
                }
            }
        }

        // Affichage

        SdlAff(de_lancer_aff, Jeu.GetDe(), Jeu);
        de_lancer_aff =false;
        SDL_RenderPresent(m_renderer);
    }
}