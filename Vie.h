//
// Created by Marius on 06/01/2022.
//

#ifndef JEU_DE_LA_VIE_VIE_H
#define JEU_DE_LA_VIE_VIE_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_W 1280
#define WINDOW_H 800

#define TAILLE_CASE 20

#define LIGNES (WINDOW_H/TAILLE_CASE)
#define COLONNES (WINDOW_W /TAILLE_CASE)


typedef int bool;

#define TRUE 1
#define FALSE 0

#define VIE 1
#define MORT 0

#define NAIT 2
#define DISPARAIT 3


void Init_SDL ();

void Init_Page(SDL_Window **screen, SDL_Renderer **renderer);

void SDL_ExitWithError(const char *message);

void SDL_ExitTexture (const char *message, SDL_Window **screen, SDL_Renderer **renderer , SDL_Texture **texture);

void Init_Fond (struct SDL_Renderer *renderer);

void Init_Quadrillage(SDL_Renderer *renderer);

void Init_Tab ( int T [LIGNES][COLONNES]);

//Configuration jeu

void Play_Vie (SDL_Renderer *renderer, int *tour, int Tab [LIGNES][COLONNES]);

void Clique (int ligne, int colonne, int T [LIGNES][COLONNES]);

void Affiche_Cellule (SDL_Renderer *renderer, int T [LIGNES][COLONNES]);

//Règles jeu

void Vie (int T [LIGNES][COLONNES]);

void Mort (int T [LIGNES][COLONNES]);

void Actualisation (SDL_Renderer *renderer, int T [LIGNES][COLONNES]);




#endif //JEU_DE_LA_VIE_VIE_H
