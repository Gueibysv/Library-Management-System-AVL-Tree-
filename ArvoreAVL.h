#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct no* avl;
typedef struct Lista lista_emprestimo;
lista_emprestimo* criar_lista();
lista_emprestimo* inserir_lista (lista_emprestimo*l, struct no *raiz);
lista_emprestimo* remover_lista (lista_emprestimo*l, struct no  *raiz, int isbn);

avl* cria_avl();
void libera_avl(avl*raiz);
int inserir_avl(avl *raiz, int isbn, int ano, int quantidade, char *titulo, char *autores, char *editora);
int remover_avl(avl *raiz,int isbn);
int altura_avl(avl *raiz);
int totalNO_avl(avl *raiz);
struct no* consulta_avl (avl*raiz, int isbn);
void preOrdem(avl *raiz);
void emOrdem(avl *raiz);
void posOrdem(avl *raiz);


