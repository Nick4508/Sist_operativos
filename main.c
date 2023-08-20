#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.c"
#include <dirent.h>
#include <time.h>



int main(){
    DIR *directorio;
    struct dirent *entrada;
    directorio = opendir(".");
    if (directorio == NULL) {
        perror("Error al abrir el directorio");
        return EXIT_FAILURE;
    }
    carpetas();
    datos_palabra *arreglo_salida[12];
    int constante_salida = 0, largo_salida = 0;
    const char *tamanios[3] = {"50X50","100X100","200X200"};
    const char *orientacion_salida[2] = {"Vertical","Horizontal"};

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
                fgets(orientacion,15,archivo);
                strtok(orientacion,"\n");
                fgets(letras,402,archivo);
                strtok(letras,"\n");

                int largo,n=0,n2=0,fila = 1;
                largo = strlen(letras);
                for(int i = 0;i<largo;i++){
                    int caracter = letras[i];
                    if( caracter >= 65 && caracter <= 90){
                        n++;
                    }
                }

                char **matriz = (char**)malloc(n*sizeof(char*));
                largo_salida = n;
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
                char try[12];
                strncpy(try,orientacion,sizeof(cmp));
                try[sizeof(try)-1] = '\0';
                clock_t inicio,fin,delta;
                coord *coordenadas ;
                double tiempo;
               
                if(try[0] == 'v' || try[0] == 'V'){
                    inicio = clock();
                    coordenadas = encontrar_vertical_2(matriz, nombre_archivo, n); 
                    fin = clock();
                    delta = fin - inicio;
                    tiempo = ((double)delta) / CLOCKS_PER_SEC;
                    arreglo_salida[constante_salida] = (datos_palabra *)malloc(sizeof(datos_palabra));
                    arreglo_salida[constante_salida]->row = coordenadas->row;
                    arreglo_salida[constante_salida]->col = coordenadas->col;
                    arreglo_salida[constante_salida]->tiempo = tiempo;
                    strcpy(arreglo_salida[constante_salida]->palabra, nombre_archivo);
                    strcpy(arreglo_salida[constante_salida]->orientacion, "vertical");
                    arreglo_salida[constante_salida]->delta = delta;
                    constante_salida++;
                    free(coordenadas);
                    
                }else{
                    inicio = clock();
                    coordenadas = encontrar_horizontal_2(matriz,nombre_archivo,n);
                    fin = clock();
                    delta = fin- inicio;
                    tiempo = ((double) fin -inicio)/CLOCKS_PER_SEC;
                    arreglo_salida[constante_salida] = (datos_palabra*)malloc(sizeof(datos_palabra));
                    arreglo_salida[constante_salida]->row = coordenadas->row;
                    arreglo_salida[constante_salida]->col = coordenadas->col;
                    arreglo_salida[constante_salida]->tiempo = tiempo;
                    strcpy(arreglo_salida[constante_salida]->palabra,nombre_archivo);
                    strcpy(arreglo_salida[constante_salida]->orientacion,"horizontal");
                    arreglo_salida[constante_salida]->delta = delta;
                    constante_salida++;
                    free(coordenadas);
                }

               

                for(int i = 0;i<n;i++){
                    free(matriz[i]);
                }
                free(matriz);
               
            }
            fclose(archivo); 
            char dir[258];

            if(orientacion[0] == 'v' || orientacion[0] == 'V'){
                if(largo_salida == 50){
                    snprintf(dir,sizeof(dir),"%s/%s/%s",orientacion_salida[0],tamanios[0],entrada->d_name);
                    if(rename(entrada->d_name,dir)==0){
                        continue;
                    }
                    else{
                        perror("error");
                    }
                }
                else if (largo_salida == 100){
                    snprintf(dir,sizeof(dir),"%s/%s/%s",orientacion_salida[0],tamanios[1],entrada->d_name);
                    if(rename(entrada->d_name,dir)==0){
                        continue;
                    }
                    else{
                        perror("error");
                    }

                }else{
                    snprintf(dir,sizeof(dir),"%s/%s/%s",orientacion_salida[0],tamanios[2],entrada->d_name);
                    if(rename(entrada->d_name,dir)==0){
                        continue;
                    }
                    else{
                        perror("error");
                    }

                }                
            }
            else{
                if(largo_salida == 50){
                    snprintf(dir,sizeof(dir),"%s/%s/%s",orientacion_salida[1],tamanios[0],entrada->d_name);
                    if(rename(entrada->d_name,dir)==0){
                        continue;
                    }
                    else{
                        perror("error");
                    }
                }
                else if (largo_salida == 100){
                    snprintf(dir,sizeof(dir),"%s/%s/%s",orientacion_salida[1],tamanios[1],entrada->d_name);
                    if(rename(entrada->d_name,dir)==0){
                        continue;
                    }
                    else{
                        perror("error");
                    }

                }else{
                    snprintf(dir,sizeof(dir),"%s/%s/%s",orientacion_salida[1],tamanios[2],entrada->d_name);
                    if(rename(entrada->d_name,dir)==0){
                        continue;
                    }
                    else{
                        perror("error");
                    }

                }
            }

        }
        
    }
    closedir(directorio);
    for(int i = 0; i < constante_salida;i++){
        printf("palabra : %s\n",arreglo_salida[i]->palabra);
        printf("orientacion : %s\n",arreglo_salida[i]->orientacion);
        printf("clocks : %ld\n",arreglo_salida[i]->delta);
        printf("tiempo : %f\n",arreglo_salida[i]->tiempo);
        printf("coord : %d,%d\n\n",arreglo_salida[i]->row,arreglo_salida[i]->col);
    }
    for(int i = 0; i < constante_salida; i++){
        free(arreglo_salida[i]);
    }
    

    return 0;
}