#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(){
	Inicio lista;
	FILE *arq;
	char linha[1000];

	arq = fopen("texto.txt", "r");
	if(arq == NULL){
		printf("Arquivo 'texto.txt' não encontrado.\n");
		return 1;
	}

	//while(fgets(linha, 1000, arq)){
	//	printf(linha);
	//}
	fgets(linha,1000,arq);
	linhaEmLista(linha, &lista, 0);
	fclose(arq);
	printLista(lista.lista[0]);
	return 0;
}






























/*	Inicio lista;
	lista.lista = (Lista*) malloc(sizeof(Lista));
	FILE *arq;
	char Linha[500];
	char *result;
	int i=1;

	arq = fopen("texto.txt","rt");
	if (arq == NULL){
		printf("arquivo texto.txt não encontrado.\n");
		return 1;
	}
	result = fgets(Linha, 500, arq);
	if (result){
		printf("Linha %d: %s", i, Linha);
	}
	i=0;
	int j=0;
	Lista *atual = lista.lista;
	for(char temp[50]; i<500;i++){
		char c = Linha[i];
		if(c >= 65 && c <= 90){
			c=c+32;
		}
		if(c != ' ' && c != ',' && c != '.' && c != '-' && c != '!' && c != '?' && c != '\0'){
			temp[j] = c;
			j++;
		}
		else{
			atual->proximo = (Lista *) malloc(sizeof(Lista));
			atual=atual->proximo;
			for(int d=0; d < 50; d++){
				atual->palavra[d] = temp[d];
			}
			j=0;
			for(int h=0; h<20; h++){
				temp[h]='\0';
			}
			atual->proximo = NULL;
			if(Linha[i] =='\0'){
				break;
			}
			while(c == ' ' || c == ',' || c == '.' || c == '-' || c == '!' || c == '?'){
				i++;
				c = Linha[i];
			}
			i--;
		}
	}
	atual = lista.lista;
	while(atual->proximo != NULL){
		printf("%s\n", atual->palavra);
		atual = atual->proximo;
	}
	fclose(arq);
}*/
