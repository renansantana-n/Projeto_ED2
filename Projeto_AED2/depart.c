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


///FUNÇÃO QUE CRIA OS DEPARTAMENTOS
void criar_departamento(Arvn* dp){ //parametro é somente a raiz, para verificações abaixo citadas..
    setlocale(LC_ALL, "Portuguese"); //setlocale tem a função de adaptação deste programa às características de uma determinado idioma ou de uma região.
    printf("\n Digite o nome do departamento: ");
    char nomed[50];
    dpn: //label que indica o local em que o processo deve ser executado de acordo com a condição criada
    gets(nomed);
    if((strlen(nomed) == 0) || (stricmp(nomed, " ") == 0)){ //caso não tenha nada escrito ou tecle ESPAÇO, solicitará que dgite novamente
        system("cls");
        printf("\n Erro! digite o nome corretamente!\n : ");
        fflush(stdin); //limpa o buffer se nada estiver inserido, pois pode estar com o valor de ENTER
        goto dpn; //desvia a execução do comando para o Label acima criado, baseado na condição determinada
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
    if(dep == NULL){ //verificando se está vazia
        printf("\n ERRO!\n");
        exit(1);
    }
    dep -> departamento = (Depto*)malloc(sizeof(Depto)); //setando departamento à variável dep, e alocando
    if(dep -> departamento == NULL){ //verificação
        printf("\n ERRO!\n");
        exit(1);
    }
    strcpy(dep -> departamento -> nome, nomed); //passando o conteúdo da string para a variável correspondente na estrutura departamento
    strcpy(dep -> departamento -> sigla, siglad);
    dep -> prof = NULL; //como não recebeu nenhum dado sobre professor, passo o valor NULL para a dep
    dep -> prim = NULL; // dep seta prim recebe VAZIO, pois trata-se de um nó isolado
    dep -> prox = dp -> raiz; //o proximo filho da subárvore será a raiz do eventual irmão
    dp -> raiz = dep; // dp ->raiz receberá todo conteúdo de dep (Relativo ao departamento) pois dp atuará como eventual primeiro filho
    efeito_carregando(); //chamada da função com efeito
}


///FUNÇÃO AUX QUE VERIFICA SE EXISTE O DEPARTAMENTO NA ÁRVORE
static int verificar_depto(Arvn* a){
    if(a -> raiz == NULL)
        return 0;
    else
        return 1;
}  //retorna 0 se vazio, caso contrário retorna 1


///FUNÇÃO AUX QUE VERIFICA A OCORRÊNCIA DE CERTA INFORMAÇÃO NA ÁRVORE, NESSE CASO DEPARTAMENTO
static ArvnNo* buscar_departamento(Arvn* dp, char* depto){ //parametros: (raiz para o laço percorrer a partir dela, e o nome do departamento para comparação)
    ArvnNo* var_dep; //variavel utilizada para percorrer o laço
    for(var_dep = dp -> raiz; var_dep != NULL; var_dep = var_dep -> prox){
        if(strcmp(var_dep -> departamento -> sigla, depto) == 0){ //caso o conteúdo encontrado seja igual retornará tal conteudo
            return var_dep;
        }
    }
    return NULL;
}


///FUNÇÃO AUX PARA MOSTRAR OS DEPARTAMENTOS
static void exibir_departamento(Arvn* dp){ //parametro é somente a raiz, para o laço percorrer a partir dela
    setlocale(LC_ALL, "Portuguese");
    ArvnNo* aux; //variavel utilizada para percorrer o laço
    //ArvnNo* aux1;
    printf("\n Abaixo segue departamentos já cadastrados!\n\n");
    for(aux = dp -> raiz; aux != NULL; aux = aux -> prox){ //a partir da raiz, faz a verificação dos departamentos enquanto a var. aux. for diferente de vazio.
       printf(" %s - %s\n", aux -> departamento -> sigla, aux -> departamento -> nome);  //exibição dos departamentos
    }
}

