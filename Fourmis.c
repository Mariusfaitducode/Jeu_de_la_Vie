//
// Created by Marius on 12/01/2022.
//

#include "Fourmis.h"
#include "Vie.h"



//Fourmis de Langton

//Configuration jeu

void Init_TabFourmis ( Case T [LIGNES][COLONNES]){

    int i, j;

    for ( i=0; i<LIGNES; i++){
        for ( j=0; j<COLONNES; j++){
            T[i][j].etat = VIDE;
        }
    }
}

void CliqueFourmis ( int colonne, int ligne, Case T [LIGNES][COLONNES]){

    if (T[ligne][colonne].etat == VIDE){
        T[ligne][colonne].etat = FOURMIS;
        T[ligne][colonne].direction = DROITE;

    }else if (T[ligne][colonne].etat == FOURMIS){
        T[ligne][colonne].etat = VIDE;
        T[ligne][colonne].direction = VIDE;
    }
}

void AfficheFourmis(SDL_Window **window, SDL_Renderer **renderer, SDL_Surface **image, SDL_Texture **texture, int colonne, int ligne, Case T[LIGNES][COLONNES]){

    if (T[ligne][colonne].etat==FOURMIS){
        Put_Image(window, renderer, image, texture, colonne*20, (ligne*20)+5,
              "C:\\Users\\Marius\\CLionProjects\\Projets_SDL\\Jeu_de_la_vie\\Image\\fourmis1.bmp");
    }
}

void EffaceFourmis(SDL_Renderer *renderer, int TVie[LIGNES][COLONNES], Case TFourmis[LIGNES][COLONNES], int colonne, int ligne){

    if (TFourmis[ligne][colonne].etat == VIDE){
        if(TVie[ligne][colonne] == MORT){

            if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0){
                SDL_ExitWithError("Couleur rendu");
            }

            SDL_Rect background;
            background.x = colonne * TAILLE_CASE + 1;
            background.y = ligne * TAILLE_CASE + 1;
            background.w = TAILLE_CASE - 1;
            background.h = TAILLE_CASE - 1;

            if (SDL_RenderFillRect(renderer, &background) != 0) {
                printf("Rectangle failed: %s\n", SDL_GetError());
            }
            SDL_RenderPresent(renderer);
        }
        else if (TVie[ligne][colonne] == VIE){
            if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0){
                SDL_ExitWithError("Couleur rendu");
            }

            SDL_Rect background;
            background.x = colonne * TAILLE_CASE + 1;
            background.y = ligne * TAILLE_CASE + 1;
            background.w = TAILLE_CASE - 1;
            background.h = TAILLE_CASE - 1;

            if (SDL_RenderFillRect(renderer, &background) != 0) {
                printf("Rectangle failed: %s\n", SDL_GetError());
            }
            SDL_RenderPresent(renderer);
        }
    }
}

void AfficheNewFourmis(SDL_Window **window, SDL_Renderer **renderer, SDL_Surface **image, SDL_Texture **texture, Case T[LIGNES][COLONNES]){

    int i, j;

    for ( i=0; i<LIGNES; i++){
        for ( j=0; j<COLONNES; j++){

            if (T[i][j].etat == NAIT){
                T[i][j].etat = FOURMIS;
                Put_Image(window, renderer, image, texture, j*20, (i*20)+5,
                          "C:\\Users\\Marius\\CLionProjects\\Projets_SDL\\Jeu_de_la_vie\\Image\\fourmis1.bmp");
            }
        }
    }
}

//Règle jeu

void Play_Fourmis (SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture, int Tab[LIGNES][COLONNES], Case fourmis[LIGNES][COLONNES], int *tour){
    Deplacements(Tab, fourmis);
    Actualisation(renderer, Tab);
    Affiche_Cellule(renderer, Tab);
    AfficheNewFourmis(&window, &renderer, &image, &texture, fourmis);
    *tour = *tour + 1;
    printf("%d\n",*tour);
}

void Deplacements(int TVie[LIGNES][COLONNES], Case TFourmis[LIGNES][COLONNES]){

    int i, j;

    for ( i=0; i<LIGNES; i++){
        for ( j=0; j<COLONNES; j++){

            if (TFourmis[i][j].etat == FOURMIS){
                if (TVie[i][j] == MORT){
                    TVie[i][j] = NAIT;

                    if (TFourmis[i][j].direction == DROITE){

                        TFourmis[i+1][j].etat = NAIT;
                        TFourmis[i+1][j].direction = BAS;
                    }
                    else if (TFourmis[i][j].direction == GAUCHE){

                        TFourmis[i-1][j].etat = NAIT;
                        TFourmis[i-1][j].direction = HAUT;
                    }
                    else if (TFourmis[i][j].direction == HAUT){

                        TFourmis[i][j+1].etat = NAIT;
                        TFourmis[i][j+1].direction = DROITE;
                    }
                    else if (TFourmis[i][j].direction == BAS){

                        TFourmis[i][j-1].etat = NAIT;
                        TFourmis[i][j-1].direction = GAUCHE;
                    }
                }
                else if (TVie[i][j] == VIE){
                    TVie[i][j] = DISPARAIT;

                    if (TFourmis[i][j].direction == DROITE){

                        TFourmis[i-1][j].etat = NAIT;
                        TFourmis[i-1][j].direction = HAUT;
                    }
                    else if (TFourmis[i][j].direction == GAUCHE){

                        TFourmis[i+1][j].etat = NAIT;
                        TFourmis[i+1][j].direction = BAS;
                    }
                    else if (TFourmis[i][j].direction == HAUT){

                        TFourmis[i][j-1].etat = NAIT;
                        TFourmis[i][j-1].direction = GAUCHE;
                    }
                    else if (TFourmis[i][j].direction == BAS){

                        TFourmis[i][j+1].etat = NAIT;
                        TFourmis[i][j+1].direction = DROITE;
                    }
                }

                TFourmis[i][j].etat = VIDE;
                TFourmis[i][j].direction = VIDE;

        }
    }
}
}

//Affichage

void Put_Image (SDL_Window **window, SDL_Renderer **renderer, SDL_Surface **image, SDL_Texture **texture, int X, int Y,  const char *message)//Permet d'afficher une image
{

    *image = SDL_LoadBMP(message);
    if ( *image == NULL ){
        SDL_ExitTexture("Affichage Fourmis", window, renderer, texture);
    }

    *texture = SDL_CreateTextureFromSurface( *renderer, *image);
    SDL_FreeSurface( *image );

    if ( *texture == NULL){
        SDL_ExitTexture("Texture", window, renderer, texture);
    }

    SDL_Rect dim_image;

    if (SDL_QueryTexture(*texture, NULL, NULL, &dim_image.w, &dim_image.h) != 0){
        SDL_ExitTexture("Chargement texture", window, renderer, texture);
    }
    dim_image.x = X;
    dim_image.y = Y;

    if (SDL_RenderCopy(*renderer, *texture, NULL, &dim_image) != 0){
        SDL_ExitTexture("Affichage texture", window, renderer, texture);
    }
    SDL_RenderPresent(*renderer) ;
}