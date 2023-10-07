#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.c"
#include <unistd.h>
#include <sys/wait.h>

void mover_jugador(JUGADOR *jugador, char direccion, LABERINTO *laberinto, int cantidad) {
    int nueva_x = jugador->x;
    int nueva_y = jugador->y;

    // Calcular la nueva posición del jugador según la dirección y cantidad
    if (direccion == 'N') {
        nueva_x -= cantidad;
    } else if (direccion == 'S') {
        nueva_x += cantidad;
    } else if (direccion == 'E') {
        nueva_y += cantidad;
    } else if (direccion == 'O') {
        nueva_y -= cantidad;
    }

    // Verificar si la nueva posición es válida
    if (nueva_x >= 0 && nueva_x < 5 && nueva_y >= 0 && nueva_y < 15 &&
        laberinto->maze[nueva_x][nueva_y] != 'B' && laberinto->maze[nueva_x][nueva_y] != '/') {
        // La nueva posición es válida, actualiza la posición del jugador
        jugador->x = nueva_x;
        jugador->y = nueva_y;
    } else {
        // La nueva posición no es válida, el jugador no se mueve
        printf("Movimiento no válido. El jugador permanece en su posición actual.\n");
    }
}

void jugador(int jugador_id, TABLERO *game, LABERINTO *cartas, int pipe_fd[3][2]) {
    char movimiento = 'N'; // 'N', 'S', 'E', 'O' o 'C' (carta especial)
    JUGADOR *jugador = &(game->jugadores[jugador_id - 1]);
    char instruccion[10];
    char orientacion;
    char cantidad;

    if (jugador_id == 1) {
        // Jugador 1 envía instrucciones a través de tuberías a los otros jugadores
        // instrucción tiene que ser del tipo  (Norte, Cantidad 1)
        snprintf(instruccion, sizeof(instruccion), "N 1");
        for (int i = 0; i < 3; i++) {
            write(pipe_fd[i][1], instruccion, sizeof(instruccion));
        }
    } else {
        // Jugadores 2, 3 y 4 reciben instrucciones a través de tuberías del Jugador 1
        read(pipe_fd[jugador_id - 2][0], instruccion, sizeof(instruccion));
        printf("El Jugador %d recibió la instrucción: %s\n", jugador_id, instruccion);

        // Analizar la instrucción recibida
        if (sscanf(instruccion, "%c %c", &orientacion, &cantidad) == 2) {
            if (orientacion == 'N' || orientacion == 'S' || orientacion == 'E' || orientacion == 'O') {
                // La instrucción es un movimiento válido
                printf("El jugador %d se mueve hacia la %c en una cantidad de %d.\n", jugador_id, orientacion, cantidad);
                mover_jugador(jugador, orientacion, cartas, cantidad);
            } else if (orientacion == 'L' || orientacion == 'B') {
                printf("El jugador %d utiliza una carta especial: %c\n", jugador_id, orientacion);
                // Hay que implementar cndo usa ladder o buscar :=)
                if (orientacion == 'L') {
                    // Logica Ladder
                } else if (orientacion == 'B') {
                    // Logica Buscar
                }
            } else {
                // La orientación no es válida
                printf("Orientación no válida: %c\n", orientacion);
            }
        } else {
            // La instrucción no tiene el formato esperado
            printf("Instrucción no válida: %s\n", instruccion);
        }
    }

    // Bucle para que todos los jugadores realicen turnos
    for (int turno = 0; turno < 5; turno++) {
        // Lógica del jugador para decidir el movimiento o uso de cartas
        if (movimiento == 'N') {
            mover_jugador(jugador, 'N', cartas, 1); 
        } else if (movimiento == 'S') {
            mover_jugador(jugador, 'S', cartas, 1); 
        } else if (movimiento == 'E') {
            mover_jugador(jugador, 'E', cartas, 1); 
        } else if (movimiento == 'O') {
            mover_jugador(jugador, 'O', cartas, 1); 
        } else {
            printf("El jugador %d utiliza una carta especial.\n", jugador_id);
        }
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

        if (pid == 0) { 
            jugador(jugador_id, game, cartas, pipe_fd); 
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
                  
