/**
 * @file restaurante.c
 * @brief Asignación recursiva de mesas para maximizar grupos atendidos
 * @author Asistente IA
 * @date 2026
 * 
 * Este programa resuelve el problema de asignar grupos de clientes a mesas
 * de capacidad fija (4 personas) para maximizar la cantidad de grupos atendidos.
 */

#include <stdio.h>

/**
 * @brief Ordena un arreglo de enteros usando recursión (sin bucles)
 * 
 * @param arr Arreglo a ordenar
 * @param n Tamaño del arreglo
 * @note Usa selección recursiva para evitar ciclos con break/continue
 */
void ordenarRecursivo(int *arr, int n) {
    // Caso base: arreglo de tamaño 0 o 1 ya está ordenado
    if (n <= 1) {
        return;
    }
    
    // Encontrar el índice del mínimo elemento (sin usar break)
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
        // No se usa break ni continue
    }
    
    // Intercambiar el mínimo con el primer elemento
    if (minIndex != 0) {
        int temp = arr[0];
        arr[0] = arr[minIndex];
        arr[minIndex] = temp;
    }
    
    // Ordenar recursivamente el resto del arreglo
    ordenarRecursivo(arr + 1, n - 1);
}

/**
 * @brief Función recursiva principal para maximizar grupos atendidos
 * 
 * @param grupos Arreglo con los tamaños de los grupos
 * @param n Número total de grupos
 * @param idx Índice actual en el arreglo de grupos
 * @param mesasDisponibles Número de mesas libres en este momento
 * @param capacidadMesa Capacidad máxima por mesa (4 personas)
 * @return int Máximo número de grupos que se pueden atender desde esta posición
 * 
 * @details Esta función explora todas las combinaciones posibles usando:
 *          - Si el grupo actual cabe y hay mesas: intenta asignarlo
 *          - Siempre considera no asignar el grupo actual
 *          - Toma la mejor opción entre ambas
 */
int maximizarGrupos(const int *grupos, int n, int idx, 
                    int mesasDisponibles, int capacidadMesa) {
    
    // === CASOS BASE ===
    
    // Caso base 1: No quedan grupos por procesar
    if (idx >= n) {
        return 0;
    }
    
    // Caso base 2: No hay mesas disponibles
    if (mesasDisponibles == 0) {
        return 0;
    }
    
    // Caso base 3: El grupo actual es demasiado grande para la capacidad de la mesa
    if (grupos[idx] > capacidadMesa) {
        // Este grupo no se puede asignar, pasar al siguiente
        return maximizarGrupos(grupos, n, idx + 1, 
                              mesasDisponibles, capacidadMesa);
    }
    
    // === CASO RECURSIVO ===
    
    // Opción 1: NO asignar el grupo actual
    // Simplemente avanzamos al siguiente grupo
    int noAsignar = maximizarGrupos(grupos, n, idx + 1, 
                                   mesasDisponibles, capacidadMesa);
    
    // Opción 2: ASIGNAR el grupo actual
    // Requiere: grupo cabe y hay mesas disponibles
    int asignar = 1 + maximizarGrupos(grupos, n, idx + 1, 
                                     mesasDisponibles - 1, capacidadMesa);
    
    // Retornar la mejor opción (la que maximiza la cantidad de grupos)
    if (asignar >= noAsignar) {
        return asignar;
    } else {
        return noAsignar;
    }
}

/**
 * @brief Versión optimizada con poda recursiva
 * 
 * @param grupos Arreglo ordenado de grupos (menor a mayor)
 * @param n Número total de grupos
 * @param idx Índice actual
 * @param mesasDisponibles Mesas libres
 * @param capacidadMesa Capacidad de cada mesa (4)
 * @param mejorActual Mejor resultado encontrado hasta ahora (para poda)
 * @return int Máximo de grupos atendidos
 */
