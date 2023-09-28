/**
 * @file main.c
 * @brief Hex Game Main File
 * @author Group 5
 * @date 2023-09-22
 */

#include "IA.h"
#include "interface.h"
#include "network.h"
/**
 * @mainpage Hex Game Documentation
 * @brief Documentation for the Hex Game Project of Group 5
 *
 * This is the main documentation page for the Hex Game project.
 * It provides an overview of the project's structure and modules.
 */

/**
 * @brief Entry point of the Hex Game.
 *
 * This function allows the user to choose between different game modes and starts the game accordingly.
 * 
 * @return 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[]){
    if(argc == 2 || argc ==4 && strcmp(argv[1],"-t") == 0){
    printf("Choose : \n 1 player vs player \n 2 player vs computer \n 3 computer vs computer \n 4 serveur \n 5 serveur ia \n");
    int choice;
    scanf("%d",&choice);    
    if (choice==1){ playervplayer();
}

    else if (choice==2){
        char color;
        if (strcmp(argv[2],"-l") == 0 && strcmp(argv[3],"bleu") == 0){color = BLUE;} else {color = RED;}
        playervcomputer(color);
}

    else if (choice==3){
        computervcomputer();
   


}
    else if (choice==4){
        initialization();
        char adrr[] = "";
        if (strcmp(argv[2],"-s") == 0){PORT = atoi(argv[3]); menu(PORT, adrr);}
        printf("test");
        if (strcmp(argv[2],"-c") == 0){
        
        size_t length = strlen(argv[3]);
        
        char newStr[128]; 
        

        if (length >= 5) {
        for (int i = 0; i < length - 5; i++) {
            newStr[i] = argv[3][i];
        }
        }
        printf("newStr: %s\n", newStr);
        char por[4];
        por[0] = argv[3][length-4];
        por[1] = argv[3][length-3];
        por[2] = argv[3][length-2];
        por[3] = argv[3][length-1];
        PORT = atoi(por);
         menu(PORT, newStr);
        }
       

}
    else if (choice==5){
        initialization();
        char adrr[] = "";
        if (strcmp(argv[2],"-s") == 0){PORT = atoi(argv[3]); menuia(PORT, adrr);}
        printf("test");
        if (strcmp(argv[2],"-c") == 0){
        
        size_t length = strlen(argv[3]);
        
        char newStr[128]; 
        

        if (length >= 5) {
        for (int i = 0; i < length - 5; i++) {
            newStr[i] = argv[3][i];
        }
        }
        printf("newStr: %s\n", newStr);
        char por[4];
        por[0] = argv[3][length-4];
        por[1] = argv[3][length-3];
        por[2] = argv[3][length-2];
        por[3] = argv[3][length-1];
        PORT = atoi(por);
        menuia(PORT, newStr);
        }


}
}
    else{
    initialization();
    gtk_init(NULL,NULL);
    create_page_accueil();
    gtk_main();
    }
    
    




return 0;



}
