/**
 * @file interface.c
 * @brief User Interface Implementation
 *
 * This file contains the implementation of the user interface for the Hex game.
 */

#include <gtk/gtk.h>
#include "interface.h"
#include "Jeu.h"
#include "IA.h"
#include "network.h"
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <arpa/inet.h>

#define PORT 1234
#define SA struct sockaddr
char* ipAd = NULL;
int turn;



char player_turn = 'B';
char player_choice;

GtkWidget *ipTextField = NULL;
GtkWidget *playerCheckboxPlayer = NULL;
GtkWidget *playerCheckboxIA = NULL;
GtkWidget *serverClientCheckboxServer = NULL;
GtkWidget *serverClientCheckboxClient = NULL;
gboolean buttonClient;
gboolean buttonServer;
gboolean buttonPlayer;
gboolean buttonIA;

/*char board[SIZE][SIZE] = {
    {'R', 'O', 'B', 'O', 'R', 'B'},
    {'O', 'R', 'B', 'O', 'R', 'B'},
    {'B', 'O', 'R', 'O', 'R', 'B'},
    {'O', 'R', 'O', 'B', 'O', 'R'},
    {'R', 'B', 'R', 'O', 'B', 'O'},
    {'B', 'O', 'R', 'B', 'O', 'R'}

/**
 * @brief Callback function when a game cell is clicked.
 *
 * Handles the cell click event and updates the game board.
 *
 * @param button The clicked button.
 * @param user_data User data (not used here).
 */
void on_cell_clicked_2_player(GtkButton *button, gpointer user_data) {
    int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "row"));
    gint col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "col"));
    GError *error = NULL;
    GtkWidget *BLUEPIC = NULL;
    GtkWidget *REDPIC = NULL;
    char *current_dir = g_get_current_dir();
    char *blue_image_path = g_build_filename(current_dir, "BLUE.png", NULL);
    char *red_image_path = g_build_filename(current_dir, "RED.png", NULL);

    GtkWidget *blue_image = gtk_image_new_from_file(blue_image_path);
    GtkWidget *red_image = gtk_image_new_from_file(red_image_path);


    
        // Affectez les images à BLUEPIC et REDPIC
        BLUEPIC = blue_image;
        REDPIC = red_image;

        // Affichez l'image BLUEPIC par défaut
        
    

    g_free(current_dir);
    g_free(blue_image_path);
    g_free(red_image_path);
    // Check if the cell is empty ('O')
    if (board[row][col] == ' ') {
        //gchar *label_text = NULL;

        // Toggle the character in the cell
        if (player_turn == 'R') {
            board[row][col] = 'R';
            //label_text = "R";
            gtk_button_set_image(GTK_BUTTON(button), REDPIC);
        } else if (player_turn == 'B') {
            board[row][col] = 'B';
            //label_text = "B";
            gtk_button_set_image(GTK_BUTTON(button), BLUEPIC);
        }

        

        //GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));
        //gtk_label_set_text(GTK_LABEL(label), label_text);

        if (CheckVictory(player_turn, board)) {
            gchar *message = g_strdup_printf("Victory player %c", player_turn);

            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "%s", message);

            g_signal_connect(dialog, "response", G_CALLBACK(on_dialog_response), NULL);
            gtk_widget_show_all(dialog);
            g_free(message);
        }

        // Toggle the player's turn for the next move
        player_turn = (player_turn == 'R') ? 'B' : 'R';
    }
    
}


/**
 * @brief Callback function when a GTK dialog response is received.
 *
 * This function quits the GTK main loop and destroys the dialog when a response is received.
 *
 * @param dialog The GTK dialog widget.
 * @param response_id The response ID.
 * @param user_data User data (not used in this callback).
 */
void on_dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data) {
    gtk_main_quit();
    gtk_widget_destroy(GTK_WIDGET(dialog)); // Fermez la boîte de dialogue
}

// IA vS IA

/**
 * @brief Callback function when a game cell is clicked in AI vs. AI mode.
 *
 * Handles the cell click event and makes moves in an AI vs. AI Hex game.
 *
 * @param button The clicked button.
 * @param user_data User data containing cellArray and other information.
 */
