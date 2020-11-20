#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "arvn.h"

///AS ESTRUTURAS ABAIXO REPRESENTAM RESPECTIVAMENTE PROFESSOR, DEPARTAMENTO, N�S
///(CONTENDO AS ANTERIORES) E A RAIZ
struct professor{
    char nome[50];
    int matricula;
    char area[50];
    char titulacao[15];
};

struct depto{
    char nome[121];
    char sigla[10];
};

struct arvnno{
    Professor* prof;
    Depto* departamento;
    ArvnNo* prim;
    ArvnNo* prox;
};

struct arvn{
    ArvnNo* raiz;
};

///FUN��O QUE CRIA A ESTRUTURA EXTERNA QUE REPRESENTA A �RVORE
Arvn* cria_arvn(){ //Vazia
    Arvn* arvn = (Arvn*)malloc(sizeof(Arvn)); //Alocando a mesma
    if(arvn == NULL){ //Simples verifica��o, analisando se a raiz da �rvore est� vazia
        printf("\n ERRO!\n");
        exit(1);
    }
    arvn -> raiz = NULL; //passando o valor VAZIO para a raiz
    return arvn;  //retorno do n� raiz
}


///FUN��O COM FINS DE EFEITOS VISUAIS
static void efeito_carregando(){
    printf(" ."); //representa o "." exibido na tela ap�s determinada fun��o ser chamada
    Sleep(100);  //tempo de exibi��o do printf acima
    printf(" .");
    Sleep(100);
    printf(" .");
    Sleep(100);
    printf("\n\n CONCLU�DO!\n");
}


///FUN��O AUX QUE VERIFICA SE H� O MESMO DEPTO INSERIDO (PELO NOME)
static ArvnNo* verifica_mesmo_dep(Arvn* a, char* depto){
    ArvnNo* depart;
    for(depart = a -> raiz; depart != NULL; depart = depart -> prox){
       if(strcmp(depart -> departamento -> nome, depto) == 0){
          return depart;
       }
    }
    return NULL;
}


///FUN��O AUX QUE PERMITIR� A ENTRADA SOMENTE DE VALORES NUM�RICOS
static int somente_num(const char* str){
    char *stop = 0;
    strtoul(str, &stop, 10); //converte string em long int
    return (stop - str == strlen (str));
}


///FUN��O AUX QUE PERMITIR� A ENTRADA SOMENTE DE LETRAS
static char* LeString(char aux[121]) {
    scanf(" %120[^\n]", aux);
    int n = strlen(aux); //n recebe o tamanho de aux
    char* string = (char*) malloc((n+1)*sizeof(char));
    strcpy(string, aux); //passando o valor atual pra outra string
    int i = 0;
    while(string[i] != '\0'){
        if(isdigit(string[i])||(ispunct(string[i]))){ //isdigit verifica se o caracter � um digito decimal, ispunct verifica se o caracter � um ponto
            printf("\n ERRO!\n digite somente caracteres.\n\a : ");
            fflush(stdin);
            return LeString(aux);
        }
        i++;
    }
    return string;
}


