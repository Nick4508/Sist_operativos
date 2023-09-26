#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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

typedef struct TABLERO{
    int sup_coord_limit[2];
    int inf_coord_limit[2];
    char tablero[170][170];
    char pares[2][50];
    int t_1;
    int t_2;
    int t_3;
    int t_4;
    int tesoros;
    int camaras;
    int cant_laberintos;
    int especiales;
    LABERINTO *laberintos;


}TABLERO;


void cambiar_fichas(char **maze){
    //Reemplaza las fichas tipo jugador [J1,J2,J3,J4]
    //Por las siguientes indicaciones J1->J,J2->Y,J3->K,J4->W;
    for(int i = 0;i < 5; i++){
        for(int j = 0;j < 15; j++){
            if(maze[i][j] == 'J'){
                if(maze[i][j+1] == '1'){maze[i][j] = 'J';j++;}
                else if(maze[i][j+1] == '2'){maze[i][j] = 'Y';j++;}
                else if(maze[i][j+1] == '3'){maze[i][j] = 'K';j++;}
                else if(maze[i][j+1] == '4'){maze[i][j] = 'W';j++;}
           
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

int randomize(TABLERO *game, LABERINTO new){
    if(game->tesoros == game->especiales){
        int ram = rand() % 2;
        if(ram){
            int x = rand() % 10, y = rand() % 10;
            while(true){
                if(!(new.maze[x][y] == 'E') && !(new.maze[x][y] == 'B') && !(new.maze[x][y] == '/') && !(new.maze[x][y] == ' ')){
                    new.maze[x][y] = game->tesoros+1;
                    if(game->tesoros == 0){game->t_1 = 1;}
                    else if (game->tesoros == 1){game->t_2 = 1;}
                    else if (game->tesoros == 2){game->t_3 = 1;}
                    else if (game->tesoros == 3){game->t_4 = 1;}
                    
                    return 1;
                }
            };
        }else{
            return 0;
            
        }
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


TABLERO *iniciar_tablero(LABERINTO *first){
    TABLERO *new = (TABLERO*)malloc(sizeof(TABLERO));

    new->camaras = 0;new->t_1 = 0;new->t_2 = 0;new->t_3 = 0;new->t_4 = 0;
    new->cant_laberintos = 1;new->especiales = 0;
    LABERINTO *laberintos = (LABERINTO*)malloc(9*sizeof(LABERINTO));

    return new;
}