void on_cell_clicked_2_iavsia(GtkButton *button, gpointer user_data) {

    GtkWidget ***cellArray = (GtkWidget ***)user_data;

    int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "row"));
    gint col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "col"));

    GError *error = NULL;
    GtkWidget *BLUEPIC = NULL;
    GtkWidget *REDPIC = NULL;
    char *current_dir = g_get_current_dir();
    char *blue_image_path = g_build_filename(current_dir, "BLUE.png", NULL);
    char *red_image_path = g_build_filename(current_dir, "RED.png", NULL);

    GtkWidget *blue_image = gtk_image_new_from_file(blue_image_path);
    GtkWidget *red_image = gtk_image_new_from_file(red_image_path);


    
        // Affectez les images à BLUEPIC et REDPIC
        BLUEPIC = blue_image;
        REDPIC = red_image;

        // Affichez l'image BLUEPIC par défaut
        
    

    g_free(current_dir);
    g_free(blue_image_path);
    g_free(red_image_path);
    // Check if the cell is empty ('O')
    if (board[row][col] == ' ' || board[row][col] != ' ' ) {
        int rowia;
        gint colia;

        


        Move bestMove = getBestMove(board, turn, 'B');

        board[bestMove.row][bestMove.col] = 'B';
        rowia = bestMove.row;
        colia = bestMove.col;
        g_print("\nIA 1 ::: %d %d\n", rowia,colia);
        gtk_button_set_image(GTK_BUTTON(cellArray[rowia][colia]), BLUEPIC);


        turn ++;

        bestMove = getBestMove(board, turn, 'R');
        turn++;

        board[bestMove.row][bestMove.col] = 'R';
        rowia = bestMove.row;
        colia = bestMove.col;
        g_print("\nIA 2 ::: %d %d\n", rowia,colia);
            
        gtk_button_set_image(GTK_BUTTON(cellArray[rowia][colia]), REDPIC);
        

            if (CheckVictory(player_turn, board)) {
                gchar *message = g_strdup_printf("Victory player %c", player_turn);

                GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                                        GTK_MESSAGE_INFO,
                                                        GTK_BUTTONS_OK,
                                                        "%s", message);

                g_signal_connect(dialog, "response", G_CALLBACK(on_dialog_response), NULL);
                gtk_widget_show_all(dialog);
                g_free(message);

            }
    }
    
}



//player VS AI

/**
 * @brief Callback function when a game cell is clicked in player vs. AI mode.
 *
 * Handles the cell click event and makes moves in a player vs. AI Hex game.
 *
 * @param button The clicked button.
 * @param user_data User data containing cellArray and other information.
 */
void on_cell_clicked_1_ia(GtkButton *button, gpointer user_data) {

    GtkWidget ***cellArray = (GtkWidget ***)user_data;


        GError *error = NULL;
        GtkWidget *BLUEPIC = NULL;
        GtkWidget *REDPIC = NULL;
        char *current_dir = g_get_current_dir();
        char *blue_image_path = g_build_filename(current_dir, "BLUE.png", NULL);
        char *red_image_path = g_build_filename(current_dir, "RED.png", NULL);

        GtkWidget *blue_image = gtk_image_new_from_file(blue_image_path);
        GtkWidget *red_image = gtk_image_new_from_file(red_image_path);


        
        // Affectez les images à BLUEPIC et REDPIC
        BLUEPIC = blue_image;
        REDPIC = red_image;
        // Affichez l'image BLUEPIC par défaut
            
        

        g_free(current_dir);
        g_free(blue_image_path);
        g_free(red_image_path);
    
    if ( turn==0 ) {
        int rowia;
        gint colia;
        Move bestMove = getBestMove(board, turn, 'B');

        board[bestMove.row][bestMove.col] = 'B';
        rowia = bestMove.row;
        colia = bestMove.col;

        turn ++;
            
        g_object_set_data(G_OBJECT(button), "row", GINT_TO_POINTER(rowia));
        g_object_set_data(G_OBJECT(button), "col", GINT_TO_POINTER(colia));
        gtk_button_set_image(GTK_BUTTON(cellArray[rowia][colia]), BLUEPIC);
    } else {
        int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "row"));
        int col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "col"));
        // Check if the cell is empty ('O')
        if (board[row][col] == ' ') {
            int rowia;
            gint colia;
            board[row][col] = 'R';

            gtk_button_set_image(GTK_BUTTON(button), REDPIC);


            Move bestMove = getBestMove(board, turn, 'B');

            board[bestMove.row][bestMove.col] = 'B';
            rowia = bestMove.row;
            colia = bestMove.col;

            turn ++;
            
            g_object_set_data(G_OBJECT(button), "row", GINT_TO_POINTER(rowia));
            g_object_set_data(G_OBJECT(button), "col", GINT_TO_POINTER(colia));
            gtk_button_set_image(GTK_BUTTON(cellArray[rowia][colia]), BLUEPIC);



            for(int i=0;i<2;i++) {
                if (CheckVictory(player_turn, board)) {
                    gchar *message = g_strdup_printf("Victory player %c", player_turn);

                    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                                            GTK_MESSAGE_INFO,
                                                            GTK_BUTTONS_OK,
                                                            "%s", message);

                    g_signal_connect(dialog, "response", G_CALLBACK(on_dialog_response), NULL);
                    gtk_widget_show_all(dialog);
                    g_free(message);break;
                }
                // Toggle the player's turn for the next move
                player_turn = (player_turn == 'R') ? 'B' : 'R';
            }
            


        }
    }
    
}


