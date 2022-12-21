#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(int argc, char ** argv){
	int Lista = 0;
	if(argc<3){
		printf("too few arguments\n");
		return 1;
	}
	if(argc>3){
		printf("too many arguments\n");
		return 1;
	}

	if(strcmp(argv[2],"arvore")==0 || strcmp(argv[2],"lista")==0){
		printf("Tipo de indice: '%s'\n",argv[2]);
		if(strcmp(argv[2], "lista") == 0){
			Lista = 1;
		}
	}
	else{
		printf("Tipo de indice '%s' não reconhecido!\n", argv[2]);
	}

	Inicio lista;
	ini(&lista);

	FILE *arq;
	arq = fopen(argv[1], "r");
	if(arq == NULL){
		printf("Arquivo '%s' não encontrado.\n", argv[1]);
		return 1;
	}

	printf("Arquivo de texto: '%s'\n", argv[1]);

	Texto texto;
	float tempo = Clock(1);
	int lineNum = getText(&texto, arq);
	fclose(arq);
	for(int i=0;i<lineNum; i++){
		linhaEmLista(texto.linha[i], &lista, NULL, i, Lista);
	}
	tempo = Clock(0);
	printf("Número de linhas no arquivo: %i\n", lineNum);
	printf("Tempo para carregar o arquivo e construir o indice: %.2f ms\n", tempo);
	//printf("\n");
	//printAll(&texto, &lista, lineNum);
	while(1){
		printf("> ");
		char action[10];
		char word[50];
		scanf("%s", &action);
		if(!strcmp(action, "busca")){
			scanf("%s", &word);
			busca(texto, lista.lista, NULL, word, Lista);
		}
	}
		

	return 0;
}
