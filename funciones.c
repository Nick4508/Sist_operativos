#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <string.h>

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

void encontrar_horizontal(char **matriz,char *palabra){
    
}
