//
// Created by Marius on 06/01/2022.
//

#include "Vie.h"

//Initialisation

void Init_SDL (){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        // Unrecoverable error, exit here.
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }
}

void Init_Page(SDL_Window **screen, SDL_Renderer **renderer){
    if(SDL_CreateWindowAndRenderer(WINDOW_W, WINDOW_H, 0, screen, renderer) != 0){
        // Unrecoverable error, exit here.
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void Init_Fond (SDL_Renderer *renderer) {

    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0) {

        printf("Color failed: %s\n", SDL_GetError());
    }

    SDL_Rect background;
    background.x = 0;
    background.y = 0;
    background.w = WINDOW_W;
    background.h = WINDOW_H;

    if (SDL_RenderFillRect(renderer, &background) != 0) {
        printf("Rectangle failed: %s\n", SDL_GetError());
    }
    SDL_RenderPresent(renderer);
}

void Init_Quadrillage(SDL_Renderer *renderer){

    int x, y;

    if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0){
        SDL_ExitWithError("Couleur rendu");
    }
    //Lignes verticales
    for(x = 0; x <=  WINDOW_W; x = x + TAILLE_CASE){
        if(SDL_RenderDrawLine(renderer,x,0,x,WINDOW_H) != 0){
            SDL_ExitWithError("Ligne");
        }
    }

    //Lignes horizontales
    for(y = 0; y <= WINDOW_H; y = y + TAILLE_CASE){
        if(SDL_RenderDrawLine(renderer, 0, y, WINDOW_W, y) != 0){
            SDL_ExitWithError("Ligne");
        }
    }
}

void Init_Tab ( int T [LIGNES][COLONNES]){

    int i, j;

    for ( i=0; i<LIGNES; i++){
        for ( j=0; j<COLONNES; j++){
            T [i][j] = MORT;
        }
    }
}

//Configuration jeu

void Play_Vie (SDL_Renderer *renderer, int *tour, int Tab [LIGNES][COLONNES]){

    Vie(Tab);
    Mort(Tab);
    Actualisation(renderer, Tab);
    *tour = *tour + 1;
    printf("%d\n",*tour);
    Affiche_Cellule(renderer, Tab);
}

void Clique (int ligne, int colonne, int T [LIGNES][COLONNES]){

    if (T[ligne][colonne] == MORT){
        T[ligne][colonne] = VIE;
    }else if (T[ligne][colonne] == VIE){
        T[ligne][colonne] = DISPARAIT;
    }
}

void Affiche_Cellule (SDL_Renderer *renderer, int T [LIGNES][COLONNES]){

    int i, j;

    for ( i=0; i<LIGNES; i++){
        for ( j=0; j<COLONNES; j++){
            if (T[i][j] == VIE){

                if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Couleur rendu");
                }

                SDL_Rect background;
                background.x = j * TAILLE_CASE;
                background.y = i * TAILLE_CASE;
                background.w = TAILLE_CASE;
                background.h = TAILLE_CASE;

                if (SDL_RenderFillRect(renderer, &background) != 0) {
                    printf("Rectangle failed: %s\n", SDL_GetError());
                }
                SDL_RenderPresent(renderer);
            }
        }
    }
}

//Règles de jeu

int Adjacents(int i, int j, int T [LIGNES][COLONNES]){

    int x, y;
    int compte = 0;

    for(x=i-1; x<i+2; x++){
        for(y=j-1; y<j+2; y++){

            if (T[x][y] == VIE || T[x][y] == DISPARAIT ){
                compte++;
            }
        }
    }
    return compte;
}

void Vie (int T [LIGNES][COLONNES]){

    int i, j;


    for ( i=0; i<LIGNES; i++){
        for ( j=0; j<COLONNES; j++){
            if (T [i][j] == MORT){
                if ( Adjacents(i,j,T) == 3){
                    T[i][j] = NAIT;
                }
            }
        }
    }
}

void Mort (int T [LIGNES][COLONNES]){

    int i, j;

    for ( i=0; i<LIGNES; i++){
        for ( j=0; j<COLONNES; j++){
            if (T [i][j] == VIE){
                if ( Adjacents(i,j,T) == 3 || Adjacents(i,j,T) == 4 ){
                    T[i][j]= VIE;
                }
                else{
                    T[i][j]= DISPARAIT;
                }
            }
        }
    }
}

void Actualisation ( SDL_Renderer *renderer, int T [LIGNES][COLONNES] ){

    int i, j;

    for ( i=0; i<LIGNES; i++){
        for ( j=0; j<COLONNES; j++){

            if ( T[i][j] == NAIT){
                T[i][j] = VIE;
            }
            else if ( T[i][j] == DISPARAIT){
                T[i][j] = MORT;
                if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0){
                    SDL_ExitWithError("Couleur rendu");
                }

                SDL_Rect background;
                background.x = j * TAILLE_CASE + 1;
                background.y = i * TAILLE_CASE + 1;
                background.w = TAILLE_CASE - 1;
                background.h = TAILLE_CASE - 1;

                if (SDL_RenderFillRect(renderer, &background) != 0) {
                    printf("Rectangle failed: %s\n", SDL_GetError());
                }
                SDL_RenderPresent(renderer);
            }
        }
    }
}


void SDL_ExitTexture (const char *message, SDL_Window **screen, SDL_Renderer **renderer , SDL_Texture **texture)
{
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*screen);
    SDL_DestroyTexture(*texture);
    SDL_ExitWithError(message);
}