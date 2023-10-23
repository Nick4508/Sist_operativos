import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.ForkJoinPool;

public class main{
    public static void main(String[] args){
        String archivo = "sopa_de_letras.txt";
        int N = 0;
        String palabra = "vacio";
        String[][] matriz = null;

        try {

            FileReader archivo_reader = new FileReader(archivo);
            BufferedReader lector = new BufferedReader(archivo_reader);

            String primera_linea = lector.readLine();
            N = Integer.parseInt(primera_linea);
            palabra = lector.readLine();
            
            matriz = new String[N][N];
            for(int i = 0; i < N; i++){
                String linea = lector.readLine();
                if (linea != null){
                    matriz[i] = linea.split(" ");
                }
            }



            lector.close();

        } catch (IOException e){
            e.printStackTrace();
        }

        // System.out.println(N);
        // System.out.println(palabra);
        // if (matriz != null) {
        //     for (int i = 0; i < N; i++) {
        //         for (int j = 0; j < N; j++) {
        //             System.out.print(matriz[i][j]);
        //         }
        //         System.out.println();
        //     }
        // }
        int largo_palabra = palabra.length();
        System.out.printf("Palabra : %s\n",palabra);
        long tiempo = System.currentTimeMillis();
        cuadrante_threads inicio = new cuadrante_threads(palabra,1,1, N, largo_palabra, matriz, tiempo);
        System.out.printf("Tiempo y posicion con hebras:\n");
        inicio.start();
        try{
            inicio.join();

        }catch(InterruptedException e){

        }
        
        System.out.printf("\nTiempo y posicion con Fork/RecursiveTask:\n");
        long tiempo_2 = System.currentTimeMillis();
        ForkJoinPool pool = new ForkJoinPool();
        pool.invoke(new cuadrante_forks(palabra, 1, 1, N, largo_palabra, matriz, tiempo_2));

        // System.out.printf("\nBusqueda : %d",busqueda);
        // long tiempo_3 = System.currentTimeMillis();
        // linea_a_linea busqueda = new linea_a_linea(tiempo_3,matriz,N,largo_palabra,palabra);
        // System.out.printf("Tiempo y posicion linea a linea:\n");

        // busqueda.start();
    }
}