void on_cell_clicked_2_ia(GtkButton *button, gpointer user_data) {

    GtkWidget ***cellArray = (GtkWidget ***)user_data;


        GError *error = NULL;
        GtkWidget *BLUEPIC = NULL;
        GtkWidget *REDPIC = NULL;
        char *current_dir = g_get_current_dir();
        char *blue_image_path = g_build_filename(current_dir, "BLUE.png", NULL);
        char *red_image_path = g_build_filename(current_dir, "RED.png", NULL);

        GtkWidget *blue_image = gtk_image_new_from_file(blue_image_path);
        GtkWidget *red_image = gtk_image_new_from_file(red_image_path);


        
        // Affectez les images à BLUEPIC et REDPIC
        BLUEPIC = blue_image;
        REDPIC = red_image;
        // Affichez l'image BLUEPIC par défaut
            
        

        g_free(current_dir);
        g_free(blue_image_path);
        g_free(red_image_path);

    int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "row"));
    int col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "col"));

    // Check if the cell is empty ('O')
    if (board[row][col] == ' ') {
        int rowia;
        gint colia;
        //gchar *label_text = NULL;
        //gchar *label_text_ia = NULL;

        board[row][col] = 'B';
        //label_text = "B";

        gtk_button_set_image(GTK_BUTTON(button), BLUEPIC);


        Move bestMove = getBestMove(board, turn, 'R');

        board[bestMove.row][bestMove.col] = 'R';
        rowia = bestMove.row;
        colia = bestMove.col;
        g_print("\n%d %d %d %d\n", row, rowia,col,colia);
        //label_text_ia = "R";

        turn ++;
        
        g_object_set_data(G_OBJECT(button), "row", GINT_TO_POINTER(rowia));
        g_object_set_data(G_OBJECT(button), "col", GINT_TO_POINTER(colia));
        int row2 = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "row"));
        int col2 = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "col"));
        g_print("%d %d\n", row2, col2);
        gtk_button_set_image(GTK_BUTTON(cellArray[rowia][colia]), REDPIC);



        for(int i=0;i<2;i++) {
            if (CheckVictory(player_turn, board)) {
                gchar *message = g_strdup_printf("Victory player %c", player_turn);

                GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                                        GTK_MESSAGE_INFO,
                                                        GTK_BUTTONS_OK,
                                                        "%s", message);

                g_signal_connect(dialog, "response", G_CALLBACK(on_dialog_response), NULL);
                gtk_widget_show_all(dialog);
                g_free(message);break;
            }
            // Toggle the player's turn for the next move
            player_turn = (player_turn == 'R') ? 'B' : 'R';
        }
        


    }
    
}

/**
 * @brief Callback function when a button is clicked.
 *
 * Handles button click events for "AI," "Network," and "Quit" buttons.
 *
 * @param widget The clicked widget.
 * @param data The button label data.
 */
void on_button_clicked(GtkWidget *widget, gpointer data) {
    char *button_label = (char *)data;
    g_print("Button clicked: %s\n", (char *)data);
    
    if ( strcmp(button_label, "AI") == 0 ) {
        create_game_interface_ia();
    } else if ( strcmp(button_label, "Network") == 0 ) {
        //interfaceReseauConfig();
    } else if ( strcmp(button_label, "Local") == 0 ) {
        create_game_interface();
    } else if ( strcmp(button_label, "Aivsai") == 0 ) {
        create_game_interface_iaVSia();
    } else {
        gtk_main_quit();
    }
}

/**
 * @brief Callback function when the Quit button is clicked.
 *
 * Handles the Quit button click event, creating a confirmation page.
 *
 * @param widget The clicked widget.
 * @param data User data (not used here).
 */
void on_quit_button_clicked(GtkWidget *widget, gpointer data) {
    // Rendre la fenêtre actuelle invisible
    GtkWidget *window = GTK_WIDGET(data);
    gtk_widget_hide(window);
    create_page_exit();
}


/**
 * @brief Callback function when the "Quitter" button is clicked on the exit confirmation page.
 *
 * Exits the application when the "Quitter" button is clicked.
 *
 * @param widget The clicked widget.
 * @param data User data (not used here).
 */
void on_button_quitter_clicked(GtkWidget *widget, gpointer data) {
    gtk_main_quit();

}

/**
 * @brief Callback function when the main window is closed.
 *
 * Handles the window close event and quits the application.
 *
 * @param widget The main window.
 * @param event The GdkEvent.
 * @param user_data User data (not used here).
 * @return Always returns FALSE to propagate the event.
 */
gboolean on_window_closed(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
    gtk_main_quit();
    return TRUE;
}

/**
 * @brief Callback function when the "Rester" button is clicked on the exit confirmation page.
 *
 * Exits the application when the "Rester" button is clicked.
 *
 * @param widget The clicked widget.
 * @param data User data (not used here).
 */
void on_button_rester_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window = GTK_WIDGET(data);
    gtk_widget_hide(window);
    create_page_accueil();
}

/**
 * @brief Creates and displays the exit confirmation page.
 *
 * Initializes the GTK interface for the exit confirmation page.
 */
