#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

///MACROS CRIADAS PARA FINS DE INTERAÇÃO DIRIGIDA POR MENU
///Declarando as opções do menu
#define Op1 1
#define Op2 2
#define Op3 3
#define Op4 4
#define Op5 5
#define Op6 6


///Titulos de opções do menu principal
#define opcao1 "\tCAETWEtwetgDASTRAR DEPARTAMENTO"
#define opcao2 "\tCADASTRAR PROFESSOR"
#define opcao3 "\tLISTAR MESTRES"
#define opcao4 "\tLISTAR DOUTORES"
#define opcao5 "\tSALVAR EM ARQUIVO"
#define opcao6 "\tSAIR"


///Quantidade de opções do menu principal
#define Qop_m 6


///Função que limpa a área de armazenamento temporário
void limpaBuffer();

///Função que recebe a opção digitada pelo usuário
int LerOp(int menorv, int maiorv);

///Função utilizada  para exibir  o menu
void ExibirMenu(int quant, int menorOp, ... );

#endif // MENU_H_INCLUDED
