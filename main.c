#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.c"
#include <dirent.h>
#include <time.h>

#define MAX_ARCHIVOS 12


int main(){
    DIR *directorio;
    struct dirent *entrada;
    directorio = opendir(".");
    if (directorio == NULL) {
        perror("Error al abrir el directorio");
        return EXIT_FAILURE;
    }
    datos_palabra *arreglo_salida[12];
    int constante_salida = 0;
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

                int largo,n=0,n2=0,fila = 1;
                largo = strlen(letras);
                for(int i = 0;i<largo;i++){
                    if(letras[i] != ' '){
                        n++;
                    }
                }
                
                n2 = (largo)/2;
                // printf("%d\n",largo);
                // printf("for %d; len/2 %d\n",n,n2);
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
                // printf("%s\n",orientacion);
                clock_t inicio,fin;
                coord *coordenadas ;
                double tiempo;
                int *fila_columna;
                if(try[0] == 'v' || try[0] == 'V'){
                    printf("-Vertical\n");
                    //buscar vertical
                }else{
                    // printf("-horizontal\n");
                    inicio = clock();
                    // printf("%s\n",nombre_archivo);
                    coordenadas = encontrar_horizontal(matriz,nombre_archivo,n);
                    fin = clock();
                    tiempo = ((double) fin -inicio)/CLOCKS_PER_SEC;
                    arreglo_salida[constante_salida] = (datos_palabra*)malloc(sizeof(datos_palabra));
                    arreglo_salida[constante_salida]->row = coordenadas->row;
                    arreglo_salida[constante_salida]->col = coordenadas->col;
                    arreglo_salida[constante_salida]->tiempo = tiempo;
                    strcpy(arreglo_salida[constante_salida]->palabra,nombre_archivo);
                    strcpy(arreglo_salida[constante_salida]->orientacion,"horizontal");
                    constante_salida++;
                    // printf("%f\n",tiempo);
                    // printf("%d,%d\n",coordenadas->row,coordenadas->col);
                    free(coordenadas);
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
    for(int i = 0; i < constante_salida;i++){
        printf("palabra : %s\n",arreglo_salida[i]->palabra);
        printf("orientacion : %s\n",arreglo_salida[i]->orientacion);
        printf("tiempo : %f\n",arreglo_salida[i]->tiempo);
        printf("coord : %d,%d\n\n",arreglo_salida[i]->row,arreglo_salida[i]->col);
    }
    for(int i = 0; i < constante_salida; i++){
        free(arreglo_salida[i]);
    }
    

    return 0;
}