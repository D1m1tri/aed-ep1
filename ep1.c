#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(){
	Inicio lista;
	lista.lista = (Lista*) malloc(sizeof(Lista*));
	int linhas = 0;
	FILE *arq;

	arq = fopen("texto.txt", "r");
	if(arq == NULL){
		printf("Arquivo 'texto.txt' não encontrado.\n");
		return 1;
	}
	Texto texto;
	int lineNum = getText(&texto, arq);

	fclose(arq);
	for(int i=0;i<lineNum; i++){
		linhaEmLista(texto.linha[i], &lista, i);
	}
	printf("\n");
	printAll(&texto, &lista, lineNum);
	return 0;
}
