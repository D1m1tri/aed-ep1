#include <string.h>
#include <time.h>
#include "lista.h"
#include "arvore.h"

typedef struct {	//armazenar o texto de forma integral
	char * linha[10000];
} Texto;


float Clock(int reset){ //função para medir o tempo
	static clock_t startTime;
	if(reset){
		startTime = clock();
	}
	clock_t endTime = clock();
	return 1000*(((float)(endTime-startTime))/CLOCKS_PER_SEC);
}

void printAll(Texto * texto, Inicio * lista, int lineNum){ //imprime tudo o que está armazenado
	for(int i=0; i<lineNum;i++){
		printf("%02i: %s",i,texto->linha[i]);
	}
	Lista * atual = lista->lista;
	printf("\npalavra		aparições	linhas\n\n");
	while(atual->existeProximo == 1){
		atual = atual->proximo;
		if(strlen(atual->palavra)<8){
			printf("%s		    %i		",atual->palavra,atual->numLinhas);
		}
		else{
			printf("%s	    %i		",atual->palavra,atual->numLinhas);
		}
		Linhas * linAtual = atual->linhas;
		while(linAtual->existeProximo==1){
			linAtual = linAtual->proximo;
			printf("%i, ",linAtual->linha);
		}
		printf("\n");
	}
	printf("\n");
}


int getText(Texto *texto, FILE *arq){ //salva as linhas do arquivo externo na memória do programa
	char linha[10000];
	int i=0;
	while(fgets(linha, 10000, arq)){
		int size = (int) strlen(linha);
		size++;
		texto->linha[i] = (char*) malloc(size*sizeof(char));
		for(int j=0;j<size;j++){
			texto->linha[i][j] = linha[j];
		}
		i++;
	}
	return i;
}

void linhaEmLista(char linha[], Inicio * lista, int numLinha){ //separação das palavras nas linhas
	static int doOnce=0;				       //para uso na lista ligada
	if(!doOnce){
		lista->lista->existeProximo = 0;
		doOnce++;
	}
	char palavra[50];
	for(int i=0; i<50;i++){
		palavra[i] = '\0';
	}
	char c='\0';
	for(int i=0; c!='\n';i++){
		c=linha[i];
		if(c>64 && c<91){
			c+=32;
		}
		if(c<97 || c>122){
			if(strlen(palavra)<1){
				palavra[0]='\0';
			}
			else{
				InsertOnList(lista->lista, palavra, numLinha);
				for(int z=0;z<50;z++){
					palavra[z]='\0';
				}
			}
		}
		else{
		strncat(palavra, &c, 1);
		}
	}
}

