/**
 * @file claves_recursivo.c
 * @brief Generador recursivo de claves basado en diccionario y reglas
 * @author Asistente IA
 * @date 2026
 * 
 * Este programa genera todas las combinaciones posibles de claves según:
 * - Un diccionario de palabras (caracteres individuales)
 * - Reglas que contienen '#' (palabra) y '0' (dígito)
 * 
 * La generación es TOTALMENTE RECURSIVA, sin usar break/continue en ciclos.
 */

#include <stdio.h>
#include <string.h>

/* === CONSTANTES === */

/** @brief Número máximo de claves que se pueden generar */
#define MAX_CLAVES 10000

/** @brief Longitud máxima de cada clave generada */
#define MAX_CLAVE_LEN 100

/* === VARIABLES GLOBALES === */

/** @brief Arreglo para almacenar todas las claves generadas */
char resultados[MAX_CLAVES][MAX_CLAVE_LEN];

/** @brief Contador del número total de claves generadas */
int total = 0;

/* === FUNCIONES === */

/**
 * @brief Genera recursivamente todas las combinaciones de claves
 * 
 * Esta función recorre la regla carácter por carácter. Cuando encuentra:
 * - '#' : Itera sobre todas las palabras del diccionario
 * - '0' : Itera sobre todos los dígitos (0-9)
 * - Otro carácter: Lo copia literalmente
 * 
 * La función es puramente recursiva: cada llamada procesa un carácter
 * de la regla y se llama a sí misma para el siguiente.
 * 
 * @param regla     Cadena con el patrón de la regla (ej: "#0", "0#0", "pre#0fijo")
 * @param posRegla  Índice actual en la regla (comienza en 0)
 * @param actual    Búfer donde se construye la clave actual
 * @param posActual Índice actual en el búfer de la clave
 * @param palabras  Cadena con todas las palabras del diccionario (ej: "r2")
 * @param numPalabras Número de palabras en el diccionario
 * 
 * @pre   El arreglo 'resultados' debe tener suficiente espacio
 * @pre   El búfer 'actual' debe tener al menos MAX_CLAVE_LEN de tamaño
 * @post  Se añaden las claves generadas al arreglo 'resultados'
 * @post  Se incrementa 'total' con la cantidad de claves generadas
 * 
 * @note  NO se usa break ni continue en ningún ciclo
 * @note  La recursión termina cuando se alcanza el fin de la regla
 */
