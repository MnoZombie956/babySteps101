/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ofzbo
 *
 * Created on 29 de fevereiro de 2020, 12:17
 */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define FALSE           0
#define TRUE            1
#define INFINITO       INT_MAX


typedef int TipoValorVertice;

typedef int TipoPeso;

typedef struct TipoGrafo {
    TipoPeso Mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
    int NumVertices;
    int NumArestas;
} TipoGrafo;

typedef TipoValorVertice TipoApontador;
typedef int TipoIndice;

typedef struct TipoItem {
    TipoPeso Chave;
} TipoItem;

typedef TipoItem TipoVetor[MAXNUMVERTICES + 1];

typedef struct conteudo{
    int vertice;
    int antecessor;
    int dist;
}conteudo;

typedef struct listaGerada{
    conteudo partes[50];
    int qnt;
}listaGerada;

//////////////////////////////////////////////////////////////////////// Gv

listaGerada lista;
int path[20]; 
int qntP=0;//quantity of cities on path
int distanciaT;
int finalD;
char cities[30][20];//thirdy cities wt 20 chars
int qntCities;

TipoApontador Aux;
int i, NArestas;
short FimListaAdj;
TipoValorVertice V1, V2, Adj;
TipoPeso Peso;
TipoGrafo Grafo;
TipoValorVertice NVertices;
TipoIndice n; /*Tamanho do heap*/
TipoValorVertice Raiz;



void FGVazio(TipoGrafo *Grafo) {
    int i, j;
    for (i = 0; i <= Grafo->NumVertices; i++)
        for (j = 0; j <= Grafo->NumVertices; j++)
            Grafo->Mat[i][j] = 0;
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoPeso *Peso, TipoGrafo *Grafo) {
    Grafo->Mat[*V1][*V2] = *Peso;
}

short ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo) {
    return (Grafo->Mat[Vertice1][Vertice2] > 0);
}

/*-- Operadores para obter a lista de adjacentes --*/

short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo) {
    TipoApontador Aux = 0;
    short ListaVazia = TRUE;
    while (Aux < Grafo->NumVertices && ListaVazia) {
        if (Grafo->Mat[*Vertice][Aux] > 0)
            ListaVazia = FALSE;
        else
            Aux++;
    }
    return (ListaVazia == TRUE);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo) {
    TipoValorVertice Result;
    TipoApontador Aux = 0;
    short Listavazia = TRUE;
    while (Aux < Grafo->NumVertices && Listavazia) {
        if (Grafo->Mat[*Vertice][Aux] > 0) {
            Result = Aux;
            Listavazia = FALSE;
        }
        else Aux++;
    }
    if (Aux == Grafo->NumVertices)
        printf("Erro: Lista adjacencia vazia (PrimeiroListaAdj)\n");
    return Result;
}

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo, TipoValorVertice *Adj, TipoPeso *Peso, TipoApontador *Prox, short *FimListaAdj) { /* --Retorna Adj apontado por Prox--*/
    *Adj = *Prox;
    *Peso = Grafo->Mat[*Vertice][*Prox];
    (*Prox)++;
    while (*Prox < Grafo->NumVertices && Grafo->Mat[*Vertice][*Prox] == 0)
        (*Prox)++;
    if (*Prox == Grafo->NumVertices) *FimListaAdj = TRUE;
}

void ImprimeGrafo(TipoGrafo *Grafo) {
    int i, j;
    printf("   ");
    for (i = 0; i < Grafo->NumVertices; i++) printf("%3d", i);
    putchar('\n');
    for (i = 0; i < Grafo->NumVertices; i++) {
        printf("%3d", i);
        for (j = 0; j < Grafo->NumVertices; j++)
            printf("%3d", Grafo->Mat[i][j]);
        putchar('\n');
    }
}

void RefazInd(TipoIndice Esq, TipoIndice Dir, TipoItem *A, TipoPeso *P, TipoValorVertice *Pos) {
    TipoIndice i = Esq;
    int j;
    TipoItem x;
    j = i * 2;
    x = A[i];
    while (j <= Dir) {
        if (j < Dir) {
            if (P[A[j].Chave] > P[A[j + 1].Chave]) j++;
        }
        if (P[x.Chave] <= P[A[j].Chave]) goto L999;
        A[i] = A[j];
        Pos[A[j].Chave] = i;
        i = j;
        j = i * 2;
    }
L999:
    A[i] = x;
    Pos[x.Chave] = i;
}

