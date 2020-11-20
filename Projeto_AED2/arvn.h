#ifndef ARVN_H_INCLUDED
#define ARVN_H_INCLUDED

typedef struct professor Professor;
typedef struct depto Depto;
typedef struct arvnno ArvnNo;
typedef struct arvn Arvn;

/// - FUNÇÕES:
Arvn* cria_arvn(); //Cria a árvore

void criar_departamento(Arvn* dp); //cria os departamentos para inserir os professores

void criar_professor(Arvn* a); //recebe os dados dos professores, criando-os

void imprime_mestres(Arvn* a); //Lista os mestres

void imprime_doutores(Arvn* a); //Lista os doutores

void arquivar_dados(Arvn* r); //Salva os dados no arquivo txt

void libera_arvn(Arvn* a); //libera a memória, desalocando tudo


#endif // ARVN_H_INCLUDED
