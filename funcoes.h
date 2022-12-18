#include <string.h>
#include <time.h>


typedef struct linhas {	//linhas nas quais uma determinada palavra aparece
	int linha;
	int existeProximo;
	struct linhas *proximo;
} Linhas;

typedef struct lista {	//argumentos armazenados nos elementos da lista
	int numLinhas;	//quantidade de linhas em que a palavra aparece
	Linhas * linhas;	//linhas nas quais a palavra aparece
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



typedef struct _no_arvore_ {
	int* linhas;
	char* palavra;
	int contador;
	int posLivre;
	struct _no_arvore_ * esq;
	struct _no_arvore_ * dir;

} No;

typedef struct {

	No * raiz;

} Arvore;




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

void InsertOnList(Lista * atual, char palavra[], int lineNum){ //insere uma palavra na lista ligada em ordem alfabética
	int size = strlen(palavra);
	size++;
	int doit=1;
	while(doit){
		if(atual->existeProximo==0){
			atual->proximo = (Lista*) malloc(sizeof(Lista));
			atual->existeProximo = 1;
			atual = atual->proximo;
			atual->linhas = (Linhas*) malloc(sizeof(Linhas));
			atual->linhas->existeProximo = 0;
			atual->existeProximo = 0;
			atual->numLinhas = 0;
			doit=0;
		}else{
		if(strcmp(atual->proximo->palavra,palavra)>0){
			Lista * temp = atual->proximo;
			atual->proximo = (Lista*) malloc(sizeof(Lista));
			atual = atual->proximo;
			atual->linhas = (Linhas*) malloc(sizeof(Linhas));
			atual->linhas->existeProximo = 0;
			atual->existeProximo = 1;
			atual->numLinhas = 0;
			atual->proximo = temp;
			doit=0;
		}else{
		if(strcmp(atual->proximo->palavra,palavra) == 0){
			atual = atual->proximo;
			doit=0;
		}else{
		atual = atual->proximo;
		}
		}
		}
	}
	if(atual->palavra == NULL){
		atual->palavra = (char*) malloc(size*sizeof(char));
	}
	for(int i=0; i<size; i++){
		atual->palavra[i] = palavra[i];
	}
	atual->numLinhas++;

	Linhas * linhaAtual = atual->linhas;
	int alert = 0;
	while(linhaAtual->existeProximo == 1){
		linhaAtual = linhaAtual->proximo;
		if(linhaAtual->linha == lineNum){
			alert = 1;
		}
	}
	if(alert == 0){
		linhaAtual->existeProximo = 1;
		linhaAtual->proximo = (Linhas*) malloc(sizeof(Linhas));
		linhaAtual = linhaAtual->proximo;
		linhaAtual->linha = lineNum;
		linhaAtual->existeProximo = 0;
	}
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Arvore * cria_arvore(){
	Arvore * arvore = (Arvore *) malloc (sizeof(Arvore));
	arvore->raiz = NULL;	
	return arvore;
}

No * busca_rec(No * no, char* palavra){

	No * aux;
	
	if(no){

		if(strcmp(no->palavra, palavra) == 0) return no;

		aux = busca_rec(no->esq, palavra);
		if(aux) return aux;
	
		return busca_rec(no->esq, palavra);

	}

	return NULL;
}

No * busca(Arvore * arvore, char* palavra){
	
	return busca_rec(arvore->raiz, palavra);	
}

void insere(Arvore * arvore, No * pai, char* palavra, int linha){

	No* novo = (No *) malloc(sizeof(No));
	
	strcpy (novo->palavra, palavra);
	novo->esq = novo->dir = NULL;

	if(!busca(arvore, palavra)){
		novo->contador = 1;
		novo->posLivre = 0;
		novo->linhas[novo->posLivre] = linha;
		novo->posLivre++;

		if(pai){

			if(strcmp(pai->palavra, palavra) > 0){
				novo->esq = pai->esq;
				pai->esq = novo;
			}
			else{
				novo->esq = pai->dir;
				pai->dir = novo;
			}
		}
		else{
			novo->esq = arvore->raiz;
			arvore->raiz = novo;
		}
	}
	else{
		novo = busca(arvore, palavra);
		novo->contador++;
		novo->linhas[novo->posLivre] = linha;
		novo->posLivre++;
	}
	
	
}
No * encontra_pai(No * pai, No * no){
	
	No* aux;

	if(pai){

		if(!strcmp(pai->esq->palavra, no->palavra) || !strcmp(pai->esq->palavra, no->palavra)) return pai;


		aux = encontra_pai(raiz->esq, no);
		if(aux) return aux;

		return encontra_pai(pai->dir, no);
	}

	return NULL;
}
