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
            char letras[402],orientacion[15];
            archivo = fopen(entrada->d_name,"r");
            if(archivo == NULL ){
                printf("Error");
            }else{
                // printf("palabra :%s\n",nombre_archivo);
                fgets(orientacion,15,archivo);
                strtok(orientacion,"\n");

                // printf("%s\n",orientacion);

                fgets(letras,402,archivo);
                strtok(letras,"\n");

                int largo,n=0,fila = 1;
                largo = strlen(letras);
                n = (largo)/2;
                char **matriz = (char**)malloc(n*sizeof(char*));
                char *sin_espacios;
                

                sin_espacios = eliminarEspacios(letras,largo);
                matriz[0] = sin_espacios;


                while(fgets(letras,402,archivo)!=NULL && fila <=n){
                    strtok(letras,"\n");
                    largo = strlen(letras);
                    sin_espacios = eliminarEspacios(letras,largo);
                    strtok(sin_espacios,"\n");
                    matriz[fila]= sin_espacios;
                    fila++;
                }
                char cmp[12] = "vertical";
                char cmp2[12] = "Vertical";

                char try[12];
                strncpy(try,orientacion,sizeof(cmp));
                try[sizeof(try)-1] = '\0';
                printf("%s\n",orientacion);
                
                if(try[0] == 'v' || try[0] == 'V'){
                    printf("-Vertical\n");
                }else{
                    printf("-horizontal\n");
                }

                // printf("Matriz de %dX%d\n",n,n);
                // for(int i = 0;i < n;i++){
                //     printf("%s\n",matriz[i]);
                // }

                for(int i = 0;i<n;i++){
                    free(matriz[i]);
                }
                free(matriz);
               
            }
            fclose(archivo);


        }
        
    }

    closedir(directorio);
    

    return 0;
}