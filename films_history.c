#include <stdlib.h>
#include <stdio.h>
typedef struct cinema {
	char nome[40];
	char estilo[40];
	int ano;
	int duration;
}cinema;
int main() {
	cinema* filme;
	int qnt_filmes = 0;
	int i = 0, j = 0, k = 0;
	int option = 0;
    char ch;
	FILE* arquivotxt;
	FILE* arquivobin;

	printf("Gravar filme (1), exibir filmes (2)\n");
	scanf("%d", &option);

	switch (option) {
		case 1: {
		    arquivotxt = fopen("ja_assistitxt", "a");
		    arquivobin = fopen("ja_assistibin", "ab");
			printf("Quantos filmes ?\n");
			scanf("%d", &qnt_filmes);

			filme = malloc(sizeof(cinema) * qnt_filmes);

			for (i = 0; i < qnt_filmes; i++) {
				printf("nome[%d]:\n",i+1);
				//scanf("%[^\n]s", filme[i].nome);
				getchar();
				gets(filme[i].nome);
				
				printf("estilo[%d]:\n", i + 1);
				//scanf("%[^\n]s", filme[i].estilo);
				gets(filme[i].estilo);
		
				printf("ano[%d]:\n", i + 1);
				scanf("%d", &filme[i].ano);
		
				printf("duracao[%d](min):\n", i + 1);
				scanf("%d", &filme[i].duration);

				fwrite(filme[i].nome,sizeof(char),40,arquivobin);
				fwrite(filme[i].estilo,sizeof(char),40,arquivobin);
				fwrite(&filme[i].ano,sizeof(int),1,arquivobin);
				fwrite(&filme[i].duration,sizeof(int),1,arquivobin);

				fprintf(arquivotxt, "%s\n", filme[i].nome);
				fprintf(arquivotxt, "%s\n", filme[i].estilo);
				fprintf(arquivotxt, "%d\n", filme[i].ano);
				fprintf(arquivotxt, "%d\n", filme[i].duration);
				fprintf(arquivotxt,"\n");
			}
			break;
		}
		case 2: {
			break;
		}
		case 3: {
			printf("caso 3?");
			break;
		}
	}
}


