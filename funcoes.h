#include <string.h>
typedef struct lista {	//argumentos armazenados nos elementos da lista
	int numLinhas;	//quantidade de linhas em que a palavra aparece
	int * linhas;	//linhas nas quais a palavra aparece
	char *palavra;	//palavra (em lowercase)
	struct lista *proximo;	//próxima palavra
	int existeProximo;	//indica se existe uma próxima palavra
} Lista;

typedef struct {	//base da lista ligada
	Lista * lista;
} Inicio;

typedef struct {	//armazenar o texto de forma integral
	char * linha[10000];
} Texto;

void printAll(Texto * texto, Inicio * lista, int lineNum){
	for(int i=0; i<lineNum;i++){
		printf("%02i: %s",i+1,texto->linha[i]);
	}
	Lista * atual = lista->lista;
	while(atual->existeProximo != 0){
		printf("%s	%i	",atual->palavra,atual->numLinhas);
		for(int z=0; z<atual->numLinhas; z++){
			printf("%i, ",atual->linhas[z]);
		}
		printf("\n");
	}
	printf("%s	%i	",atual->palavra,atual->numLinhas);
	for(int z=0; z<atual->numLinhas; z++){
		printf("%i, ",atual->linhas[z]);
	}
	printf("\n");
}

int getText(Texto *texto, FILE *arq){
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

void linhaEmLista(char linha[], Inicio * lista, int numLinha){
	Lista * atual; 
	atual = lista->lista;
	static int doOnce=0;
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
				printf("%s\n",palavra);
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
