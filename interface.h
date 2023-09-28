/**
 * @file interface.h
 * @brief Header file containing function declarations for the user interface.
 *
 * This header file declares functions related to the graphical user interface
 * for the application, including functions for creating various interface pages,
 * handling button clicks, and more.
 */

#ifndef INTERFACE_H
#define INTERFACE_H
#include <gtk/gtk.h>

// Déclarations des fonctions de la page d'accueil
void on_button_clicked(GtkWidget *widget, gpointer data);
void on_quit_button_clicked(GtkWidget *widget, gpointer data);
void create_page_accueil();

// Déclarations des fonctions de la page de confirmation de sortie
void on_button_quitter_clicked(GtkWidget *widget, gpointer data);
void on_button_rester_clicked(GtkWidget *widget, gpointer data);
void create_page_exit();

// Déclarations des fonctions de l'interface du jeu
void on_cell_clicked_2_player(GtkButton *button, gpointer user_data);
gboolean on_window_closed(GtkWidget *widget, GdkEvent *event, gpointer user_data);
void create_game_interface();
void create_game_interface_ia();
// Fonction appelée lorsqu'un CheckBox est activé/désactivé
static void on_checkbox_toggled(GtkWidget *widget, gpointer data);

// Fonction appelée lorsqu'un bouton "Jouer" est cliqué
static void on_play_button_clicked(GtkWidget *widget, gpointer data);

// Fonction appelée lorsqu'un bouton "Exit" est cliqué
static void on_exit_button_clicked(GtkWidget *widget, gpointer data);

void interfaceReseauConfig();

void on_dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data);

// Player vs IA
void on_cell_clicked_1_ia(GtkButton *button, gpointer user_data);
void on_cell_clicked_2_ia(GtkButton *button, gpointer user_data);



// IA vs IA
void create_game_interface_iaVSia();

#endif

