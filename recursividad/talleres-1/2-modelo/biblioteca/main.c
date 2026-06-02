/**
 * @file biblioteca.c
 * @brief Ordenamiento recursivo de libros con conteo de intercambios
 * @author Asistente IA
 * @date 2026
 * 
 * Este programa ordena alfabéticamente una lista de títulos de libros
 * usando Quicksort recursivo y cuenta el número total de intercambios.
 */

#include <stdio.h>
#include <string.h>

#define MAX_TITULO_LEN 100
#define MAX_LIBROS 100

/**
 * @brief Intercambia dos cadenas en un arreglo
 * 
 * @param arr Arreglo de cadenas
 * @param i Índice del primer elemento
 * @param j Índice del segundo elemento
 */
void intercambiar(char *arr[], int i, int j) {
    if (i == j) {
        return;  // No es necesario intercambiar consigo mismo
    }
    
    char *temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/**
 * @brief Función de partición para Quicksort
 * 
 * Toma el último elemento como pivote y coloca todos los elementos menores
 * a la izquierda y mayores a la derecha.
 * 
 * @param arr Arreglo de cadenas
 * @param inicio Índice inicial del segmento
 * @param fin Índice final del segmento
 * @param intercambios Puntero al contador de intercambios
 * @return int Índice de la posición final del pivote
 * 
 * @note Esta función NO usa break ni continue
 * @note Compara cadenas usando strcmp (orden alfabético)
 */
int particionar(char *arr[], int inicio, int fin, int *intercambios) {
    // Elegir el pivote como el último elemento
    char *pivote = arr[fin];
    
    // Índice del elemento más pequeño (indica la posición donde irán los menores)
    int i = inicio - 1;
    
    // Recorrer el segmento [inicio, fin-1]
    // Usamos un bucle for estándar, pero sin break/continue
    for (int j = inicio; j <= fin - 1; j++) {
        // Si el elemento actual es menor o igual al pivote (orden alfabético)
        if (strcmp(arr[j], pivote) <= 0) {
            // Incrementar el índice del menor
            i++;
            
            // Intercambiar arr[i] y arr[j]
            if (i != j) {
                intercambiar(arr, i, j);
                (*intercambios)++;  // Contar este intercambio
            }
        }
        // No se usa continue, simplemente se continúa con la siguiente iteración
    }
    
    // Colocar el pivote en su posición correcta
    if (i + 1 != fin) {
        intercambiar(arr, i + 1, fin);
        (*intercambios)++;  // Contar el intercambio del pivote
    }
    
    // Retornar la posición del pivote
    return i + 1;
}

/**
 * @brief Función recursiva principal de Quicksort
 * 
 * @param arr Arreglo de cadenas a ordenar
 * @param inicio Índice inicial del segmento a ordenar
 * @param fin Índice final del segmento a ordenar
 * @param intercambios Puntero al contador de intercambios
 * 
 * @details Algoritmo:
 *          1. Si el segmento tiene más de 1 elemento
 *          2. Particionar el segmento
 *          3. Ordenar recursivamente la parte izquierda
 *          4. Ordenar recursivamente la parte derecha
 */
void quicksortRecursivo(char *arr[], int inicio, int fin, int *intercambios) {
    // === CASO BASE ===
    // Si el segmento tiene 0 o 1 elemento, ya está ordenado
    if (inicio >= fin) {
        return;
    }
    
    // === CASO RECURSIVO ===
    // Particionar el arreglo y obtener la posición del pivote
    int pivoteIndex = particionar(arr, inicio, fin, intercambios);
    
    // Ordenar recursivamente los elementos izquierdos (menores que el pivote)
    quicksortRecursivo(arr, inicio, pivoteIndex - 1, intercambios);
    
    // Ordenar recursivamente los elementos derechos (mayores que el pivote)
    quicksortRecursivo(arr, pivoteIndex + 1, fin, intercambios);
}

/**
 * @brief Función wrapper para ordenar la biblioteca
 * 
 * @param libros Arreglo de títulos de libros
 * @param numLibros Número total de libros
 * @param intercambios Puntero al contador de intercambios
 */
void ordenarBiblioteca(char *libros[], int numLibros, int *intercambios) {
    if (numLibros <= 1) {
        return;
    }
    
    quicksortRecursivo(libros, 0, numLibros - 1, intercambios);
}

/**
 * @brief Imprime el contenido de la biblioteca
 * 
 * @param libros Arreglo de títulos
 * @param numLibros Número de libros
 */
void imprimirBiblioteca(char *libros[], int numLibros) {
    printf("[");
    for (int i = 0; i < numLibros; i++) {
        printf("\"%s\"", libros[i]);
        if (i < numLibros - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * @brief Versión con depuración paso a paso
 * 
 * Muestra el estado del arreglo después de cada partición
 * para entender cómo funciona la recursión.
 * 
 * @param libros Arreglo de títulos
 * @param inicio Inicio del segmento
 * @param fin Fin del segmento
 * @param profundidad Nivel de recursión (para indentación)
 * @param intercambios Puntero al contador
 * @return int Índice del pivote
 */
int particionarDebug(char *arr[], int inicio, int fin, 
                     int profundidad, int *intercambios) {
    
    // Imprimir indentación
    for (int i = 0; i < profundidad; i++) {
        printf("  ");
    }
    
    char *pivote = arr[fin];
    printf("Partición [%d..%d], pivote=\"%s\"\n", inicio, fin, pivote);
    
    int i = inicio - 1;
    
    for (int j = inicio; j <= fin - 1; j++) {
        for (int k = 0; k < profundidad; k++) {
            printf("  ");
        }
        printf("  Comparando \"%s\" con \"%s\"", arr[j], pivote);
        
        if (strcmp(arr[j], pivote) <= 0) {
            i++;
            if (i != j) {
                printf(" → intercambiar (menor o igual)");
                intercambiar(arr, i, j);
                (*intercambios)++;
                
                // Mostrar estado actual
                printf(" → ");
                for (int k = inicio; k <= fin; k++) {
                    printf("\"%s\" ", arr[k]);
                }
            } else {
                printf(" → ya está en posición");
            }
        } else {
            printf(" → es mayor, queda donde está");
        }
        printf("\n");
    }
    
    // Colocar pivote en posición correcta
    if (i + 1 != fin) {
        for (int k = 0; k < profundidad; k++) {
            printf("  ");
        }
        printf("  Moviendo pivote a posición %d\n", i + 1);
        intercambiar(arr, i + 1, fin);
        (*intercambios)++;
    }
    
    return i + 1;
}

/**
 * @brief Versión de depuración de Quicksort
 */
void quicksortDebug(char *arr[], int inicio, int fin, 
                    int profundidad, int *intercambios) {
    
    // Indentación
    for (int i = 0; i < profundidad; i++) {
        printf("  ");
    }
    printf("Quicksort [%d..%d]\n", inicio, fin);
    
    // Caso base
    if (inicio >= fin) {
        for (int i = 0; i < profundidad; i++) {
            printf("  ");
        }
        printf("→ Segmento trivial, retornar\n");
        return;
    }
    
    int pivoteIndex = particionarDebug(arr, inicio, fin, profundidad, intercambios);
    
    for (int i = 0; i < profundidad; i++) {
        printf("  ");
    }
    printf("Estado actual: ");
    for (int i = inicio; i <= fin; i++) {
        printf("\"%s\" ", arr[i]);
    }
    printf("\n");
    
    quicksortDebug(arr, inicio, pivoteIndex - 1, profundidad + 1, intercambios);
    quicksortDebug(arr, pivoteIndex + 1, fin, profundidad + 1, intercambios);
}

/**
 * @brief Función principal
 */
int main() {
    printf("=== ORDENAMIENTO DE BIBLIOTECA ===\n");
    printf("Método: Quicksort recursivo\n\n");
    
    // === CASO DE PRUEBA PROPORCIONADO ===
    char *libros1[] = {"Zoo", "Antología", "Bibliografía", "Científica", "Drama"};
    int numLibros1 = sizeof(libros1) / sizeof(libros1[0]);
    
    printf("Entrada:\n");
    imprimirBiblioteca(libros1, numLibros1);
    
    // Crear copia para no modificar el original
    char *copia1[MAX_LIBROS];
    for (int i = 0; i < numLibros1; i++) {
        copia1[i] = libros1[i];
    }
    
    int intercambios1 = 0;
    ordenarBiblioteca(copia1, numLibros1, &intercambios1);
    
    printf("\nSalida:\n");
    imprimirBiblioteca(copia1, numLibros1);
    printf("✓ Se ha podido ordenar el librero en %d pasos (intercambios)\n\n", 
           intercambios1);
    
    // === VERSIÓN CON DEPURACIÓN ===
    printf("=== PROCESO DETALLADO DE ORDENAMIENTO ===\n\n");
    
    char *libros2[] = {"Zoo", "Antología", "Bibliografía", "Científica", "Drama"};
    int numLibros2 = sizeof(libros2) / sizeof(libros2[0]);
    
    char *copia2[MAX_LIBROS];
    for (int i = 0; i < numLibros2; i++) {
        copia2[i] = libros2[i];
    }
    
    int intercambios2 = 0;
    quicksortDebug(copia2, 0, numLibros2 - 1, 0, &intercambios2);
    
    printf("\nResultado final: ");
    imprimirBiblioteca(copia2, numLibros2);
    printf("Total de intercambios: %d\n\n", intercambios2);
    
    // === PRUEBAS ADICIONALES ===
    printf("=== PRUEBAS ADICIONALES ===\n");
    
    // Prueba 1: Lista ya ordenada
    char *prueba1[] = {"A", "B", "C", "D"};
    int n1 = sizeof(prueba1) / sizeof(prueba1[0]);
    char *copiaP1[MAX_LIBROS];
    for (int i = 0; i < n1; i++) copiaP1[i] = prueba1[i];
    int inter1 = 0;
    ordenarBiblioteca(copiaP1, n1, &inter1);
    printf("\nLista ordenada [A,B,C,D]: %d intercambios (mínimo)\n", inter1);
    
    // Prueba 2: Lista inversa
    char *prueba2[] = {"D", "C", "B", "A"};
    int n2 = sizeof(prueba2) / sizeof(prueba2[0]);
    char *copiaP2[MAX_LIBROS];
    for (int i = 0; i < n2; i++) copiaP2[i] = prueba2[i];
    int inter2 = 0;
    ordenarBiblioteca(copiaP2, n2, &inter2);
    printf("Lista inversa [D,C,B,A]: %d intercambios\n", inter2);
    
    // Prueba 3: Libro repetido
    char *prueba3[] = {"Matemáticas", "Arte", "Matemáticas", "Física"};
    int n3 = sizeof(prueba3) / sizeof(prueba3[0]);
    char *copiaP3[MAX_LIBROS];
    for (int i = 0; i < n3; i++) copiaP3[i] = prueba3[i];
    int inter3 = 0;
    ordenarBiblioteca(copiaP3, n3, &inter3);
    printf("Con repeticiones: ");
    imprimirBiblioteca(copiaP3, n3);
    printf("  Intercambios: %d\n", inter3);
    
    return 0;
}
