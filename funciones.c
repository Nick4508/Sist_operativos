#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>

typedef struct 
{
    int row;
    int col;
}coord;

typedef struct 
{
    int row;
    int col;
    char orientacion[15];
    char palabra[50];
    double tiempo;
}datos_palabra;


void carpetas(){
    const char *vertical = "Vertical";
    const char *horizontal = "Horizontal";
    const char *tamanios[3] = {"50X50","100X100","200X200"};
    
    if(access(vertical,F_OK) != 0){
        if(mkdir(vertical,0777) != 0){
            perror("Carpeta ya existente");
            return ;
        }
    }
    if(access(horizontal,F_OK) != 0){
        if(mkdir(horizontal,0777) != 0){
            perror("Carpeta ya existente");
            return ;
        }
    
    }
    for(int i = 0; i < 3;i++){
        char dir1[50],dir2[50];
        snprintf(dir1,sizeof(dir1),"%s/%s",vertical,tamanios[i]);
        snprintf(dir2,sizeof(dir2),"%s/%s",horizontal,tamanios[i]);

        if(access(dir1,F_OK)!=0){
            if(mkdir(dir1,0777)!= 0){
                perror("Carpeta ya existente");
                return ;
            }
        }
        if(access(dir2,F_OK)!=0){
            if(mkdir(dir2,0777)!= 0){
                perror("Carpeta ya existente");
                return ;
            }
        }
    }
}

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
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if((j+tope-cont) > n){
                j=n;
            }
            if(matriz[i][j] == palabra[cont]){
                cont++;
                
                if(cont == tope){
                    a->row = i+1;
                    a->col = j+1;
                    return a;
                }

            }else{
                cont = 0;
            }
        }
    }

    
}
