
#include "Arvoreavl.h" //inclui os Protótipos

// Estrutura para a Arvore Balanceada
struct no{
 	int isbn, ano, quantidade;
    char autores [50];
    char titulo [50];
    char editora [50];
    int altura;
    struct no *esq;
    struct no *dir;
};
// Inicialização da estrutura da Arvore Balanceada
avl* cria_avl(){
    avl* raiz = (avl*) malloc(sizeof(avl));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}
// Remove o nó
void libera_no(struct no* no){
    if(no == NULL)
        return;
    libera_no(no->esq);
    libera_no(no->dir);
    free(no);
    no = NULL;
}
// remove a arvore balanceada
void libera_avl(avl* raiz){
    if(raiz == NULL)
        return;
    libera_no(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}
// determina a  altura do nó
int altura_no(struct no* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}
// calcula o faor de balanceamento da arvore
int fatorBalanceamento_no(struct no* no){
    return labs(altura_no(no->esq) - altura_no(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}
// verifica se a arvore está vazia
int Vazia_avl(avl *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}
// determina a altura da arvore balanceada
int altura_avl(avl *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_avl(&((*raiz)->esq));
    int alt_dir = altura_avl(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}
 // Impressão pré-ordem
void preOrdem(avl *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
       
        printf("\n Isbn:%i -  Titulo:%s -  Autores:%s -  Editora:%s -  Ano:%i - Quantidade:%i\n",(*raiz)->isbn,(*raiz)->titulo,(*raiz)->autores,(*raiz)->editora,
		(*raiz)->ano,(*raiz)->quantidade);
        preOrdem(&((*raiz)->esq));
        preOrdem(&((*raiz)->dir));
    }
}
 // Impressão em-ordem
void emOrdem(avl *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem(&((*raiz)->esq));
        printf("\n Isbn:%i -  Titulo:%s -  Autores:%s -  Editora:%s -  Ano:%i - Quantidade%i\n",(*raiz)->isbn,(*raiz)->titulo,(*raiz)->autores,(*raiz)->editora,
		(*raiz)->ano,(*raiz)->quantidade);
        emOrdem(&((*raiz)->dir));
    }
}
 // Impressão pós-ordem
void posOrdem(avl *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem(&((*raiz)->esq));
        posOrdem(&((*raiz)->dir));
       printf("\n Isbn:%i -  Titulo:%s -  Autores:%s -  Editora:%s -  Ano:%i - Quantidade%i\n",(*raiz)->isbn,(*raiz)->titulo,(*raiz)->autores,(*raiz)->editora,
		(*raiz)->ano,(*raiz)->quantidade);
    }
}
// função para pesquisar livro na arvore balanceada
avl consulta_avl (avl *raiz, int isbn){
    if(raiz == NULL)
        return NULL;
    struct no* atual = *raiz;
    while(atual != NULL){
        if(isbn == atual->isbn){
            return atual;
        }
        if(isbn > atual->isbn)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return NULL;
}

//=================================
void RotacaoLL(avl *A){//LL
    printf("RotacaoLL\n");
    struct no *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_no((*A)->esq),altura_no((*A)->dir)) + 1;
    B->altura = maior(altura_no(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(avl *A){//RR
    printf("RotacaoRR\n");
    struct no *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_no((*A)->esq),altura_no((*A)->dir)) + 1;
    B->altura = maior(altura_no(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(avl *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(avl *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}
// ==========================================================
// função para inserir livro na avl... ISBn é a nossa chave
int inserir_avl(avl *raiz, int isbn, int ano, int quantidade, char *titulo, char *autores, char *editora){
    int res;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct no *novo;
        novo = (struct no*)malloc(sizeof(struct no));
        if(novo == NULL)
            return 0;
        strcpy(novo->titulo, titulo);
        strcpy(novo->editora, editora);
        strcpy(novo->autores, autores);
        novo->quantidade = quantidade;
        novo->isbn = isbn;
		novo->ano = ano;    
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
    // ao adicionar um livro e tiverem o mesmo isbn e o mesmo nome, adicona na quantidade do livros porque são iguais
	 if(consulta_avl (raiz, isbn) != NULL && strcmp((*raiz)->titulo, titulo) == 0 ){
        	(*raiz)->quantidade++;
		}
    struct no *atual = *raiz;
    if(isbn < atual->isbn){
        if((res = inserir_avl(&(atual->esq),  isbn,  ano,  quantidade, titulo, autores, editora)) == 1){
            if(fatorBalanceamento_no(atual) >= 2){
                if(isbn < (*raiz)->esq->isbn ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(isbn > atual->isbn){
            if((res = inserir_avl(&(atual->dir), isbn,  ano,  quantidade, titulo, autores, editora)) == 1){
                if(fatorBalanceamento_no(atual) >= 2){
                    if((*raiz)->dir->isbn < isbn){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            return 0;
        }
    }

    atual->altura = maior(altura_no(atual->esq),altura_no(atual->dir)) + 1;

    return res;
}

struct no* procuraMenor(struct no* atual){
    struct no *no1 = atual;
    struct no *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}
// remoção do livro na arvore
int remover_avl(avl *raiz, int isbn){
	if(*raiz == NULL){// valor não existe
	    printf("valor não existe!!\n");
	    return 0;
	}

    int res;
	if(isbn < (*raiz)->isbn){
	    if((res = remover_avl(&(*raiz)->esq, isbn)) == 1){
            if(fatorBalanceamento_no(*raiz) >= 2){
                if(altura_no((*raiz)->dir->esq) <= altura_no((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->isbn < isbn){
	    if((res = remover_avl(&(*raiz)->dir, isbn)) == 1){
            if(fatorBalanceamento_no(*raiz) >= 2){
                if(altura_no((*raiz)->esq->dir) <= altura_no((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->isbn == isbn){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nó tem 1 filho ou nenhum
			struct no *antigo = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(antigo);
		}else { // nó tem 2 filhos
			struct no* temp = procuraMenor((*raiz)->dir);
			(*raiz)->isbn = temp->isbn;
			remover_avl(&(*raiz)->dir, (*raiz)->isbn);
            if(fatorBalanceamento_no(*raiz) >= 2){
				if(altura_no((*raiz)->esq->dir) <= altura_no((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_no((*raiz)->esq),altura_no((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_no((*raiz)->esq),altura_no((*raiz)->dir)) + 1;

	return res;
}
// função auxiliar parar remover quantidades de livros quando a função inserir livros for solicitada
int remover_quantidades(struct no*raiz){
	struct no *aux = raiz;
	
	if(aux->quantidade != 0){
		aux->quantidade--;
		return 1;
	}
	else{
		return 0;
	}
}
// função auxiliar parar adicionar quantidades de livros quando a função remover livros  for solicitada
int adicionar_quantidades(struct no*raiz){
	struct no *aux = raiz;
		aux->quantidade++;
		return 1;
}
// função para imprimir livros indisponiveis ou seja que a sua quantidade é 0
void imprimir_indisponiveis (avl*raiz){
	struct no* aux = *raiz;
	if(aux == NULL)
        return;
    if(*raiz != NULL && (*raiz)->quantidade == 0 ){
       emOrdem(raiz);
    }
    else{
    	emOrdem(&((*raiz)->esq));
        emOrdem(&((*raiz)->dir));
	}
}
// =====================================================================
// Estrutura para lista de livros
struct Lista{
	
	int isbn, ano, quantidade;
	char titulo[50], autores[50], editora[50];
	struct Lista* prox;
	
};


lista_emprestimo* criar_lista(){
	return NULL;
}

// lista de livros emprestados
lista_emprestimo* inserir_lista (lista_emprestimo*l, struct no*raiz){
	
	int resp = remover_quantidades (raiz);
	lista_emprestimo* novo = (lista_emprestimo*)malloc(sizeof(lista_emprestimo));
		novo->isbn = raiz->isbn;
		strcpy (novo->titulo, raiz->titulo);
        strcpy (novo->editora, raiz->editora);
        strcpy (novo->autores, raiz->autores);
        novo->ano = raiz->ano;
		if(resp == 1){
			novo->prox = l;
			return novo;
		}
		else{
			return NULL;
		}
}

lista_emprestimo* remover_lista (lista_emprestimo*l, struct no*raiz, int isbn){
	
	int resp = adicionar_quantidades (raiz);
	lista_emprestimo *aux = l;
	lista_emprestimo*ant=NULL;
	while((aux!=NULL) && (aux->isbn != isbn)){
		ant=aux;
		aux=aux->prox;
	}
	if(l==NULL){
		return l;
	}
	if(ant==NULL){
		l=aux->prox;
	}
	else {
		ant->prox=aux->prox;
	}
	if(resp == 1){
			free(aux);
			return l;
		}
		else{
			return NULL;
		}
}

lista_emprestimo *solicitar_livro (lista_emprestimo*l,avl*raiz, int isbn){
	struct no* resp = consulta_avl (raiz,isbn) ;
	if (consulta_avl (raiz,isbn) != NULL) {
	
		l = inserir_lista(l,resp);
		return l;
	
		}
		
	else{
		return NULL;
	}
}

lista_emprestimo *devolver_livro (lista_emprestimo*l,avl*raiz, int isbn){
	struct no* resp = consulta_avl (raiz,isbn) ;
	if (consulta_avl (raiz,isbn) != NULL){
	
		l=remover_lista(l,resp,isbn);
		return l;
	
		}
		
	else{
		
		return NULL;
	}
}

void imprimir_emprestimo(lista_emprestimo*l){
	lista_emprestimo *p;
	
	for(p=l; p!=NULL; p=p->prox){

				printf("\nIsbn: %i",p->isbn);
				printf("\nTitulo: %s",p->titulo);
				printf("\nAutores: %s",p->autores);
				printf("\nEditora: %s",p->editora);
				printf("\nAno: %i\n",p->ano);
			}
}
//==================================================== Funcoes de ficheiros =====================================================

void carregarLivros(avl*raiz){
    int isbn, ano, qtd;
    char autores [200];
    char titulo [200];
    char editora [200];


    FILE *ficheiro;
    int verificar=0;

    ficheiro = fopen("livros.txt", "r");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir arquivo ou selecao de arquivos incorreta.\n");
        return;
    }
    
    //Le os dados do ficheiro txt linha por linha

        while (fscanf(ficheiro, "%d;%d;%d;%[^;];%[^;];%[^\n]", &isbn, &ano, &qtd, titulo, autores, editora) != EOF )
        {
            //printf("%d, %d, %d, %s, %s, %s\n", isbn, ano , qtd, titulo, autores, editora);
            verificar = inserir_avl(raiz,isbn,ano,qtd,titulo,autores,editora);
        }

        if (verificar == 1)
            printf("\nTodos os livros foram carregados com Sucesso.\n\n");
        else
            printf("\nOcorreu um erro na insercao dos livros.\n");
            
    fclose(ficheiro);

}

void insercaoLivro(avl*raiz){

    int isbn, ano, qtd;
    char autores [200];
    char titulo [200];
    char editora [200];
    int res;
    int verif = 1;
            
            while(verif != 0){
            system("clear");
            printf("\n\nInsira o nome do Livro: ");
            gets(titulo);
            printf("\n\nInsira o nome do Autor do Livro: ");
            gets(autores);
            printf("\n\nInsira o nome da Editora: ");
            gets(editora);
            printf("\n\nDigite o ISBN do Livro: ");   
            scanf("%d",&isbn);
            printf("\nInsira o Ano de Publicacao do Livro: ");
            scanf("%d",&ano);
            printf("\nInsira a quantidade de Livros que deseja adicionar: ");
            scanf("%d",&qtd);
            //printf("%d, %d, %d, %s, %s, %s\n", isbn, ano , qtd, titulo, autores, editora); 
  	        res = inserir_avl(raiz, isbn,  ano,  qtd, titulo, autores, editora);
            if (res == 1)
            printf("\nLivro Salvo com Sucesso.\n");
            else
            printf("\nErro ao inserir Livro.\n");
            
            printf("Deseja continuar? \n");
            printf("SIM[1]\n");
            printf("NAO[0]\n");
            scanf("%d", &verif);

            }
    
}

//============================================== FIM FUNCOES DE FICHEIROS ======================================================






