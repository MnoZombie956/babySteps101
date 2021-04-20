#include <iostream>
#define TAM 25
using namespace std;
void exibe_mtz(char mtz[64][64],int tam){
    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            printf("%c ",mtz[i][j]);
        }
        printf("\n");
    }
}
void preenche(char mtz[64][64],int tam,char ch){
    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            mtz[i][j]=ch;
        }
    }
}
void preenche_bombas(char mtz[64][64], int tam, int dif) {
	srand(time(0));
	int ry, rx;
	int qbombas;
	int tbombas;
	tbombas = (dif * 0.11) * tam *tam;
	for (qbombas = 0; qbombas < tbombas; ) {
		rx = (rand() % tam) ;
		ry = (rand() % tam) ;
		if (mtz[rx][ry] != '1') {
			mtz[rx][ry] = '1';
			qbombas++;
		}
	}
}
unsigned long long int i,j=0;
void expandir_campo(char mtz[64][64], int rows, int columns, int tam) {
    i++;
    system("clear");
    exibe_mtz(mtz,TAM);
    printf("\nident:%llu desc:%llu\n",i,j);
	if (mtz[rows][columns] == ' ') {
	    j++;
		mtz[rows][columns] = '~';
		if ((rows+1)<tam) {
			expandir_campo(mtz, rows + 1, columns, tam);

		}
		if ((rows - 1)>=0) {
			expandir_campo(mtz, rows - 1, columns, tam);

		}
		if ((columns + 1)<tam) {
			expandir_campo(mtz, rows, columns + 1, tam);
		}
		if ((columns - 1) >= 0) {
			expandir_campo(mtz, rows, columns - 1, tam);

		}
	}
}
int main(){
    char mtz[64][64];
    preenche(mtz,TAM,' ');
    preenche_bombas(mtz,TAM,4);
    exibe_mtz(mtz,TAM);
    do{
        scanf("%d %d",&i,&j);
        expandir_campo(mtz,i,j,TAM);
    }while(1);
    return 0;
}




