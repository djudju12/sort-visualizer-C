#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#define TAMANHO  5

struct node {
    int data;
    struct node *next;
};
struct node *head;

void copy(int array[])                         //copying array elements and create linked list
{
    struct node*temp = malloc(sizeof(struct node));
    temp->data=array[0];
    temp->next=NULL;
    head =temp;
    int i;
    for(i=1;i<TAMANHO;i++)
    {
        struct node*temp2= malloc(sizeof(struct node));
        temp->next= temp2;
        temp2->data = array[i];
        temp2->next = NULL;
        temp=temp2;
     }  
}

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
    printf("List is : ");

	while(temp!=NULL)
    {
      printf(" %d ",temp->data);
      temp=temp->next;

    }
    printf("\n");
}

void removerPrimeiro()
{
	struct node *temp;
	
	temp = head;
	head = head->next;
	free(temp);
}

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

void adicionarPrimeiro(int valor)
{
	struct node* temp;
	
	temp = malloc(sizeof(struct node));
	temp->data = valor;
	
	temp->next = head;
	head = temp;
}


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

void menuAlteracao(int vet[]){
	bool sair=false;
	copy(vet);
	
	
	while(sair==false){
		system("cls");
		printlist();
		printf("<1> Substituir\n<2> Remover\n<3> Adicionar\n<4> Salvar alteracoes\n");
		char op;
		int index, novo_valor;
		op = getch();
		switch(op){
			case '1':
				printf("Index: ");
				scanf("%d", &index);
				printf("Novo valor: ");
				scanf("%d", &novo_valor);
				if(index == 0){
					removerPrimeiro();
					adicionarPrimeiro(novo_valor);
				}
				else{
					remover(index);
					adicionar(index, novo_valor);
				}
				break;
			case '2':
				printf("index: ");
				scanf("%d", &index);
				if(index == 0)
					removerPrimeiro();
				else
					remover(index);
				break;
			case '3':
				printf("Valor: ");
				scanf("%d", &novo_valor);
				adicionarUltimo(novo_valor);
				break;
			case '4':
				sair = true;
				break;
		}
	}
}

int main() {
    int array[] = {10, 40, 30, 20, 50}, i;
	
	menuAlteracao(array);
	
	int* novo_array = converterVetor();
	
	for(i=0;i<lenLinkedList();i++)
		printf("%d ", novo_array[i]);
	
	free(novo_array);
	

}
