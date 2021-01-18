/*
	Marco Tulio Siqueira da Mata 20193007156 - 31/10/2020 - ;)

	laedes - professora Natalia - cefetmg - runcodes
*/
#include <stdio.h>
#include <stdlib.h>
#define TAM_MAX 500
#define TOLERANCE_ERROR 0.06 // valor tolerado em que o ponto do meio do padrao se desvia do ponto do meio da linha
#define preta 0
#define branca 255
/*
	Explicação do exercicios para meu eu futuro:
	Lemos um arquivo, 1st linha: n, seguintes linhas: n inteiros; e armazenamos num vetor.
	Geramos uma lista de segmentos, em que os segmentos
	são os nucleos em que inteiros se repetem.
	Para cada segmento, existe um segType que indica sua posição na ordem crescente
	dos segmentos gerados.
	Eh criada uma matrix relacionando a qnt de inteiros em cada segmentos e seu
	segType.
	Como segundo exercicio, eh dado um padrao para ser procurado na lista de 
	segmentos que criamos. Caso encontrado o padrao, exibimos onde, na lista de
	segmentos, ele comeca e acaba em termos de index.
	Apos isto, calculamos quantas vezes cada inteiros de segmentos existem
	até chegarmos na posicao do arquivo em que eh a mesma que o inteiro do meio
	do padrao encontrado(transcrevemos seu ponto meio na lista para o correspondente
	no arquivo). Por fim, exibimos onde está(posicao) o ponto do meio do padrao no arquivo.
*/

struct segment{
	int size;
	int *items;// segments' items
	int segType; // position in the crescent order
	int midPointIArchPosition;//midPoint of the detected parttern in terms of archive position
	int midPointArchValue;
};
typedef struct archData{
	struct segment *segs; //clusters of repetitive numbers
	int segsIdx; // segs quantity - 1
	int segsPatternIdx;//where is the pattern in segs, if found

	int *items; // archive items read
	int itemsQnt; // items quantity, read in archive
	int** mtx; // answer's matrix, parte I exercicio
}archData;

typedef struct itemType{
	int value;
	struct itemType *next;
}itemType;

typedef struct linkedlist{
	struct itemType *first, *last;
	int elements_number;
}linkedlist;

int prompt_and_operateFile(FILE* *arch, archData* archD, int* pattern, int patternSize);
int doesItExistInSegment(archData* archD, int dataItem);
int addToSegment(archData* archD, int dataItem);
void createNewSegmentAndAdd(archData* archD, int dataItem);
void segmentsProcedures(archData* archD);
void outputMatrix(archData* archD);
void generateMatrix(archData* archD);
void determineParternMidPoint_arch(archData* archD, int listStartPosition, int listMidPosition);
int detectPatternAndMidPoint(archData* archD, int* pattern, int patternSize);

void linkedList_Start(linkedlist *list);
int linkedList_Qnt(linkedlist *list);
int linkedList_Empty(linkedlist *list);
int linkedList_Insert(linkedlist *list, itemType item);
itemType *linkedList_Search(linkedlist *list, itemType item);
int linkedList_Remove(linkedlist *list, itemType *previous, itemType *item);
void linkedList_Print(linkedlist *list);

//RODAR antes de mexer
int main(){
	FILE* arch;
	archData archD;
	int pattern[] = { 
		preta, branca, preta, branca, preta, branca,
        preta, branca, preta, branca, preta, branca,
        preta
    };
	int patternSize = 13;



	switch(prompt_and_operateFile(&arch,&archD,pattern,patternSize)){//parte III do problema
		case -1://indeterminado
			printf("Resultado: Formato da pista nao estimado.");
			break;
		case 0://esquerda
			printf("Resultado: Curva a esquerda.");
			break;
		case 1://reta
			printf("Resultado: Pista em linha reta.");
			break;
		case 2://direita
			printf("Resultado: Curva a direita.");
			break;
		case 3:
			printf("Resultado: Pista sem faixa de pedestres");
			break;
		case 4:
			printf("Resultado: Pista com faixa de pedestres");
			break;
		default:
			printf("erro no arquivo");
			break;
	}
	//generateMatrix(&archD);
	//outputMatrix(&archD);//parte I do problema
	//if(detectPatternAndMidPoint(&archD,pattern,patternSize)){//parte II do problema
	//	printf("Resultado: Padrao encontrado.\n");
	//	printf("Ponto Medio: %d", archD.segs[archD.segsPatternIdx].midPointIArchPosition);
	//}else{
	//	printf("Resultado: Padrao nao encontrado.\n");
	//}
	return 0;
}

