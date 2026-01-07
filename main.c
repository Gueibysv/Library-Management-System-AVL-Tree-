#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.c"

int main(){
    avl* arv; 
    arv = cria_avl();
    lista_emprestimo *lp;
    lp = criar_lista();
	int isbn, ano, quantidade, isbn2= 333,ano2,quantidade2 = 0, isbn3;
    char autores [50], autores2 [50];
    char titulo [50], titulo2 [50] = "sdsd";
    char editora [50], editora2 [50];
    
    
    
    
    scanf("%s",&titulo);
    
       scanf("%s",&editora);
       
          scanf("%s",&autores);
          
             scanf("%d",&isbn);
             
             scanf("%d",&ano);
             
             scanf("%d",&quantidade);
             
             
    int res,res2;
  	res = inserir_avl(arv, isbn,  ano,  quantidade, titulo, autores, editora);	
  	res2 = inserir_avl(arv, isbn2,  ano,  quantidade, titulo, autores, editora);	
  	
 	lp = solicitar_livro (lp,arv, isbn);
 	imprimir_indisponiveis(arv);
    printf("\n\n");
     printf("\nAVL tree:\n");
     emOrdem(arv);
    printf("\n\n");
    imprimir_emprestimo(lp);
    
   	lp = solicitar_livro (lp,arv, isbn2);
   	printf("\n\n");
     printf("\nAVL tree:\n");
     emOrdem(arv);
    printf("\n\n");
    imprimir_emprestimo(lp);

//
//    int NR = 4, dadosR[4] = {7,51,3,5};
//    for(i=0;i<NR;i++){
//        printf("\nRemovendo: %d\n",dadosR[i]);
//        res = remove_ArvAVL(avl,dadosR[i]);
//        printf("\n\nres = %d\n",res);
//        preOrdem_ArvAVL(avl);
//        //printf("\n\n");
//    }
//
//    printf("\nAVL tree:\n");
//    preOrdem_ArvAVL(avl);
//    printf("\n\n");

   

    libera_avl(arv);

    return 0;
}