int maximizarGruposPoda(const int *grupos, int n, int idx, 
                        int mesasDisponibles, int capacidadMesa, 
                        int mejorActual) {
    
    // Casos base (igual que antes)
    if (idx >= n || mesasDisponibles == 0) {
        return 0;
    }
    
    // Poda: Si ya superamos el mejor resultado, no seguimos
    if (mejorActual > mesasDisponibles) {
        return 0;
    }
    
    if (grupos[idx] > capacidadMesa) {
        return maximizarGruposPoda(grupos, n, idx + 1, 
                                  mesasDisponibles, capacidadMesa, 
                                  mejorActual);
    }
    
    int noAsignar = maximizarGruposPoda(grupos, n, idx + 1, 
                                       mesasDisponibles, capacidadMesa, 
                                       mejorActual);
    
    int asignar = 1 + maximizarGruposPoda(grupos, n, idx + 1, 
                                         mesasDisponibles - 1, 
                                         capacidadMesa, mejorActual);
    
    if (asignar >= noAsignar) {
        return asignar;
    } else {
        return noAsignar;
    }
}

/**
 * @brief Función wrapper para resolver el problema
 * 
 * @param grupos Arreglo con tamaños de grupos
 * @param numGrupos Número total de grupos
 * @param numMesas Número de mesas disponibles
 * @param capacidadMesa Capacidad máxima por mesa (default 4)
 * @return int Número máximo de grupos que pueden ser atendidos
 */
int resolverRestaurante(int *grupos, int numGrupos, 
                        int numMesas, int capacidadMesa) {
    
    // Paso 1: Ordenar grupos de menor a mayor (estrategia greedy para optimizar)
    // Ordenamos porque es mejor asignar grupos pequeños primero
    ordenarRecursivo(grupos, numGrupos);
    
    printf("Grupos ordenados: ");
    for (int i = 0; i < numGrupos; i++) {
        printf("%d ", grupos[i]);
    }
    printf("\n");
    
    // Paso 2: Llamar a la función recursiva
    return maximizarGrupos(grupos, numGrupos, 0, 
                          numMesas, capacidadMesa);
}

/**
 * @brief Versión con seguimiento detallado para depuración
 * 
 * @param grupos Arreglo ordenado de grupos
 * @param n Total de grupos
 * @param idx Índice actual
 * @param mesasDisponibles Mesas libres
 * @param capacidadMesa Capacidad de la mesa
 * @param profundidad Nivel de recursión (para indentación)
 * @return int Máximo de grupos atendidos
 */
int maximizarGruposDebug(const int *grupos, int n, int idx, 
                         int mesasDisponibles, int capacidadMesa, 
                         int profundidad) {
    
    // Imprimir indentación
    for (int i = 0; i < profundidad; i++) {
        printf("  ");
    }
    
    printf("Evaluando grupo[%d]=%d (mesas=%d)\n", 
           idx, idx < n ? grupos[idx] : -1, mesasDisponibles);
    
    // Casos base
    if (idx >= n) {
        printf("%*s→ No hay más grupos, retorna 0\n", profundidad * 2, "");
        return 0;
    }
    
    if (mesasDisponibles == 0) {
        printf("%*s→ No hay mesas disponibles, retorna 0\n", profundidad * 2, "");
        return 0;
    }
    
    if (grupos[idx] > capacidadMesa) {
        printf("%*s→ Grupo %d excede capacidad (%d > %d), se omite\n", 
               profundidad * 2, "", grupos[idx], grupos[idx], capacidadMesa);
        return maximizarGruposDebug(grupos, n, idx + 1, 
                                   mesasDisponibles, capacidadMesa, 
                                   profundidad + 1);
    }
    
    // Opción 1: No asignar
    printf("%*s--- Opción: NO asignar grupo %d ---\n", 
           profundidad * 2, "", grupos[idx]);
    int noAsignar = maximizarGruposDebug(grupos, n, idx + 1, 
                                        mesasDisponibles, capacidadMesa, 
                                        profundidad + 1);
    
    // Opción 2: Asignar
    printf("%*s--- Opción: ASIGNAR grupo %d (usa 1 mesa) ---\n", 
           profundidad * 2, "", grupos[idx]);
    int asignar = 1 + maximizarGruposDebug(grupos, n, idx + 1, 
                                          mesasDisponibles - 1, 
                                          capacidadMesa, profundidad + 1);
    
    // Comparar resultados
    int resultado;
    if (asignar >= noAsignar) {
        resultado = asignar;
        printf("%*s✓ Mejor: ASIGNAR (%d > %d)\n", 
               profundidad * 2, "", asignar, noAsignar);
    } else {
        resultado = noAsignar;
        printf("%*s✓ Mejor: NO ASIGNAR (%d > %d)\n", 
               profundidad * 2, "", noAsignar, asignar);
    }
    
    return resultado;
}

