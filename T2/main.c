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
    
    int *random_cards = (int*)malloc(9*sizeof(int)) ; // cartas en el mazo
    int *real_cards = (int*)malloc(9*sizeof(int)) ; // cartas en la mesa
    for(int i = 0; i < 9; i++){random_cards[i] = 0;real_cards[i] = 0;} // setearlas a 0
    randomize_deck(random_cards); // randomizar el mazo de cartas
      
  
    // for(int i = 0; i < 9;i++){
    //     printf("%d-",random_cards[i]); 
    // }printf("\n");
    // printf("a"); 
    int p;
    p  = search(game,cartas,'O',random_cards,real_cards,0); 
    p  = search(game,cartas,'E',random_cards,real_cards,0); 
    printf("%d\n%d\n",real_cards[1],real_cards[2]); 
    for(int i = 0; i < 9;i++){
        printf("%d-",random_cards[i]); 
    }printf("\n");
    return 0;    
}        
                  