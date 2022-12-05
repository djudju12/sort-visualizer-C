/*
	Código: Implementação das Operações de Listas Linkadas
	Autor: Jonathan W. dos Santos
	Data: 05/12/2022
*/

#include "linkedlist.h"

typedef struct node{
    int data;
    struct node *next;
}node;

//recebe um vetor e converte para uma linked list
void copy(int array[], int tamanho)
{
    node *temp = malloc(sizeof(node));  //Reserva espaço para o primeiro nodo
  
    //Coloca o primeiro elemento do array no começo da lista
    temp->data=array[0]; 
    temp->next=NULL; 
    head = temp;
    int i;
    //Atribui o restantes dos elementos do array
    for(i=1;i<tamanho;i++)
    {
        node*temp2= malloc(sizeof(node));
        temp->next= temp2;
        temp2->data = array[i];
        temp2->next = NULL;
        temp=temp2;
     }  
}

//percorre a lista
void percorrer()
{
	node *temp;
	
	temp = head;
	while(temp != NULL){
		temp = temp->next;
	}	
}

//Printa os elemento da lista
void printlist() {
    node*temp = head;

	while(temp!= NULL){
		printf(" %d ",temp->data);
		temp=temp->next;
    }
    printf("\n");
}

//remove o primeiro elemento da lista
void removerPrimeiro()
{
	node *temp;
	
	temp = head;
	head = head->next;
	free(temp);
}

//remove um elemento em dada posicao
void remover(int index)
{
	node *temp, *posicao;
	int i = 0;
	
	posicao = malloc(sizeof(node));
	temp = head;
	
	//Percorre a lista ate que i < posicao - 1
	while(i < index - 1){
		temp = temp->next; //temp == posicao - 1
		i++;
	}
	posicao = temp->next; //posiçao guarda exatamente o elemento que será removido
	temp->next = posicao->next; //sobrescreve o valor que estava na posição index
	free(posicao); //libera a memoria de posiçao
	
}

//adicionar um elemento em dada posicao
void adicionar(int index, int valor)
{
	node *temp, *newnode;
	int i=0;
	
	newnode = malloc(sizeof(node));	
	temp = head;
	newnode->data = valor;
	newnode->next = 0;
	//Percorre a lista ate que i < posicao - 1
	while(i<index -1){
		temp = temp->next; //temp = posição
		i++;
	}
	newnode->next = temp->next; //O proximo valor do novo nodo é igual ao proximo valor do nodo temporario. 
	temp->next = newnode; //Sobrescreve o valor d temp->next 
}

//adiciona um elemento na posicao 0
void adicionarPrimeiro(int valor)
{
	node* temp;
	
	temp = malloc(sizeof(node));
	temp->data = valor;
	temp->next = head;
	head = temp;
}

//adiciona um elemento na ultima posicao
void adicionarUltimo(int valor)
{
	node *temp, *start;
	
	temp = malloc(sizeof(node));
	temp->next = 0;
	temp->data = valor;
	start = head;
	while(start->next != NULL){
		start = start->next;
	}
	start->next = temp;
}

//retorna o tamanho da lista
int lenLinkedList(){
	node *temp;
	
	temp = head;
	int i=0;
	while(temp != NULL){
		i++;
		temp = temp->next;
	}
	
	return i;
}

//converte a lista para um vetor 
int* converterVetor(){
	node *temp = head;
	int len = lenLinkedList();
	int *vetor = calloc(len, sizeof(int));
	
	int i=0;
	while(temp != NULL){
		vetor[i++] = temp->data;
		temp = temp->next;
	}
	
	return vetor;
}

//libera o espaço da list
void freeList()
{
   node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}
