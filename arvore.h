typedef struct linha {
	int linha;
	struct linha * proximo;
	int existeProximo;
} LinhasArvore;

typedef struct _no_arvore_ {
	LinhasArvore * linhas;
	char * palavra;
	int aparicoes;
	struct _no_arvore_ * esq;
	struct _no_arvore_ * dir;
} No;

typedef struct {
	No * raiz;
} Arvore;








No * busca_bin_rec(No * no, char* palavra){	// busca por uma palavra (parte recursiva)

	if(no){

		if(!strcmp(no->palavra, palavra)) return no;
		if(strcmp(no->palavra, palavra) < 0) return busca_bin_rec(no->esq, palavra);
		return busca_bin_rec(no->dir, palavra);
	}

	return NULL;
}
No * busca_bin(Arvore * arvore, char* palavra){	// busca por uma palavra (parte a ser chamada)
	
	return busca_bin_rec(arvore->raiz, palavra);	
}



No * criarNo(){					// cria um novo Nó e retorna seu ponteiro
	No * novo = (No *)malloc(sizeof(No));
	novo->esq = novo->dir = NULL;
	novo->linhas = (LinhasArvore *) malloc(sizeof(LinhasArvore));
	novo->aparicoes = 0;
	return novo;
}

Arvore * cria_arvore(){				// cria a base da Arvore
	Arvore * arvore = (Arvore *) malloc (sizeof(Arvore));
	arvore->raiz = criarNo();	
	return arvore;
}

void insertLineArvore(LinhasArvore * linhaAtual, int lineNum){
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

void insere_ord_rec(No * raiz, char * palavra, int linha){// insere uma palavra nova (recursão)

	if(strcmp(raiz->palavra, palavra)){
		if(strcmp(raiz->palavra, palavra) < 0){
			if(raiz->esq){
				insere_ord_rec(raiz->esq, palavra, linha);
			}
			else{ 
				raiz->esq = criarNo();
				raiz = raiz->esq;
			}
		}
		else{
			if(raiz->dir){
				insere_ord_rec(raiz->dir, palavra, linha);
			}
			else{
				raiz->dir = criarNo();
				raiz=raiz->dir;
			}
		}
		strcpy(raiz->palavra, palavra);
	}
	if(!raiz->palavra){
		strcpy(raiz->palavra, palavra);
	}
	insertLineArvore(raiz->linhas, linha);
	raiz->aparicoes++;
}

void insere_ord(Arvore * arvore, char* palavra, int linha){// insere uma palavra nova (chamar)
	insere_ord_rec(arvore->raiz, palavra, linha);
}