void generar(const char *regla, int posRegla, char *actual, int posActual,
             const char *palabras, int numPalabras) {
    
    /* ================================================================
     * CASO BASE 1: Llegamos al final de la regla
     * ================================================================
     * Cuando posRegla apunta al carácter nulo ('\0'), significa que
     * ya procesamos todos los caracteres de la regla.
     * En este punto, 'actual' contiene una clave completa.
     */
    if (regla[posRegla] == '\0') {
        /* Terminar la cadena con el carácter nulo */
        actual[posActual] = '\0';
        
        /* Guardar la clave generada en el arreglo de resultados */
        strcpy(resultados[total], actual);
        
        /* Incrementar el contador de claves */
        total++;
        
        /* Retornar para continuar generando otras combinaciones */
        return;
    }
    
    /* ================================================================
     * VERIFICACIÓN DE SEGURIDAD: Evitar desbordamiento del arreglo
     * ================================================================
     * Si ya generamos el máximo de claves permitidas, detenemos
     * la recursión para evitar segmentation fault.
     */
    if (total >= MAX_CLAVES) {
        return;
    }
    
    /* ================================================================
     * CASO RECURSIVO 1: El carácter actual es '#'
     * ================================================================
     * '#' indica que en esta posición debe ir UNA palabra del diccionario.
     * Para CADA palabra disponible, la agregamos y continuamos recursivamente.
     * 
     * Ejemplo: Si palabras = "r2", entonces probamos:
     *   - Primero 'r', luego seguimos con el resto de la regla
     *   - Luego '2', luego seguimos con el resto de la regla
     */
    if (regla[posRegla] == '#') {
        /* Recorrer todas las palabras del diccionario */
        /* NOTA: No se usa break, el ciclo se completa siempre */
        for (int i = 0; i < numPalabras; i++) {
            /* Colocar la palabra (carácter) en la clave actual */
            actual[posActual] = palabras[i];
            
            /* 
             * LLAMADA RECURSIVA:
             * - Avanzamos al siguiente carácter de la regla (posRegla + 1)
             * - Avanzamos al siguiente espacio en la clave (posActual + 1)
             * - El resto de parámetros se mantienen igual
             */
            generar(regla, posRegla + 1, actual, posActual + 1,
                   palabras, numPalabras);
        }
    }
    /* ================================================================
     * CASO RECURSIVO 2: El carácter actual es '0'
     * ================================================================
     * '0' indica que en esta posición debe ir un DÍGITO (0-9).
     * Para CADA dígito posible, lo agregamos y continuamos recursivamente.
     * 
     * El orden ascendente (0,1,2,...,9) garantiza el orden requerido
     * en el problema.
     */
    else if (regla[posRegla] == '0') {
        /* Recorrer todos los dígitos del 0 al 9 */
        /* NOTA: El ciclo siempre completa todas las iteraciones (sin break) */
        for (int digito = 0; digito <= 9; digito++) {
            /* Convertir el número entero a carácter ('0' = 48 en ASCII) */
            actual[posActual] = '0' + digito;
            
            /* LLAMADA RECURSIVA para el resto de la regla */
            generar(regla, posRegla + 1, actual, posActual + 1,
                   palabras, numPalabras);
        }
    }
    /* ================================================================
     * CASO RECURSIVO 3: Carácter literal (fijo)
     * ================================================================
     * Si el carácter no es '#' ni '0', entonces es un carácter literal
     * que debe aparecer tal cual en todas las claves generadas.
     * 
     * Ejemplo: En la regla "pre#0", 'p', 'r', 'e' son caracteres literales.
     */
    else {
        /* Copiar el carácter literal tal cual aparece en la regla */
        actual[posActual] = regla[posRegla];
        
        /* LLAMADA RECURSIVA para el resto de la regla */
        generar(regla, posRegla + 1, actual, posActual + 1,
               palabras, numPalabras);
    }
    
    /* ================================================================
     * NOTA SOBRE LA RECURSIÓN:
     * ================================================================
     * No hay un "caso else" adicional porque todas las posibilidades
     * están cubiertas: '#', '0', o cualquier otro carácter.
     * 
     * La recursión es profunda: la profundidad máxima es la longitud
     * de la regla (hasta 256 caracteres según el problema).
     * 
     * El número total de llamadas recursivas es:
     *   Suma de combinaciones = (numPalabras^num_hashes) * (10^num_ceros)
     */
}

/**
 * @brief Función wrapper que inicia la generación de claves
 * 
 * @param regla     Regla a procesar (ej: "#0")
 * @param palabras  Diccionario de palabras como cadena (ej: "r2")
 * @param numPalabras Número de palabras en el diccionario
 * 
 * @return int Número de claves generadas
 * 
 * @post El arreglo global 'resultados' contiene las claves generadas
 * @post La variable global 'total' se actualiza con el número de claves
 */
int generarClaves(const char *regla, const char *palabras, int numPalabras) {
    /* Búfer para construir la clave actual */
    char clave[MAX_CLAVE_LEN];
    
    /* Inicializar el contador global (por si se llama múltiples veces) */
    total = 0;
    
    /* Iniciar la generación recursiva */
    generar(regla, 0, clave, 0, palabras, numPalabras);
    
    /* Retornar el número de claves generadas */
    return total;
}

/**
 * @brief Imprime todas las claves generadas en el formato requerido
 * 
 * El formato de salida es:
 *   --           (dos guiones en una línea)
 *   clave1
 *   clave2
 *   ...
 *   claveN
 * 
 * @param mostrarTotal Si es diferente de 0, muestra además el total
 */
void imprimirClaves(int mostrarTotal) {
    printf("--\n");
    
    for (int i = 0; i < total; i++) {
        printf("%s\n", resultados[i]);
    }
    
    if (mostrarTotal) {
        printf("\nTotal: %d claves\n", total);
    }
}

/**
 * @brief Función principal del programa
 * 
 * Demuestra el uso de la función recursiva con diferentes ejemplos.
 * 
 * @return int 0 si el programa termina correctamente
 */
