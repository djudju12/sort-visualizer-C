/*
	Trabalho de Programa��o P/ Resolu��o de Problemas - Visualizador de algoritmos
	Alunos: Jonathan Santos,
	Data: 06/12/2022
*/

#ifndef SORTVISUALIZER_H
#define SORTVISUALIZER_H

//-----Bibliotecas-----//

#include <stdio.h>	   
#include <stdlib.h>	   
#include <time.h>	   
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include "linkedlist.h"
#include "console.h"

//----------------------//

//------Constantes------//

#define MIN_AMOSTRA 5		// tamanho minimo da amostra
#define CARACTERE 219		// caractere que compoe as barras 
#define LARGURA_MENU 40 	// largura do menu 
#define OFFSET_X 4			// distanciamento das barras do vetor com o menu e o canto direito 
#define OFFSET_Y 10			// altura do menu
#define BARRA_Y 186			// caractere que forma a barra separa o menu do visualizador
#define VEL_MIN 10		
#define VEL_MAX 999   
                        
// teclas ASCII -> key_down/up/left/right
#define K_D 80
#define K_U 72
#define K_L 75
#define K_R 77
#define ENTER 13

// constantes p/ trocar a cor dos caracteres no console
#define VERMELHO "\x1b[31m"
#define VERDE "\x1b[32m"
#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"

// constantes p/ trocar a cor do background no console
#define VERMELHO_BG "\x001b[41;1m"
#define VERDE_BG "\x001b[42;1m"

//----------------------//

//-------GLOBAIS-------//

// Dimens�es da tela
typedef struct tela{
	int dx;
	int dy;
}TELA;
TELA dimensoes;

// Tamanho da amostra
int TAMANHO;  

// Coordenada onde come�a a impress�o do vetor gr�fico
int X_INICIAL;

// Tamanho maximo da amostra e valor maximo de um valor da amostra
int MAX_AMOSTRA, VALOR_MAXIMO;

//----------------------//

//-------FUN��ES-------//


void mainMenu();                   											// Menu para selecionar o algoritmo
void menuAlgoritmo(char algoritmo[]);   									// Recebe uma string com o nome do algoritmo selecionado. Cont�m as op��es relacionadas ao algoritmo
void alterarTamanho();														// Altera a variavel TAMANHO
void menuAlteracao(int vet[]);												// Menu de altera��o da amostra 
void alterarVelocidade(int *velocidade);									// Menu de altera��o da velocidade
int receberValor(int posx, int posy);   									// Fun��o auxiliar que retorna um valor digitado pelo us�rio na posi��o x, y
void printBarraY();															// Printa a barra vertical do menu
void imprimirLayout(int vet[]); 											// Imprime o layout do menu
int selecionarIndex(int vetor[], int cor); 									// Seleciona um index usando as setas do teclado. Cores do background 1 -> vermelho, 2 -> verde
void substituirValor(int index);
void removerValor(int index);

int* gerarVetor();															// Gera um vetor aleat�rio com tamanho = TAMANHO
void visualizarAlgoritmo(char algoritmo[], int vetor[], int velocidade);	// Roda a fun��o de ordena��o do algoritmo selecionado
void visualizarVetor(int vet[]);											// Printa o vetor em barras
void imprimir(int a[]);														// Printa o vetor n�merico no menu

void trocarColuna(int index, int valor_atual, int cor);						// Troca uma coluna na posicao INDEX. Cores: 0 -> normal, 1 -> vermelho, 2 -> verde, 3 -> azul
void trocarVetor(int vet[], int l, int r, int velocidade);					// Troca as colunas um subvetor l-r do vetor[]
void apagarVetor(int l, int r);												// apaga um vetor de barras
void trocarBubble(int vet[], int l, int r, int velocidade);					// Funciona como o trocarColuna, por�m especifico para o BubbleSort
void apagarColuna(int index);												// Apaga uma barra 

// Algoritmos de ordena��o
void insertionSort(int a[], int velocidade);
void mergeSort(int a[], int l, int r, int velocidade);
void quickSort3(int *vet, int l, int r, int velocidade);
int p3(int *vet, int left, int right, int *lt, int *gt);
void bubbleSort(int vet[], int velocidade);
void quickSort(int vet[], int low, int high, int velocidade);
int partition(int vet[], int low, int high);
void swap(int *a, int *b);

//----------------------//

#endif

