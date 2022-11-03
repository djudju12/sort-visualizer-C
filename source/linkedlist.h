#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

struct node {
    int data;
    struct node *next;
};
struct node *head;

void adicionar(int index, int valor);
void adicionarPrimeiro(int valor);
void adicionarUltimo(int valor);
int* converterVetor();
void copy(int array[], int tamanho);
void freeList();
void percorrer();
int lenLinkedList();
void printlist();
void removerPrimeiro();
void remover(int index);

#endif // LINKEDLIST-OPS_H_INCLUDED
