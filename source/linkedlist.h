/*
	C�digo: Declara��es das Opera��es de Listas Linkadas
	Autor: Jonathan W. dos Santos
	Data: 05/12/2022
*/


#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

struct node *head;
//----OPERA�OES LINKED LIST----//

// recebe um vetor e converte para uma linked list
void copy(int array[], int tamanho);

// percorre a lista
void percorrer();

void printlist();

// remove o primeiro elemento da lista
void removerPrimeiro();

// remove um elemento na posicao index
void remover(int index);

// adiciona um elemento na posicao
void adicionar(int index, int valor);

// adiciona um elemento na posicao 0
void adicionarPrimeiro(int valor);

// adiciona um elemento na ultima posicao
void adicionarUltimo(int valor);

// retorna o tamanho da lista
int lenLinkedList();

// converte a lista para um vetor 
int* converterVetor();

// libera o espa�o da lista
void freeList();

#endif // LINKEDLIST-OPS_H_INCLUDED
