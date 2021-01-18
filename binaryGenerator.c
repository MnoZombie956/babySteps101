#include <stdio.h>
#define NUM_DIGITS 8 // How many bits you are going to generate. interval: [0,2^n[
//cuidado para nao  estourar o console do gdb
int all1(int *num){
    for(int i=0;i<NUM_DIGITS;i++){
        if(num[i]!=1){
            return 0;
        }
    }
    return 1;
}
int plus1(int *num,int p){
    if(all1(num)){
        return 1;
    }
    if(num[p]==0){
        num[p]=1;
    }else if(num[p]==1){
        num[p]=0;
        plus1(num,p-1);
    }
    return 0;
}
int main () {
    FILE* arch = fopen("gerado.txt","w");

    int num[NUM_DIGITS];
    int i=0;
    for(int i=0;i<NUM_DIGITS;i++){
        num[i]=0;
    }

    for(i=0;1;i++){
        for(int k=0;k<NUM_DIGITS;k++){
            fprintf(arch,"%d",num[k]);
            //printf("%d",num[k]);
        }
        fprintf(arch,"\n");
        //printf("\n");
        if(plus1(num,NUM_DIGITS-1)){
            break;
        }
    }
    
    printf("^- dec: %d\n",i);
}
