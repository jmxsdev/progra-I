#include <stdio.h>
#define EXIT_SUCCESS 0

void palindromo(char palabra[], int idx_inicio, int idx_final)
{
  if (idx_inicio >= idx_final) {
    printf("Es palindromo\n");
    return;
  }
  else if (palabra[idx_inicio] == palabra[idx_final]) {
    palindromo(palabra, idx_inicio + 1, idx_final - 1); 
  }else {
    printf("No es palindromo\n");
    return;
  }

}

int main(int argc, char *argv[])
{
  char palabra[] = "arepera";
  palindromo(palabra, 0, 6);
  return EXIT_SUCCESS;
}
