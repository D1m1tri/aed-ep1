typedef struct linhas {
	int linha;
	struct linhas * proximo;
	int existeProximo;
} Linhas;

typedef struct lista {
	int numLinhas;
	Linhas * linhas;
	char * palavra;
	struct lista * proximo;
	int existeProximo;
} Lista;

typedef struct {
	Lista * lista;
} Inicio;

void ini(Inicio * atual){
	atual->lista = (Lista*) malloc(sizeof(Lista));
}

void createList(Lista * atual, Lista * substituto){	//cria um Nó novo e zera os valores
	atual->proximo = (Lista *) malloc(sizeof(Lista));
	atual->existeProximo = 1;
	atual = atual->proximo;
	atual->linhas = (Linhas *) malloc(sizeof(Linhas));
	atual->linhas->existeProximo = 0;
	atual->existeProximo=0;
	if(substituto){
		atual->proximo = substituto;
		atual->existeProximo=1;
	}
	atual->palavra = NULL;
	atual->numLinhas = 0;
}

void insertLine(Linhas * linhaAtual, int lineNum){
	int noRepeat = 1;
	while(linhaAtual->existeProximo == 1){
		linhaAtual = linhaAtual->proximo;
		if(linhaAtual->linha == lineNum){
			noRepeat = 0;
		}
	}
	if(noRepeat){
		linhaAtual->existeProximo = 1;
		linhaAtual->proximo = (Linhas *) malloc(sizeof(Linhas));
		linhaAtual = linhaAtual->proximo;
		linhaAtual->linha = lineNum;
		linhaAtual->existeProximo = 0;
	}
}

void InsertOnList(Lista * atual, char palavra[], int lineNum){
	int doit = 1;
	while(doit){
		if(atual->existeProximo == 0){
			createList(atual, NULL);
			doit = 0;
		}else{
		
		if(strcmp(atual->proximo->palavra, palavra) > 0){
			createList(atual, atual->proximo);
			doit = 0;
		}else{

		if(strcmp(atual->proximo->palavra, palavra) == 0){
			doit = 0;
		}else{

		atual = atual->proximo;
		}}}
	}
	int size = strlen(palavra);
	size++;
	atual = atual->proximo;
	if(atual->palavra == NULL){
		atual->palavra = (char *) malloc(size*sizeof(char));
		for(int i=0; i<size; i++){
			atual->palavra[i] = palavra[i];
		}
	}
	atual->numLinhas++;
	insertLine(atual->linhas, lineNum);
}
