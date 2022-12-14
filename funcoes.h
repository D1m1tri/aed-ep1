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
	lista->lista->existeProximo = 0;
	char palavra[50];
	char c;
	/*for (int i=0; c != '\n'; i++){
		c = linha[i];
	printf("3");
		if (c >= 65 && c <= 90){
			c=c+32;
		}
	printf("4");
		if (c==' '||c==','||c=='.'||c=='-'||c=='!'||c=='?'||c=='\n'||c=='/'){
	printf("5");
			if(strlen(palavra)>0){
				int size = (int) strlen(palavra);
				size++;
	printf("6");
				if(atual->existeProximo == 0){
					atual->proximo = (Lista*) malloc(sizeof(Lista));
					atual->existeProximo = 1;
					atual = atual->proximo;
					atual->existeProximo = 0;
					atual->numLinhas = 0;
					atual->palavra = (char *) malloc(size*sizeof(char));
				}
				else{
	printf("7");
					if(strcmp(atual->proximo->palavra,palavra)>0){
						Lista * reserva = atual->proximo;
						atual->proximo = (Lista *) malloc(sizeof(Lista));
						atual = atual->proximo;
						atual->palavra = (char *) malloc(size*sizeof(char));
						atual->proximo = reserva;
						atual->existeProximo = 1;
					}
					else{
						atual = atual->proximo;
					}
				}
	printf("8");
				if(strlen(atual->palavra)>0 || strcmp(atual->palavra,palavra) == 0){
					atual->numLinhas++;
					int i[atual->numLinhas];
					int alerta = 0;
	printf("9");
					for(int z=0; z<atual->numLinhas-1; z++){
						if(atual->linhas[z] == numLinha) alerta=1;
						i[z] = atual->linhas[z];
					}
	printf("10");
					if(alerta){
					       	atual->numLinhas--;
					}
					else{
						i[atual->numLinhas-1] = numLinha;
					}
					free(atual->linhas);
					atual->linhas = (int*) malloc(atual->numLinhas*sizeof(int));
					for(int z=0; z<atual->numLinhas; z++){
						atual->linhas[z] = i[z];
					}

					for(int g=0;g<size;g++){
						atual->palavra[g] = palavra[g];
						palavra[g] = '\0';
					}
					atual->proximo = (Lista*) malloc(sizeof(Lista));
					atual = lista->lista;
				}
			}
			else{
				palavra[0] = '\0';
			}
		}
		else{
			strncat(palavra, &c, 1);
		}
		if(c == '\0'){
			break;
		}
	}*/
}
