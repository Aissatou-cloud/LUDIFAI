#include "AffichageSDL.h"
#include <iostream>
#include <string>


using namespace std;

AffichageSDL::AffichageSDL(): m_window(nullptr), m_renderer(nullptr), m_font(nullptr), pseudo_j1(nullptr), pseudo_j2(nullptr), pseudo_j3(nullptr), pseudo_j4(nullptr)
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

    m_encadrer.loadFromFile("data/encadrer.png", m_renderer);
    m_menu.loadFromFile("data/menu.png", m_renderer);

    m_1.loadFromFile("data/1.png", m_renderer);
    m_1_sombre.loadFromFile("data/1_sombre.png", m_renderer);

    m_2.loadFromFile("data/2.png", m_renderer);
    m_2_sombre.loadFromFile("data/2_sombre.png", m_renderer);

    m_3.loadFromFile("data/3.png", m_renderer);
    m_3_sombre.loadFromFile("data/3_sombre.png", m_renderer);

    m_4.loadFromFile("data/4.png", m_renderer);
    m_4_sombre.loadFromFile("data/4_sombre.png", m_renderer);
    
    //m_start.loadFromFile("data/start.png", m_renderer);

    bouton1 = {50, 350, 80, 80};
    bouton2 = {150, 350, 80, 80};
    bouton3 = {250, 350, 80, 80};
    bouton4 = {350, 350, 80, 80};
    bouton_start = {0,0, 100, 100};


}

//libere la meoire allouee
AffichageSDL::~AffichageSDL(){
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    //Mix_FreeChunk(de_son);
    de_son = nullptr;


}





