#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "menu.h"

///FUNÇÃO QUE LIMPA O BUFFER, LÊ E DESCARTA CARACTERES NA ENTRADA
void limpaBuffer(){
	int valorLido; //valor tem que ser inteiro
	do{
		valorLido = getchar(); //pega o valor digitado
	}
	while((valorLido != '\n') && (valorLido != EOF)); //vai pegando o valor digitado
}


///CASO USUÁRIO ERRE DIVERSAS VEZES, A APLICAÇÃO SERÁ ENCERRADA
static int limitar_erro(int erro){
    if(erro == 5){ //quantidade máxima permitida de erros
        system("cls");
        printf("\n\a DESCULPE, VOCÊ ERROU DIVERSAS VEZES\n APLICAÇÃO ENCERRADA!\n\n");
        exit(1);
    }
    return erro;
}


static int somente_num(const char* str){
    char *stop = 0;
    strtoul(str, &stop, 10); //converte string em long int
    return (stop - str == strlen (str));
}

///FUNÇÃO QUE RECEBE O VALOR DIGITADO
int LerOp(int menorValor, int maiorValor){
	int op;
	char* a;
	int erro = 0;
	while(1){
		printf("\n Digite sua opcao: ");
        scanf(" %i", &op);
        somente_num(a);
		if(op >= menorValor && op <= maiorValor){
			limpaBuffer();
			break;
		}else{
		    erro = erro + 1;
		    limitar_erro(erro);
			printf("\n Opção inválida! Tente novamente.");
			printf("\n A opção deve estar entre %i e %i. \n", menorValor, maiorValor);
			limpaBuffer();
		}
	}
	return op;
}


///FUNÇÃO QUE EXIBE O MENU
void ExibirMenu(int nItens, int menorOpcao, ...){
	va_list argumentos;
	va_start(argumentos, menorOpcao);
	system("cls");
	printf("\n\tMENU DE OPÇÕES\t\n\n");
	int i;
	for(i = 0; i < nItens; i++){
		printf(" %i %s \n", menorOpcao++, va_arg(argumentos, char *));
	}
	va_end(argumentos);
}
