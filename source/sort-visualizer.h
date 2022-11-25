#ifndef SORTVISUALIZER_H
#define SORTVISUALIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include "linkedlist.h"
#include "console.h"

#define MIN_AMOSTRA 5 //tamanho minimo da amostra
#define CARACTERE 219
#define LARGURA_MENU 40
#define OFFSET_X 4
#define OFFSET_Y 10
#define BARRA_Y 186
#define VEL_MIN 10
#define VEL_MAX 999

//teclas ASCII
#define K_D 80
#define K_U 72
#define K_L 75
#define K_R 77
#define ENTER 13


//Para trocar a cor das colunas no terminal
#define VERMELHO "\x1b[31m"
#define VERDE "\x1b[32m"
#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"

//Para trocar a cor do background no terminal
#define VERMELHO_BG "\x001b[41;1m"
#define VERDE_BG "\x001b[42;1m"

//----VARIAVEIS GLOBAIS----//
// Dimensões
int D_X, D_Y;
// Tamanho da amostra
int TAMANHO=20;
// Coordenada onde começa a impressão do vetor gráfico
int X_INICIAL;
// Tamanho maximo da amostra e valor maximo de um valor da amostra
int MAX_AMOSTRA, VALOR_MAXIMO;

//assinatura das funções
void menuAlgoritmo(char algoritmo[]);  //lembrete: fazer alterações para dipensar o uso de ponteiros nos menus
void mainMenu();
int* gerarVetor();
void visualizarAlgoritmo(char algoritmo[], int vetor[], int velocidade);
void alterarTamanho(); 
void visualizarVetor(int vet[]);
void insertionSort(int a[], int velocidade);
void mergeSort(int a[], int l, int r, int velocidade);
void trocarColuna(int index, int valor_atual, int cor);
void imprimir(int a[]);
void trocarVetor(int vet[], int l, int r, int velocidade);
void apagarVetor(int l, int r);
void menuAlteracao(int vet[]);
void printBarraY();
void imprimir(int a[]);
int selecionarIndex(int vetor[], int cor);
void reprint(int vetor[]);
void trocarBubble(int vet[], int l, int r, int velocidade);
void imprimirLayout(int vet[]);
void apagarColuna(int index);
void alterarVelocidade(int *velocidade);
void quickSort(int vet[], int low, int high, int velocidade);
int partition(int vet[], int low, int high);
void swap(int *a, int *b);
void bubbleSort(int vet[], int velocidade);
void substituirValor(int index);
int receberValor(int posx, int posy);
void removerValor(int index);
void quickSort3(int *vet, int l, int r, int velocidade);
int p3(int *vet, int left, int right, int *lt, int *gt);

#endif

