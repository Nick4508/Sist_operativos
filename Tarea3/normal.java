public class normal {
    private String palabra;
    private String[][] matriz;

    public normal(String palabra, String[][] matriz) {
        this.palabra = palabra;
        this.matriz = matriz;
    }

    public void buscarPalabra() {
        int filas = matriz.length;
        int columnas = matriz[0].length;

        // Búsqueda horizontal
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j <= columnas - palabra.length(); j++) {
                StringBuilder sample = new StringBuilder();
                for (int k = 0; k < palabra.length(); k++) {
                    sample.append(matriz[i][j + k]);
                }
                if (sample.toString().equals(palabra)) {
                    System.out.printf("Fila : %d, Columna: %d\n", i + 1, j + 1);
                }
            }
        }

        // Búsqueda vertical
        for (int i = 0; i <= filas - palabra.length(); i++) {
            for (int j = 0; j < columnas; j++) {
                StringBuilder sample = new StringBuilder();
                for (int k = 0; k < palabra.length(); k++) {
                    sample.append(matriz[i + k][j]);
                }
                if (sample.toString().equals(palabra)) {
                    System.out.printf("Fila : %d, Columna: %d\n", i + 1, j + 1);
                }
            }
        }
    }
}