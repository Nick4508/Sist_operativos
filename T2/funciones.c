#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LABERINTO{
    char **maze;
    int salidas;
    int escalera;
    int norte;
    int sur;
    int este;
    int oeste;
    char tipo;
    int id;
    int tesoros;
    /* data */
}LABERINTO;

typedef struct JUGADOR {
    int id;           
    int x;           
    int y;            
    int tesoros;      
    char ficha;       
    int laberinto; 
} JUGADOR;

typedef struct TABLERO{
    int sup_coord_limit[2];
    int inf_coord_limit[2];
    char **tablero;
    char **pares;
    int t_1;
    int t_2;
    int t_3;
    int t_4;
    int tesoros;
    int camaras;
    int cant_laberintos;
    int cant_pares;
    int especiales;
    int turnos;
    LABERINTO *laberintos;
    JUGADOR *jugadores;
}TABLERO;


void cambiar_fichas(char **maze){
    //Reemplaza las fichas tipo jugador [J1,J2,J3,J4]
    //Por las siguientes indicaciones J1->J,J2->S,J3->T,J4->F;
    for(int i = 0;i < 5; i++){
        for(int j = 0;j < 15; j++){
            if(maze[i][j] == 'J'){
                if(maze[i][j+1] == '1'){maze[i][j] = 'J';j++;}
                else if(maze[i][j+1] == '2'){maze[i][j] = 'S';j++;}
                else if(maze[i][j+1] == '3'){maze[i][j] = 'T';j++;}
                else if(maze[i][j+1] == '4'){maze[i][j] = 'F';j++;}
           
            }
        }
        char *new = (char*)malloc(15*sizeof(char));
        int k = 0;
        for(int j = 0; j <15; j++){
            if(!(maze[i][j] == '1') && !(maze[i][j] == '2') && !(maze[i][j] == '3') && !(maze[i][j] == '4')){
                new[k] = maze[i][j];
                k++;
            }
        }
        maze[i] = new;        
    }    
}

int randomize(TABLERO *game, LABERINTO *new,int id){
    // if(true){
    if(game->tesoros == game->especiales){
        int ram = rand() %2;
        if(ram){
            while(true){
                int x = rand() % 5, y = rand() % 9;
                if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                    if(game->tesoros == 0){game->t_1 = 1;new[id].maze[x][y] = '1';}
                    else if (game->tesoros == 1){game->t_2 = 1;new[id].maze[x][y] = '2';}
                    else if (game->tesoros == 2){game->t_3 = 1;new[id].maze[x][y] = '3';}
                    else if (game->tesoros == 3){game->t_4 = 1;new[id].maze[x][y] = '4';}
                    game->tesoros = game->tesoros +1;
                    return 1;
                }
            };
        }else{
            int decider = rand() % 4;
            //Camaras
            if(decider == 1){
                while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'C';
                        game->camaras = game->camaras + 1;
                        game->especiales = game->especiales + 1;
                        return 0;
                    }
                
                }                
            }
            //+5 turnos
            else if(decider == 2){
                while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'U';//up
                        game->especiales = game->especiales + 1;
                        return 0;
                    }
                
                } 
            }
            //-3 turnos
            else if(decider == 3){
                while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'L'; //less
                        game->especiales = game->especiales + 1;
                        return 0;
                    }
                
                } 
            }
            //Tps por jugador
            else if(decider == 4){}
                int jugador = rand() % 4;
                if(jugador == 1){
                    while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'G';//tp player 1
                        game->especiales = game->especiales + 1;
                        return 0;
                        }
                    } 
                }
                else if(jugador == 2){
                    while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'R';//tp player 2
                        game->especiales = game->especiales + 1;
                        return 0;
                        }
                    }
                }
                else if(jugador == 3){
                    while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'V';//tp player 3
                        game->especiales = game->especiales + 1;
                        return 0;
                        }
                    }
                }
                else if(jugador == 4){
                    while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'Z';//tp player 4
                        game->especiales = game->especiales + 1;
                        return 0;
                        }
                    }
                }
            return 0;
            
        }
    }
    else if(game->tesoros > game->especiales){
        int decider = rand() % 4;
            //Camaras
            if(decider == 1){
                while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'C';
                        game->camaras = game->camaras + 1;
                        game->especiales = game->especiales + 1;
                        return 0;
                    }
                
                }                
            }
            //+5 turnos
            else if(decider == 2){
                while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'U';//up
                        game->especiales = game->especiales + 1;
                        return 0;
                    }
                
                } 
            }
            //-3 turnos
            else if(decider == 3){
                while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'L'; //less
                        game->especiales = game->especiales + 1;
                        return 0;
                    }
                
                } 
            }
            //Tps por jugador
            else if(decider == 4){}
                int jugador = rand() % 4;
                if(jugador == 1){
                    while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'G';//tp player 1
                        game->especiales = game->especiales + 1;
                        return 0;
                        }
                    } 
                }
                else if(jugador == 2){
                    while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'R';//tp player 2
                        game->especiales = game->especiales + 1;
                        return 0;
                        }
                    }
                }
                else if(jugador == 3){
                    while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'V';//tp player 3
                        game->especiales = game->especiales + 1;
                        return 0;
                        }
                    }
                }
                else if(jugador == 4){
                    while (true){
                    int x = rand() % 5, y = rand() % 9;
                    if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                        new[id].maze[x][y] = 'Z';//tp player 4
                        game->especiales = game->especiales + 1;
                        return 0;
                        }
                    }
                }
            return 0;
            
    }else{
        while(true){
            int x = rand() % 5, y = rand() % 9;
            if(!(new[id].maze[x][y] == 'E') && !(new[id].maze[x][y] == 'B') && !(new[id].maze[x][y] == '/') && !(new[id].maze[x][y] == ' ')&& !(new[id].maze[x][y] == 'J')&& !(new[id].maze[x][y] == 'S')&& !(new[id].maze[x][y] == 'T')&& !(new[id].maze[x][y] == 'F')){
                if(game->tesoros == 0){game->t_1 = 1;new[id].maze[x][y] = '1';}
                else if (game->tesoros == 1){game->t_2 = 1;new[id].maze[x][y] = '2';}
                else if (game->tesoros == 2){game->t_3 = 1;new[id].maze[x][y] = '3';}
                else if (game->tesoros == 3){game->t_4 = 1;new[id].maze[x][y] = '4';}
                game->tesoros = game->tesoros +1;
                return 1;
            }
        };
    }
}

