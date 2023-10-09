#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.c"
#include <unistd.h>
#include <sys/wait.h>

/*
mover_jugador: Esta función se encarga de mover a un jugador en el laberinto en la dirección especificada por un número de casillas.
También verifica si la nueva posición es válida y realiza acciones específicas en función de la casilla en la que se encuentra el jugador.
*/
void mover_jugador(JUGADOR *jugador, char direccion, LABERINTO *laberinto, int cantidad, TABLERO *game,int id_player) {
    int nueva_x = jugador[id_player-1].x;
    int nueva_y = jugador[id_player-1].y;
    int id_laberinto = jugador[id_player-1].laberinto;
    
    int x  = jugador[id_player-1].x,y = jugador[id_player-1].y;
    char ficha_atras = '0';
    if(x == 0 && y == 4){ficha_atras = 'b';}
    if(x == 4 && y == 4){ficha_atras = 'b';}
    if(x == 2 && y == 8){ficha_atras = 'b';}
    if(x == 2 && y == 0){ficha_atras = 'b';}
    // Calcular la nueva posición del jugador según la dirección y cantidad
    if (direccion == 'N') {
        nueva_x -= cantidad;
    } else if (direccion == 'S') {
        nueva_x += cantidad;
    } else if (direccion == 'E') {
        nueva_y += 2*cantidad;
    } else if (direccion == 'O') {
        nueva_y -= 2*cantidad;
    }

    // Verificar si la nueva posición es válida
    if (nueva_x >= 0 && nueva_x < 5 && nueva_y >= 0 && nueva_y < 9  && laberinto[id_laberinto].maze[nueva_x][nueva_y] != '/' && laberinto[id_laberinto].maze[nueva_x][nueva_y] != 'T' && laberinto[id_laberinto].maze[nueva_x][nueva_y] != 'S' && laberinto[id_laberinto].maze[nueva_x][nueva_y] != 'F' && laberinto[id_laberinto].maze[nueva_x][nueva_y] != 'J') {
        // La nueva posición es válida, actualiza la posición del jugador
        laberinto[id_laberinto].maze[jugador[id_player-1].x][jugador[id_player-1].y] = ficha_atras;
        
        jugador[id_player-1].x = nueva_x;
        jugador[id_player-1].y = nueva_y;

        laberinto[id_laberinto].maze[nueva_x][nueva_y] = jugador[id_player-1].letra;
        // Comprobar el contenido de la casilla
        char casilla = laberinto[id_laberinto].maze[nueva_x][nueva_y];
        if (casilla == 'U') {
            game->turnos += 5;
        } else if (casilla == 'L') {
            game->turnos -= 3;
        } else if (casilla == 'G') {
            if(game->cant_tps >= 2){
                //se tepea
            }else{
                printf("No hay suficientes casillas de tp para poder usar esta casilla\n");
            }
        } else if (casilla == 'R') {
            if(game->cant_tps >= 2){
                //se tepea
            }else{
                printf("No hay suficientes casillas de tp para poder usar esta casilla\n");
            }
        } else if (casilla == 'V') {
            if(game->cant_tps >= 2){
                //se tepea
            }else{
                printf("No hay suficientes casillas de tp para poder usar esta casilla\n");
            }
        } else if (casilla == 'Z') {
            if(game->cant_tps >= 2){
                //se tepea
            }else{
                printf("No hay suficientes casillas de tp para poder usar esta casilla\n");
            }
        } else if (casilla == 'C') {
            game->camaras++;
        } else if (casilla >= '1' && casilla <= '4' && (casilla - '0') == jugador[id_player-1].id) {
            // El jugador ha encontrado un tesoro
            printf("El jugador %d ha encontrado un tesoro en la casilla %c.\n", jugador[id_player].id, casilla);
            jugador[id_player].tesoros++; // Sumar 1 al contador de tesoros del jugador
            // Reemplazar la casilla con espacio en blanco para indicar que el tesoro ha sido recogido
            laberinto[id_laberinto].maze[nueva_x][nueva_y] = ficha_atras;
        }
    } else {
        // La nueva posición no es válida, el jugador no se mueve
        printf("Movimiento no válido. El jugador permanece en su posición actual.\n");
    }
}
/*
jugador: Esta función representa a un jugador individual en el juego.
Puede recibir instrucciones de movimiento o acciones especiales a través de tuberías y ejecutar las acciones correspondientes.
*/
void jugador(int jugador_id, TABLERO *game, LABERINTO *cartas, int pipe_fd[3][2],int fd[4][2]) {
    char movimiento = 'N'; // 'N', 'S', 'E', 'O' o 'C' (carta especial)
    JUGADOR *jugador = &(game->jugadores[jugador_id - 1]);
    char instruccion[10];
    char instruccion_1[10];
    char instruccion_2[10];
    char instruccion_3[10];
    char instruccion_4[10];
    int cantidad;

    if (jugador_id == 1) {
        // Jugador 1 genera las instrucciones
        printf("Ingrese la instrucción para el jugador 1: ");
        scanf("%s", instruccion_1);
        printf("Ingrese la instrucción para el jugador 2: ");
        scanf("%s", instruccion_2);
        printf("Ingrese la instrucción para el jugador 3: ");
        scanf("%s", instruccion_3);
        printf("Ingrese la instrucción para el jugador 4: ");
        scanf("%s", instruccion_4);

        write(fd[0][1],instruccion_1,sizeof(instruccion_1));
        write(fd[1][1],instruccion_2,sizeof(instruccion_2));
        write(fd[2][1],instruccion_3,sizeof(instruccion_3));
        write(fd[3][1],instruccion_4,sizeof(instruccion_4));
        write(pipe_fd[0][1],instruccion_2,sizeof(instruccion_3));
        write(pipe_fd[1][1],instruccion_3,sizeof(instruccion_3));
        write(pipe_fd[2][1],instruccion_4,sizeof(instruccion_3));

        // Envia la instrucción al jugador correspondiente
        }
    else {
        // Jugadores 2, 3 y 4 reciben instrucciones a través de tuberías del Jugador 1
        read(pipe_fd[jugador_id - 2][0], instruccion, sizeof(instruccion));
        printf("El Jugador %d recibió la instrucción: %s\n", jugador_id, instruccion);
    }
  
  

}
/*
escalera: Esta función permite a un jugador utilizar una escalera para moverse entre áreas del laberinto.
Dependiendo de la orientación, el jugador se moverá a una nueva ubicación en el laberinto.
*/
void escalera(LABERINTO *cards, JUGADOR *jugadores,int id_player, char orientacion){
    int x = jugadores[id_player-1].x;
    int y = jugadores[id_player-1].y;
    char player;
    if(id_player == 1){player = 'J';}
    if(id_player == 2){player = 'S';}
    if(id_player == 3){player = 'T';}
    if(id_player == 4){player = 'F';}
    char ficha_atras = '0';
    if(x == 0 && y == 4){ficha_atras = 'b';}
    if(x == 4 && y == 4){ficha_atras = 'b';}
    if(x == 2 && y == 8){ficha_atras = 'b';}
    if(x == 2 && y == 0){ficha_atras = 'b';}
    int id_laberinto = jugadores[id_player-1].laberinto;
    int x_escalera,y_escalera;
    if(orientacion == 'N'){ 
        x_escalera = x-1;
        y_escalera = y;
        cards[id_laberinto].maze[x][y] = ficha_atras;
        cards[id_laberinto].maze[x_escalera][y_escalera] = '0';
        cards[id_laberinto].maze[x_escalera-1][y_escalera] = player;

    }
    else if(orientacion == 'S'){
        x_escalera = x+1;
        y_escalera = y;
        if(id_laberinto == 3){
            cards[id_laberinto].maze[x][y] = 'b';
            cards[id_laberinto].maze[x_escalera][y_escalera] = '0';
            cards[id_laberinto].maze[x_escalera+2][y] = player;
            return;
        }
        cards[id_laberinto].maze[x][y] = ficha_atras;
        cards[id_laberinto].maze[x_escalera][y_escalera] = '0';
        cards[id_laberinto].maze[x_escalera+1][y] = player;
    }// especial
    else if(orientacion == 'E'){
        x_escalera = x;
        y_escalera = y+2;
        cards[id_laberinto].maze[x][y] = ficha_atras;
        cards[id_laberinto].maze[x_escalera][y_escalera] = '0';
        cards[id_laberinto].maze[x_escalera][y_escalera+2] = player;

    }
    else if(orientacion == 'O'){
        x_escalera = x;
        y_escalera = y-2;
        if(id_laberinto == 8){
            cards[id_laberinto].maze[x][y] = 'b';
            cards[id_laberinto].maze[x_escalera][y_escalera] = '0';
            cards[id_laberinto].maze[x_escalera][y_escalera-4] = player;
            return;
        }
        cards[id_laberinto].maze[x][y] = ficha_atras;
        cards[id_laberinto].maze[x_escalera][y_escalera] = '0';
        cards[id_laberinto].maze[x_escalera][y_escalera-2] = player;

    }//especial

}
/*
pasar_a_laberinto: Esta función permite a un jugador moverse de un laberinto a otro utilizando una conexión previamente establecida.
*/
void pasar_a_laberinto(TABLERO *game,JUGADOR *jugadores, LABERINTO *cards, char orientacion, int *mazo,int *mesa,int id_player){
    int x = jugadores[id_player-1].x;
    int y = jugadores[id_player-1].y;
    char player;
    if(id_player == 1){player = 'J';}
    if(id_player == 2){player = 'S';}
    if(id_player == 3){player = 'T';}
    if(id_player == 4){player = 'F';}
    int id_origen,id_destino;
    char orientacion_origen,orientacion_destino;
    for(int i = 0; i < game->cant_pares;i++){
        sscanf(game->pares[i],"%d%c%c%d",&id_origen,&orientacion_origen,&orientacion_destino,&id_destino);
        if(id_origen == jugadores[id_player-1].laberinto && orientacion == orientacion_origen){
            if(orientacion == 'N'){
                if(x == 0 && y == 4){
                    jugadores[id_player-1].x = 4;
                    jugadores[id_player-1].y = 4;
                    jugadores[id_player-1].laberinto = id_destino;
                    cards[id_origen].maze[0][4] = 'b';
                    cards[id_destino].maze[4][4] = player;
                }
            }
            else if(orientacion == 'S'){
                if(x == 4 && y == 4){
                    jugadores[id_player-1].x = 0;
                    jugadores[id_player-1].y = 4;
                    jugadores[id_player-1].laberinto = id_destino;
                    cards[id_origen].maze[4][4] = 'b';
                    cards[id_destino].maze[0][4] = player;
                }
            }
            else if(orientacion == 'E'){
                if(x == 2 && y == 8){
                    jugadores[id_player-1].x = 2;
                    jugadores[id_player-1].y = 0;
                    jugadores[id_player-1].laberinto = id_destino;
                    cards[id_origen].maze[2][8] = 'b';
                    cards[id_destino].maze[2][0] = player;
                }
            }
            else if(orientacion == 'O'){
                if(x == 2 && y == 0){
                    jugadores[id_player-1].x = 2;
                    jugadores[id_player-1].y = 8;
                    jugadores[id_player-1].laberinto = id_destino;
                    cards[id_origen].maze[2][0] = 'b';
                    cards[id_destino].maze[2][8] = player;
                }
            }


        }
    }
    
}
/*
buscar: Esta función permite a un jugador realizar una acción de búsqueda en el laberinto para descubrir nuevos laberintos o tesoros.
También maneja situaciones especiales, como moverse de un laberinto a otro a través de una búsqueda.
*/
void buscar(TABLERO *game,JUGADOR *jugadores, LABERINTO *cards, char orientacion, int *mazo,int *mesa,int id_player){
    int p;
    int x = jugadores[id_player-1].x;
    int y = jugadores[id_player-1].y;
    char player;
    if(id_player == 1){player = 'J';}
    if(id_player == 2){player = 'S';}
    if(id_player == 3){player = 'T';}
    if(id_player == 4){player = 'F';}
    if(orientacion == 'N'){
        if(x == 0 && y == 4){
            p = search(game,cards,orientacion,mazo,mesa,jugadores[id_player-1].laberinto);
            if(p!= 0){
                jugadores[id_player-1].laberinto = p;
                jugadores[id_player-1].x = 4;
                jugadores[id_player-1].y = 4;
                cards[p].maze[4][4] = player; 
                randomize(game,cards,p);

                return ;
            }else{
                printf("No se pudo realizar el movimiento\n");
                cards[jugadores[id_player-1].laberinto].maze[0][4] = player;
            }
            
        }
    }
    else if(orientacion == 'S'){
        if(x == 4 && y == 4){
            p = search(game,cards,orientacion,mazo,mesa,jugadores[id_player-1].laberinto);
            if(p!= 0){
                jugadores[id_player-1].laberinto = p;
                cards[p].maze[0][4] = player;
                jugadores[id_player-1].x = 0;
                jugadores[id_player-1].y = 4; 
                randomize(game,cards,p);
                return ;
            }else{
                printf("No se pudo realizar el movimiento\n");
                cards[jugadores[id_player-1].laberinto].maze[4][4] = player;
            }    
        }
    }
    else if(orientacion == 'E'){
        if(x == 2 && y == 8){
            p = search(game,cards,orientacion,mazo,mesa,jugadores[id_player-1].laberinto);
            if(p!= 0){
                jugadores[id_player-1].laberinto = p;
                cards[p].maze[2][0] = player;
                jugadores[id_player-1].x = 2;
                jugadores[id_player-1].y = 0; 
                randomize(game,cards,p);

                return ;
            }else{
                printf("No se pudo realizar el movimiento\n");
                cards[jugadores[id_player-1].laberinto].maze[2][8] = player;
            }    
        }
    }
    else if(orientacion == 'O'){
        if(x == 2 && y == 0){
            p = search(game,cards,orientacion,mazo,mesa,jugadores[id_player-1].laberinto);
            if(p!= 0){
                jugadores[id_player-1].laberinto = p;
                cards[p].maze[2][8] = player;
                jugadores[id_player-1].x = 2;
                jugadores[id_player-1].y = 8; 
                randomize(game,cards,p);

                return ;
            }else{
                printf("No se pudo realizar el movimiento\n");
                cards[jugadores[id_player-1].laberinto].maze[2][0] = player;
            }
        }
    }
}
/*
empezar_juego: Esta función muestra instrucciones y una descripción del juego al principio del programa y espera a que el jugador presione Enter para comenzar el juego.
*/
void empezar_juego(){
    printf("Usted jugara lo que se conoce como Magic Maze\nEsta es una vesion simplificada del juego con este nombre");
    printf("Este juego consiste en recolectar 4 tesoros distribuidos por un laberinto, y luego volver al principio, en una cantidad finita de turnos(15),cada tesoro estara numerado y pertenecera al correspondiente jugador\n");
    printf("Encontrara 4 tipos de casillas especiales:\n-'U' una casilla que le permitira obtener 5 turnos extras\n-'C' que son las casillas tipo camara si hay 2 de estas casillas activas no podra obtener mas turnos\n");
    printf("-'L' casilla que le quitara 3 turnos\n-'G'-'R'-'V'-'Z' estas casillas son tp's por jugador respectivamente, para poder usarlas deben existir 2 de estas casillas disponibles en el tablero de juego (se indicara si esto llega a pasar)\n");
    printf("Usted manejara el comportamiento de los cuatros jugadores, estos son:\n-'J' el jugador principal\n-'S' el segundo jugador\n");
    printf("-'T' el tercer jugador\n-'F' el cuarto jugador\n");
    printf("Ocupe sabiamente sus turnos ya que estos son limitados\n");
    printf("Al principio de cada turno se le mostrara el laberinto donde esta cada jugador,como tambien informacion importante para usted\n");
    printf("Cada jugador puede tener dos tipos de cartas, que son el 'Buscar' (B) o 'Escalera' (E), para usar Buscar coloquese sobre una Casilla tipo B y ocupe la carta en la direccion correspondiente, para usar una Escalera coloquese en una de las areas colindantes a una casilla tipo E e indique la direccion de la Escalera\n");
    printf("El usar Escalera abre paso a los demas jugadores para poder pasar libremente, la accion Buscar permite acceder a nuevos laberintos que pueden llegar a contener los tesoros, cuando se haya colocado un laberinto en el tablero este pasara a poder transitarse sin necesidad de hacer la accion de nuevo\n");
    printf("Al ejecutar estas acciones especiales consumira el turno del jugador correspondiente\n");
    printf("En cada turno podra decidir sobre los demas jugadores, que deberan hacer estos, el formato de instruccion es el siguiente:\n");
    printf("(Orientacion)(Cantidad/Especial), donde la orientacion puede ser 'N,S,E,O', la cantidad es un numero entre 1 y 4, y Especial es una accion Buscar o Escalera, la accion Escalera sera el numero 5 y la accion Buscar es el numero 6\n");
    printf("Ejemplo: 'N4' indicando el moverse al Norte 4 posiciones, 'O6' indicando que se realize la Accion buscar hacia el oeste\n");
    printf("Cualquier instruccion que no siga esos parametros se considera erronea y el jugador pierde el turno quedandose inmovil");
    printf("Situaciones especiales: cuando exista una conexion entre dos laberintos estara indicado y ademas las casillas que antes eran 'B' pasaran a ser 'b', para pasar de un laberinto a otro tendra que insertar una instruccion buscar, similar a como se agregan conexiones\n");
    printf("Una vez leidas las instrucciones y funcionamiento del juego, presione Enter para continuar");
    char linea[100];
    while(true){
        fgets(linea, sizeof(linea),stdin);
        linea[strcspn(linea, "\n")] = '\0';
        if(strlen(linea) == 0){
            printf("\n\n=====================Bienvenido a Magic Maze=====================\n");
            break;

        }
    }
}
/*
mostrar_jugadores: Esta función muestra información sobre la posición y el estado de los jugadores en el laberinto
*/
void mostrar_jugadores(JUGADOR *jugadores,int id_player, LABERINTO *cards,TABLERO *game){
    int x = jugadores[id_player-1].x;
    int y = jugadores[id_player-1].y;
    int id_laberinto = jugadores[id_player-1].laberinto;
    int id_origen,id_destino;
    char orientacion_origen,orientacion_destino;
    const char *orientaciones[4] = {"Norte","Sur","Este","Oeste"};
    char player;
    if(id_player == 1){player = 'J';}
    if(id_player == 2){player = 'S';}
    if(id_player == 3){player = 'T';}
    if(id_player == 4){player = 'F';}
    
    printf("El jugador numero: %d (%C) esta en el laberinto numero: %d\n",id_player,player,id_laberinto);
    printf("Coordenadas : X = %d,Y = %d\n",x+1,(y/2)+1);
    printf("Carta: %c\n",jugadores[id_player-1].ficha);
    for(int i = 0; i < 5;i++){
        printf("%s\n",cards[id_laberinto].maze[i]);
    }printf("\n");

    int aux;
    for(int i = 0; i < game->cant_pares;i++){
        sscanf(game->pares[i],"%d%c%c%d",&id_origen,&orientacion_origen,&orientacion_destino,&id_destino);
        if(id_origen == id_laberinto){
            if(orientacion_origen == 'N'){aux = 0;}
            if(orientacion_origen == 'S'){aux = 1;}
            if(orientacion_origen == 'E'){aux = 2;}
            if(orientacion_origen == 'O'){aux = 3;}
            printf("El laberinto en el %s,esta conectado con el laberinto %d\n",orientaciones[aux],id_destino);
        }
    }
    printf("\n");
}
/*
crear_jugadores: Esta función crea procesos hijo para representar a los cuatro jugadores del juego. Utiliza tuberías para la comunicación entre los procesos.
*/
void crear_jugadores(TABLERO *game, LABERINTO *cartas, int *random_cards, int *real_cards,int fd[4][2]) {
    // Crear tuberías para la comunicación entre los procesos
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
            // El proceso hijo ejecutará la función jugador()
            jugador(jugador_id, game, cartas, pipe_fd,fd); 
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
}
/*
ejecutar_instruccion: Esta función ejecuta una instrucción dada por un jugador, que puede ser moverse, usar una escalera o realizar una búsqueda.
*/
void ejecutar_instruccion(int id_jugador, TABLERO *game,JUGADOR *jugadores,LABERINTO *cards,int *random_cards, int *real_cards,char orientacion,int cantidad){

    int id_origen,id_destino;
    char orientacion_origen,orientacion_destino;
    if(cantidad == 5){
        if(jugadores[id_jugador-1].ficha == 'E'){
            escalera(cards,jugadores,id_jugador,orientacion);
        }
        else{
            printf("El Jugador %d, no tiene la carta especial Escalera\n",id_jugador);
        }
    }//Escalera
    else if (cantidad == 6){
        if(jugadores[id_jugador-1].ficha == 'B'){
            buscar(game,jugadores,cards,orientacion,random_cards,real_cards,id_jugador);
        }
        else{
            for(int i = 0; i < game->cant_pares;i++){
                sscanf(game->pares[i],"%d%c%c%d",&id_origen,&orientacion_origen,&orientacion_destino,&id_destino);
                if(id_origen == jugadores[id_jugador-1].laberinto && orientacion == orientacion_origen){
                    pasar_a_laberinto(game,jugadores,cards,orientacion,random_cards,real_cards,id_jugador);
                    return;
                }
            }
            printf("No es posible ejecutar la accion\n");
        }
    }//Buscar 
    else{
        mover_jugador(jugadores,orientacion,cards,cantidad,game,id_jugador);
    }//mover


}
/*
main: Esta función es la función principal del programa. Inicializa el juego y ejecuta los turnos hasta que se cumpla una condición de victoria o se acaben los turnos.
*/
int main(){ 
    srand((unsigned)time(NULL)); 

    TABLERO *game;  
    LABERINTO *cartas = (LABERINTO*)malloc(9*sizeof(LABERINTO));
    JUGADOR *jugadores = (JUGADOR*)malloc(4*sizeof(JUGADOR));
    for(int i = 0; i < 4 ;i++){jugadores[i] = iniciar_jugadores(i+1);}
    asignar_carta(jugadores);

    
     
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
    
    char instruccion_1[10];
    char instruccion_2[10];
    char instruccion_3[10];
    char instruccion_4[10];

    int fd[4][2];
    for (int i = 0; i < 4; i++) {
        if (pipe(fd[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

   empezar_juego();
    char Orientacion,formato[15];
    int numero;
    while (game->turnos > 0){
        printf("TE QUEDAN %d ANTES DE QUE ACABE EL JUEGO\n",game->turnos);
        mostrar_jugadores(jugadores,1,cartas,game);
        mostrar_jugadores(jugadores,2,cartas,game);
        mostrar_jugadores(jugadores,3,cartas,game);
        mostrar_jugadores(jugadores,4,cartas,game);

        crear_jugadores(game,cartas,random_cards,real_cards,fd);
        read(fd[0][0],instruccion_1,sizeof(instruccion_1));
        read(fd[1][0],instruccion_2,sizeof(instruccion_2));
        read(fd[2][0],instruccion_3,sizeof(instruccion_3));
        read(fd[3][0],instruccion_4,sizeof(instruccion_4));

        for(int i = 1; i <5; i++){
            if(i == 1){sscanf(instruccion_1,"%c%d",&Orientacion,&numero);}
            if(i == 2){sscanf(instruccion_2,"%c%d",&Orientacion,&numero);}
            if(i == 3){sscanf(instruccion_3,"%c%d",&Orientacion,&numero);}
            if(i == 4){sscanf(instruccion_4,"%c%d",&Orientacion,&numero);}
            
            if((Orientacion == 'O' || Orientacion == 'N' || Orientacion == 'S' || Orientacion == 'E')&& (numero>0 && numero < 7)){
                ejecutar_instruccion(i,game,jugadores,cartas,random_cards,real_cards,Orientacion,numero);
            }else{
                printf("Instruccion no valida, perdiste el turno del jugador %d\n",i);
            }

        }
        int cont = 0;
        for(int i = 0; i < 4; i++){
            if(jugadores[i].tesoros && jugadores[i].laberinto == 0){
                cont++;
            }
        }
        if(cont == 4){
            printf("Lograste recolectar todos los tesoros y volver al laberinto inicial, FELICIDADES\nHas ganado");
            for (int i = 0; i < 4; i++) {
                close(fd[i][0]);
                close(fd[i][1]);
            }
        }
        char linea[100];
        printf("Presione enter para continuar\n");
         while(true){
        fgets(linea, sizeof(linea),stdin);
        linea[strcspn(linea, "\n")] = '\0';
        if(strlen(linea) == 0){
            break;

        }
    }
        game->turnos--;
    }
    printf("No lograste el objetivo,Has perdido ");
    
    for (int i = 0; i < 4; i++) {
        close(fd[i][0]);
        close(fd[i][1]);
    }



    // for(int i = 0; i < 9; i++){
    //     for(int j = 0;)
    //     free(cartas[i].maze);
    // }
    // free(cartas);
    // free(jugadores);
    // free(random_cards);
    // free(real_cards);

    // Liberar memoria y realizar otras tareas de limpieza al final del juego

    return 0;
}
                  
