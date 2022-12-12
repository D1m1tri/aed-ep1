#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista {
	char palavra[50];
	struct lista *proximo;
} Lista;

typedef struct {
	Lista * lista;
} Inicio;


int main(){
	Inicio lista;
	lista.lista = (Lista*) malloc(sizeof(Lista));
	FILE *arq;
	char Linha[100];
	char *result;
	int i=1;

	arq = fopen("texto.txt","rt");
	if (arq == NULL){
		printf("arquivo texto.txt não encontrado.\n");
		return 1;
	}
	result = fgets(Linha, 100, arq);
	if (result){
		printf("Linha %d: %s", i, Linha);
	}
	i=0;
	int j=0;
	Lista *atual = lista.lista;
	for(char c=Linha[0], temp[50]; c!='\n';i++){
		c = Linha[i];
		if(c >= 65 && c <= 90){
			c=c+32;
		}
		if(c != ' ' && c != ',' && c != '.' && c != '-' && c != '!' && c != '?'){
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
}
