/**
*   PROJETO DE ALGORITMOS E ESTRUTURA DE DADOS II - PROF. THIAGO PEREIRA RIQUE
*   DESCRIÇÃO: O projeto é baseado em uma estrutura organizacional de uma instituição de ensino superior
                              composta por departamentos vinculados à professores.

*   AUTOR: RENAN SANTANA DO NASCIMENTO (renan.nascimento.santana@hotmail.com)
*   DATA DE CRIAÇÃO: 15/01/2020
*   VERSÃO: 1.0
*   ÚLTIMA MODIFICAÇÃO:  19/01/2020 */


//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "menu.h"
#include "arvn.h"
#include "depart.h"

int main(){
    setlocale(LC_ALL, "Portuguese");
    unsigned int op;
    unsigned int sair = 0;

    Arvn* arv = cria_arvn();

    do{
        p1:
        ExibirMenu(Qop_m, Op1, opcao1, opcao2, opcao3, opcao4, opcao5, opcao6);
        op = LerOp(Op1, Op1 + Qop_m - 1);
        switch(op){
            case Op1:
                system("cls");
                printf("\n CADASTRAMENTO DE DEPARTAMENTO:\n\n");
                criar_departamento(arv);
                limpaBuffer();
                break;

            case Op2:
                system("cls");
                printf("\n CADASTRAMENTO DE PROFESSORES:\n\n");
                criar_professor(arv);
                limpaBuffer();
                break;

            case Op3:
                system("cls");
                printf("\n LISTAGEM DE MESTRES:\n\n");
                imprime_mestres(arv);
                limpaBuffer();
                break;

            case Op4:
                system("cls");
                printf("\n LISTAGEM DE DOUTORES:\n\n");
                imprime_doutores(arv);
                limpaBuffer();
                break;

            case Op5:
                system("cls");
                arquivar_dados(arv);
                limpaBuffer();
                break;

            case Op6:
                system("cls");
                libera_arvn(arv);
                system("color 06");
                printf("\n Obrigado pelo uso!\n\n");
                return 0;

            default:
                printf("\nERRO!\n");
                limpaBuffer();
                return 1;
        }
    }while (!sair);
    return 0;
}