int prompt_and_operateFile(FILE* *arch, archData* archD, int* pattern, int patternSize){
	char archName[20];
	int n=0;
	int linesPairQnt=0;
	int successfullyLines=0;
	double middlePointsPositionBigSum=0;
	double middlePointsTendency=0;
	//char* archName = "testp.txt";
	printf("Digite o nome do arquivo: ");
	scanf("%s",&archName[0]);
	*arch=fopen(archName,"r");
	if(*arch==NULL){
		printf("Couldn't open file\n");
		return -2;
	}
	rewind(*arch);
	fscanf(*arch,"%d",&linesPairQnt);
	printf("lines pairs: %d\n\n",linesPairQnt);
	if(linesPairQnt==0){ // so we don't need to read the archive
		return -2;
	}
	for(int j=0; j< linesPairQnt; j++){
		fscanf(*arch,"%d",&n);

		archD->itemsQnt=n;
		archD->items=(int*)malloc(sizeof(int)*(n));
		(*archD).segs = (struct segment*)malloc(sizeof(struct segment)); //reserve memory for at least 1 segment
		archD->segs[0].size=0;//first segment has nothing
		archD->segsIdx=0; //segsIdx tells 1st segment vectorial position
		archD->segs[0].items=(int*)malloc(sizeof(int));
		archD->segs[0].items[0]=0;

		printf("LINE NUMBER: %d\n",j);
		printf("Read data [qnt: %d]:\n",n);
		for(int i=0;i<n;i++){
			fscanf(*arch,"%d ",&archD->items[i]);
			printf("%d ",archD->items[i]);
		}

		generateMatrix(archD);
		outputMatrix(archD);//parte I do problema
 
		switch(detectPatternAndMidPoint(archD,pattern,patternSize)){
			case 0://n existe padrao
				printf("line %d: NO pattern\n\n", j);
				break;
			case 1://existe padrao
				printf("line %d: PATTERN\n\n", j);
				return 4;//padrao é a faixa de pedestrees PARTE EXTRA, comentar 
				successfullyLines++;
				middlePointsPositionBigSum+=archD->segs[archD->segsPatternIdx].midPointIArchPosition;
				break;
		}
/*
		free(archD->items);
		free((*archD).segs);
		free(archD->segs[0].items);*/
	}
	return 3;// considerando sem faixa de pedestres PARTE EXTRA, comentar 
	middlePointsTendency = middlePointsPositionBigSum / (double)successfullyLines;
	printf(
		"bigSum:%lf goodLines:%d goodQuocient:%lf tendency:%lf\nerror:%lf middleLine:%d linesPairQnt:%d\n",
		middlePointsPositionBigSum,successfullyLines,(double)successfullyLines/(double)linesPairQnt,middlePointsTendency,
		(archD->itemsQnt/2)*TOLERANCE_ERROR,archD->itemsQnt/2, linesPairQnt
	);
	if((double)successfullyLines/(double)linesPairQnt>=0.7){
		//What I did is an interval within a tolerance disparaty about the middle value in the line
		double maxValue=(((double)archD->itemsQnt)/2)*(1 + TOLERANCE_ERROR);
		double minValue=(((double)archD->itemsQnt)/2)*(1 - TOLERANCE_ERROR);
		printf("max %lf and min %lf\n", minValue, maxValue);
		if(middlePointsTendency > maxValue){
			return 2;
		}
		if(middlePointsTendency < minValue){
			return 0;
		}
		return 1; // it's in the middle of the inequality
	}
	return -1;
}
int doesItExistInSegment(archData* archD, int dataItem){
	return dataItem==archD->segs[archD->segsIdx].items[0]?0:1;
}
int addToSegment(archData* archD, int dataItem){
	archD->segs[archD->segsIdx].size++;
	archD->segs[archD->segsIdx].items=(int*)realloc(
		archD->segs[archD->segsIdx].items,
		sizeof(int)*(archD->segs[archD->segsIdx].size)
	);//space for +1 item
	//add dataItem to the rightmost compatible segment founded
	archD->segs[archD->segsIdx].items[archD->segs[archD->segsIdx].size-1]=dataItem;
	return 0;
}
void createNewSegmentAndAdd(archData* archD, int dataItem){
	archD->segsIdx++;
	archD->segs=(struct segment*)realloc(
		archD->segs,
		sizeof(struct segment)*(archD->segsIdx+1)
	);
	archD->segs[archD->segsIdx].items=(int*)malloc(sizeof(int));//space for at least 1 int
	archD->segs[archD->segsIdx].size=0;

	addToSegment(archD,dataItem);
}
void segmentsProcedures(archData* archD){
	int* flashItem=(int*)malloc(sizeof(int)*(archD->segsIdx+1));
	int flashItemSize=archD->segsIdx+1;
	printf("\nSegs Quantity: %d\n", flashItemSize);
	for(int i=0;i<=archD->segsIdx;i++){//copy numbers
		flashItem[i]=archD->segs[i].items[0];
	}
	for(int i=0;i<=archD->segsIdx;i++){//crescent order
		for(int j=i;j<=archD->segsIdx;j++){
			if(flashItem[i]>flashItem[j]){
				int flashValue=flashItem[j];
				flashItem[j]=flashItem[i];
				flashItem[i]=flashValue;
			}
		}
	}
	for(int i=0;i<flashItemSize;i++){ //remove repeated elements
		for(int j=0;j<flashItemSize;j++){
			if((flashItem[i]==flashItem[j])&&(i!=j)){
				for(int k=j;k<flashItemSize;k++){ //shift left
					flashItem[k]=flashItem[k+1];
				}
				flashItemSize--; //new size
				j=0;
			}
		}
	}
	for(int i=0;i<flashItemSize;i++){ // indicate the type of each segment, accordingly to its crescent position
		for(int j=0;j<=archD->segsIdx;j++){
			if(archD->segs[j].items[0]==flashItem[i]){
				archD->segs[j].segType=i+1;
			}
		}
	}
	for(int i=0;i<=archD->segsIdx;i++){//copy numbers
		printf("segs[%d] = %d for %dx times, segType: %d\n",
			i,
			archD->segs[i].items[0],
			archD->segs[i].size,
			archD->segs[i].segType
		);
	}
}
void outputMatrix(archData* archD){
	printf("Matrix (segType x segTimes):\n");
	for(int j=0;j<=archD->segsIdx;j++)
		printf("%d ",archD->segs[j].segType);
	printf("\n");
	for(int j=0;j<=archD->segsIdx;j++)
		printf("%d ",archD->segs[j].size);
}
void generateMatrix(archData* archD){
	archD->segs[0].items[0]=archD->items[0];
	archD->segs[0].size++;
	for(int i=1;i<archD->itemsQnt;i++){
		int dataItem = archD->items[i];
		switch(doesItExistInSegment(archD,dataItem)){
			case 0:
				addToSegment(archD, dataItem);			
				break;
			case 1:
				createNewSegmentAndAdd(archD,dataItem);
				break;
		}		
	}
	segmentsProcedures(archD);
}
void determineParternMidPoint_arch(archData* archD, int listStartPosition, int listMidPosition){
	int posSum=0;
	int k=0;
	for(k=0; k <= listMidPosition - 1; k++){
		posSum += archD->segs[k].size;
		printf("		segs[k].size|%d|+posSum=>%d\n",archD->segs[k].size,posSum);
	}
	if((archD->segs[k].size%2)==0){// se par
		posSum += (archD->segs[k].size/2) - 1;
	}else{
		posSum += archD->segs[k].size/2;
	}
	archD->segs[k].midPointIArchPosition = posSum;
	archD->segs[k].midPointArchValue = archD->items[posSum];
	archD->segsPatternIdx=k;
	printf("	In archive: pos=%d, value=%d\n",
		posSum, 
		archD->items[posSum]
	);
}
int detectPatternAndMidPoint(archData* archD, int* pattern, int patternSize){
	linkedlist list;
	linkedList_Start(&list);
	for(int i=0; i<=archD->segsIdx; i++){ // creating the list
		itemType aux;
		aux.value = archD->segs[i].items[0];
		linkedList_Insert(&list, aux);
	}
	printf("\nGenerated Procedured List(first item of each segment, no rep.):\n");
	linkedList_Print(&list);
	printf("\nSearching by Pattern: ");
	for(int i=0; i<patternSize; i++){
		printf("'%d' ",pattern[i]);
	}printf("\n\n");

	itemType *aux = list.first->next;
	printf("aux->value=%d, aux->next.value=%d\n\n",aux->value, aux->next->value);
	for(int i=0, found=1; aux->next != NULL; aux = aux->next, i++, found=1){
		printf("list[%d].value|%d| == |%d|pattern[0] ?\n",i,aux->value,pattern[0]);
		if(aux->value == pattern[0]){
			printf("	aux ->value %d == %d pattern[0] ?\n",aux->value,pattern[0]);
			itemType *aux2 = aux->next;
			int j=1;
			for(j=1; (j<patternSize) && (aux2 != NULL); aux2 = aux2->next, j++){
				printf("	aux2->value %d == %d pattern[%d] ?\n",aux2->value,pattern[j],j);
				if((aux2->next == NULL) && (j<patternSize-1)){
					printf("	doesn't have a complete pattern at the end\n");
					return 0;
				} 
				if(aux2->value!=pattern[j]){
					found = 0;
					printf("	ops\n");
					break;
				}
			}
			if(found==1){
				printf("found: slist[%d], elist[%d], midPointListPosition: %d\n",
					i, //inicio do index na lista gerada em que o padrão é encontrado
					i+j-1,//fim do index na 
					((i+j)/2)//posição i em que o ponto medio está na lista
				);
				determineParternMidPoint_arch(archD, i, ((i+j)/2));
				return 1;
			}
		}
	}
	return 0;
}

