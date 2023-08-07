#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.c"
#include <dirent.h>

int main(){
    DIR *directorio;
    struct dirent *entrada;
    directorio = opendir(".");
    if (directorio == NULL) {
        perror("Error al abrir el directorio");
        return EXIT_FAILURE;
    }

    while ((entrada = readdir(directorio)) != NULL) {
        size_t longitud = strlen(entrada->d_name);
        if (longitud >= 4 && entrada->d_name[longitud - 4] == '.' && entrada->d_name[longitud - 3] == 't' && entrada->d_name[longitud - 2] == 'x' && entrada->d_name[longitud - 1] == 't'){
                
            char nombre_archivo[100];
            
            strncpy(nombre_archivo,entrada->d_name,longitud-4);
            nombre_archivo[longitud-4]='\0';
            FILE *archivo;
            char letras[401],orientacion[15];
            archivo = fopen(entrada->d_name,"r");
            if(archivo == NULL ){
                printf("Error");
            }else{
                // printf("palabra :%s\n",nombre_archivo);
                printf("primera linea:");
                fgets(orientacion,15,archivo);
                printf("%s",orientacion);
                // printf("segunda linea:");
                fgets(letras,401,archivo);
                // printf("%s\n",letras);
                int largo,largo_spaceless = 0,n=0,fila = 1;
                largo = strlen(letras);
                n = (largo-1)/2;
                char **matriz = (char**)malloc(n*sizeof(char*));
                // printf("largo :%d\n",largo);
                // printf("largo :%d\n",n);
                char *sin_espacios;
                strtok(letras,"\n");

                sin_espacios = eliminarEspacios(letras,largo);
                matriz[0] = sin_espacios;
                largo_spaceless = strlen(sin_espacios);
                while(fgets(letras,401,archivo)!=NULL && fila <n){
                    strtok(letras,"\n");
                    sin_espacios = eliminarEspacios(letras,largo);
                    matriz[fila]= sin_espacios;
                    fila++;
                }
                printf("matriz :\n");
                for(int i = 0;i<n;i++){
                    printf("%s\n",matriz[i]);
                }


                for(int i = 0;i<n;i++){
                    free(matriz[i]);
                }
                free(matriz);
                // printf("%s\n",sin_espacios);

                // printf("Largo sin espacios: %d\n",largo_spaceless);
            }
            fclose(archivo);


        }
        
    }

    closedir(directorio);
    // FILE *archivo;
    // char letras[201];

    // archivo = fopen("casa.txt","r");

    // if(archivo == NULL ){
    //     printf("Error");
    // }else{
    //     printf("primera linea:\n");
    //     fgets(letras,15,archivo);
    //     printf("%s",letras);
    //     printf("segunda linea:\n");
    //     fgets(letras,200,archivo);
    //     printf("%s",letras);
    //     int largo;
    //     largo = strlen(letras);
    //     printf("%d\n",largo);
    //     char *sin_espacios;
    //     sin_espacios = eliminarEspacios(letras,largo);
    //     printf("%s",sin_espacios);
    //     free(sin_espacios);
    // }
    // fclose(archivo);

    return 0;
}