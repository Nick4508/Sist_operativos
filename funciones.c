#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include <string.h>

char* eliminarEspacios(char *texto,int largo){

    char *new = (char*)malloc(((largo-1)/2)*sizeof(char));
    int j=0;
    for(int i = 0;i<largo;i++){
        if(texto[i] !=' '){
            new[j++]=texto[i];
        }
    }
    new[j] = '\0';
    return new;
}

void encontrar_horizontal(char **matriz,char *palabra){
    
}