void linkedList_Start(linkedlist *list){
	list->first = malloc(sizeof(itemType));
	list->first->next = NULL;
	list->last = list->first;
	list->elements_number = 0;
}

int linkedList_Qnt(linkedlist *list){
	return list->elements_number;
}

int linkedList_Empty(linkedlist *list){
	return list->first == list->last;
}

int linkedList_Insert(linkedlist *list, itemType item){
	itemType *new_item = malloc(sizeof(itemType));
	new_item->value = item.value;
	new_item->next = NULL;
	list->last->next = new_item;
	list->last = list->last->next;

	list->elements_number++;
	return 1;
}

itemType *linkedList_Search(linkedlist *list, itemType item){
	itemType *aux;
	for(aux = list->first; aux->next != NULL; aux = aux->next){
		if(aux->next->value == item.value){
			return aux;
		}
	}
	return NULL;
}

int linkedList_Remove(linkedlist *list, itemType *previous, itemType *item){
	itemType *aux = previous->next;
	item->value = aux->value;
	previous->next = aux->next;
	free(aux);
	list->elements_number--;
	return 1;
}

void linkedList_Print(linkedlist *list){
	itemType *aux = NULL;
	for(aux = list->first->next; aux != NULL; aux = aux->next){
		printf("'%d' ",aux->value);
	}aux = list->first->next;printf("\n");
	for(int i=0; aux != NULL; aux = aux->next, i++){
		printf(" %d  ",i);
	}printf("\n");		
}

