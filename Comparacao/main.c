#include "lista.h"
#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc,char* argv[])
{
    /*
    Sao necesssarios pelo menos 4 parametros para inicializar o programa.
    argv[1] = quantidade de elementos iniciais
    argv[2] = quantidade de elementos que vai ser incrementada em cada iteração
    argv[3]= quantidade de elementos finais
    argv[4]= local de arquivo de saida;
    */

    printf("\nSao necesssarios pelo menos 4 parametros para inicializar o programa.\n");

    int inicio, step, fim;
    char file_name[] = "resultado.txt";
    printf("Quantidade de elementos iniciais\n");
    scanf("%d", &inicio);

    printf("Quantidade de elementos que vai ser incrementada em cada iteração\n");
    scanf("%d", &step);

    printf("Quantidade de elementos finais\n");
    scanf("%d", &fim);

    Node *lista = create_linked_list();  //Lista
    ABB *abb = NULL; //Árvore de Busca Binária

    int number;
    srand(time(NULL));
    FILE* arq=fopen(file_name,"wt"); //arquivo de saida
    long tempo_lista, tempo_abb;
    int i,j;
    int op,op2;
    for( i=inicio;i<=fim;i+=step){ //varios testes sao realizados, comecando com "inicio" elementos ate "fim"  elementos

        lista = NULL;
        abb = NULL;
        printf("Realizando Teste com %d elementos\n",i);

        for(j=0;j<i;j++){//insere "i" quantidade de elementos para esse teste
            number=rand()%i; //numero  aleatorio
            lista = insert_node(lista,number); // adiciona número na lista.
            abb = insert_abb(abb,number); // adiciona número na abb.
        }
        int* sortedNumbers= (int*) malloc(sizeof(int)*i);
        for( j=0;j<i;j++){
           sortedNumbers[j]=rand()%i; //define os numeros que serao procurados. (sempre aleatorios)
        }

        op=0;
         for(j=0;j<i;j++){
           search_node(lista,sortedNumbers[j],&op);//procura na lista
        }
        op2=0;
         for( j=0;j<i;j++){
           search_abb(abb,sortedNumbers[j],&op2); //procura na abb
        }
        fprintf(arq,"%d %lf %lf\n",i,op/(double)i,op2/(double)i); //imprimi a quantidade de elementos inseridos/procurados
                                                                //  e a media de operações para achar um elemento.

        //Libera a memoria alocada para esse teste.
        free(sortedNumbers);
        free_list(lista);
        free_abb(abb);
    }
    fclose(arq);

    return 0;
}
