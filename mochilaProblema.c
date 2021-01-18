// A Binary KnapSack(0-1) problem brute force solver 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct objects{
	double w; // peso objeto
	double v; // valor objeto
};
typedef struct data{
	int n; // quantidade itens
	double w; // peso maximo mochila
	struct objects *itens; // itens dos objetos lidos
	int* vsolution; //solucao a ser verificada
}data;
FILE* promptArchName(FILE* *arch){
	char archName[30]="mx.txt";
	printf("Digite o nome do arquivo: ");
	//scanf("%s",&archName[0]);
	printf("nome: %s\n",archName); // comentar dps
	*arch = fopen(archName, "r");
	return *arch;
}
int archToStruct(FILE* *archf, data* archd){
	fscanf(*(archf),"%lf",&archd->w);
	fscanf(*(archf),"%d",&archd->n);	
	
	printf("archd.w: %lf\narchd.n: %d\n",archd->w,archd->n); //comentar dps

	archd->itens = malloc(sizeof(struct objects)*archd->n);
	archd->vsolution = (int*)malloc(sizeof(int)*archd->n);

	for(int i = 0; i < archd->n; i++){
		fscanf(*(archf),"%lf %lf",&archd->itens[i].w,&archd->itens[i].v);
		printf("o[%d]: %lf %lf\n",i,archd->itens[i].w,archd->itens[i].v); // comentar dps
	}
	for(int i = 0; i < archd->n; i++){
		fscanf(*(archf),"%d",&archd->vsolution[i]);
		printf("vs[%d]: %d\n",i,archd->vsolution[i]); // comentar dps
	}
	return 1;
}
int all1(int *num, int num_digits){
    for(int i=0;i<num_digits+1;i++){
        if(num[i]!=1){
            return 0;
        }
    }
    return 1;
}
int plus1InBinary(int *num,int p){
    if(all1(num, p)){
        return 1;
    }
    if(num[p]==0){
        num[p]=1;
    }else if(num[p]==1){
        num[p]=0;
        plus1InBinary(num,p-1);
    }
    return 0;
}
double bestValuePossible(data *archd){
	double vbest=0, vaux=0, waux=0;
	int *combinations=(int*)malloc(sizeof(int)*archd->n); // um array representando em binario as combinacoes
	                                                      // dos itens possiveis
	long long unsigned int possibleComb = pow(2,archd->n);

	for(int i=0; i<(archd->n); i++){
		combinations[i]=0;
	}
	printf("Calculando melhor valor\npossibleComb: %lu\n",possibleComb);
	for(long long int i=0; i<possibleComb; i++, plus1InBinary(combinations,archd->n - 1)){
		for(int ii=0; ii<(archd->n); ii++){
			printf("%d ",combinations[ii]);
		}
		printf("|");

		vaux=0, waux=0;
		for(int j=0; j<archd->n; j++){
			if(combinations[j]==1){
				vaux+=archd->itens[j].v;
				waux+=archd->itens[j].w;
			}
		}
		printf("vaux: %lf, waux: %lf\n",vaux,waux);
		if(vaux >= vbest && waux <=archd->w){
			printf("Nova melhor Config encontrada: %lf, anterior: %lf, peso: %lf\n",vaux,vbest,waux); // comentar dps
			printf("Objetos: \n");
			for(int k=0;k<archd->n;k++){
				if(combinations[k]==1){
					printf("     ik: %d iw: %lf iv: %lf\n",
						k,
						archd->itens[k].w,
						archd->itens[k].v
					);
				}
			}
			vbest = vaux;
		}
	}
	return vbest;
}
int checkSolutionViability(data *archd){
	double wsum=0, vsum=0, vbest=bestValuePossible(archd);
	if(vbest<0){
		printf("vBest calculado deu negativo\n"); //comentar dps
		return 4;
	}
	for(int i=0;i<archd->n;i++){
		if(archd->vsolution[i]==1){
			wsum+=archd->itens[i].w;	
			vsum+=archd->itens[i].v;		
		}
	}
	if(wsum>archd->w){
		return 3; // solucao inviavel
	}
	if(vsum==vbest && wsum<=(archd->w)){
		return 0; // solucao otima
	}
	if(vsum<vbest && wsum<=(archd->w)){
		return 1; // solucao viavel mas nao otima
	}
	if(vsum>vbest){
		printf("nosso melhor vbest esta errado\n"); // comentar dps
		return 4; // nosso melhor valor esta errado
	}

	return 4; // 
}
int main () {
	FILE* archf; //archive file
	data archd; // archive data
	char buffer[500];

	if(promptArchName(&archf)==NULL){ // le o arquivo do diretorio
		printf("Sem arquivo\n"); //comentar dps
		return 0;
	}else{
		rewind(archf);
		printf("Lido\n");// comentar dps
	}

	if(archToStruct(&archf,&archd)){ // passa o arquivo lido para uma estrutura do programa
		printf("archToStruct OK\n"); // comentar dps
	}else{
		printf("archToStruct FAILED\n"); // comentar dps
	}

	switch(checkSolutionViability(&archd)){
		case 0:
			printf("Solucao otima.");
			break;
		case 1:
			printf("Solucao viavel mas nao otima.");
			break;
		case 3:
			printf("Solucao inviavel.");
			break;
		case 4:
			printf("Erro, indecindivel.");
	}

	fclose(archf);
	return 0;
}