void create_page_exit() {
    // Initialize GTK
    gtk_init(NULL, NULL);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Confirmation de sortie");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Connect the window close event to gtk_main_quit
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
                                    "window { background-color: #f0f0f0; }\n"
                                    "label { font-size: 18pt; color: #333; }\n"
                                    ".emoji-label { font-size: 120pt; }\n"
                                    ".button { min-width: 150px; padding: 15px 30px; font-size: 18pt; border: 2px solid #007BFF; color: #007BFF; border-radius: 15px; margin-top: 50px; }\n"
                                    ".button:hover { background-color: #007BFF; color: white; }\n"
                                    ".button-box { margin-top: 40px; margin-bottom: 40px; }\n"
                                    ".bordered-label { border: 3px solid #555; padding: 20px; color: #555; border-radius: 20px; background-color: #f9f9f9; }\n"
                                    ".custom-label { font-size: 24pt; font-weight: bold; color: #FF5733; margin-bottom: 20px; }\n",
                                    -1, NULL);

    GdkScreen *screen = gtk_window_get_screen(GTK_WINDOW(window));
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    GtkWidget *label = gtk_label_new(NULL);
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_scale_new(3.0);
    pango_attr_list_insert(attr_list, attr);
    gtk_label_set_label(GTK_LABEL(label), "😢\n");
    gtk_label_set_attributes(GTK_LABEL(label), attr_list);
    pango_attr_list_unref(attr_list);
    gtk_widget_set_name(label, "emoji-label");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);

    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(button_box), TRUE);

    GtkWidget *button_rester = gtk_button_new_with_label("Rester");
    GtkWidget *button_quitter = gtk_button_new_with_label("Quitter");
    gtk_widget_set_name(button_rester, "button");
    gtk_widget_set_name(button_quitter, "button");

    gtk_box_pack_start(GTK_BOX(button_box), button_rester, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(button_box), button_quitter, TRUE, TRUE, 0);

    GtkWidget *text_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *label_text = gtk_label_new("Do you really want to leave?\n");
    gtk_widget_set_name(label_text, "custom-label");
    gtk_box_pack_start(GTK_BOX(text_box), label_text, TRUE, TRUE, 10);
    gtk_widget_set_name(text_box, "bordered-label");
    gtk_grid_attach(GTK_GRID(grid), text_box, 0, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), button_box, 0, 2, 2, 1);

    g_signal_connect(button_quitter, "clicked", G_CALLBACK(on_button_quitter_clicked), NULL);
    g_signal_connect(button_rester, "clicked", G_CALLBACK(on_button_rester_clicked), window);

    gtk_widget_show_all(window);

    g_object_unref(provider);
}

/**
 * @brief Creates and displays the welcome page of the application.
 *
 * Initializes the GTK interface for the welcome page, including labels and buttons
 * for choosing game modes and starting the game.
 */
void create_page_accueil() {
    // Initialize GTK
    gtk_init(NULL, NULL);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Game Interface");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Connect the window close event to gtk_main_quit
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Center the window on the screen
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Create a CSS provider and load custom styling
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider,
                                    "button.custom-button {\n"
                                    "    font-size: 16px;\n"
                                    "    background-color: #007acc;\n"
                                    "    color: white;\n"
                                    "    min-width: 100px;\n"
                                    "    min-height: 30px;\n"
                                    "}\n"
                                    "button.custom-button:hover {\n"
                                    "    background-color: #0055aa;\n"
                                    "}\n"
                                    "#welcome-label { font-size: 24px; font-weight: bold; color: #FF5733; margin-bottom: 10px; }\n",
                                    -1, NULL);

    // Apply CSS provider to the default screen
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Create a vertical box as the main container
    GtkWidget *main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), main_vbox);
    gtk_widget_set_valign(main_vbox, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(main_vbox, GTK_ALIGN_CENTER);

    // Create a label widget
    GtkWidget *label = gtk_label_new("Welcome to the Game\n\n");
    gtk_widget_set_name(label, "welcome-label"); // Apply CSS class to the label
    gtk_box_pack_start(GTK_BOX(main_vbox), label, FALSE, FALSE, 0);

    // Create a horizontal box to hold the buttons
    GtkWidget *hbox_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(main_vbox), hbox_buttons, FALSE, FALSE, 0);

    // Create buttons for choosing to play with AI or network
    GtkWidget *button_ai = gtk_button_new_with_label("Play with AI");
    GtkWidget *button_local = gtk_button_new_with_label("Play with Human");
    GtkWidget *button_network = gtk_button_new_with_label("Play on network");
    GtkWidget *button_aivsai = gtk_button_new_with_label("AI vs AI");
    GtkWidget *button_quit = gtk_button_new_with_label("Quit");

    // Apply CSS class to the buttons
    gtk_widget_set_name(button_ai, "custom-button");
    gtk_widget_set_name(button_network, "custom-button");
    gtk_widget_set_name(button_local, "custom-button");
    gtk_widget_set_name(button_aivsai, "custom-button");
    gtk_widget_set_name(button_quit, "custom-button");

    // Connect button signals
    g_signal_connect(button_ai, "clicked", G_CALLBACK(on_button_clicked), "AI");
    g_signal_connect(button_network, "clicked", G_CALLBACK(on_button_clicked), "Network");
    g_signal_connect(button_quit, "clicked", G_CALLBACK(on_quit_button_clicked), window);
    g_signal_connect(button_local, "clicked", G_CALLBACK(on_button_clicked), "Local");
    g_signal_connect(button_aivsai, "clicked", G_CALLBACK(on_button_clicked), "Aivsai");

    // Pack buttons into the horizontal box
    gtk_box_pack_start(GTK_BOX(hbox_buttons), button_ai, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), button_network, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), button_local, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), button_aivsai, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), button_quit, FALSE, FALSE, 0);

    gtk_widget_show_all(window);

    g_object_unref(css_provider);
}

