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

void printAll(Texto * texto, Lista * atual, Arvore * raiz, int lineNum, int Lista){ //imprime tudo o que está armazenado
	for(int i=0; i<lineNum;i++){
		printf("%02i: %s",i,texto->linha[i]);
	}
	if(Lista){
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
	}
	else{
		printf("\npalavra		aparições	linhas\n\n");
		printArvore(raiz->raiz);
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

void linhaEmLista(char linha[], Inicio * lista, Arvore * raiz, int numLinha, int Lista){ //separação das palavras nas linhas
	static int doOnce=0;				       //para uso na lista ligada
	if(!doOnce && Lista){
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
		if(c=='.'|| c==','|| c=='-'|| c=='/'|| c=='!'|| c=='?'|| c==';'|| c==':'|| c=='('|| c==')'|| c=='\0'|| c=='\n'|| c=='"'|| c=='"' || c==' '){
			if(strlen(palavra)<1){
				palavra[0]='\0';
			}
			else{
				if(Lista){
					InsertOnList(lista->lista, palavra, numLinha);
				}
				else{
					printf("%s	",palavra);
					insere_ord(raiz, palavra, numLinha);
				}
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

Lista * buscaLista(Lista * atual, char * palavra){

	while(atual->existeProximo){
		atual = atual->proximo;
		if(strcmp(atual->palavra, palavra)==0){
			return atual;
		}	
	}
	return NULL;
}

void busca(Texto texto, Lista * lista, No * raiz,char palavra[], int Lista){
	float tempo = Clock(1);
	if(Lista){
		lista = buscaLista(lista, palavra);
		tempo = Clock(0);
		if(lista == NULL){
			printf("Palavra '%s' não encontrada.\n", palavra);
		}
		else{
			printf("Existem %i ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", lista->numLinhas,palavra);
			Linhas * linha = lista->linhas;
			while(linha->existeProximo){
				linha = linha->proximo;
				printf("%05i: %s", linha->linha+1, texto.linha[linha->linha]);
			}
		}
	}
	else{
		No * no = busca_bin(raiz, palavra);
		tempo = Clock(0);
		if(no == NULL){
			printf("Palavra '%s' não encontrada.\n",palavra);
		}
		else{
			printf("Existem %i ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", no->numLinhas,palavra);
			LinhasArvore * linha = no->linhas;
			while(linha->existeProximo){
				linha = linha->proximo;
				printf("%05i: %s", linha->linha+1, texto.linha[linha->linha]);
			}
		}
	}
	printf("Tempo de busca: %f ms\n", tempo);
}
