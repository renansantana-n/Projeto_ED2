#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "arvn.h"

///AS ESTRUTURAS ABAIXO REPRESENTAM RESPECTIVAMENTE PROFESSOR, DEPARTAMENTO, NÓS
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

///FUNÇÃO QUE CRIA A ESTRUTURA EXTERNA QUE REPRESENTA A ÁRVORE
Arvn* cria_arvn(){ //Vazia
    Arvn* arvn = (Arvn*)malloc(sizeof(Arvn)); //Alocando a mesma
    if(arvn == NULL){ //Simples verificação, analisando se a raiz da árvore está vazia
        printf("\n ERRO!\n");
        exit(1);
    }
    arvn -> raiz = NULL; //passando o valor VAZIO para a raiz
    return arvn;  //retorno do nó raiz
}


///FUNÇÃO COM FINS DE EFEITOS VISUAIS
static void efeito_carregando(){
    printf(" ."); //representa o "." exibido na tela após determinada função ser chamada
    Sleep(100);  //tempo de exibição do printf acima
    printf(" .");
    Sleep(100);
    printf(" .");
    Sleep(100);
    printf("\n\n CONCLUÍDO!\n");
}


///FUNÇÃO AUX QUE VERIFICA SE HÁ O MESMO DEPTO INSERIDO (PELO NOME)
static ArvnNo* verifica_mesmo_dep(Arvn* a, char* depto){
    ArvnNo* depart;
    for(depart = a -> raiz; depart != NULL; depart = depart -> prox){
       if(strcmp(depart -> departamento -> nome, depto) == 0){
          return depart;
       }
    }
    return NULL;
}


///FUNÇÃO AUX QUE PERMITIRÁ A ENTRADA SOMENTE DE VALORES NUMÉRICOS
static int somente_num(const char* str){
    char *stop = 0;
    strtoul(str, &stop, 10); //converte string em long int
    return (stop - str == strlen (str));
}


///FUNÇÃO AUX QUE PERMITIRÁ A ENTRADA SOMENTE DE LETRAS
static char* LeString(char aux[121]) {
    scanf(" %120[^\n]", aux);
    int n = strlen(aux); //n recebe o tamanho de aux
    char* string = (char*) malloc((n+1)*sizeof(char));
    strcpy(string, aux); //passando o valor atual pra outra string
    int i = 0;
    while(string[i] != '\0'){
        if(isdigit(string[i])||(ispunct(string[i]))){ //isdigit verifica se o caracter é um digito decimal, ispunct verifica se o caracter é um ponto
            printf("\n ERRO!\n digite somente caracteres.\n\a : ");
            fflush(stdin);
            return LeString(aux);
        }
        i++;
    }
    return string;
}


