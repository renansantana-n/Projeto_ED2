#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "arvn.h"
#include "depart.h"

struct depto{
    char nome[60];
    char sigla[10];
};

struct arvnno{
    Professor* prof;
    Depto* departamento;
    ArvnNo* prim;
    ArvnNo* prox;
};


///FUN��O QUE CRIA OS DEPARTAMENTOS
void criar_departamento(Arvn* dp){ //parametro � somente a raiz, para verifica��es abaixo citadas..
    setlocale(LC_ALL, "Portuguese"); //setlocale tem a fun��o de adapta��o deste programa �s caracter�sticas de uma determinado idioma ou de uma regi�o.
    printf("\n Digite o nome do departamento: ");
    char nomed[50];
    dpn: //label que indica o local em que o processo deve ser executado de acordo com a condi��o criada
    gets(nomed);
    if((strlen(nomed) == 0) || (stricmp(nomed, " ") == 0)){ //caso n�o tenha nada escrito ou tecle ESPA�O, solicitar� que dgite novamente
        system("cls");
        printf("\n Erro! digite o nome corretamente!\n : ");
        fflush(stdin); //limpa o buffer se nada estiver inserido, pois pode estar com o valor de ENTER
        goto dpn; //desvia a execu��o do comando para o Label acima criado, baseado na condi��o determinada
    }
    fflush(stdin); //limpa o buffer
    printf("\n Digite a sigla do departamento acima criado: ");
    char siglad[20];
    dps:
    gets(siglad);
    if((strlen(siglad) == 0) || (stricmp(siglad, " ") == 0)){
        system("cls");
        printf("\n Erro! digite a sigla corretamente!\n : ");
        fflush(stdin);
        goto dps;
    }
    fflush(stdin);
    ArvnNo* dep = (ArvnNo*)malloc(sizeof(ArvnNo)); //alocando a variavel do tipo ArvnNo*  para posteriormente passar os valores correspondentes ao Departamento
    if(dep == NULL){ //verificando se est� vazia
        printf("\n ERRO!\n");
        exit(1);
    }
    dep -> departamento = (Depto*)malloc(sizeof(Depto)); //setando departamento � vari�vel dep, e alocando
    if(dep -> departamento == NULL){ //verifica��o
        printf("\n ERRO!\n");
        exit(1);
    }
    strcpy(dep -> departamento -> nome, nomed); //passando o conte�do da string para a vari�vel correspondente na estrutura departamento
    strcpy(dep -> departamento -> sigla, siglad);
    dep -> prof = NULL; //como n�o recebeu nenhum dado sobre professor, passo o valor NULL para a dep
    dep -> prim = NULL; // dep seta prim recebe VAZIO, pois trata-se de um n� isolado
    dep -> prox = dp -> raiz; //o proximo filho da sub�rvore ser� a raiz do eventual irm�o
    dp -> raiz = dep; // dp ->raiz receber� todo conte�do de dep (Relativo ao departamento) pois dp atuar� como eventual primeiro filho
    efeito_carregando(); //chamada da fun��o com efeito
}


///FUN��O AUX QUE VERIFICA SE EXISTE O DEPARTAMENTO NA �RVORE
static int verificar_depto(Arvn* a){
    if(a -> raiz == NULL)
        return 0;
    else
        return 1;
}  //retorna 0 se vazio, caso contr�rio retorna 1


///FUN��O AUX QUE VERIFICA A OCORR�NCIA DE CERTA INFORMA��O NA �RVORE, NESSE CASO DEPARTAMENTO
static ArvnNo* buscar_departamento(Arvn* dp, char* depto){ //parametros: (raiz para o la�o percorrer a partir dela, e o nome do departamento para compara��o)
    ArvnNo* var_dep; //variavel utilizada para percorrer o la�o
    for(var_dep = dp -> raiz; var_dep != NULL; var_dep = var_dep -> prox){
        if(strcmp(var_dep -> departamento -> sigla, depto) == 0){ //caso o conte�do encontrado seja igual retornar� tal conteudo
            return var_dep;
        }
    }
    return NULL;
}


///FUN��O AUX PARA MOSTRAR OS DEPARTAMENTOS
static void exibir_departamento(Arvn* dp){ //parametro � somente a raiz, para o la�o percorrer a partir dela
    setlocale(LC_ALL, "Portuguese");
    ArvnNo* aux; //variavel utilizada para percorrer o la�o
    //ArvnNo* aux1;
    printf("\n Abaixo segue departamentos j� cadastrados!\n\n");
    for(aux = dp -> raiz; aux != NULL; aux = aux -> prox){ //a partir da raiz, faz a verifica��o dos departamentos enquanto a var. aux. for diferente de vazio.
       printf(" %s - %s\n", aux -> departamento -> sigla, aux -> departamento -> nome);  //exibi��o dos departamentos
    }
}

