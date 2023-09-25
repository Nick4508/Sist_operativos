#include <unistd.h>
#include <stdio.h>
#include <string.h>

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
    /* data */
}LABERINTO;

typedef struct TABLERO{
    int sup_coord_limit[2];
    int inf_coord_limit[2];
    char tablero[170][170];
    char pares[2][50];

}TABLERO;

TABLERO *iniciar_tablero(LABERINTO *inicio){
    TABLERO *game;
    
    

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
        archivo = fopen(nombre,"r");
        while (fgets(lineas,15,archivo)!= NULL && fila <= 5){
            strtok(lineas,"\n");
            char *new = (char*)malloc(15*sizeof(char));
            strcpy(new,lineas);
            nuevo.maze[fila] = new;
            fila++;
        }
        fclose(archivo);
        return nuevo;
    }else{
        nuevo.salidas=0;
        nuevo.id = id;nuevo.escalera = 0;nuevo.norte =0;nuevo.sur = 0;nuevo.este = 0;nuevo.oeste = 0;
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
        
    }
    for(int i = 0;i < 5; i++){
        printf("%s\n",maze[i]);
    }
}