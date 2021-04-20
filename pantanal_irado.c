#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void exibe_mtz(char mtz[2][94][94], int tam, int layer) {
	int i = 0, j = 0, k = tam;
	for (i = 0; i < tam; i++, k--) {
		for (j = 0; j < tam; j++) {
			printf("[%c] ", mtz[layer][i][j]);
		}
		printf("%d \n", k);
	}
	for (k = 1; (k <= 9) && (k <= tam); k++) {
		printf(" %d  ", k);
	}
	for (k = 10; k <= tam; k++) {
		printf(" %d ", k);
	}
}
void preenche_bombas(char mtz[2][94][94], int tam, int dif) {
	srand(time(0));
	int ry, rx;
	int qbombas;
	int tbombas;
	tbombas = (dif * 0.11) * tam * tam;
	for (qbombas = 0; qbombas < tbombas; ) {
		rx = (rand() % tam);
		ry = (rand() % tam);
		if (mtz[0][rx][ry] != 'B') {
			mtz[0][rx][ry] = 'B';
			qbombas++;
		}
	}
}
char analiza_celula(char mtz[2][94][94], int tam, int i, int j, char ch) {
	char bprox = 48;
	if (i == 0 && j == 0 && mtz[0][i][j] != ch) { //SUPERIOR ESQUERDO
		if (mtz[0][0][1] == ch) {
			bprox++;
		}
		if (mtz[0][1][1] == ch) {
			bprox++;
		}
		if (mtz[0][1][0] == ch) {
			bprox++;
		}
	}
	else if ((i == (tam - 1)) && (j == (tam - 1)) && (mtz[0][i][j] != ch)) { //INFERIOR DIREITO
		if (mtz[0][tam - 2][tam - 2] == ch) {
			bprox++;
		}
		if (mtz[0][tam - 2][tam - 1] == ch) {
			bprox++;
		}
		if (mtz[0][tam - 1][tam - 2] == ch) {
			bprox++;
		}
	}
	else if ((i == (tam - 1)) && (j == 0) && (mtz[0][i][j] != ch)) { //INFERIOR ESQUERDO
		if (mtz[0][tam - 2][0] == ch) {
			bprox++;
		}
		if (mtz[0][tam - 2][1] == ch) {
			bprox++;
		}
		if (mtz[0][tam - 1][1] == ch) {
			bprox++;
		}

	}
	else if ((i == 0) && (j == (tam - 1)) && (mtz[0][i][j] != ch)) { //SUPERIOR DIREITO
		if (mtz[0][0][tam - 2] == ch) {
			bprox++;
		}
		if (mtz[0][1][tam - 2] == ch) {
			bprox++;
		}
		if (mtz[0][1][tam - 1] == ch) {
			bprox++;
		}
	}
	else if ((j == 0) && (mtz[0][i][j] != ch)) { //lado esquerdo sem cantos
		if (mtz[0][i - 1][j + 1] == ch) {
			bprox++;
		}
		if (mtz[0][i][j + 1] == ch) {
			bprox++;
		}
		if (mtz[0][i + 1][j + 1] == ch) {
			bprox++;
		}
		if (mtz[0][i - 1][0] == ch) {
			bprox++;
		}
		if (mtz[0][i + 1][0] == ch) {
			bprox++;
		}
	}
	else if ((i == 0) && (mtz[0][i][j] != ch)) { //lado superior sem cantos
		if (mtz[0][1][j - 1] == ch) {
			bprox++;
		}
		if (mtz[0][1][j] == ch) {
			bprox++;
		}
		if (mtz[0][1][j + 1] == ch) {
			bprox++;
		}
		if (mtz[0][0][j - 1] == ch) {
			bprox++;
		}
		if (mtz[0][0][j + 1] == ch) {
			bprox++;
		}
	}
	else if ((j == (tam - 1)) && (mtz[0][i][j] != ch)) { //lado direito sem cantos
		if (mtz[0][i - 1][j - 1] == ch) {
			bprox++;
		}
		if (mtz[0][i][j - 1] == ch) {
			bprox++;
		}
		if (mtz[0][i + 1][j - 1] == ch) {
			bprox++;
		}
		if (mtz[0][i - 1][j] == ch) {
			bprox++;
		}
		if (mtz[0][i + 1][j] == ch) {
			bprox++;
		}
	}
	else if ((i == (tam - 1)) && (mtz[0][i][j] != ch)) { //lado inferior sem cantos;
		if (mtz[0][i - 1][j - 1] == ch) {
			bprox++;
		}
		if (mtz[0][i - 1][j] == ch) {
			bprox++;
		}
		if (mtz[0][i - 1][j + 1] == ch) {
			bprox++;
		}
		if (mtz[0][i][j - 1] == ch) {
			bprox++;
		}
		if (mtz[0][i][j + 1] == ch) {
			bprox++;
		}
	}
	else if (mtz[0][i][j] != ch) {
		if (mtz[0][i - 1][j - 1] == ch) {
			bprox++;
		}
		if (mtz[0][i - 1][j] == ch) {
			bprox++;
		}
		if (mtz[0][i - 1][j + 1] == ch) {
			bprox++;
		}
		if (mtz[0][i][j - 1] == ch) {
			bprox++;
		}
		if (mtz[0][i][j + 1] == ch) {
			bprox++;
		}
		if (mtz[0][i + 1][j - 1] == ch) {
			bprox++;
		}
		if (mtz[0][i + 1][j] == ch) {
			bprox++;
		}
		if (mtz[0][i + 1][j + 1] == ch) {
			bprox++;
		}
	}
	return bprox;
}
void analiza_prox(char mtz[2][94][94], int tam) {
	//mtz[0][1][1] = 'B';//testa o superior esquerdo
	//mtz[0][0][1] = 'B';
	//mtz[0][1][0] = 'B';
	//mtz[0][tam-2][tam-2] = 'B';//testa o inferior direito
	//mtz[0][tam-1][tam-2] = 'B';
	//mtz[0][tam-2][tam-1] = 'B';
	//mtz[0][tam - 2][0] = 'B';//testa o inferior esquerdo
	//mtz[0][tam - 2][1] = 'B';
	//mtz[0][tam - 1][1] = 'B';
	//mtz[0][0][tam - 2] = 'B';//testa o superior direito
	//mtz[0][1][tam - 2] = 'B';
	//mtz[0][1][tam - 1] = 'B';
	int i = 0, j = 0;
	char bprox;
	// 0 na ascii eh 48
	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			bprox = analiza_celula(mtz, tam, i, j, 'B');
			if (bprox != 48 && mtz[0][i][j] != 'B') {
				mtz[0][i][j] = bprox;
			}
			else if (mtz[0][i][j] != 'B') {
				mtz[0][i][j] = ' ';
			}
		}
	}
}
void preenche_selecionado(char mtz[2][94][94], int tam, char ch, int layer) {
	int i, j;
	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			mtz[layer][i][j] = ch;
		}
	}
}
void expandir_campo(char mtz[2][94][94], int rows, int columns, int tam) {
	if (  mtz[0][rows][columns] == ' ') {
		mtz[1][rows][columns] = ' ';
		mtz[0][rows][columns] = '-';

		if ((rows + 1) < tam) {
			if (mtz[1][rows + 1][columns] == '#') {
				mtz[1][rows + 1][columns]=mtz[0][rows + 1][columns];
			}
			expandir_campo(mtz, rows + 1, columns, tam);
		}
		if ((rows - 1) >= 0) {
			if (mtz[1][rows - 1][columns] == '#') {
				mtz[1][rows - 1][columns] = mtz[0][rows - 1][columns];
			}
			expandir_campo(mtz, rows - 1, columns, tam);
		}
		if ((columns + 1) < tam) {
			if (mtz[1][rows][columns + 1] == '#') {
				mtz[1][rows][columns +1 ] = mtz[0][rows][columns+1];
			}
			expandir_campo(mtz, rows, columns + 1, tam);
		}
		if ((columns - 1) >= 0) {
			if (mtz[1][rows][columns - 1] == '#') {
				mtz[1][rows][columns-1] = mtz[0][rows][columns-1];
			}
			expandir_campo(mtz, rows, columns - 1, tam);
		}
		if ((columns - 1) >= 0 && rows-1 >=0) {
			if (mtz[1][rows-1][columns - 1] == '#') {
				mtz[1][rows-1][columns - 1] = mtz[0][rows-1][columns - 1];
			}
			expandir_campo(mtz, rows-1, columns - 1, tam);
		}
		if ((columns - 1) >= 0 && rows+1<tam) {
			if (mtz[1][rows+1][columns - 1] == '#') {
				mtz[1][rows+1][columns - 1] = mtz[0][rows+1][columns - 1];
			}
			expandir_campo(mtz, rows+1, columns - 1, tam);
		}
		if ((rows - 1) >= 0 && columns+1<tam) {
			if (mtz[1][rows-1][columns + 1] == '#') {
				mtz[1][rows-1][columns + 1] = mtz[0][rows-1][columns + 1];
			}
			expandir_campo(mtz, rows-1, columns + 1, tam);
		}
		if ((columns + 1) <tam && rows+1<tam) {
			if (mtz[1][rows+1][columns + 1] == '#') {
				mtz[1][rows+1][columns + 1] = mtz[0][rows + 1][columns + 1];
			}
			expandir_campo(mtz, rows+1, columns + 1, tam);
		}
	}
}
//rx = (tam-rx) em y rows
//ry = ry em x columns
//apos modificação, rows eh o x cartesiano
//					columns eh o y cartesiano
void welcome() {
	printf("===================\n##--MINESWEEPER--##\n===================\nby: MTSM\n\n");
}
int win(char mtz[2][94][94], int tam, int dif) {
	int astk = 0;
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			if (mtz[1][i][j] == '#' ) {
				astk++;
			}
			if (mtz[0][i][j] == '-') {
				mtz[0][i][j] = ' ';
			}
		}
	}
	if (astk <= ((dif * 0.11) * tam * tam)) {
		return 1;
	}
	return 0;
}
int main() {
	char mtz[2][94][94];
	int rows = 0, columns = 0;
	int dif = 0, tam = 0;
	int gameover = 0;
	int moves = 0;
	welcome();
	printf("Size[max: 94] and Difficult[1 to 4]:\n");
	scanf("%d", &tam);
	scanf("%d", &dif);
	preenche_selecionado(mtz, tam, '#', 1);
	preenche_bombas(mtz, tam, dif);
	analiza_prox(mtz, tam);
	//exibe_mtz(mtz, tam, 0);

	for (gameover = 0; gameover == 0;) {
		system("clear");
		welcome();
		//exibe_mtz(mtz, tam, 0);
		//printf("\n\n");
		exibe_mtz(mtz, tam, 1);

		printf("\n");
		scanf("%d", &columns);
		scanf("%d", &rows);

		columns--; // eixo x cartesiano
		rows = (tam - rows); // eixo y cartesiano

		//printf("%d %d", rows, columns); //apos manipulacao

		if (mtz[0][rows][columns] == 'B') {
			gameover = 1;
			break;
		}
		else {
			mtz[1][rows][columns] = mtz[0][rows][columns];
			moves++;
			expandir_campo(mtz, rows, columns, tam);
		}
		if (win(mtz,tam,dif)) {
			break;
		}
	}
	if (gameover) {
		system("clear");
		welcome();
		exibe_mtz(mtz, tam, 0);
		printf("\nBOOM ! :(\n");
	}
	else {
		system("clear");
		welcome();
		exibe_mtz(mtz, tam, 1);
		printf("\nYOUR JOB HERE IS OVER !\nGO BACK TO YOUR FAMILY MY SON !\nTHANKS FOR YOUR SERVICE !\n");
	}
}