LABERINTO crear_laberintos(char *nombre,int id){
    FILE *archivo;
    LABERINTO nuevo;
    nuevo.maze = (char**)malloc(5*sizeof(char*));
    char lineas[15];
    int fila =0;
    if(strcmp("Inicio.txt",nombre) == 0){
        nuevo.este = 1;
        nuevo.norte = 1;
        nuevo.sur = 1;
        nuevo.oeste = 1;
        nuevo.id = id;
        nuevo.tipo = 'I';
        nuevo.salidas = 4;
        nuevo.escalera = 0;
        nuevo.tesoros = 0;
        archivo = fopen(nombre,"r");
        while (fgets(lineas,15,archivo)!= NULL && fila <= 5){
            strtok(lineas,"\n");
            char *new = (char*)malloc(15*sizeof(char));
            strcpy(new,lineas);
            nuevo.maze[fila] = new;
            fila++;
        }
        fclose(archivo);
        cambiar_fichas(nuevo.maze);
        return nuevo;
    }else{
        nuevo.salidas=0;
        nuevo.id = id;nuevo.escalera = 0;nuevo.norte =0;nuevo.sur = 0;nuevo.este = 0;nuevo.oeste = 0,nuevo.tesoros = 0;
        archivo = fopen(nombre,"r");
        while (fgets(lineas,15,archivo)!= NULL && fila <= 5){
            strtok(lineas,"\n");
            char *new = (char*)malloc(15*sizeof(char));
            strcpy(new,lineas);
            nuevo.maze[fila] = new;
            fila++;
        }
        fclose(archivo);
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 15;j++){
                if(nuevo.maze[i][j]=='E'){nuevo.escalera++;}
                if(i == 0){
                    if(nuevo.maze[i][j] == 'B'){
                        nuevo.norte = 1;
                        nuevo.salidas++;
                    }
                }
                if(i == 2){
                    if(j == 0){if(nuevo.maze[i][j] == 'B'){nuevo.oeste = 1;nuevo.salidas++;}}
                    if(j != 0){if(nuevo.maze[i][j] == 'B'){nuevo.este = 1;nuevo.salidas++;}}
                }
                if(i == 4){if(nuevo.maze[i][j] == 'B'){nuevo.sur = 1;nuevo.salidas++;}}
            }
        }
        if(nuevo.salidas == 2){nuevo.tipo = 'L';}
        if(nuevo.salidas == 3){nuevo.tipo = 'T';}

        
    }
    return nuevo;
};

