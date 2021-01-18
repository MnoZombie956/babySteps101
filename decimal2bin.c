#include <stdio.h>

void dec2bin(int dec){
  dec/2>=1?dec2bin(dec/2):0;
  if(dec%2==0)
    printf("0");
  if(dec%2==1)
    printf("1");
}
int main(){
  int N=0;
  printf("Digite um numero inteiro: ");
  scanf("%d",&N);
  printf("Resultado: ");
  dec2bin(N);
  printf("\n");
}