/**
 * @brief Función principal del programa
 */
int main() {
    // === CASO DE PRUEBA PROPORCIONADO ===
    printf("=== PROBLEMA DE ASIGNACIÓN DE MESAS ===\n");
    printf("Capacidad por mesa: 4 personas\n\n");
    
    int numMesas = 6;
    int gruposInicial[] = {2, 3, 4, 1, 5};
    int numGrupos = sizeof(gruposInicial) / sizeof(gruposInicial[0]);
    
    printf("Entrada:\n");
    printf("  Mesas disponibles: %d\n", numMesas);
    printf("  Grupos: ");
    for (int i = 0; i < numGrupos; i++) {
        printf("%d ", gruposInicial[i]);
    }
    printf("\n\n");
    
    // Copiar arreglo para no modificar el original
    int grupos[100];
    for (int i = 0; i < numGrupos; i++) {
        grupos[i] = gruposInicial[i];
    }
    
    // Resolver el problema
    int resultado = resolverRestaurante(grupos, numGrupos, numMesas, 4);
    
    printf("\nResultado:\n");
    printf("  Máximo de grupos atendidos: %d\n", resultado);
    printf("  (Esperado: 4)\n\n");
    
    // === VERSIÓN CON DEPURACIÓN ===
    printf("=== PROCESO DETALLADO DE RECURSIÓN ===\n");
    
    // Reordenar grupos nuevamente para debug
    int gruposDebug[] = {2, 3, 4, 1, 5};
    ordenarRecursivo(gruposDebug, numGrupos);
    
    printf("Árbol de decisión (DFS):\n");
    int resultadoDebug = maximizarGruposDebug(gruposDebug, numGrupos, 0, 
                                              numMesas, 4, 0);
    
    printf("\nResultado final: %d grupos atendidos\n", resultadoDebug);
    
    // === PRUEBAS ADICIONALES ===
    printf("\n=== PRUEBAS ADICIONALES ===\n");
    
    // Prueba 1: Todos los grupos caben
    int prueba1[] = {1, 2, 1, 2};
    int grupos1[4];
    for (int i = 0; i < 4; i++) grupos1[i] = prueba1[i];
    printf("\nPrueba 1 - Grupos [1,2,1,2], Mesas=4:\n");
    printf("  Resultado: %d\n", resolverRestaurante(grupos1, 4, 4, 4));
    printf("  Esperado: 4 (todos caben)\n");
    
    // Prueba 2: Grupos muy grandes
    int prueba2[] = {5, 6, 4, 3};
    int grupos2[4];
    for (int i = 0; i < 4; i++) grupos2[i] = prueba2[i];
    printf("\nPrueba 2 - Grupos [5,6,4,3], Mesas=3:\n");
    printf("  Resultado: %d\n", resolverRestaurante(grupos2, 4, 3, 4));
    printf("  Esperado: 2 (solo 4 y 3, o 3 y 4)\n");
    
    // Prueba 3: Sin mesas
    int prueba3[] = {1, 2, 3};
    int grupos3[3];
    for (int i = 0; i < 3; i++) grupos3[i] = prueba3[i];
    printf("\nPrueba 3 - Grupos [1,2,3], Mesas=0:\n");
    printf("  Resultado: %d\n", resolverRestaurante(grupos3, 3, 0, 4));
    printf("  Esperado: 0\n");
    
    return 0;
}