void mostrar_tablero(TABLERO *game){
    int i = game->sup_coord_limit[0],j = game->sup_coord_limit[1],k = game->inf_coord_limit[0],u = game->inf_coord_limit[1];
    if((i - 5) < 0){i = 0;}else{i = i -5;}
    if((j - 5) < 0){j = 0;}else{j =j-5;}
    if((k + 5) > 85){k = 85;}else{k = k+5;}
    if((u + 5) > 85){u = 85;}else{u= u+5;}
    
    for(int o = i; o < k; o++){
        for(int l = j; l < u; l++){
            printf("%c",game->tablero[o][l]);
        }
        printf("\n");
    }
}

void randomize_deck(int *cards){
    
    for(int i = 1 ; i < 9; i++){
        while (true){
            int card = rand()% 8 +1, cont = 0;
            for(int j = 0 ; j < i; j++){
                if(card == cards[j]){
                    cont++;                    
                }
            } 
            if(cont == 0){
                cards[i] = card;

                break;
            }
        }
    }
}

TABLERO *iniciar_tablero(LABERINTO *cartas){
    TABLERO *new = (TABLERO*)malloc(sizeof(TABLERO));
    
    new->camaras = 0;new->t_1 = 0;new->t_2 = 0;new->t_3 = 0;new->t_4 = 0;
    new->cant_laberintos = 1;new->especiales = 0,new->tesoros = 0;new->cant_pares = 0;
    new->turnos = 15;

    char **tablero = (char**)malloc(85*sizeof(char*));
    char linea[85] = "-------------------------------------------------------------------------------------";
    
    for(int i = 0;i < 85; i++){
        char *line = (char*)malloc(85*sizeof(char));
        strcpy(line,linea);
        tablero[i] = line;
    }
    
    int k = 39,u = 39;
    for(int i = 0; i < 5; i++ ){
        for(int j = 0;j < 15;j++){
            if(!(cartas[0].maze[i][j] == ' ')){tablero[k][u] = cartas[0].maze[i][j];u++;}
        }
        for(int o = 44; o <85; o++){
            tablero[k][o] = '-';
        }
        u = 39;
        k++;
    }
    
    char **pares = (char**)malloc(70*sizeof(char*));
    char set[5] = "----";
    for(int i = 0; i < 70; i++){
        char *lineas = (char*)malloc(5*sizeof(char));
        strcpy(lineas,set);
        pares[i] = lineas;
    }
    new->pares = pares;
 
    new->sup_coord_limit[0] = 39;
    new->sup_coord_limit[1] = 39;
    new->inf_coord_limit[0] = 44;
    new->inf_coord_limit[1] = 44;
    
    new->tablero = tablero;



    return new;
}

JUGADOR iniciar_jugadores(int id){
    JUGADOR nuevo;
    if(id == 1){
        nuevo.id = id;
        nuevo.x = 1;
        nuevo.y = 2;
    }
    if(id == 2){
        nuevo.id = id;
        nuevo.x = 1;
        nuevo.y = 6;
    }
    if(id == 3){
        nuevo.id = id;
        nuevo.x = 3;
        nuevo.y = 2;
    }
    if(id == 4){
        nuevo.id = id;
        nuevo.x = 3;
        nuevo.y = 6;
    }
    nuevo.tesoros = 0;
    nuevo.laberinto = 0;
    nuevo.ficha = 'C';

    return nuevo;
}
void asignar_carta(JUGADOR *jugadores){
    int buscar = 0, escalera = 0,cantidad = 4,actual = 0;
    while (!(cantidad == 0)){
        if(buscar == escalera){
            int i = rand() % 2;
            if(i){
                buscar++;
                jugadores[actual].ficha = 'B';
                actual++;
            }else{
                escalera++;
                jugadores[actual].ficha = 'E';
                actual++;
            }
        }else{
            if(buscar < escalera){
                buscar++;
                jugadores[actual].ficha = 'B';
                actual++;
            }else{
                escalera++;
                jugadores[actual].ficha = 'E';
                actual++;
            }
        }
        cantidad--;
    }
}

