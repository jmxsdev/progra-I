#include <stdio.h>
#define EXIT_SUCCESS 0

void decimal_binario(int divisor){
  if (divisor <= 3) {
    int modulo = divisor % 2;
    int residuo = divisor / 2;
    printf("El binario seria: %d%d",modulo,residuo);
  }
  else {
    decimal_binario(divisor / 2);
    printf("%d", divisor % 2);
  }
}



int main()
{
  decimal_binario(1422);
  printf("\n");
  return EXIT_SUCCESS;
}
