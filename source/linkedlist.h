/*
	Código: Declarações das Operações de Listas Linkadas
	Autor: Jonathan W. dos Santos
	Data: 05/12/2022
*/


#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

struct node *head;
//----OPERAÇOES LINKED LIST----//

//recebe um vetor e converte para uma linked list
void copy(int array[], int tamanho);

//percorre a lista
void percorrer();

void printlist();

//remove o primeiro elemento da lista
void removerPrimeiro();

//remove um elemento em dada posicao
void remover(int index);

//adicionar um elemento em dada posicao
void adicionar(int index, int valor);

//adiciona um elemento na posicao 0
void adicionarPrimeiro(int valor);

//adiciona um elemento na ultima posicao
void adicionarUltimo(int valor);

//retorna o tamanho da lista
int lenLinkedList();

//converte a lista para um vetor 
int* converterVetor();

//libera o espaço da list
void freeList();
#endif // LINKEDLIST-OPS_H_INCLUDED