void Constroi(TipoItem *A, TipoPeso *P, TipoValorVertice *Pos) {
    TipoIndice Esq;
    Esq = n / 2 + 1;
    while (Esq > 1) {
        Esq--;
        RefazInd(Esq, n, A, P, Pos);
    }
}

TipoItem RetiraMinInd(TipoItem *A, TipoPeso *P, TipoValorVertice *Pos) {
    TipoItem Result;
    if (n < 1) {
        printf("Erro: heap vazio\n");
        return Result;
    }
    Result = A[1];
    A[1] = A[n];
    Pos[A[n].Chave] = 1;
    n--;
    RefazInd(1, n, A, P, Pos);
    return Result;
}

void DiminuiChaveInd(TipoIndice i, TipoPeso ChaveNova, TipoItem *A, TipoPeso *P, TipoValorVertice *Pos) {
    TipoItem x;
    if (ChaveNova > P[A[i].Chave]) {
        printf("Erro: ChaveNova maior que a chave atual\n");
        return;
    }
    P[A[i].Chave] = ChaveNova;
    while (i > 1 && P[A[i / 2].Chave] > P[A[i].Chave]) {
        x = A[i / 2];
        A[i / 2] = A[i];
        Pos[A[i].Chave] = i / 2;
        A[i] = x;
        Pos[x.Chave] = i;
        i /= 2;
    }
}

void Dijkstra(TipoGrafo *Grafo, TipoValorVertice *Raiz) {
    TipoPeso P[MAXNUMVERTICES + 1];
    TipoValorVertice Pos[MAXNUMVERTICES + 1];
    long Antecessor[MAXNUMVERTICES + 1];
    short Itensheap[MAXNUMVERTICES + 1];
    TipoVetor A;
    TipoValorVertice u, v;
    TipoItem temp;
    
    //printf("ak 1\n");
    for (u = 0; u <= Grafo->NumVertices; u++) { /*Constroi o heap com todos os valores igual a INFINITO*/
        Antecessor[u] = -1;
        P[u] = INFINITO;
        A[u + 1].Chave = u; /*Heap a ser construido*/
        Itensheap[u] = TRUE;
        Pos[u] = u + 1;
    }
    //printf("ak 2\n");
    n = Grafo->NumVertices;
    P[*(Raiz)] = 0;
    Constroi(A, P, Pos);
    while (n >= 1) { /*enquanto heap nao vazio*/
        temp = RetiraMinInd(A, P, Pos);
        u = temp.Chave;
        Itensheap[u] = FALSE;
        //printf("ak 3\n");
        if (!ListaAdjVazia(&u, Grafo)) {
            //printf("ak 4\n");
            Aux = PrimeiroListaAdj(&u, Grafo);
            FimListaAdj = FALSE;
            while (!FimListaAdj) {
                ProxAdj(&u, Grafo, &v, &Peso, &Aux, &FimListaAdj);
                if (P[v] > (P[u] + Peso)) {
                    P[v] = P[u] + Peso;
                    Antecessor[v] = u;
                    DiminuiChaveInd(Pos[v], P[v], A, P, Pos);
                    
                    lista.partes[lista.qnt].vertice   =v;
                    lista.partes[lista.qnt].antecessor=Antecessor[v];
                    lista.partes[lista.qnt].dist    =P[v];
                    
                    lista.qnt++;
                }
            }
        }
    }
}

