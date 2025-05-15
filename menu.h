#ifndef MENU_H
#define MENU_H

#include <allegro.h>

// Constantes
#define NUM_OPTIONS 3
#define NUM_SUBOPTIONS 3
#define SCREEN_W 640
#define SCREEN_H 480

// Enum pour les états du menu
typedef enum {
    MENU_PRINCIPAL,
    MENU_OPTIONS,
    MENU_CONTROLES,
    MENU_GUIDE
} MenuState;

// Variables globales externes (à définir dans menu.c)
extern FONT *big_font;
extern BITMAP *buffer;
extern BITMAP *background;
extern SAMPLE *menu_sound;

// Fonctions principales
void initialisation_allegro();
void afficher_controles(BITMAP *cible);
void afficher_guide(BITMAP *cible);
void boucle_menu();

#endif
