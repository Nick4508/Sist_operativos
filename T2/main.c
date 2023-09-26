#include <stdio.h>
#include <stdlib.h>
#include "funciones.c"

int main(){ 
    TABLERO *game; 
     
     
    game = iniciar_tablero();
    mostrar_tablero(game); 
      
    // for(int j = 0;j<9;j++){
    // for(int i  = 0 ; i <5;i++){
    //     printf("%s\n",cartas[j].maze[i]); 
    // }
    // printf("----\n");
    // }
    return 0;   
}        
                 