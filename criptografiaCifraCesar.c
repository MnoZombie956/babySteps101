#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// A circular cesarcyper-like algorithm to encrypt-decrypt phrases. (pls use SHA-256 instead ;D)

void printFullString(char* str){
  for(int i=0; str[i]!='\0'; i++){
    printf("%c",str[i]);
  }
}

char shiftAlphabet(char ch){//to uncrypt
  if(ch!='#'){
    if(ch<=90 && ch>=65){//if uppercase
      return (ch - 3) <= 64 ? ch + 23 : ch - 3;
    }
    if(ch<=122 && ch>=97){//if lowercase
      return (ch - 3) <= 96 ? ch + 23 : ch - 3;
    }
  }
  return '#';
}

void decodeThis(char* buffer){
  int szb = strlen(buffer);
  char auxc1buffer, auxc2buffer, flashC;
  //printf("szb=%d\n\n\n",szb);
  //forget, bullshit
  //int endIn = szb % 2 == 0 ? szb/4 : szb/4 + 1;
  for(int i=0, istep=1; istep<=(((int)szb)/4); i+=2, istep++){
    //if(istep!=szb/4-1){
      flashC=buffer[i];//troca as letras dos pares iniciais
      buffer[i]=buffer[i+1];
      buffer[i+1]=flashC;
    //}
    //printf("buffer[i]:%c buffer[i+1]:%c    &&    ",buffer[i],buffer[i+1]);
    //if(istep!=szb/4-1){
      flashC=buffer[szb-i-2];//troca as letras dos pares finais
      buffer[szb-i-2]=buffer[szb-1-i];
      buffer[szb-1-i]=flashC;
    //}
    //printf("buffer[szb-i-2]:%c buffer[iszb-i-1]:%c    swapLetters    istep<%d>    i:%d    szb:%d\n",buffer[szb-i-2],buffer[szb-i-1],istep,i,szb);
    //printf("We are NOT the odd pair    istep:%d    szb:%d    buffer[i+2]:%c    buffer[i+3]:%c\n",istep,szb,buffer[i+2],buffer[i+3]);
    if((istep==((int)szb/4)) && (((szb/2)%2)!=0)){
      //printf("We are in the odd pair    istep:%d    szb:%d    buffer[i+2]:%c    buffer[i+3]:%c\n",istep,szb,buffer[i+2],buffer[i+3]);

      flashC=buffer[i+2];
      buffer[i+2]=buffer[i+3];
      buffer[i+3]=flashC;

      if(buffer[i+2]=='#')
        buffer[i+2]=' ';
      if(buffer[i+3]=='#')
        buffer[i+3]=' ';

      buffer[i+2]=shiftAlphabet(buffer[i+2]);
      buffer[i+3]=shiftAlphabet(buffer[i+3]);
    }

    if(istep%2!=0){//troca os pares iniciais com os finais
      //printf("SWAP PAIRS OF LETTERS\n");
      auxc1buffer=buffer[i];//grava o primeiro par
      auxc2buffer=buffer[i+1];

      buffer[i]=buffer[szb-i-2];//coloca ultimo par no primeiro
      buffer[i+1]=buffer[szb-i-1];

      buffer[szb-i-2]=auxc1buffer;//coloca o primeiro salvo par no ultimo
      buffer[szb-i-1]=auxc2buffer;

      //printf("swapped %c%c to %c%c\n",buffer[i],buffer[i+1],buffer[szb-2-i],buffer[szb-1-i]);
    }
    //printFullString(buffer);
    //printf(" shifted-v-\n");
    //if(istep<=szb/4-1){
      buffer[i]      =shiftAlphabet(buffer[i]      );
      buffer[i+1]    =shiftAlphabet(buffer[i+1]    );
      buffer[szb-1-i]=shiftAlphabet(buffer[szb-1-i]);
      buffer[szb-2-i]=shiftAlphabet(buffer[szb-2-i]);
      //}
    if(buffer[i]=='#')
      buffer[i]=' ';
    if(buffer[i+1]=='#')
      buffer[i+1]=' ';
    if(buffer[szb-2-i]=='#')
      buffer[szb-2-i]=' ';
    if(buffer[szb-1-i]=='#')
      buffer[szb-1-i]=' ';
//    printFullString(buffer);
//    printf("\n\n");
  }
// ENCRYPTED TO UNENCRYPTED EXAMPLE TEXTS:
//rglfil#drwF#w#udvdgrsdhvkqdi#hpohxhwrpfhp#dudgilvhg#t#qhv#lfhw#u#d#hqhs#r#vhahhgf#uidu#D ->
//A cifra de Cesar pode ser facilmente decifrada mesmo que se tenha apenas o texto cifrado
//VR#RLOUYPD -> AMO LIVROS
}

// OPERACOES REALIZADAS
/*Encriptar, objetivo eh fazer o contrario

  espacos recebem '#'

  se strlen(str) for impar '#' na ultima pos

  pegar pares de letras

  inverter a posicao de cada pares

  trocar o ultimo par com o primeiro o terceiro par com o antipenultimo
  , o 5nt par com o n-4 e assim por diante (o meio permanece o msm caso o numero
  de pares for par e é trocado caso seja impar)
*/

int main () {
  printf("Digite o nome do arquivo: ");
  //char arch1Name[]="cryptoCode.txt";
  char arch1Name[200];
  char buffer[10000];
  scanf("%s",arch1Name);
  FILE* arch = fopen(arch1Name,"r");

  if(arch==NULL){
    //printf("arquivo nao aberto!\n");
  }

  fscanf(arch,"%s",&buffer[0]);
  printf("\n--------------------\nMensagem codificada:\n--------------------\n");
  printFullString(buffer);
  printf("\n");

  decodeThis(buffer);

  printf("\n----------------------\nMensagem decodificada:\n----------------------\n");
  printFullString(buffer);
  fclose(arch);
  //arch = fopen(arch1Name,"w");
  //fseek(arch,SEEK_SET,0);
  //fprintf(arch,"%s",&buffer[0]);
  //fclose(arch);
}
