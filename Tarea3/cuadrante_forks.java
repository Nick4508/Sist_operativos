import java.util.concurrent.RecursiveAction;

public class cuadrante_forks extends RecursiveAction{
    private long tiempo_inicio;
    private int N;
    private int largo_palabra;
    private int relative_x;
    private int relative_y;
    private String palabra;
    private String[][] matriz;

    public cuadrante_forks(String palabra, int relative_x,int relative_y,int N, int largo_palabra, String[][] matriz, long tiempo){
        this.N = N;
        this.largo_palabra = largo_palabra;
        this.palabra = palabra;
        this.relative_x = relative_x;
        this.relative_y = relative_y;
        this.matriz = matriz;
        this.tiempo_inicio = tiempo;
 
    } 
   
    public void buscar_horizontal(){
        for(int i  = 0; i < N ; i++){
            String sample = "";
            for(int j = 0; j < N; j++){
                sample = sample+matriz[i][j];
            }
            if(sample.equals(palabra)){
                long tiempo_final = System.currentTimeMillis();
                System.out.printf("Fila : %d, Columna: %d\n" ,relative_x+i, relative_y);
                long busqueda = tiempo_final-tiempo_inicio;
                System.out.printf("Se demoró %d milisegundos\n",busqueda);
            }
        }
        
    }
    
    public void buscar_vertical(){
        for(int i  = 0; i < N ; i++){
            String sample = "";
            for(int j = 0; j < N; j++){
                sample = sample+matriz[j][i];
            }
            if(sample.equals(palabra)){
                long tiempo_final = System.currentTimeMillis();
                System.out.printf("Fila : %d, Columna: %d\n" ,relative_x, relative_y + i);
                long busqueda = tiempo_final-tiempo_inicio;
                System.out.printf("Se demoró %d milisegundos\n",busqueda);
            }
        }
    }
   
    protected void compute(){
        if(N == largo_palabra){
            buscar_horizontal();
            buscar_vertical();
        }else{
            String[][] matriz_1 = new String[N/2][N/2];
                String[][] matriz_2 = new String[N/2][N/2];
                String[][] matriz_3 = new String[N/2][N/2];
                String[][] matriz_4 = new String[N/2][N/2];
                for(int i = 0; i < N/2;i ++){
                    for(int j  = 0; j< N/2;j++){
                        matriz_1[i][j] = matriz[i][j];
                    }
                }
                for(int i  = 0; i < N/2; i ++){
                    for(int j = N/2; j < N; j++){
                        matriz_2[i][j-(N/2)] = matriz[i][j];
                    }
                }
                for(int i = N/2 ; i < N;i++){
                    for(int j = 0; j <N/2; j++){
                        matriz_3[i-(N/2)][j] = matriz[i][j];
                    }
                }
                for(int i = N/2; i < N; i++){
                    for(int j = N/2; j < N; j++){
                        matriz_4[i-(N/2)][j-(N/2)] = matriz[i][j];
                    }
                }
                cuadrante_forks primer_sector = new cuadrante_forks(palabra, relative_x,relative_y,N/2,largo_palabra,matriz_1,tiempo_inicio);
                cuadrante_forks segundo_sector = new cuadrante_forks(palabra,relative_x,relative_y+N/2,N/2,largo_palabra,matriz_2,tiempo_inicio); 
                cuadrante_forks tercer_sector = new cuadrante_forks(palabra, relative_x + N/2, relative_y, N/2, largo_palabra, matriz_3, tiempo_inicio);
                cuadrante_forks cuarto_sector = new cuadrante_forks(palabra, relative_x+N/2, relative_y+N/2, N/2, largo_palabra, matriz_4, tiempo_inicio);
                
                invokeAll(primer_sector,segundo_sector,tercer_sector, cuarto_sector);
        }

    }
}
