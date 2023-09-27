#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.c"

int main(){ 
    srand((unsigned)time(NULL)); 

    TABLERO *game; 
    LABERINTO *cartas = (LABERINTO*)malloc(9*sizeof(LABERINTO));
    cartas[0] = crear_laberintos("Inicio.txt",0);
    char nombre[15];
    for(int i = 1; i<9;i++){ 
        snprintf(nombre,sizeof(nombre),"tablero%d.txt",i);
        cartas[i] = crear_laberintos(nombre,i);
    } 
    game = iniciar_tablero(cartas);
    
    int p ;
    for(int i = 1; i < 9;i++){
        p = randomize(game,cartas,i);
    }
    for(int j = 1;j<9;j++){ 
    for(int i  = 0 ; i <5;i++){ 
        printf("%s\n",cartas[j].maze[i]); 
    }
    printf("----\n");     
    } 
    return 0;   
}        
                  