public class linea_a_linea {
    private long tiempo;
    private int N;
    private String[][] matriz;
    private int largo_palabra;
    private String palabra;

    public linea_a_linea(long tiempo, String[][] matriz, int N, int largo_palabra,String palabra){
        this.tiempo = tiempo;
        this.matriz = matriz;
        this.N = N;
        this.largo_palabra = largo_palabra;
        this.palabra = palabra;
    }
    public void busqueda_horizontal(){
        for(int i  = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(matriz[i][j].substring(j,j+1).equals(palabra.substring(0, 1))){
                    if(j+largo_palabra <N){
                        if(matriz[i][j].substring(j, j+largo_palabra).equals(palabra)){
                            long tiempo_final = System.currentTimeMillis();
                            System.out.printf("Fila : %d, Columna : %d\n",i+1,j+1);
                            System.out.printf("Tiempo demorado %d milisegundos\n",tiempo_final-tiempo);
                            return ;
                        }
                    }
                }   
                
            }   
        }
    }
    public void busqueda_vertical(){

    }
    public void start(){
        busqueda_horizontal();
        // busqueda_vertical();
    }
    
}
