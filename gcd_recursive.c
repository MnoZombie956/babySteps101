#include <stdio.h>
int mdc(int a, int b){
    if(a==b)
        return b;/*euclides*/
    else
        return a > b ? mdc(a-b,b) : mdc(b-a,a);
}

int main(){
    int n1,n2;
    printf("Digite dois numeros inteiros: ");
    scanf("%d %d",&n1,&n2);
    printf("Resultado: %d", mdc(n1,n2));
    return 0;
}