/* *
 * @brief Creates and displays the game interface.
 *
 * Initializes the GTK interface for the game board.
 */
void create_game_interface() {
    gtk_init(NULL, NULL);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hex Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(on_window_closed), NULL);

    GtkWidget *game_area = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), game_area);

    // Add labels for column numbering
    for (gint i = 0; i < SIZE; i++) {
        gchar *column_label_text = g_strdup_printf("\n%c\n", 'A' + i);
        GtkWidget *column_label = gtk_label_new(column_label_text);
        gtk_widget_set_halign(column_label, GTK_ALIGN_CENTER);
        gtk_grid_attach(GTK_GRID(game_area), column_label, i + 1, 0, 1, 1);
        g_free(column_label_text);
    }

    // Add labels for row numbering
    for (gint i = 0; i < SIZE; i++) {
        gchar *row_label_text = g_strdup_printf("\t%d\t", i + 1);
        GtkWidget *row_label = gtk_label_new(row_label_text);
        gtk_widget_set_valign(row_label, GTK_ALIGN_CENTER);
        gtk_grid_attach(GTK_GRID(game_area), row_label, 0, i + 1, 1, 1);
        g_free(row_label_text);
    }

    // Création du tableau de cellules
    GtkWidget ***cellArray = (GtkWidget ***)malloc(SIZE * sizeof(GtkWidget**));
    for (int i = 0; i < SIZE; i++) {
        cellArray[i] = (GtkWidget **)malloc(SIZE * sizeof(GtkWidget *));
        for (int j = 0; j < SIZE; j++) {
            cellArray[i][j] = gtk_button_new();

            // Set initial label text to the character in the cell
            gchar *label_text = g_strdup_printf("%c", board[i][j]);
            GtkWidget *label = gtk_label_new(label_text);
            g_free(label_text);
            gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
            gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
            gtk_container_add(GTK_CONTAINER(cellArray[i][j]), label);

            // Connecter le signal clicked à la fonction de clic
            g_signal_connect(G_OBJECT(cellArray[i][j]), "clicked", G_CALLBACK(on_cell_clicked_2_player), cellArray);

            // Garder les coordonnées de la cellule dans les données de l'objet
            g_object_set_data(G_OBJECT(cellArray[i][j]), "row", GINT_TO_POINTER(i));
            g_object_set_data(G_OBJECT(cellArray[i][j]), "col", GINT_TO_POINTER(j));

            // Attacher la cellule au conteneur grid
            gtk_grid_attach(GTK_GRID(game_area), cellArray[i][j], j + 1, i + 1, 1, 1);
        }
    }

    turn = 0;
    gtk_widget_show_all(window);
}


/**
 * @brief Creates the game interface for AI vs. AI mode.
 *
 * Initializes the GTK user interface, including the game board and labels for column and row numbering.
 * Connects the clicked event of game cells to the on_cell_clicked_2_iavsia function.
 */