///FUNÇÃO QUE CRIA OS DEPARTAMENTOS
void criar_departamento(Arvn* dp){ //parametro é somente a raiz, para verificações abaixo citadas..
    setlocale(LC_ALL, "Portuguese"); //setlocale tem a função de adaptação deste programa às características de uma determinado idioma ou de uma região.
    printf("\n Digite o nome do departamento: ");
    char nomed[121];
    dpn: //label que indica o local em que o processo deve ser executado de acordo com a condição criada
    LeString(nomed);
    if(!verifica_mesmo_dep(dp, nomed)){ //chamada da função que verifica a existência do mesmo nome de departamento
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
    else{
        printf("\n ERRO! Departamento com mesmo nome já inserido!\n");
        fflush(stdin);
    }
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
    printf("\n Abaixo segue departamentos já cadastrados!\n\n");
    for(aux = dp -> raiz; aux != NULL; aux = aux -> prox){ //a partir da raiz, faz a verificação dos departamentos enquanto a var. aux. for diferente de vazio.
       printf(" %s - %s\n", aux -> departamento -> sigla, aux -> departamento -> nome);  //exibição dos departamentos
    }
}

///FUNÇÃO AUX QUE VERIFICA A EXISTÊNCIA DE PROFESSORES, A PARTIR DA MATRÍCULA
static int verificar_professor(Arvn* a, int matricula){ //parametros: a raiz (para percorrer a partir dela, e a matricula para comparação)
    ArvnNo* prof; //var. aux. para percorrer o laço
    for(prof = a -> raiz; prof != NULL; prof = prof -> prox){
        ArvnNo* prof1; //var. aux. inter,a que percorrerá o laço mais interno
        for(prof1 = prof -> prim; prof1 != NULL; prof1 = prof1 -> prox){
            if(prof1 -> prof -> matricula == matricula){  //verifica se a matricula cadastrada é semelhante a alguma anteriormente cadastrada
                return 1;
            }
        }
    } return 0;
}


///FUNÇÃO AUX PARA INSERIR OS PROFESSORES, COM SEUS RESPECTIVOS DADOS, NA ÁRVORE
static Professor* cadastrar_professor(Arvn* prf){ //parametro é um nó raiz, para verificações abaixo citadas
    setlocale(LC_ALL, "Portuguese");
    char nome[121];
    char area[121];
    char titulacao[15];
    int matricula; //var OK utilizada como condição de parada do laço
    char strMat[20]; //variavel auxiliar que receberá o valor matricula digitado
    printf("\n Digite as informações solicitadas!\n");
    pt_1:
        printf(" Matrícula: ");
        gets (strMat);
        matricula = atoi(strMat); //converte o tipo string para inteiro

        if((matricula < 0) || (matricula > 9999) || (stricmp(strMat, " ") == 0) || (strlen(strMat) == 0)){
            system("cls");
            printf("\n Matrícula: ");
            fprintf(stderr, "\n Digite um valor entre 0 e 9999.\n");
            fflush(stdin);
            goto pt_1;
        }
        if (!somente_num (strMat)){
            system("cls");
            printf("\n Matrícula: ");
            fprintf (stderr, "\n Por favor, digite somente números.\n :");
            fflush(stdin);
            goto pt_1;
        }
    fflush(stdin);

    if(!verificar_professor(prf, matricula)){ //chamada da função que compara matrículas, caso não tenha sido digitado a mesma matrícula, prosseguirá o programa
        printf("\n");
        printf(" Nome: ");
        LeString(nome);
        fflush(stdin);

        printf(" Área: ");
        LeString(area);
        fflush(stdin);

        ptt:
        printf(" Titulação\n"); //pfoi implementado dessa forma para evitar erros de digitação e comparação, sendo assim o usuário escolhe seu titulo a partir das opções
        printf(" 1 - Doutor    2 - Mestre:\n ESC: ");
        int titulo; //variável auxiliar que recebe a titulação
        scanf("%i", &titulo);
        if(titulo == 1){ //casos
            strcpy(titulacao, "Doutorado"); //passando DOUTORADO para a variavel principal criada anteriormente.
            fflush(stdin);
        }
        else if(titulo == 2){
            strcpy(titulacao, "Mestrado"); //passando MESTRADO para a variavel principal criada anteriormente.
            fflush(stdin);
        }
        else{ //caso o usuário erre as opções
            system("cls");
            printf("\n ERRO! Escolha corretamente uma opção!\n\n");
            fflush(stdin);
            goto ptt;
        }
        printf("\n Aguarde a inserção\n ");
        Sleep(500); //tempo em que a frase acima estará visivel até que a função efeito seja chamada
        efeito_carregando();
        Professor* profe = (Professor*)malloc(sizeof(Professor)); //variavel do tipo Professor* que receberá todos os dados acima recebidos
        if(profe == NULL){ //verificação
            printf("\n ERRO!\n");
            exit(1);
        }
        strcpy(profe -> nome, nome); //passando os dados para a struct professor
        profe -> matricula = matricula;
        strcpy(profe -> area, area);
        strcpy(profe -> titulacao, titulacao);
        return profe; //retornando a variavel com todos valores já recebidos
    }
    else{
        return NULL;
    }
}

///FUNÇÃO QUE CRIA O PROFESSOR, ASSOCIANDO A SEU DETERMINADO DEPARTAMENTO
void criar_professor(Arvn* a){
    if(verificar_depto(a)){ //verifica o que a função Verificar_depto retornará, para continuar a execução do programa
        ArvnNo* aux; //var aux
        printf("\n Escolha a sigla correspondente: ");
        exibir_departamento(a);  //função que exibe os departamentos para o usuário escolher
        printf("\n ESC: ");
        char dep[15];
        pts:
        gets(dep);
        if((strlen(dep) == 0) || (strcmp(dep, " ") == 0)){ //comparações ..
            printf("\n Digite corretamente: ");
            fflush(stdin);
            goto pts;
        }
        fflush(stdin);
        aux = buscar_departamento(a, dep); //a variavel nó criada anteriormente  recebe a função que verifica a existência de departamentos
        if(aux != NULL){
            Professor* aux1; //var. aux. do tipo Professor*
            aux1 = cadastrar_professor(a); //recebe a função que cadastra o professor
            if(aux1 != NULL){
                ArvnNo* prof_dep; //variavel do tio nó, representa a associação entre professor e departamento
                prof_dep = (ArvnNo*)malloc(sizeof(ArvnNo)); //alocando a variável criada anteriormente
                if(prof_dep == NULL){
                    printf("\n ERRO!\n");
                    exit(1);
                }
                prof_dep -> prof = aux1; //passando o cadastro do professor realizado anteriormente, para variável tipo nó
                prof_dep -> departamento = NULL; //passando NULL para a var. aux. pq já está cadastrado esse departamento, sendo assim não foi solicitado nenhum dado relacionado a departamentio
                prof_dep -> prim = NULL;
                ArvnNo* anterior = NULL; //variavel ANTERIOR recebe valor VAZIO, pois não foi inserido nada anteriormente
                ArvnNo* proximo = aux -> prim; //Var. PROXIMO recebe a var. aux. criada que seta o eventual primeiro filho na árvore

                while(proximo != NULL && strcmp(proximo -> prof -> nome, prof_dep -> prof -> nome) < 0){ //Ordenação
                    anterior = proximo; //var. ANTERIOR receberá a var. PROXIMO, pois ela seta o primeiro filho, fazendo com que a anterior já tenha seus dados
                    proximo = proximo -> prox; //e a var. PROXIMO recebe PROXIMO->PROX, indicando que o novo valor dela será o próximo a ser recebido
                }
                prof_dep -> prox = proximo; //a var. que associa Prof e Depto irá setar a próx, que por sua vez será recebido
                if(anterior == NULL){
                    aux -> prim = prof_dep;
                }else{
                    anterior -> prox = prof_dep;
                }
            }
            else{ //caso o cadastro sejá impossivel realizar
                printf("\n Erro!\n Cadastro sem sucesso!\n\n");
            }
        }else{ //caso não exista o departamento
            printf("\n Departamento inexistente!\n\n");
        }
    }
    else{
        printf("\n Impossivel! Sem departamentos cadastrados!\n\n"); //Só aparecerá essa mensagem caso o usuário tente inserir um professor, sem ter departamentos para o mesmo
    }
}


///FUNÇÃO PARA IMPRESSÃO DE MESTRES
void imprime_mestres(Arvn* a){
    if(verificar_depto(a)){ //verificação da existência do departamento
        ArvnNo* mestres;
        for(mestres = a -> raiz; mestres != NULL; mestres = mestres -> prox){ //esse FOR percorrerá a partir da raiz, exibindo todos os mestres
            printf("\n %s\n", mestres -> departamento -> sigla); //sigla do departamento de cada mestre
            ArvnNo* aux = mestres -> prim; //var. aux criada que seta o primeiro eventual nó, para verificar...
            while(aux != NULL){ // enquanto diferente de VAZIO ...
                if(strcmp(aux -> prof -> titulacao, "Mestrado") == 0) // ... se o mesmo é mestre
                    printf(" %s\n",aux -> prof -> nome);
                aux = aux -> prox;
            }
        }
    }
    else{ //caso a função de verificar departamentos retornar 0
        printf("\n Não há departamentos inseridos!\n");
    }
}


///FUNÇÃO PARA IMPRESSÃO DE DOUTORES
void imprime_doutores(Arvn* a){
    if(verificar_depto(a)){
        ArvnNo* doutores;
        for(doutores = a -> raiz; doutores != NULL; doutores = doutores -> prox){  //esse FOR percorrerá a partir da raiz, exibindo todos os doutores
            printf(" %s\n", doutores -> departamento -> sigla); //sigla do departamento de cada doutor
            ArvnNo* aux = doutores -> prim;
            while(aux != NULL){
                if(strcmp(aux -> prof -> titulacao, "Doutorado") == 0)
                    printf(" %s\n",aux -> prof -> nome);
                aux = aux -> prox;
            }
        }
    }
    else{ //caso a função de verificar departamentos retornar 0
        printf("\n Não há departamentos inseridos!\n");
    }
}


///FUNÇÃO PARA SALVAR DADOS NO ARQUIVO
void arquivar_dados(Arvn* r){
    setlocale(LC_ALL, "Portuguese");
    if(verificar_depto(r)){
        printf("\n SALVANDO ");
        efeito_carregando(); //chamada da função de efeito
        ArvnNo* q;
        q = (ArvnNo*) malloc(sizeof(ArvnNo));
        if(q == NULL){
            printf("\n ERRO!");
            exit(1);
        }
        FILE* arq1 = fopen("Arquivo.txt", "w"); //atualizar arquivo, abre em modo escrita e permitindo inserção de informações
        for(q = r -> raiz; q != NULL; q = q ->prox){
            fprintf(arq1," %s\n", q -> departamento->sigla);

            ArvnNo* a = q -> prim;
            while(a != NULL){
                fprintf(arq1," %s \t %s \t %s \n",a -> prof -> nome, a -> prof -> area, a -> prof -> titulacao); //Exibição dos dados no arquivo
                a = a -> prox;
            }
        } fclose(arq1); //fechando arquivo
    }else{
        printf("\n Sem dados para salvamento...\n");
        Sleep(1000);
    }
}


///FUNÇÃO AUXILIAR PARA LIBERAR A MEMÓRIA, NÓ POR NÓ
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

///FUNÇÃO QUE LIBERA ESPAÇO ALOCADO NA MEMÓRIA PELA ÁRVORE, LIBERANDO TUDO
void libera_arvn (Arvn* a){
    if(a -> raiz != NULL){
        printf("\n Liberando memória usada!\n");
        efeito_carregando();
        libera(a -> raiz);
    }
    free(a);
}