void AffichageSDL:: SdlAff(bool menu, bool cliquer, bool de_lancer, De de, Jeu &Jeu){

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
    if(menu)
    {
        m_menu.draw(m_renderer, 0, 0, dimx, dimy);
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
    
    
        // Si la souris est sur le bouton 1
         if (mouseX >= bouton1.x && mouseX <= bouton1.x + bouton1.w &&
            mouseY >= bouton1.y && mouseY <= bouton1.y + bouton1.h) {
            m_1_sombre.draw(m_renderer, bouton1.x, bouton1.y, bouton1.w, bouton1.h);
        } else {
            if(cliquer && Jeu.GetNbJoueur()==1)
            {
                m_1_sombre.draw(m_renderer, bouton1.x, bouton1.y, bouton1.w, bouton1.h);
            }else{
                m_1.draw(m_renderer, bouton1.x, bouton1.y, bouton1.w, bouton1.h);
            }
            
        }

        if (mouseX >= bouton2.x && mouseX <= bouton2.x + bouton2.w &&
            mouseY >= bouton2.y && mouseY <= bouton2.y + bouton2.h) {
            m_2_sombre.draw(m_renderer, bouton2.x, bouton2.y, bouton2.w, bouton2.h);
        } else {
            if(cliquer && Jeu.GetNbJoueur()==2)
            {
                m_2_sombre.draw(m_renderer, bouton2.x, bouton2.y, bouton2.w, bouton2.h);
            }else{
                m_2.draw(m_renderer, bouton2.x, bouton2.y, bouton2.w, bouton2.h);
            }
            
        }

       if (mouseX >= bouton3.x && mouseX <= bouton3.x + bouton3.w &&
            mouseY >= bouton3.y && mouseY <= bouton3.y + bouton3.h) {
            m_3_sombre.draw(m_renderer, bouton3.x, bouton3.y, bouton3.w, bouton3.h);
        } else {
            if(cliquer && Jeu.GetNbJoueur()==3)
            {
                m_3_sombre.draw(m_renderer, bouton3.x, bouton3.y, bouton3.w, bouton3.h);
            }else{
                m_3.draw(m_renderer, bouton3.x, bouton3.y, bouton3.w, bouton3.h);
            }
            
        }

        if (mouseX >= bouton4.x && mouseX <= bouton4.x + bouton4.w &&
            mouseY >= bouton4.y && mouseY <= bouton4.y + bouton4.h) {
            m_4_sombre.draw(m_renderer, bouton4.x, bouton4.y, bouton4.w, bouton4.h);
        } else {
            if(cliquer && Jeu.GetNbJoueur()==4)
            {
                m_4_sombre.draw(m_renderer, bouton4.x, bouton4.y, bouton4.w, bouton4.h);
            }else{
                m_4.draw(m_renderer, bouton4.x, bouton4.y, bouton4.w, bouton4.h);
            }
            
        }

        // Si la souris est sur le bouton 1
        /*if (mouseX >= bouton_start.x && mouseX <= bouton_start.x + bouton_start.w &&
            mouseY >= bouton_start.y && mouseY <= bouton_start.y + bouton_start.h) {
            m_start.draw(m_renderer, bouton_start.x, bouton_start.y, bouton_start.w, bouton_start.h);
        } else {
            if(cliquer)
            {
                m_start.draw(m_renderer, bouton_start.x, bouton_start.y, bouton_start.w, bouton_start.h);
            }else{
                m_start_sombre.draw(m_renderer, bouton_start.x, bouton_start.y, bouton_start.w, bouton_start.h);
            }
            
        }*/




    }else{

        m_plateau.draw(m_renderer, 0, 0, dimx, dimy); //à haut en gauche
        
        if(Jeu.GetJoueurActuel()==0)
        {
            m_encadrer.draw(m_renderer, 12, 370, 219, 218);
        }
        if(Jeu.GetJoueurActuel()==1)
        {
            m_encadrer.draw(m_renderer, 12, 11, 219, 218);
        }
        if(Jeu.GetJoueurActuel()==2)
        {
            m_encadrer.draw(m_renderer, 370, 11, 220, 218);
        }
        if(Jeu.GetJoueurActuel()==3)
        {
            m_encadrer.draw(m_renderer, 370, 370, 220, 218);
        }
    
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

    /*if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {       //44100 frequence en Hz, format par defaut, stereo, 2042 taille buffer audio, plus petit = plus rapide 
        cout << "Erreur Mix_OpenAudio : " << Mix_GetError() << std::endl;
    }

    
    ///son
    de_son = Mix_LoadWAV("data/son/de_son.wav");
    if (!de_son) {
        cout << "Erreur de chargement du son : " << Mix_GetError() <<endl;
    }

    Mix_VolumeChunk(de_son, MIX_MAX_VOLUME);*/


}


void AffichageSDL::AnimerDeplacement(Jeu &Jeu, int id_joueur, int id_pion, int i_depart, int i_arrivee) {
    for (int i = i_depart + 1; i <= i_arrivee; i++) {
        float x, y;

        if (i <= 52) {
            // On est encore sur le chemin classique
            int case_depart = Jeu.IdVersCase(*Jeu.GetJoueur(id_joueur));
            int index_chemin = (i + case_depart) % 52;
            x = Jeu.GetChemin(index_chemin).first;
            y = Jeu.GetChemin(index_chemin).second;
        } else {
            // On est dans la zone gagnante du joueur
            int index_gagnant = i - 53;
            const pair<int, int>* tab_zone = Jeu.IdversTableauGagnant(id_joueur);
            x = tab_zone[index_gagnant].first;
            y = tab_zone[index_gagnant].second;
        }

        Jeu.GetJoueur(id_joueur)->SetXpion(id_pion, x);
        Jeu.GetJoueur(id_joueur)->SetYpion(id_pion, y);

        SdlAff(false, false, false, Jeu.GetDe(), Jeu);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(200);
    }
}








void AffichageSDL::SdlBoucle(Jeu &Jeu)
{
    SDL_Event events;
    bool menu=true;
    bool quit = false;
    bool de_lancer_aff = false;
    bool cliquer = false;
    cout<<"Le pion 0 de J0 a pour i= "<<Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(0).GetI()<<endl;

    while (!quit)
    {
        

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true;

            if(menu && events.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = events.button.x;
                int y = events.button.y;

                if (x >= bouton1.x && x <= bouton1.x + bouton1.w && y >= bouton1.y && y <= bouton1.y + bouton1.h) 
                {
                    Jeu.SetNbJoueur(1);
                    std::cout << "1 joueur sélectionné\n";
                    cliquer = true;
                }
                else if (x >= bouton2.x && x <= bouton2.x + bouton2.w && y >= bouton2.y && y <= bouton2.y + bouton2.h) 
                {
                    Jeu.SetNbJoueur(2);
                    std::cout << "2 joueur sélectionné\n";
                    cliquer = true;
                }
                else if (x >= bouton3.x && x <= bouton3.x + bouton3.w && y >= bouton3.y && y <= bouton3.y + bouton3.h) 
                {
                    Jeu.SetNbJoueur(3);
                    std::cout << "3 joueur sélectionné\n";
                    cliquer = true;
                }
                else if (x >= bouton4.x && x <= bouton4.x + bouton4.w && y >= bouton4.y && y <= bouton4.y + bouton4.h) 
                {
                    Jeu.SetNbJoueur(4);
                    std::cout << "4 joueur sélectionné\n";
                    cliquer = true;
                }
            }
            
            if (events.type == SDL_KEYDOWN)
            {
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    quit = true;
                    break;

                case SDL_SCANCODE_0:
                    menu=false;
                    break;

                case SDL_SCANCODE_SPACE:
                    if (Jeu.GetEtat()==ATTENTE_LANCER_DE)
                    {
                        Jeu.Gerer_Jeu(0);   //changer?
                        //Mix_PlayChannel(-1, de_son, 0);     //-1 canal, 0 pour jouer une fois
                        de_lancer_aff = true;
                        /*if (Mix_PlayChannel(-1, de_son, 0) == -1) {
                            std::cout << "Erreur de lecture du son : " << Mix_GetError() << std::endl;
                        }*/
                        
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

        //Mix_CloseAudio(); 

        // Affichage

        SdlAff(menu, cliquer, de_lancer_aff, Jeu.GetDe(), Jeu);
        de_lancer_aff =false;
        SDL_RenderPresent(m_renderer);
    }
}