void create_game_interface_iaVSia() {
    gtk_init(NULL, NULL);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hex Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(on_window_closed), NULL);

    GtkWidget *game_area = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), game_area);

    // Add labels for column numbering
    for (gint i = 0; i < SIZE; i++) {
        gchar *column_label_text = g_strdup_printf("\n%c\n", 'A' + i);
        GtkWidget *column_label = gtk_label_new(column_label_text);
        gtk_widget_set_halign(column_label, GTK_ALIGN_CENTER);
        gtk_grid_attach(GTK_GRID(game_area), column_label, i + 1, 0, 1, 1);
        g_free(column_label_text);
    }

    // Add labels for row numbering
    for (gint i = 0; i < SIZE; i++) {
        gchar *row_label_text = g_strdup_printf("\t%d\t", i + 1);
        GtkWidget *row_label = gtk_label_new(row_label_text);
        gtk_widget_set_valign(row_label, GTK_ALIGN_CENTER);
        gtk_grid_attach(GTK_GRID(game_area), row_label, 0, i + 1, 1, 1);
        g_free(row_label_text);
    }

    // Création du tableau de cellules
    GtkWidget ***cellArray = (GtkWidget ***)malloc(SIZE * sizeof(GtkWidget**));
    for (int i = 0; i < SIZE; i++) {
        cellArray[i] = (GtkWidget **)malloc(SIZE * sizeof(GtkWidget *));
        for (int j = 0; j < SIZE; j++) {
            cellArray[i][j] = gtk_button_new();

            // Set initial label text to the character in the cell
            gchar *label_text = g_strdup_printf("%c", board[i][j]);
            GtkWidget *label = gtk_label_new(label_text);
            g_free(label_text);
            gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
            gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
            gtk_container_add(GTK_CONTAINER(cellArray[i][j]), label);

            // Connecter le signal clicked à la fonction de clic
            g_signal_connect(G_OBJECT(cellArray[i][j]), "clicked", G_CALLBACK(on_cell_clicked_2_iavsia), cellArray);

            // Garder les coordonnées de la cellule dans les données de l'objet
            g_object_set_data(G_OBJECT(cellArray[i][j]), "row", GINT_TO_POINTER(i));
            g_object_set_data(G_OBJECT(cellArray[i][j]), "col", GINT_TO_POINTER(j));

            // Attacher la cellule au conteneur grid
            gtk_grid_attach(GTK_GRID(game_area), cellArray[i][j], j + 1, i + 1, 1, 1);
        }
    }

    turn = 0;
    gtk_widget_show_all(window);
}

/**
 * @brief Creates the game interface for player vs. AI mode.
 *
 * Initializes the GTK user interface, including the game board and labels for column and row numbering.
 * Prompts the player to choose a color (Blue or Red) and sets the player's color accordingly.
 * Connects the clicked event of game cells to the on_cell_clicked_2_ia function.
 */
void create_game_interface_ia() {
    turn = 0;
    gtk_init(NULL, NULL);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Display a dialog to choose the color
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Choisir une couleur",
                             GTK_WINDOW(window),
                             GTK_DIALOG_MODAL,
                             "Blue", GTK_RESPONSE_ACCEPT,
                             "Red", GTK_RESPONSE_REJECT,
                             NULL);

    // Get the vbox of the dialog
    GtkWidget *vbox = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Add a label to guide the player
    GtkWidget *label = gtk_label_new("Choisissez votre couleur :");
    gtk_widget_set_margin_top(label, 10);
    gtk_widget_set_margin_bottom(label, 10);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_widget_show(label);

    // Display the dialog and wait for the player's response
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    // Depending on the response, set the player's color
    if (result == GTK_RESPONSE_ACCEPT) {
        player_choice = 'B'; // Blue
    } else if (result == GTK_RESPONSE_REJECT) {
        player_choice = 'R'; // Red
    }

    // Close the dialog
    gtk_widget_destroy(dialog);


    gtk_window_set_title(GTK_WINDOW(window), "Hex Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(on_window_closed), NULL);
    GtkWidget *game_area = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), game_area);

    // Add labels for column numbering
    for (gint i = 0; i < SIZE; i++) {
        gchar *column_label_text = g_strdup_printf("\n%c\n", 'A' + i);
        GtkWidget *column_label = gtk_label_new(column_label_text);
        gtk_widget_set_halign(column_label, GTK_ALIGN_CENTER);
        gtk_grid_attach(GTK_GRID(game_area), column_label, i + 1, 0, 1, 1);
        g_free(column_label_text);
    }

    // Add labels for row numbering
    for (gint i = 0; i < SIZE; i++) {
        gchar *row_label_text = g_strdup_printf("\t%d\t", i + 1);
        GtkWidget *row_label = gtk_label_new(row_label_text);
        gtk_widget_set_valign(row_label, GTK_ALIGN_CENTER);
        gtk_grid_attach(GTK_GRID(game_area), row_label, 0, i + 1, 1, 1);
        g_free(row_label_text);
    }


    if (player_choice == 'B') {

        // Création du tableau de cellules
        GtkWidget ***cellArray = (GtkWidget ***)malloc(SIZE * sizeof(GtkWidget**));
        for (int i = 0; i < SIZE; i++) {
            cellArray[i] = (GtkWidget **)malloc(SIZE * sizeof(GtkWidget *));
            for (int j = 0; j < SIZE; j++) {
                cellArray[i][j] = gtk_button_new();

                // Set initial label text to the character in the cell
                gchar *label_text = g_strdup_printf("%c", board[i][j]);
                GtkWidget *label = gtk_label_new(label_text);
                g_free(label_text);
                gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
                gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
                gtk_container_add(GTK_CONTAINER(cellArray[i][j]), label);

                // Connecter le signal clicked à la fonction de clic
                g_signal_connect(G_OBJECT(cellArray[i][j]), "clicked", G_CALLBACK(on_cell_clicked_2_ia), cellArray);

                // Garder les coordonnées de la cellule dans les données de l'objet
                g_object_set_data(G_OBJECT(cellArray[i][j]), "row", GINT_TO_POINTER(i));
                g_object_set_data(G_OBJECT(cellArray[i][j]), "col", GINT_TO_POINTER(j));

                // Attacher la cellule au conteneur grid
                gtk_grid_attach(GTK_GRID(game_area), cellArray[i][j], j + 1, i + 1, 1, 1);
            }
        }

    } else if ( player_choice == 'R' ) {
        // Création du tableau de cellules
        GtkWidget ***cellArray = (GtkWidget ***)malloc(SIZE * sizeof(GtkWidget**));
        for (int i = 0; i < SIZE; i++) {
            cellArray[i] = (GtkWidget **)malloc(SIZE * sizeof(GtkWidget *));
            for (int j = 0; j < SIZE; j++) {
                cellArray[i][j] = gtk_button_new();

                // Set initial label text to the character in the cell
                gchar *label_text = g_strdup_printf("%c", board[i][j]);
                GtkWidget *label = gtk_label_new(label_text);
                g_free(label_text);
                gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
                gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
                gtk_container_add(GTK_CONTAINER(cellArray[i][j]), label);

                // Connecter le signal clicked à la fonction de clic
                g_signal_connect(G_OBJECT(cellArray[i][j]), "clicked", G_CALLBACK(on_cell_clicked_1_ia), cellArray);

                // Garder les coordonnées de la cellule dans les données de l'objet
                g_object_set_data(G_OBJECT(cellArray[i][j]), "row", GINT_TO_POINTER(i));
                g_object_set_data(G_OBJECT(cellArray[i][j]), "col", GINT_TO_POINTER(j));

                // Attacher la cellule au conteneur grid
                gtk_grid_attach(GTK_GRID(game_area), cellArray[i][j], j + 1, i + 1, 1, 1);
            }
        }
        on_cell_clicked_1_ia(GTK_BUTTON(NULL), cellArray);

    }
    gtk_widget_show_all(window);

}
//////////////////////////////////////////////////////////////////////////////////////////////////

