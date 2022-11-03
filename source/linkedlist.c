#include "linkedlist.h"

//----OPERAÇOES LINKED LIST----//

//recebe um vetor e converte para uma linked list
void copy(int array[], int tamanho)
{
    struct node*temp = malloc(sizeof(struct node));
    temp->data=array[0];
    temp->next=NULL;
    head =temp;
    int i;
    for(i=1;i<tamanho;i++)
    {
        struct node*temp2= malloc(sizeof(struct node));
        temp->next= temp2;
        temp2->data = array[i];
        temp2->next = NULL;
        temp=temp2;
     }  
}

//percorre a lista
void percorrer()
{
	struct node* temp;
	
	temp = head;
	while(temp != NULL){
		temp = temp->next;
	}	
}

void printlist() {
    struct node*temp = head;

	while(temp!=NULL){
		printf(" %d ",temp->data);
		temp=temp->next;
    }
    printf("\n");
}

//remove o primeiro elemento da lista
void removerPrimeiro()
{
	struct node *temp;
	
	temp = head;
	head = head->next;
	free(temp);
}

//remove um elemento em dada posicao
void remover(int index)
{
	struct node *temp, *posicao;
	int i = 0;
	
	posicao = malloc(sizeof(struct node));
	temp = head;
	while(i < index - 1){
		temp = temp->next;
		i++;
	}
	posicao = temp->next;
	temp->next = posicao->next;
	free(posicao);
	
}

//adicionar um elemento em dada posicao
void adicionar(int index, int valor)
{
	struct node *temp, *newnode;
	int i=0;
	
	newnode = malloc(sizeof(struct node));	
	temp = head;
	newnode->data = valor;
	newnode->next = 0;
	while(i<index -1){
		temp = temp->next;
		i++;
	}
	newnode->next = temp->next;
	temp->next = newnode;
}

//adiciona um elemento na posicao 0
void adicionarPrimeiro(int valor)
{
	struct node* temp;
	
	temp = malloc(sizeof(struct node));
	temp->data = valor;
	temp->next = head;
	head = temp;
}

//adiciona um elemento na ultima posicao
void adicionarUltimo(int valor)
{
	struct node *temp, *start;
	
	temp = malloc(sizeof(struct node));
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
	struct node *temp;
	
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
	struct node *temp = head;
	int len = lenLinkedList(), i=0;
	int *vetor = calloc(len, sizeof(int));
	
	while(temp != NULL){
		vetor[i++] = temp->data;
		temp = temp->next;
	}
	
	return vetor;
}

//libera o espaço da list
void freeList()
{
   struct node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

