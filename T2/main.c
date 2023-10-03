#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.c"
#include <unistd.h>
#include <sys/wait.h>

void jugador(int jugador_id, TABLERO *game, LABERINTO *cartas, int pipe_fd[3][2]) {
    // Lógica del jugador

    char movimiento = 'N'; // Movimiento del jugador (cambiar según sea necesario)

    if (jugador_id == 1) {
        // Jugador 1 envía instrucciones a través de tuberías a los otros jugadores
        char instruccion[20];
        snprintf(instruccion, sizeof(instruccion), "Moverte al Norte"); // Ejemplo de instrucción
        for (int i = 0; i < 3; i++) {
            write(pipe_fd[i][1], instruccion, sizeof(instruccion));
        }
    } else {
        // Jugadores 2, 3 y 4 reciben instrucciones a través de tuberías del Jugador 1
        char instruccion_recibida[20];
        read(pipe_fd[jugador_id - 2][0], instruccion_recibida, sizeof(instruccion_recibida));
        printf("El Jugador %d recibió la instrucción: %s\n", jugador_id, instruccion_recibida);
    }

    // Bucle para que todos los jugadores realicen turnos
    for (int turno = 0; turno < 5; turno++) {
        // Lógica del jugador para decidir el movimiento o uso de cartas
        // Ejemplo:
        if (movimiento == 'N') {
            printf("El jugador %d se mueve hacia el Norte.\n", jugador_id);
            // Llama a la función para mover al jugador hacia el Norte en el tablero
            // Por ejemplo, puedes llamar a una función como move_player(game, jugador_id, 'N')
        } else if (movimiento == 'S') {
            printf("El jugador %d se mueve hacia el Sur.\n", jugador_id);
            
        } else if (movimiento == 'E') {
            printf("El jugador %d se mueve hacia el Este.\n", jugador_id);
        } else if (movimiento == 'O') {
            printf("El jugador %d se mueve hacia el Oeste.\n", jugador_id);
        } else {
            printf("El jugador %d utiliza una carta especial.\n", jugador_id);
        }

        // Cambia el movimiento para el siguiente turno (puedes implementar tu lógica aquí)
        movimiento = 'N'; // Cambiar esto según la lógica del juego
    }
}

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


        int pipe_fd[3][2];
    for (int i = 0; i < 3; i++) {
        if (pipe(pipe_fd[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    // Crear procesos hijos para representar a los jugadores
    for (int jugador_id = 1; jugador_id <= 4; jugador_id++) {
        pid_t pid = fork();

        if (pid == 0) { // Proceso hijo
            jugador(jugador_id, game, cartas, pipe_fd); // Llamar a la función del jugador en el proceso hijo
            exit(0);
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    // Cerrar las tuberías
    for (int i = 0; i < 3; i++) {
        close(pipe_fd[i][0]);
        close(pipe_fd[i][1]);
    }

    // Liberar memoria y realizar otras tareas de limpieza al final del juego

    return 0;
}
                  
