#include <stdio.h>

int fat(int n) {
  if (n == 1) {
    return 1;
  } else {
    return n*fat(n-1);
  }
}

int pot(int x, int n) {
  if(n == 0) {
    return 1;
  } else {
    return x * pot(x, n-1);
  }
}

float e(int x, int n) {
  if(n == 0) {
    return 1; 
  }
  else {
    return  e(x, n-1) + (float) pot(x, n)/fat(n);
  }
}


int main() {
  printf("%.20f", e(2, 27));
  // Maior valor com 21 casas decimais de precisao
  // Após o 27, o resultado começa a diminuir, o que não deveria acontecer
}