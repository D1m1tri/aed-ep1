#include <string.h>
typedef struct lista {
	char *palavra;
	struct lista *proximo;
} Lista;

typedef struct {
	Lista * lista[10000];
} Inicio;

void linhaEmLista(char linha[], Inicio * lista, int numLinha){
	lista->lista[numLinha] = (Lista *) malloc(sizeof(Lista));
	Lista *atual = lista->lista[numLinha];
	atual->proximo = NULL;
	char palavra[50];
	char c;
	for (int i=0; c != '\n'; i++){
		c = linha[i];
		if (c >= 65 && c <= 90){
			c=c+32;
		}
		if (c==' '||c==','||c=='.'||c=='-'||c=='!'||c=='?'||c=='\0'){
			int size = (int) strlen(palavra);
			size++;
			atual->palavra = (char*) malloc(size*sizeof(char));
			for (int g=0; g<size; g++){
				atual->palavra[g] = palavra[g];
				palavra[g] = '\0';
			}
			atual->proximo = (Lista*) malloc(sizeof(Lista));
			atual = atual->proximo;
			atual->proximo = NULL;
			while(c==' '||c==','||c=='.'||c=='-'||c=='!'||c=='?'){
				i++;
				c = linha[i];
			}
			i--;
			c = linha[i];
		}
		else{
			strncat(palavra, &c, 1);
		}
		if(c == '\0'){
			break;
		}
	}
}

void printLista(Lista * atual){
	while(atual->proximo != NULL){
		printf("%s\n", atual->palavra);
		atual = atual->proximo;
	}
}
