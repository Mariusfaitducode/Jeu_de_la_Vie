//
// Created by Marius on 12/01/2022.
//

#ifndef JEU_DE_LA_VIE_FOURMIS_H
#define JEU_DE_LA_VIE_FOURMIS_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_W 1280
#define WINDOW_H 800

#define TAILLE_CASE 20

#define LIGNES (WINDOW_H/TAILLE_CASE)
#define COLONNES (WINDOW_W /TAILLE_CASE)


typedef struct {
    int etat;
    int direction;
}Case;


#define TRUE 1
#define FALSE 0

#define VIE 1
#define MORT 0

#define NAIT 2
#define DISPARAIT 3

#define FOURMIS 1
#define VIDE 0

#define DROITE 1
#define GAUCHE 2
#define HAUT 3
#define BAS 4

void Init_TabFourmis ( Case T [LIGNES][COLONNES]);

void CliqueFourmis ( int colonne, int ligne, Case T [LIGNES][COLONNES]);

void AfficheFourmis(SDL_Window **window, SDL_Renderer **renderer, SDL_Surface **image, SDL_Texture **texture, int colonne, int ligne, Case T[LIGNES][COLONNES]);

void EffaceFourmis(SDL_Renderer *renderer, int TVie[LIGNES][COLONNES], Case TFourmis[LIGNES][COLONNES], int colonne, int ligne);

void AfficheNewFourmis(SDL_Window **window, SDL_Renderer **renderer, SDL_Surface **image, SDL_Texture **texture, Case T[LIGNES][COLONNES]);

//Regle jeu

void Play_Fourmis (SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture, int Tab[LIGNES][COLONNES], Case fourmis[LIGNES][COLONNES], int *tour);

void Deplacements(int TVie[LIGNES][COLONNES], Case TFourmis[LIGNES][COLONNES]);

//Affichage

void Put_Image (SDL_Window **window, SDL_Renderer **renderer, SDL_Surface **image, SDL_Texture **texture, int X, int Y,  const char *message);

#endif //JEU_DE_LA_VIE_FOURMIS_H
