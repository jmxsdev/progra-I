#define EXIT_SUCCESS 0
#include <stdio.h>

int promedio_vector(int vec[], int cantidad, int media){
  if (cantidad == 1) {
    return vec[0];
  }else {
    int resultado = (vec[cantidad] + promedio_vector(vec, cantidad - 1, media) / media);
    return resultado;
  }
}

int main(int argc, char *argv[])
{
  int vec[4] = {2,2,2,2};
  int promedio = promedio_vector(vec, 3, 4);
  printf("El promedio es: %d\n", promedio);
  return EXIT_SUCCESS;
}