/*
// La fonction d'envoi et du reçois des données via les sockets (User vs User)
void connexionServer(int connfd)
{
        int *i,*j;
        
        i = (int*)malloc(sizeof(int));
	j = (int*)malloc(sizeof(int));
	
	char buff[3];
          
	// infinite loop for chat
	for (;;) {
	
		bzero(buff, 3);
		
		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));
		(*i) = buff[0] - '0';
		(*j) = buff[1] - '0';
		
		// print buffer which contains the client contents
		printf("( i , j ) = ( %d , %d ) \n", *i, *j);
		bzero(buff, 3);
		
		// La position i,j à envoyer
                printf("Saisir le couple (i,j) a envoyer : ");
                scanf("%d%d",i,j);
                
		buff[0] = (*i) + '0';
		buff[1] = (*j) + '0';

		// and send that buffer to client
		write(connfd, buff, sizeof(buff));

		// if msg contains "Exit" then server exit and chat ended.
		if ( *i == -1 || *j == -1) {
			printf("Server Exit...\n");
			return;
		
		}
	}
}



void serverVsClient()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// La communication entre le Joueur 1 et le Joueur 2
	connexionServer(connfd);

	// Fermer la socket
	close(sockfd);
	
	return;
}

void connexionClient(int sockfd)
{
    int *i,*j;
    i = (int*) malloc (sizeof(int));
    j = (int*) malloc (sizeof(int));
    char buff[20];
    
    for (;;) {
        bzero(buff, sizeof(buff));
        
        printf("Saisir (i,j) : ");
        scanf("%d%d",i,j);  
	buff[0] = (*i) + '0';
	buff[1] = (*j) + '0';        
        write(sockfd, buff, sizeof(buff));
        
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
	(*i) = buff[0] - '0';
	(*j) = buff[1] - '0';        
        printf("La couple ( i , j ) = ( %d , %d )", *i, *j);
        
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}
 
void clientVsServer()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
 
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ipAd);
    servaddr.sin_port = htons(PORT);
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
 
    // function for chat
    connexionClient(sockfd);
 
    // close the socket
    close(sockfd);
}

*/

/*

///////////////////////////////////

/**
 * @brief Handles the click event of the "Play" button.
 *
 * Retrieves the text entered in the text field, displays the entered IP address in the console,
 * and triggers either serverVsClient() or clientVsServer() based on the selected options.
 *
 * @param widget The clicked widget (not used here).
 * @param data User data (not used here).
 */