int search(TABLERO *game, LABERINTO *cards, char orientacion, int *mazo,int *mesa,int origen){
    char new_par[5];
    if(orientacion == 'N'){
        for(int i = game->cant_laberintos; i < 9;i++){
            if(mazo[i] < 9){
                if(cards[mazo[i]].sur){
                    int id_new_lab = cards[mazo[i]].id;
                    snprintf(new_par,sizeof(new_par),"%d%cS%d",origen,orientacion,cards[mazo[i]].id);
                    strcpy(game->pares[game->cant_pares],new_par);
                    snprintf(new_par,sizeof(new_par),"%dS%c%d",cards[mazo[i]].id,orientacion,origen);
                    strcpy(game->pares[game->cant_pares + 1],new_par);

                    cards[origen].maze[0][4] = 'b';
                    cards[mazo[i]].maze[4][4] = 'b';
                    mesa[game->cant_laberintos] = mazo[i];
                    mazo[i] = 9;

                    game->cant_laberintos++;
                    game->cant_pares = game->cant_pares +2;
                    return id_new_lab;
                }
            }
        }
    }
    else if (orientacion == 'S'){
        for(int i = game->cant_laberintos; i < 9;i++){
            if(mazo[i] < 9){
                if(cards[mazo[i]].norte){
                    int id_new_lab = cards[mazo[i]].id;
                    snprintf(new_par,sizeof(new_par),"%d%cN%d",origen,orientacion,cards[mazo[i]].id);
                    strcpy(game->pares[game->cant_pares],new_par);
                    snprintf(new_par,sizeof(new_par),"%dN%c%d",cards[mazo[i]].id,orientacion,origen);
                    strcpy(game->pares[game->cant_pares + 1],new_par);

                    cards[origen].maze[4][4] = 'b';
                    cards[mazo[i]].maze[0][4] = 'b';
                    mesa[game->cant_laberintos] = mazo[i];
                    mazo[i] = 9;

                    game->cant_laberintos++;
                    game->cant_pares = game->cant_pares +2;
                    return id_new_lab;
                }
            }
        }
    }
    else if (orientacion == 'E'){
        for(int i = game->cant_laberintos; i < 9;i++){
            if(mazo[i] < 9){
                if(cards[mazo[i]].oeste){
                    int id_new_lab = cards[mazo[i]].id;
                    snprintf(new_par,sizeof(new_par),"%d%cO%d",origen,orientacion,cards[mazo[i]].id);
                    strcpy(game->pares[game->cant_pares],new_par);
                    snprintf(new_par,sizeof(new_par),"%dO%c%d",cards[mazo[i]].id,orientacion,origen);
                    strcpy(game->pares[game->cant_pares + 1],new_par);

                    cards[origen].maze[2][8] = 'b';
                    cards[mazo[i]].maze[2][0] = 'b';
                    mesa[game->cant_laberintos] = mazo[i];
                    mazo[i] = 9;

                    game->cant_laberintos++;
                    game->cant_pares = game->cant_pares +2;
                    return id_new_lab;
                }
            }
        }
    }
    else if (orientacion == 'O'){
        for(int i = game->cant_laberintos; i < 9;i++){
            if(mazo[i] < 9){
                if(cards[mazo[i]].este){
                    int id_new_lab = cards[mazo[i]].id;
                    snprintf(new_par,sizeof(new_par),"%d%cE%d",origen,orientacion,cards[mazo[i]].id);
                    strcpy(game->pares[game->cant_pares],new_par);
                    snprintf(new_par,sizeof(new_par),"%dE%c%d",cards[mazo[i]].id,orientacion,origen);
                    strcpy(game->pares[game->cant_pares + 1],new_par);

                    cards[origen].maze[2][0] = 'b';
                    cards[mazo[i]].maze[2][8] = 'b';
                    mesa[game->cant_laberintos] = mazo[i];
                    mazo[i] = 9;

                    game->cant_laberintos++;
                    game->cant_pares = game->cant_pares +2;
                    return id_new_lab;
                }
            }
        }
    }
    return 0;
}


