#include <stdio.h>
#include <stdlib.h>
#include "funciones.c"

int main(){ 

    char nombre[20];
    LABERINTO *laberintos = malloc(9*sizeof(LABERINTO));
    laberintos[0] = crear_laberintos("Inicio.txt",0);
    for(int i = 1; i < 9;i++){
        snprintf(nombre,sizeof(nombre),"tablero%d.txt",i);
        laberintos[i] = crear_laberintos(nombre,i);
    }
    cambiar_fichas(laberintos[0].maze); 
          
    return 0;  
}     
               