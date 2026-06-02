/**
 * @file quadtree.c
 * @brief Implementación recursiva para contar píxeles negros en un Quadtree
 * @author Asistente IA
 * @date 2026
 * 
 * Este programa lee una cadena que representa un quadtree y calcula
 * recursivamente el número total de píxeles negros en una imagen de 32x32.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Calcula recursivamente los píxeles negros en un quadtree
 * 
 * La función recorre la cadena del quadtree usando un índice pasado por referencia.
 * En cada nodo:
 * - Si es 'f': retorna el área total del cuadrante actual
 * - Si es 'e': retorna 0
 * - Si es 'p': suma recursivamente los resultados de sus 4 hijos
 * 
 * @param tree Cadena que representa el quadtree (ej: "ppeeefpffeefe")
 * @param index Índice actual en la cadena (se pasa por referencia para avanzar)
 * @param size Tamaño del cuadrante actual en píxeles (ancho o alto)
 * @return int Número de píxeles negros en el cuadrante actual
 * 
 * @note El parámetro size se reduce a la mitad en cada nivel recursivo
 * @note Cuando size=1, representa un solo píxel
 */
int countBlackPixels(const char *tree, int *index, int size) {
    // --- CASOS BASE ---
    
    // Caso base 1: Nodo 'f' (full) - todos los píxeles son negros
    if (tree[*index] == 'f') {
        // Avanzamos al siguiente carácter para la próxima llamada
        (*index)++;
        // El área total es size * size (píxeles negros en este cuadrante)
        return size * size;
    }
    
    // Caso base 2: Nodo 'e' (empty) - todos los píxeles son blancos
    if (tree[*index] == 'e') {
        // Avanzamos al siguiente carácter
        (*index)++;
        // No hay píxeles negros en este cuadrante
        return 0;
    }
    
    // --- CASO RECURSIVO: Nodo 'p' (parent) - tiene 4 hijos ---
    if (tree[*index] == 'p') {
        // Avanzamos al primer hijo
        (*index)++;
        
        // El nuevo tamaño para cada hijo es la mitad (porque dividimos el cuadrante)
        int childSize = size / 2;
        
        // Variable para acumular el total de píxeles negros de los 4 hijos
        int totalBlackPixels = 0;
        
        // --- Procesamos los 4 hijos recursivamente ---
        // Orden de los hijos según la figura: NO, NE, SO, SE
        // (Noroeste, Noreste, Suroeste, Sureste)
        
        // Hijo 1: Cuadrante Noroeste (top-left)
        totalBlackPixels += countBlackPixels(tree, index, childSize);
        
        // Hijo 2: Cuadrante Noreste (top-right)
        totalBlackPixels += countBlackPixels(tree, index, childSize);
        
        // Hijo 3: Cuadrante Suroeste (bottom-left)
        totalBlackPixels += countBlackPixels(tree, index, childSize);
        
        // Hijo 4: Cuadrante Sureste (bottom-right)
        totalBlackPixels += countBlackPixels(tree, index, childSize);
        
        // Retornamos la suma de los píxeles negros de los 4 cuadrantes
        return totalBlackPixels;
    }
    
    // Si llegamos aquí, hay un carácter inválido en la entrada
    // (esto no debería ocurrir si la entrada es válida)
    fprintf(stderr, "Error: Carácter inválido '%c' en el quadtree\n", tree[*index]);
    return -1;
}

/**
 * @brief Función wrapper que inicia el conteo de píxeles negros
 * 
 * @param tree Cadena que representa el quadtree
 * @return int Número total de píxeles negros en la imagen de 32x32
 */
int getBlackPixels(const char *tree) {
    int index = 0;  // Índice inicial en la cadena
    
    // La imagen es de 32x32 píxeles
    // El área total inicial es 32 * 32 = 1024 píxeles
    int imageSize = 32;
    
    return countBlackPixels(tree, &index, imageSize);
}

/**
 * @brief Versión alternativa con explicación paso a paso (para depuración)
 * 
 * @param tree Cadena del quadtree
 * @param index Índice actual (por referencia)
 * @param size Tamaño del cuadrante
 * @param depth Profundidad actual (para indentación en depuración)
 * @return int Número de píxeles negros
 */
