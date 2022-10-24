#include "Vie.h"
#include "Fourmis.h"

int main(int argc, char *argv[]) {

    //INITIALISATION
    //INITIALISATION CREATION FENETRE + RENDU

    int type_jeu;

    printf("Jeu de la vie = 1 / Fourmis de langton = 2 :\n");
    scanf("%d",&type_jeu);
    while(type_jeu<0 || type_jeu>2){
        printf("Jeu de la vie = 1 / Fourmis de langton = 2 :\n");
        scanf("%d",&type_jeu);
    }

    int Tab[LIGNES][COLONNES];

    Case fourmis [LIGNES][COLONNES];


    int ligne;
    int colonne;

    int start;
    int tour = 0;

    SDL_Window *window = NULL;      //Déclarer un pointeur de fenêtre
    SDL_Renderer *renderer = NULL;      //Déclarer un pointeur de rendu

    SDL_Surface *image = {NULL};
    SDL_Texture *texture = {NULL};

    // Initialiser SDL2
    Init_SDL();

    //Creation fenetre + rendu
    Init_Page(&window, &renderer);

    //Initialisation Plateau
    Init_Fond(renderer);
    Init_Quadrillage(renderer);

    Init_Tab(Tab);
    Init_TabFourmis(fourmis);

    SDL_RenderPresent(renderer);



    //EVENT : COMMANDES JOUEURS

    SDL_bool program_launched = SDL_TRUE;

    while (program_launched)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {

            if (start == TRUE){
                if(type_jeu==1){
                    Play_Vie(renderer, &tour, Tab);
                }
                if (type_jeu == 2){
                    Play_Fourmis(window, renderer, image, texture, Tab, fourmis, &tour);
                }
            }

            switch(event.type){

                case SDL_MOUSEBUTTONDOWN:

                    ligne = event.button.y / TAILLE_CASE;
                    colonne = event.button.x / TAILLE_CASE;

                    if (type_jeu == 1){
                        Clique(ligne, colonne, Tab);
                        Actualisation(renderer, Tab);
                        Affiche_Cellule(renderer, Tab);
                    }
                    if (type_jeu == 2){
                        CliqueFourmis( colonne, ligne, fourmis);
                        AfficheFourmis(&window, &renderer, &image, &texture, colonne, ligne, fourmis);
                        EffaceFourmis(renderer, Tab, fourmis, colonne, ligne);
                    }

                    break;

                case SDL_KEYDOWN :
                    if(event.key.keysym.sym == SDLK_SPACE && start != TRUE){
                        start = TRUE;
                    }else{
                        start = FALSE;
                    }
                    if(event.key.keysym.sym == SDLK_UP){
                        if (type_jeu == 1){
                            Play_Vie(renderer, &tour, Tab);
                        }
                        if (type_jeu == 2){
                            Play_Fourmis(window, renderer, image, texture, Tab, fourmis, &tour);
                            //Play_Vie(renderer, &tour, Tab);
                        }
                    }
                    break;

                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }


    //FERMETURE

    // Ferme la fenetre
    //SDL_DestroyTexture( texture_pion);
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );

    // Nettoyage
    SDL_Quit();


    return 0;
}