static void on_play_button_clicked(GtkWidget *widget, gpointer data) {
    // Obtenez le texte saisi dans le champ de texte
    const gchar *ip_address = gtk_entry_get_text(GTK_ENTRY(ipTextField));
    ipAd = (char *)ip_address;
    
    // Affichez l'adresse IP dans la console
    printf("Adresse IP saisie : %s\n", ip_address);
    
    //if(buttonServer&&buttonPlayer)
      //serverVsClient();
      
    //else if(buttonClient&&buttonPlayer)
      //clientVsServer();
      
    
    // Vous pouvez également l'afficher dans une autre partie de l'interface utilisateur
    // par exemple, en utilisant une étiquette (GtkLabel) pour l'afficher.
}

// Fonction appelée lorsqu'un CheckBox est activé/désactivé
/**
 * @brief Handles the toggled event of a CheckBox.
 *
 * Updates the state of various CheckBoxes and prints messages in the console based on the
 * CheckBoxes' states.
 *
 * @param widget The toggled CheckBox widget.
 * @param data User data (not used here).
 */
static void on_checkbox_toggled(GtkWidget *widget, gpointer data) {

    buttonClient = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(serverClientCheckboxClient));
    buttonServer = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(serverClientCheckboxServer));
    buttonPlayer = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(playerCheckboxPlayer));
    buttonIA = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(playerCheckboxIA));
    
    // Vous pouvez ajouter ici le code pour gérer l'état du CheckBox
      if (buttonClient) {
        g_print("La case Client est cochée.\n");
        // Vous pouvez ajouter du code pour réagir lorsque la case est cochée.
    } if(buttonServer) {
        g_print("La case Server est cochée.\n");
        // Vous pouvez ajouter du code pour réagir lorsque la case est décochée.
    } if(buttonPlayer) {
        g_print("La case Player est cochée.\n");
        // Vous pouvez ajouter du code pour réagir lorsque la case est décochée.
    } if(buttonIA) {
        g_print("La case IA est cochée.\n");
        // Vous pouvez ajouter du code pour réagir lorsque la case est décochée.
    }
}


// Fonction appelée lorsqu'un bouton "Exit" est cliqué
/**
 * @brief Handles the click event of the "Exit" button.
 *
 * Exits the GTK main loop, effectively closing the application.
 *
 * @param widget The clicked "Exit" button widget (not used here).
 * @param data User data (not used here).
 */
static void on_exit_button_clicked(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

/**
 * @brief Initializes the network configuration interface.
 *
 * Initializes the GTK interface for configuring network play, including CheckBoxes for
 * server/client and player/IA selection, IP address input field, and "Play" and "Exit" buttons.
 */
/*
void interfaceReseauConfig() {

    gtk_init(NULL,NULL);

    // Création de la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Application GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Création de la boîte principale
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    // CheckBox pour Server/Client
    GtkWidget *serverClientLabel = gtk_label_new("Server/Client : ");
    serverClientCheckboxServer = gtk_check_button_new_with_label("Server");
    serverClientCheckboxClient = gtk_check_button_new_with_label("Client");
    g_signal_connect(serverClientCheckboxServer, "toggled", G_CALLBACK(on_checkbox_toggled), NULL);
    g_signal_connect(serverClientCheckboxClient, "toggled", G_CALLBACK(on_checkbox_toggled), NULL);
    gtk_box_pack_start(GTK_BOX(box), serverClientLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), serverClientCheckboxServer, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), serverClientCheckboxClient, FALSE, FALSE, 0);

    // TextField pour saisir l'IP
    GtkWidget *ipLabel = gtk_label_new("Saisir l'IP : ");
    ipTextField = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), ipLabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), ipTextField, FALSE, FALSE, 0);
    

    // CheckBox pour Player/IA
    GtkWidget *playerIALabel = gtk_label_new("Player/IA : ");
    playerCheckboxPlayer = gtk_check_button_new_with_label("Player");
    playerCheckboxIA = gtk_check_button_new_with_label("IA");
    g_signal_connect(playerCheckboxPlayer, "toggled", G_CALLBACK(on_checkbox_toggled), NULL);
    g_signal_connect(playerCheckboxIA, "toggled", G_CALLBACK(on_checkbox_toggled), NULL);
    gtk_box_pack_start(GTK_BOX(box), playerIALabel, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), playerCheckboxPlayer, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), playerCheckboxIA, FALSE, FALSE, 0);

    // Bouton "Jouer"
    GtkWidget *playButton = gtk_button_new_with_label("Jouer");
    g_signal_connect(playButton, "clicked", G_CALLBACK(on_play_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(box), playButton, FALSE, FALSE, 0);

    // Bouton Exit
    GtkWidget *exitButton = gtk_button_new_with_label("Exit");
    g_signal_connect(exitButton, "clicked", G_CALLBACK(on_exit_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(box), exitButton, FALSE, FALSE, 0);

    // Afficher tous les éléments
    gtk_widget_show_all(window);

}



//

/**
 * @brief Main entry point for the program, displaying the main interface.
 *
 * Initializes GTK, creates the main window, and displays the main user interface.
 */
void interfPrinc() {
    gtk_init(NULL,NULL);
    create_page_accueil();
    gtk_main();
    return;
}

