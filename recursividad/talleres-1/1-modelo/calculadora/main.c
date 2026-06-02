#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Función para encontrar la posición de un operador fuera de paréntesis
int find_operator(const char *expr, int start, int end, const char *operators) {
    int parentheses_count = 0;
    
    for (int i = end; i >= start; i--) {
        if (expr[i] == ')') parentheses_count++;
        else if (expr[i] == '(') parentheses_count--;
        else if (parentheses_count == 0) {
            // Buscar el operador en la cadena de operadores
            for (int j = 0; operators[j] != '\0'; j++) {
                if (expr[i] == operators[j]) {
                    return i;
                }
            }
        }
    }
    return -1;
}

// Función para evaluar una expresión simple (sin operadores)
double evaluate_simple(double a, double b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b != 0) return a / b;
            else {
                printf("Error: División por cero\n");
                exit(1);
            }
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Función recursiva principal
double evaluate_expression(const char *expr, int start, int end) {
    // Eliminar espacios
    while (start <= end && isspace(expr[start])) start++;
    while (end >= start && isspace(expr[end])) end--;
    
    if (start > end) return 0;
    
    // Caso base: expresión entre paréntesis
    if (expr[start] == '(' && expr[end] == ')') {
        // Verificar que sea un paréntesis que englobe toda la expresión
        int balance = 0;
        int is_balanced = 1;
        for (int i = start; i <= end; i++) {
            if (expr[i] == '(') balance++;
            else if (expr[i] == ')') balance--;
            if (balance == 0 && i < end) {
                is_balanced = 0;

            }
        }
        if (is_balanced) {
            return evaluate_expression(expr, start + 1, end - 1);
        }
    }
    
    // Buscar operadores por orden de precedencia (de menor a mayor)
    int pos;
    
    // Suma y resta (menor precedencia)
    pos = find_operator(expr, start, end, "+-");
    if (pos != -1) {
        double left = evaluate_expression(expr, start, pos - 1);
        double right = evaluate_expression(expr, pos + 1, end);
        return evaluate_simple(left, right, expr[pos]);
    }
    
    // Multiplicación y división
    pos = find_operator(expr, start, end, "*/");
    if (pos != -1) {
        double left = evaluate_expression(expr, start, pos - 1);
        double right = evaluate_expression(expr, pos + 1, end);
        return evaluate_simple(left, right, expr[pos]);
    }
    
    // Potencia (mayor precedencia)
    pos = find_operator(expr, start, end, "^");
    if (pos != -1) {
        double left = evaluate_expression(expr, start, pos - 1);
        double right = evaluate_expression(expr, pos + 1, end);
        return evaluate_simple(left, right, expr[pos]);
    }
    
    // Caso base: número
    char num_str[100];
    int j = 0;
    for (int i = start; i <= end; i++) {
        if (isdigit(expr[i]) || expr[i] == '.' || (i == start && expr[i] == '-')) {
            num_str[j++] = expr[i];
        }
    }
    num_str[j] = '\0';
    return atof(num_str);
}

// Función wrapper
double evaluate(const char *expression) {
    return evaluate_expression(expression, 0, strlen(expression) - 1);
}

// Función principal con ejemplos
int main() {
    char expression[200];
    
    printf("Calculadora recursiva de expresiones aritméticas\n");
    printf("Operadores soportados: +, -, *, /, ^\n");
    printf("Soporta paréntesis anidados\n");
    printf("Ejemplo: (2+3)*4, 2^3+1, ((2+3)*(4-1))\n\n");
    
    while (1) {
        printf("Ingrese expresión (o 'exit' para salir): ");
        fgets(expression, sizeof(expression), stdin);
        
        // Eliminar el salto de línea
        expression[strcspn(expression, "\n")] = '\0';
        
        if (strcmp(expression, "exit") == 0) {
            break;
        }
        
        double result = evaluate(expression);
        printf("Resultado: %.6f\n\n", result);
    }
    
    return 0;
}