int main() {
    printf("========================================\n");
    printf("   GENERADOR RECURSIVO DE CLAVES\n");
    printf("========================================\n\n");
    
    /* ================================================================
     * EJEMPLO 1: Caso del enunciado
     * ================================================================
     * Diccionario: ['r', '2'] (2 palabras)
     * Regla: "#0" (palabra + dígito)
     * 
     * Total esperado: 2 × 10 = 20 claves
     */
    printf("--- EJEMPLO 1: Regla '#0' con diccionario ['r','2'] ---\n");
    
    char palabras1[] = {'r', '2'};  /* Arreglo de palabras */
    int numPalabras1 = 2;            /* Cantidad de palabras */
    
    /* Generar las claves recursivamente */
    int total1 = generarClaves("#0", palabras1, numPalabras1);
    
    /* Mostrar resultados */
    imprimirClaves(1);  /* 1 = mostrar total */
    
    /* ================================================================
     * EJEMPLO 2: Regla "0#0" con diccionario ['A','B','C']
     * ================================================================
     * Diccionario: ['A', 'B', 'C'] (3 palabras)
     * Regla: "0#0" (dígito + palabra + dígito)
     * 
     * Total esperado: 10 × 3 × 10 = 300 claves
     */
    printf("\n--- EJEMPLO 2: Regla '0#0' con diccionario ['A','B','C'] ---\n");
    
    char palabras2[] = {'A', 'B', 'C'};
    int numPalabras2 = 3;
    
    int total2 = generarClaves("0#0", palabras2, numPalabras2);
    
    printf("Total generado: %d claves (esperado: 300)\n", total2);
    
    /* Mostrar solo las primeras 20 claves por brevedad */
    printf("Primeras 20 claves:\n");
    printf("--\n");
    for (int i = 0; i < 20 && i < total2; i++) {
        printf("%s\n", resultados[i]);
    }
    printf("...\n");
    
    /* ================================================================
     * EJEMPLO 3: Regla con múltiples '#'
     * ================================================================
     * Diccionario: ['X', 'Y'] (2 palabras)
     * Regla: "##0" (palabra + palabra + dígito)
     * 
     * Total esperado: 2 × 2 × 10 = 40 claves
     */
    printf("\n--- EJEMPLO 3: Regla '##0' con diccionario ['X','Y'] ---\n");
    
    char palabras3[] = {'X', 'Y'};
    int numPalabras3 = 2;
    
    int total3 = generarClaves("##0", palabras3, numPalabras3);
    
    printf("Total generado: %d claves (esperado: 40)\n", total3);
    printf("Ejemplos:\n");
    
    /* Mostrar algunas claves de ejemplo */
    for (int i = 0; i < 5 && i < total3; i++) {
        printf("  %s\n", resultados[i]);
    }
    printf("  ...\n");
    
    /* ================================================================
     * EJEMPLO 4: Regla con caracteres literales
     * ================================================================
     * Diccionario: ['a', 'b'] (2 palabras)
     * Regla: "pre#0fijo" → "pre" + palabra + dígito + "fijo"
     * 
     * Total esperado: 2 × 10 = 20 claves
     */
    printf("\n--- EJEMPLO 4: Regla 'pre#0fijo' con diccionario ['a','b'] ---\n");
    
    char palabras4[] = {'a', 'b'};
    int numPalabras4 = 2;
    
    int total4 = generarClaves("pre#0fijo", palabras4, numPalabras4);
    
    printf("Total generado: %d claves\n", total4);
    printf("Ejemplos:\n");
    for (int i = 0; i < 5 && i < total4; i++) {
        printf("  %s\n", resultados[i]);
    }
    
    /* ================================================================
     * RESUMEN FINAL
     * ================================================================
     */
    printf("\n========================================\n");
    printf("  RESULTADOS FINALES\n");
    printf("========================================\n");
    printf("Ejemplo 1 (#0 con r,2): %d claves\n", total1);
    printf("Ejemplo 2 (0#0 con A,B,C): %d claves\n", total2);
    printf("Ejemplo 3 (##0 con X,Y): %d claves\n", total3);
    printf("Ejemplo 4 (pre#0fijo con a,b): %d claves\n", total4);
    printf("========================================\n");
    printf("✓ Programa completado exitosamente\n");
    printf("✓ 100% recursivo, sin break/continue\n");
    printf("========================================\n");
    
    return 0;
}