int countBlackPixelsDebug(const char *tree, int *index, int size, int depth) {
    // Imprimir indentación según la profundidad
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    char nodeType = tree[*index];
    printf("Nodo: %c, Tamaño: %dx%d, Área: %d\n", 
           nodeType, size, size, size * size);
    
    // Caso base: f
    if (nodeType == 'f') {
        (*index)++;
        printf("%*s→ Cuadrante completamente negro: +%d píxeles\n", 
               depth * 2, "", size * size);
        return size * size;
    }
    
    // Caso base: e
    if (nodeType == 'e') {
        (*index)++;
        printf("%*s→ Cuadrante completamente blanco: +0 píxeles\n", 
               depth * 2, "");
        return 0;
    }
    
    // Caso recursivo: p
    if (nodeType == 'p') {
        (*index)++;
        int childSize = size / 2;
        printf("%*s→ Cuadrante mixto, dividiendo en 4 subcuadrantes de %dx%d\n", 
               depth * 2, "", childSize, childSize);
        
        int total = 0;
        
        // Procesar hijos (Noroeste, Noreste, Suroeste, Sureste)
        printf("%*s  Procesando Noroeste:\n", depth * 2, "");
        total += countBlackPixelsDebug(tree, index, childSize, depth + 1);
        
        printf("%*s  Procesando Noreste:\n", depth * 2, "");
        total += countBlackPixelsDebug(tree, index, childSize, depth + 1);
        
        printf("%*s  Procesando Suroeste:\n", depth * 2, "");
        total += countBlackPixelsDebug(tree, index, childSize, depth + 1);
        
        printf("%*s  Procesando Sureste:\n", depth * 2, "");
        total += countBlackPixelsDebug(tree, index, childSize, depth + 1);
        
        printf("%*s→ Total del cuadrante: %d píxeles negros\n", 
               depth * 2, "", total);
        
        return total;
    }
    
    return -1;
}

/**
 * @brief Función principal del programa
 * 
 * Lee una cadena del usuario, cuenta los píxeles negros usando recursión
 * y muestra el resultado.
 * 
 * @return int 0 si el programa termina correctamente
 */
int main() {
    char tree[1000];  // Buffer para almacenar la cadena del quadtree
    
    printf("=== CONTADOR DE PÍXELES NEGROS EN QUADTREE ===\n");
    printf("El quadtree representa una imagen de 32x32 píxeles (1024 total)\n");
    printf("Símbolos:\n");
    printf("  'p' = parent (nodo padre, tiene 4 hijos)\n");
    printf("  'f' = full (cuadrante completamente negro)\n");
    printf("  'e' = empty (cuadrante completamente blanco)\n");
    printf("\nEjemplo de entrada: ppeeefpffeefe\n");
    printf("Ejemplo de salida esperada: 448\n\n");
    
    while (1) {
        printf("Ingrese la representación del quadtree (o 'salir' para terminar): ");
        
        // Leer la línea completa
        fgets(tree, sizeof(tree), stdin);
        
        // Eliminar el carácter de nueva línea si está presente
        size_t len = strlen(tree);
        if (len > 0 && tree[len - 1] == '\n') {
            tree[len - 1] = '\0';
        }
        
        // Verificar si el usuario quiere salir
        if (strcmp(tree, "salir") == 0) {
            printf("¡Hasta luego!\n");
            break;
        }
        
        // Verificar que la cadena no esté vacía
        if (strlen(tree) == 0) {
            printf("Por favor ingrese una cadena válida.\n\n");
            continue;
        }
        
        // --- Versión normal (sin debug) ---
        int result = getBlackPixels(tree);
        printf("\nResultado (versión normal):\n");
        printf("Número de píxeles negros: %d\n", result);
        
        // --- Versión con depuración (opcional) ---
        printf("\n--- Proceso detallado (debug) ---\n");
        int index = 0;
        int debugResult = countBlackPixelsDebug(tree, &index, 32, 0);
        printf("--- Fin del proceso detallado ---\n");
        printf("Resultado (debug): %d\n\n", debugResult);
    }
    
    return 0;
}
