typedef struct linha {
	int linha;
	struct linha * proximo;
	int existeProximo;
} LinhasArvore;

typedef struct no {
	int numLinhas;
	LinhasArvore * linhas;
	char * palavra;
	struct no * esq;
	struct no * dir;
} No;

typedef struct arvore {
	No * raiz;
} Arvore;

Arvore * criarArvore(){
	Arvore * novo = (Arvore *) malloc(sizeof(Arvore));;
	novo->raiz = NULL;
	return novo;
}

No * criarNo(char * palavra){					// cria um novo Nó e retorna seu ponteiro
	No * novo = (No *) malloc(sizeof(No));
	novo->numLinhas = 0;
	novo->linhas = (LinhasArvore *) malloc(sizeof(LinhasArvore));
	int size = strlen(palavra);
	size++;
	novo->palavra = (char *) malloc(size*sizeof(char));
	for(int i=0; i<size; i++){
		novo->palavra[i] = palavra[i];
	}
	strcpy(novo->palavra, palavra);
	novo->esq = NULL;
	novo->dir = NULL;
}

void insertLineArvore(LinhasArvore * linhaAtual, int lineNum){	// insere uma linha no Nó
	int noRepeat = 1;
	while(linhaAtual->existeProximo == 1){
		linhaAtual = linhaAtual->proximo;
		if(linhaAtual->linha == lineNum){
			noRepeat = 0;
		}
	}
	if(noRepeat){
		linhaAtual->existeProximo = 1;
		linhaAtual->proximo = (LinhasArvore *) malloc(sizeof(LinhasArvore));
		linhaAtual = linhaAtual->proximo;
		linhaAtual->linha = lineNum;
		linhaAtual->existeProximo = 0;
	}
}

void insereOrd(No * raiz, char * palavra, int linha){// insere uma palavra nova
	printf("%s\n", raiz->palavra);
	if(strcmp(raiz->palavra, palavra) == 0){
		raiz->numLinhas++;
		insertLineArvore(raiz->linhas, linha);
	}
	else{
		if(strcmp(raiz->palavra, palavra) < 0){
			if(raiz->esq){
				insereOrd(raiz->esq, palavra, linha);
			}
			else{
				raiz->esq = criarNo(palavra);
				insertLineArvore(raiz->dir->linhas, linha);
			}
		}
		else{
			if(raiz->dir){
				insereOrd(raiz->dir, palavra, linha);
			}
			else{
				raiz->dir = criarNo(palavra);
				insertLineArvore(raiz->dir->linhas, linha);
			}
		}
	}
}

void insere_ord(Arvore * raiz, char * palavra, int linha){
	if(raiz->raiz){
		insereOrd(raiz->raiz, palavra, linha);
	}
	else{
		raiz->raiz = criarNo(palavra);
		insertLineArvore(raiz->raiz->linhas, linha);
	}
}


No * busca_bin(No * raiz, char* palavra){	// busca por uma palavra (parte recursiva)
	if(raiz){
		if(strcmp(raiz->palavra, palavra) == 0){
			return raiz;
		}
		if(strcmp(raiz->palavra, palavra) < 0){
			return busca_bin(raiz->esq, palavra);
		}
		else{
			return busca_bin(raiz->dir, palavra);
		}
	}
	else{
		return NULL;
	}
}

void printArvore(No * raiz){
	if(raiz->esq){
		printArvore(raiz->esq);
	}
	if(raiz->dir){
		printArvore(raiz->dir);
	}
	if(strlen(raiz->palavra) < 8){
		printf("%s		   %i		", raiz->palavra, raiz->numLinhas);
	}
	else{
		printf("%s	    %i		", raiz->palavra, raiz->numLinhas);
	}
	/*LinhasArvore * linAtual = raiz->linhas;
	while(linAtual->existeProximo==1){
		linAtual = linAtual->proximo;
		printf("%i, ", linAtual->linha);
	}*/
	printf("\n");
}
