#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

	Arvore * raiz = (Arvore *) malloc(sizeof(Arvore));
	raiz->raiz = NULL;

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
		linhaEmLista(texto.linha[i], &lista, raiz, i, Lista);
	}
	tempo = Clock(0);
	printf("Número de linhas no arquivo: %i\n", lineNum);
	printf("Tempo para carregar o arquivo e construir o indice: %.2f ms\n", tempo);
	//printf("\n");
	//printAll(&texto, lista.lista, raiz, lineNum, Lista); // *** APENAS PARA DEBUG ***
	while(1){
		printf("> ");
		char action[10];
		char word[50];
		scanf("%s", &action);
		if(!strcmp(action,"fim")){
			break;
		}
		scanf("%s", &word);
		for(int i=0; action[i]; i++){
			action[i] = (char) tolower((int)action[i]);
		}
		for(int i=0; word[i]; i++){
			word[i] = tolower(word[i]);
		}
		if(!strcmp(action, "busca")){
			busca(texto, lista.lista, raiz->raiz, word, Lista);
		}
		else{
			printf("Opção inválida!\n");
		}
	}
		

	return 0;
}