///FUN��O QUE CRIA OS DEPARTAMENTOS
void criar_departamento(Arvn* dp){ //parametro � somente a raiz, para verifica��es abaixo citadas..
    setlocale(LC_ALL, "Portuguese"); //setlocale tem a fun��o de adapta��o deste programa �s caracter�sticas de uma determinado idioma ou de uma regi�o.
    printf("\n Digite o nome do departamento: ");
    char nomed[121];
    dpn: //label que indica o local em que o processo deve ser executado de acordo com a condi��o criada
    LeString(nomed);
    if(!verifica_mesmo_dep(dp, nomed)){ //chamada da fun��o que verifica a exist�ncia do mesmo nome de departamento
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
    else{
        printf("\n ERRO! Departamento com mesmo nome j� inserido!\n");
        fflush(stdin);
    }
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
    printf("\n Abaixo segue departamentos j� cadastrados!\n\n");
    for(aux = dp -> raiz; aux != NULL; aux = aux -> prox){ //a partir da raiz, faz a verifica��o dos departamentos enquanto a var. aux. for diferente de vazio.
       printf(" %s - %s\n", aux -> departamento -> sigla, aux -> departamento -> nome);  //exibi��o dos departamentos
    }
}

///FUN��O AUX QUE VERIFICA A EXIST�NCIA DE PROFESSORES, A PARTIR DA MATR�CULA
static int verificar_professor(Arvn* a, int matricula){ //parametros: a raiz (para percorrer a partir dela, e a matricula para compara��o)
    ArvnNo* prof; //var. aux. para percorrer o la�o
    for(prof = a -> raiz; prof != NULL; prof = prof -> prox){
        ArvnNo* prof1; //var. aux. inter,a que percorrer� o la�o mais interno
        for(prof1 = prof -> prim; prof1 != NULL; prof1 = prof1 -> prox){
            if(prof1 -> prof -> matricula == matricula){  //verifica se a matricula cadastrada � semelhante a alguma anteriormente cadastrada
                return 1;
            }
        }
    } return 0;
}


///FUN��O AUX PARA INSERIR OS PROFESSORES, COM SEUS RESPECTIVOS DADOS, NA �RVORE
static Professor* cadastrar_professor(Arvn* prf){ //parametro � um n� raiz, para verifica��es abaixo citadas
    setlocale(LC_ALL, "Portuguese");
    char nome[121];
    char area[121];
    char titulacao[15];
    int matricula; //var OK utilizada como condi��o de parada do la�o
    char strMat[20]; //variavel auxiliar que receber� o valor matricula digitado
    printf("\n Digite as informa��es solicitadas!\n");
    pt_1:
        printf(" Matr�cula: ");
        gets (strMat);
        matricula = atoi(strMat); //converte o tipo string para inteiro

        if((matricula < 0) || (matricula > 9999) || (stricmp(strMat, " ") == 0) || (strlen(strMat) == 0)){
            system("cls");
            printf("\n Matr�cula: ");
            fprintf(stderr, "\n Digite um valor entre 0 e 9999.\n");
            fflush(stdin);
            goto pt_1;
        }
        if (!somente_num (strMat)){
            system("cls");
            printf("\n Matr�cula: ");
            fprintf (stderr, "\n Por favor, digite somente n�meros.\n :");
            fflush(stdin);
            goto pt_1;
        }
    fflush(stdin);

    if(!verificar_professor(prf, matricula)){ //chamada da fun��o que compara matr�culas, caso n�o tenha sido digitado a mesma matr�cula, prosseguir� o programa
        printf("\n");
        printf(" Nome: ");
        LeString(nome);
        fflush(stdin);

        printf(" �rea: ");
        LeString(area);
        fflush(stdin);

        ptt:
        printf(" Titula��o\n"); //pfoi implementado dessa forma para evitar erros de digita��o e compara��o, sendo assim o usu�rio escolhe seu titulo a partir das op��es
        printf(" 1 - Doutor    2 - Mestre:\n ESC: ");
        int titulo; //vari�vel auxiliar que recebe a titula��o
        scanf("%i", &titulo);
        if(titulo == 1){ //casos
            strcpy(titulacao, "Doutorado"); //passando DOUTORADO para a variavel principal criada anteriormente.
            fflush(stdin);
        }
        else if(titulo == 2){
            strcpy(titulacao, "Mestrado"); //passando MESTRADO para a variavel principal criada anteriormente.
            fflush(stdin);
        }
        else{ //caso o usu�rio erre as op��es
            system("cls");
            printf("\n ERRO! Escolha corretamente uma op��o!\n\n");
            fflush(stdin);
            goto ptt;
        }
        printf("\n Aguarde a inser��o\n ");
        Sleep(500); //tempo em que a frase acima estar� visivel at� que a fun��o efeito seja chamada
        efeito_carregando();
        Professor* profe = (Professor*)malloc(sizeof(Professor)); //variavel do tipo Professor* que receber� todos os dados acima recebidos
        if(profe == NULL){ //verifica��o
            printf("\n ERRO!\n");
            exit(1);
        }
        strcpy(profe -> nome, nome); //passando os dados para a struct professor
        profe -> matricula = matricula;
        strcpy(profe -> area, area);
        strcpy(profe -> titulacao, titulacao);
        return profe; //retornando a variavel com todos valores j� recebidos
    }
    else{
        return NULL;
    }
}

///FUN��O QUE CRIA O PROFESSOR, ASSOCIANDO A SEU DETERMINADO DEPARTAMENTO
void criar_professor(Arvn* a){
    if(verificar_depto(a)){ //verifica o que a fun��o Verificar_depto retornar�, para continuar a execu��o do programa
        ArvnNo* aux; //var aux
        printf("\n Escolha a sigla correspondente: ");
        exibir_departamento(a);  //fun��o que exibe os departamentos para o usu�rio escolher
        printf("\n ESC: ");
        char dep[15];
        pts:
        gets(dep);
        if((strlen(dep) == 0) || (strcmp(dep, " ") == 0)){ //compara��es ..
            printf("\n Digite corretamente: ");
            fflush(stdin);
            goto pts;
        }
        fflush(stdin);
        aux = buscar_departamento(a, dep); //a variavel n� criada anteriormente  recebe a fun��o que verifica a exist�ncia de departamentos
        if(aux != NULL){
            Professor* aux1; //var. aux. do tipo Professor*
            aux1 = cadastrar_professor(a); //recebe a fun��o que cadastra o professor
            if(aux1 != NULL){
                ArvnNo* prof_dep; //variavel do tio n�, representa a associa��o entre professor e departamento
                prof_dep = (ArvnNo*)malloc(sizeof(ArvnNo)); //alocando a vari�vel criada anteriormente
                if(prof_dep == NULL){
                    printf("\n ERRO!\n");
                    exit(1);
                }
                prof_dep -> prof = aux1; //passando o cadastro do professor realizado anteriormente, para vari�vel tipo n�
                prof_dep -> departamento = NULL; //passando NULL para a var. aux. pq j� est� cadastrado esse departamento, sendo assim n�o foi solicitado nenhum dado relacionado a departamentio
                prof_dep -> prim = NULL;
                ArvnNo* anterior = NULL; //variavel ANTERIOR recebe valor VAZIO, pois n�o foi inserido nada anteriormente
                ArvnNo* proximo = aux -> prim; //Var. PROXIMO recebe a var. aux. criada que seta o eventual primeiro filho na �rvore

                while(proximo != NULL && strcmp(proximo -> prof -> nome, prof_dep -> prof -> nome) < 0){ //Ordena��o
                    anterior = proximo; //var. ANTERIOR receber� a var. PROXIMO, pois ela seta o primeiro filho, fazendo com que a anterior j� tenha seus dados
                    proximo = proximo -> prox; //e a var. PROXIMO recebe PROXIMO->PROX, indicando que o novo valor dela ser� o pr�ximo a ser recebido
                }
                prof_dep -> prox = proximo; //a var. que associa Prof e Depto ir� setar a pr�x, que por sua vez ser� recebido
                if(anterior == NULL){
                    aux -> prim = prof_dep;
                }else{
                    anterior -> prox = prof_dep;
                }
            }
            else{ //caso o cadastro sej� impossivel realizar
                printf("\n Erro!\n Cadastro sem sucesso!\n\n");
            }
        }else{ //caso n�o exista o departamento
            printf("\n Departamento inexistente!\n\n");
        }
    }
    else{
        printf("\n Impossivel! Sem departamentos cadastrados!\n\n"); //S� aparecer� essa mensagem caso o usu�rio tente inserir um professor, sem ter departamentos para o mesmo
    }
}


///FUN��O PARA IMPRESS�O DE MESTRES
void imprime_mestres(Arvn* a){
    if(verificar_depto(a)){ //verifica��o da exist�ncia do departamento
        ArvnNo* mestres;
        for(mestres = a -> raiz; mestres != NULL; mestres = mestres -> prox){ //esse FOR percorrer� a partir da raiz, exibindo todos os mestres
            printf("\n %s\n", mestres -> departamento -> sigla); //sigla do departamento de cada mestre
            ArvnNo* aux = mestres -> prim; //var. aux criada que seta o primeiro eventual n�, para verificar...
            while(aux != NULL){ // enquanto diferente de VAZIO ...
                if(strcmp(aux -> prof -> titulacao, "Mestrado") == 0) // ... se o mesmo � mestre
                    printf(" %s\n",aux -> prof -> nome);
                aux = aux -> prox;
            }
        }
    }
    else{ //caso a fun��o de verificar departamentos retornar 0
        printf("\n N�o h� departamentos inseridos!\n");
    }
}


///FUN��O PARA IMPRESS�O DE DOUTORES
void imprime_doutores(Arvn* a){
    if(verificar_depto(a)){
        ArvnNo* doutores;
        for(doutores = a -> raiz; doutores != NULL; doutores = doutores -> prox){  //esse FOR percorrer� a partir da raiz, exibindo todos os doutores
            printf(" %s\n", doutores -> departamento -> sigla); //sigla do departamento de cada doutor
            ArvnNo* aux = doutores -> prim;
            while(aux != NULL){
                if(strcmp(aux -> prof -> titulacao, "Doutorado") == 0)
                    printf(" %s\n",aux -> prof -> nome);
                aux = aux -> prox;
            }
        }
    }
    else{ //caso a fun��o de verificar departamentos retornar 0
        printf("\n N�o h� departamentos inseridos!\n");
    }
}


///FUN��O PARA SALVAR DADOS NO ARQUIVO
void arquivar_dados(Arvn* r){
    setlocale(LC_ALL, "Portuguese");
    if(verificar_depto(r)){
        printf("\n SALVANDO ");
        efeito_carregando(); //chamada da fun��o de efeito
        ArvnNo* q;
        q = (ArvnNo*) malloc(sizeof(ArvnNo));
        if(q == NULL){
            printf("\n ERRO!");
            exit(1);
        }
        FILE* arq1 = fopen("Arquivo.txt", "w"); //atualizar arquivo, abre em modo escrita e permitindo inser��o de informa��es
        for(q = r -> raiz; q != NULL; q = q ->prox){
            fprintf(arq1," %s\n", q -> departamento->sigla);

            ArvnNo* a = q -> prim;
            while(a != NULL){
                fprintf(arq1," %s \t %s \t %s \n",a -> prof -> nome, a -> prof -> area, a -> prof -> titulacao); //Exibi��o dos dados no arquivo
                a = a -> prox;
            }
        } fclose(arq1); //fechando arquivo
    }else{
        printf("\n Sem dados para salvamento...\n");
        Sleep(1000);
    }
}


///FUN��O AUXILIAR PARA LIBERAR A MEM�RIA, N� POR N�
static void libera(ArvnNo* r){
    ArvnNo* p = r -> prim;
    while (p != NULL){
        ArvnNo* t = p -> prox;
        libera(p);
        p = t;
    }
    if(r -> departamento != NULL){
        free(r -> departamento);
    }
    if(r -> prof != NULL){
        free(r -> prof);
    }
    free(r);
}

///FUN��O QUE LIBERA ESPA�O ALOCADO NA MEM�RIA PELA �RVORE, LIBERANDO TUDO
void libera_arvn (Arvn* a){
    if(a -> raiz != NULL){
        printf("\n Liberando mem�ria usada!\n");
        efeito_carregando();
        libera(a -> raiz);
    }
    free(a);
}
