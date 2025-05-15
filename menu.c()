#include "menu.h"
#include <stdlib.h>

FONT *big_font = NULL;
BITMAP *buffer = NULL;
BITMAP *background = NULL;
SAMPLE *menu_sound = NULL;

// Options de menu
const char *menu_options[NUM_OPTIONS] = {
    "Nouvelle Partie",
    "Options",
    "Quitter"
};
const char *options_sous_menu[NUM_SUBOPTIONS] = {
    "Controles",
    "Guide",
    "Retour"
};

void initialisation_allegro() {
    allegro_init();
    install_keyboard();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_color_depth(24);

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0) != 0) {
        allegro_message("Probleme gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    background = load_bitmap("Blueback.bmp", NULL);
    if (!background) {
        allegro_message("Erreur chargement background");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if (!buffer) {
        allegro_message("Erreur creation bitmaps");
        exit(EXIT_FAILURE);
    }

    menu_sound = load_sample("menusound.wav");
    if (!menu_sound) {
        allegro_message("impossible de charger le son du menu");
    }
}

void afficher_controles(BITMAP *cible) {
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    set_trans_blender(0, 0, 0, 128);
    rectfill(cible, 50, 80, SCREEN_W - 50, SCREEN_H - 80, makecol(0, 0, 0));
    drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

    textout_centre_ex(cible, font, "CONTROLES DU JEU", SCREEN_W / 2, 100, makecol(0, 255, 0), -1);
    textout_ex(cible, font, "- Deplacement gauche: Fleche GAUCHE", 100, 150, makecol(255, 255, 255), -1);
    textout_ex(cible, font, "- Deplacement droite: Fleche DROITE", 100, 180, makecol(255, 255, 255), -1);
    textout_ex(cible, font, "- Monter: Fleche HAUT", 100, 210, makecol(255, 255, 255), -1);
    textout_ex(cible, font, "- Descendre: Fleche BAS", 100, 240, makecol(255, 255, 255), -1);
    textout_centre_ex(cible, font, "[Retour via le menu Options]", SCREEN_W / 2, 300, makecol(150, 150, 150), -1);
}

void afficher_guide(BITMAP *cible) {
    const char *lignes_guide[] = {
        "Dans Galaxia Classic, ton objectif est de defendre ton",
        "vaisseau spatial contre des vagues d'ennemis venus de",
        "l'espace. Les ennemis attaquent en formation ou foncent",
        "vers toi pour te surprendre, alors reste mobile et tire",
        "avec precision pour les eliminer.",
        "",
        "Chaque ennemi detruit te rapporte 50 points, alors plus",
        "tu en abats, plus ton score grimpe. Survis le plus",
        "longtemps possible, esquive les tirs ennemis et tente",
        "de battre ton propre record a chaque partie."
    };

    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    set_trans_blender(0, 0, 0, 128);
    rectfill(cible, 50, 80, SCREEN_W - 50, SCREEN_H - 80, makecol(0, 0, 0));
    drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

    textout_centre_ex(cible, font, "GUIDE DU JOUEUR", SCREEN_W / 2, 100, makecol(0, 200, 255), -1);

    int y = 150;
    for (int i = 0; i < sizeof(lignes_guide) / sizeof(char*); i++) {
        textout_ex(cible, font, lignes_guide[i], 50, y, makecol(200, 200, 200), -1);
        y += 20;
    }
    textout_centre_ex(cible, font, "[Retour via le menu Options]", SCREEN_W / 2, 400, makecol(150, 150, 150), -1);
}

void boucle_menu() {
    big_font = load_font("big_fontp.ttf", NULL, NULL);
    if (!big_font) big_font = font;

    int selected = 0;
    int key_pressed;
    MenuState menu_state = MENU_PRINCIPAL;

    while (!key[KEY_ESC]) {
        blit(background, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        textout_centre_ex(buffer, big_font, "GALAXIA CLASSIC", SCREEN_W / 2, 50, makecol(255, 0, 0), -1);

        switch (menu_state) {
            case MENU_PRINCIPAL:
                for (int i = 0; i < NUM_OPTIONS; i++) {
                    int color = (i == selected) ? makecol(255, 255, 0) : makecol(255, 255, 255);
                    textout_ex(buffer, font, menu_options[i], SCREEN_W / 2 - 100, 150 + i * 30, color, -1);
                }
                break;

            case MENU_OPTIONS:
                for (int i = 0; i < NUM_SUBOPTIONS; i++) {
                    int color = (i == selected) ? makecol(0, 255, 255) : makecol(200, 200, 200);
                    textout_ex(buffer, font, options_sous_menu[i], SCREEN_W / 2 - 100, 150 + i * 30, color, -1);
                }
                break;

            case MENU_CONTROLES:
                afficher_controles(buffer);
                break;

            case MENU_GUIDE:
                afficher_guide(buffer);
                break;
        }

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if (keypressed()) {
            key_pressed = readkey() >> 8;

            switch (menu_state) {
                case MENU_PRINCIPAL:
                    if (key_pressed == KEY_DOWN) {
                        if (menu_sound) play_sample(menu_sound, 255, 128, 1000, 0);
                        selected = (selected + 1) % NUM_OPTIONS;
                    } else if (key_pressed == KEY_UP) {
                        if (menu_sound) play_sample(menu_sound, 255, 128, 1000, 0);
                        selected = (selected - 1 + NUM_OPTIONS) % NUM_OPTIONS;
                    } else if (key_pressed == KEY_ENTER) {
                        if (menu_sound) play_sample(menu_sound, 255, 128, 1000, 0);
                        if (selected == 0) allegro_message("Nouvelle Partie !");
                        else if (selected == 1) {
                            menu_state = MENU_OPTIONS;
                            selected = 0;
                        } else if (selected == 2) {
                            goto end_program;
                        }
                    }
                    break;

                case MENU_OPTIONS:
                    if (key_pressed == KEY_DOWN) {
                        if (menu_sound) play_sample(menu_sound, 255, 128, 1000, 0);
                        selected = (selected + 1) % NUM_SUBOPTIONS;
                    } else if (key_pressed == KEY_UP) {
                        if (menu_sound) play_sample(menu_sound, 255, 128, 1000, 0);
                        selected = (selected - 1 + NUM_SUBOPTIONS) % NUM_SUBOPTIONS;
                    } else if (key_pressed == KEY_ENTER) {
                        if (menu_sound) play_sample(menu_sound, 255, 128, 1000, 0);
                        if (selected == 0) menu_state = MENU_CONTROLES;
                        else if (selected == 1) menu_state = MENU_GUIDE;
                        else if (selected == 2) {
                            menu_state = MENU_PRINCIPAL;
                            selected = 0;
                        }
                    }
                    break;

                case MENU_CONTROLES:
                case MENU_GUIDE:
                    if (key_pressed == KEY_ENTER) {
                        if (menu_sound) play_sample(menu_sound, 255, 128, 1000, 0);
                        menu_state = MENU_OPTIONS;
                        selected = 2;
                    }
                    break;
            }
        }
        rest(50);
    }

end_program:
    destroy_bitmap(background);
    destroy_bitmap(buffer);
    destroy_font(big_font);
    destroy_sample(menu_sound);
}
