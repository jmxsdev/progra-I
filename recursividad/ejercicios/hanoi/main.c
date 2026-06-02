#include <stdio.h>
#define MAX 20

// Estructura que representa un poste (palo)
typedef struct {
    int discos[MAX];  // arreglo de discos (base en índice 0, tope en el último ocupado)
    int tope;         // índice del último elemento (-1 si está vacío)
} Poste;

// Inicializar un poste vacío
void inicializar_poste(Poste *p) {
    p->tope = -1;
}

// Verificar si un poste está vacío
int esta_vacio(Poste *p) {
    return p->tope == -1;
}

// Verificar si un poste está lleno
int esta_lleno(Poste *p) {
    return p->tope == MAX - 1;
}

// Obtener el disco en el tope (sin quitarlo)
int ver_tope(Poste *p) {
    if (esta_vacio(p)) return -1;
    return p->discos[p->tope];
}

// Apilar un disco en el poste (lo pone en el tope)
void apilar(Poste *p, int disco) {
    if (esta_lleno(p)) {
        printf("Error: poste lleno\n");
        return;
    }
    p->tope++;
    p->discos[p->tope] = disco;
}

// Desapilar el disco del tope y retornarlo
int desapilar(Poste *p) {
    if (esta_vacio(p)) {
        printf("Error: poste vacio\n");
        return -1;
    }
    int disco = p->discos[p->tope];
    p->tope--;
    return disco;
}

// Mover un disco desde un poste origen a un poste destino
// Retorna 1 si el movimiento es válido, 0 si no
int mover_disco(Poste *origen, Poste *destino, char nombre_origen, char nombre_destino) {
    if (esta_vacio(origen)) {
        printf("Movimiento invalido: poste %c esta vacio\n", nombre_origen);
        return 0;
    }
    
    int disco_origen = ver_tope(origen);
    int disco_destino = ver_tope(destino);
    
    if (!esta_vacio(destino) && disco_origen > disco_destino) {
        printf("Movimiento invalido: no se puede poner disco %d sobre disco %d\n", 
               disco_origen, disco_destino);
        return 0;
    }
    
    // Realizar el movimiento
    int disco = desapilar(origen);
    apilar(destino, disco);
    printf("Mover disco %d de %c a %c\n", disco, nombre_origen, nombre_destino);
    return 1;
}

// Función recursiva de las Torres de Hanoi
// n: número de discos a mover
// origen: poste de donde se mueven
// destino: poste a donde se mueven
// auxiliar: poste auxiliar
// nom_o, nom_d, nom_a: nombres para imprimir (ej: 'A', 'B', 'C')
void hanoi(int n, Poste *origen, Poste *destino, Poste *auxiliar,
           char nom_o, char nom_d, char nom_a) {
    // CASO BASE: mover un solo disco
    if (n == 1) {
        mover_disco(origen, destino, nom_o, nom_d);
        return;
    }
    
    // PASO RECURSIVO
    // 1. Mover n-1 discos de origen a auxiliar (usando destino como apoyo)
    hanoi(n - 1, origen, auxiliar, destino, nom_o, nom_a, nom_d);
    
    // 2. Mover el disco más grande de origen a destino
    mover_disco(origen, destino, nom_o, nom_d);
    
    // 3. Mover n-1 discos de auxiliar a destino (usando origen como apoyo)
    hanoi(n - 1, auxiliar, destino, origen, nom_a, nom_d, nom_o);
}

// Función para mostrar el estado actual de los tres postes
void mostrar_estado(Poste *A, Poste *B, Poste *C, char nombreA, char nombreB, char nombreC) {
    printf("\n--- Estado actual ---\n");
    
    printf("Poste %c: ", nombreA);
    if (esta_vacio(A)) printf("vacio");
    else {
        for (int i = 0; i <= A->tope; i++) {
            printf("%d ", A->discos[i]);
        }
    }
    printf("\n");
    
    printf("Poste %c: ", nombreB);
    if (esta_vacio(B)) printf("vacio");
    else {
        for (int i = 0; i <= B->tope; i++) {
            printf("%d ", B->discos[i]);
        }
    }
    printf("\n");
    
    printf("Poste %c: ", nombreC);
    if (esta_vacio(C)) printf("vacio");
    else {
        for (int i = 0; i <= C->tope; i++) {
            printf("%d ", C->discos[i]);
        }
    }
    printf("\n\n");
}

int main() {
    Poste A, B, C;
    int n;
    
    // Inicializar los tres postes
    inicializar_poste(&A);
    inicializar_poste(&B);
    inicializar_poste(&C);
    
    // Pedir número de discos
    printf("Ingrese el numero de discos: ");
    scanf("%d", &n);
    
    // Inicializar el poste A con los discos (el más grande abajo)
    // Para que [1,2,3,4,5] funcione, asumimos que 1 es el más pequeño, n es el más grande
    // Los apilamos de manera que el más grande quede abajo (índice 0) y el más pequeño arriba (tope)
    printf("Inicializando poste A con discos del 1 (pequeno) al %d (grande)\n", n);
    for (int i = n; i >= 1; i--) {
        apilar(&A, i);
    }
    
    printf("\nEstado inicial:\n");
    mostrar_estado(&A, &B, &C, 'A', 'B', 'C');
    
    printf("\nResolviendo Torres de Hanoi para %d discos:\n", n);
    hanoi(n, &A, &B, &C, 'A', 'C', 'B');
    
    printf("\nEstado final:\n");
    mostrar_estado(&A, &B, &C, 'A', 'B', 'C');
    
    return 0;
}
