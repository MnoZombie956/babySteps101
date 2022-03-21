// triangulo de pascal
#include <stdlib.h>
#include <stdio.h>
#define N_LINHAS 20
#define NUM 20
//Depois de 20 estoura
unsigned long long int factorial(int n){
    if (n >= 1)
        return n*factorial(n-1);
    else
        return 1;
}
unsigned long long int combination(int n, int p){
    unsigned long long int res=factorial(n)/(factorial(n-p)*factorial(p));
    return res;
}
int main () {
    for(int n=0;n<N_LINHAS+1;n++){
        printf("%dº# ",n);
        for(int p=0;p<=n;p++){
            printf("%llu ",combination(n,p));
        }
        printf("\n");
    }
    printf("fatorial de %d: %llu",NUM,factorial(NUM));
}