void gerarCaminho(listaGerada ls, int Raiz, int toNum){
    conteudo flash;

    int min=INT_MAX;
    int k=0;
    int lastK=0;
    for(k=0; k < ls.qnt; k++){
        if(ls.partes[k].vertice==toNum && ls.partes[k].dist<min){
            min = ls.partes[k].dist;
            
            flash.dist=min;
            flash.vertice=ls.partes[k].antecessor;
            
            lastK=k;
        }
    }
    path[qntP++]=ls.partes[lastK].vertice;
    if(ls.partes[lastK].vertice==finalD) distanciaT=ls.partes[lastK].dist;
    
    if(flash.vertice!=Raiz){
        gerarCaminho(ls, Raiz, flash.vertice);
    }
}
int stringExiste(char string[20]){
    //printf("proucurando por %s\n",string);
    for(int i=0;i<30;i++){
        //printf("compare |%s| |%s|\n",string,cities[i]);
        if(strcmp(string,&cities[i][0])==0){
            //printf("igual string|%s| mapa|%s| return num:%d\n",string,&cities[i][0],i);            
            return i;
        }
    }
    //printf("none equal returning -1\n"); 
    return -1;
}

int main(int argc, char *argv[]) { /*-- Programa principal --*/
    char archName[20];
    FILE *arch;
    
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s",archName);
    //printf("\n");
    arch = fopen(/*"arch.txt"*/archName,"r");

    if(arch == NULL){
       printf("Kein arch!");   
       exit(1);             
    }
    
    NVertices = 0;
    NArestas = 0;   
    
    qntCities=0;
    for(int j=0;j<30;j++){
        strcpy(&cities[j][0],"");
    }
    
    fseek(arch, 0, SEEK_SET); 
    fscanf(arch, "%d", &NVertices);
    //printf("%d\n",NVertices);
  
    Grafo.NumVertices = NVertices;
    Grafo.NumArestas = 0;
    FGVazio(&Grafo);
    
    lista.qnt=0;
    distanciaT=0;
    
    char c1[20],c2[20];
    for(int k=0, i=0, j=0; k<NVertices; k+=1) {
        fscanf(arch, "%s %s %d", c1, c2, &Peso);
        //printf("%s %s %d\n", &c1[k][0], &c2[k][0], Peso);
        
        //printf("s1: %s s2: %s\n", &mapa[k].cidadeNome[0], &mapa[k+1].cidadeNome[0]);
        /*
        V1=java_hashCode(&c1[k][0])-65;
        V2=java_hashCode(&c2[k][0])-65;
        */
        int h1=stringExiste(c1),h2=stringExiste(c2);
        if(h1==-1){
            strcpy(cities[j],c1);
            h1=j++;

            //printf("adicionou city: %s num: %d\n",&cities[j-1][0],j-1);
        }else{
            //printf("city: %s ja existe->num: %d em h1 atribuira à v1\n",&cities[h1][0],h1);
        }
        if(h2==-1){
            strcpy(cities[j],c2);
            h2=j++;
            
            //printf("adicionou city: %s num: %d\n",&cities[j-1][0],j-1);
        }else{
            //printf("city: %s ja existe->num: %d atribuira à h1\n",&cities[h2][0],h2);
        }
        V1=h1;
        V2=h2;
        //printf("v1 %d v2 %d\n",V1,V2);
        
        Grafo.NumArestas+=2;
        InsereAresta(&V1, &V2, &Peso, &Grafo);
        InsereAresta(&V2, &V1, &Peso, &Grafo);
        
        //printf("associacao feita \n");
        
        //printf("s1: %s n: %d\n", cities[j-2], j-2);
        //printf("s2: %s n: %d\n", cities[j-1], j-1);
    }
    
    //ImprimeGrafo(&Grafo);
    
    char in[20]; char to[20];
    fscanf(arch, "%s", in);
    fscanf(arch, "%s", to);
    
    Raiz = stringExiste(in);
    finalD = stringExiste(to);
    
    //printf("Raiz: %s e %s Hashed: %d e %d\n", in, to, Raiz, finalD);
    
    Dijkstra(&Grafo, &Raiz);
    
    /*for(int i=0;i<lista.qnt;i++){
        printf("L %d %d %d\n",lista.partes[i].vertice,lista.partes[i].antecessor,lista.partes[i].dist);
    }*/
    
    //printf("foi gerar raiz %d toNum %d\n",Raiz,lista.partes[finalD-1]);
    


    path[qntP++]=finalD;

    gerarCaminho(lista, Raiz, finalD);

    printf("Menor percurso: ");
    for(int k=qntP; k>0; k--) printf("%s ",cities[path[k]]);
    printf("\nDistancia total: %d Km",distanciaT);

    fclose(arch); 
    return 0;
}