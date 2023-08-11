#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <string.h>
#include <ctype.h>

typedef struct 
{
    int row;
    int col;
    /* data */
}coord;

typedef struct 
{
    int row;
    int col;
    char orientacion[15];
    char palabra[50];
    double tiempo;
    /* data */
}datos_palabra;


char* eliminarEspacios(char *texto,int largo){
    int n = 0;
    for (int i = 0; i < largo; i++) {
        if (texto[i] != ' ') {
            n++;
        }
    }
    
    char *new = (char*)malloc((n+1)*sizeof(char));
    int j=0;
    for(int i = 0;i<largo;i++){
        if(texto[i] !=' '){
            new[j++]=texto[i];
        }
    }
    new[j] = '\0';
    strtok(new,"\n");
    return new;
}

coord *encontrar_horizontal(char **matriz,char *palabra, int n){
    int cont = 0,tope = strlen(palabra);
    for(int i = 0;palabra[i]!='\0';++i){
        palabra[i] = toupper(palabra[i]);
    }
    // printf("%s\n",palabra);
    coord *a = (coord*)malloc(sizeof(coord));
    // if ('P' == palabra[0]){printf(" si");}else{printf(" no");}
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(matriz[i][j] == palabra[cont]){
                cont++;
                if(cont == tope){
                    a->row = i+1;
                    a->col = j+1;
                    return a;}
            }else{
                cont = 0;
            }
        }
    }

    
}
