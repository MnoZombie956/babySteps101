#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_DIGITS 35661	// 1000! + 1

void printAns(int *num,int numT){
  //printf("ANSWERR\n\n");
  for(int i=numT; i>=0; i--){printf ("%d", num[i]);}
  //printf("\n\n");
}

void multiplyStringByNumber(int *string, int *strSize,int num){
  int carry=0, flashP=0, digits=0;
  int flashAns[NUM_DIGITS];
  for(; digits<=*strSize; digits++){//i nao reseta
    flashAns[digits]=string[digits];//transcreve antes
    flashP=flashAns[digits]*num+carry;//atualiza flashP
    string[digits]=flashP%10;//pega o primeiro flashP
    carry=flashP/10;//segundo
  }
  if(carry!=0)//continua carry
    for(; carry!=0; carry/=10,digits++){
      string[digits]=carry%10;
    }
  *strSize=digits-1;
}


void doBigFactorial(int num){
  int ans[NUM_DIGITS], ansTam=0;
  for(int i=1; i<=NUM_DIGITS-1; i++)
    ans[i]=0;
  ans[0]=1;
  for(int i=2; i<=num; i++){
    //printf("multi by %d\n",i);
    multiplyStringByNumber(ans,&ansTam,i);
  }
  printAns(ans,ansTam);
}

int main(){
  int num;
  //int quickString[]={'6','5','1','5','1','4'};

  printf("Digite um numero inteiro: ");
  scanf("%d", &num);

  printf("Resultado: ");
  doBigFactorial(num);
}
