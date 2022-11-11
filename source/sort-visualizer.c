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
#define OFFSET_Y 9
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
// Velocidade
int VELOCIDADE=100;

//assinatura das funções
void menuAlgoritmo(char algoritmo[]);  //lembrete: fazer alterações para dipensar o uso de ponteiros nos menus
void mainMenu();
int* gerarVetor();
void visualizarAlgoritmo(char algoritmo[], int vetor[]);
void alterarTamanho(); 
void visualizarVetor(int vet[]);
void insertionSort(int a[]);
void mergeSort(int a[], int l, int r);
void trocarColuna(int index, int valor_atual, int cor);
void imprimir(int a[]);
void trocarVetor(int vet[], int l, int r);
void apagarVetor(int l, int r);
void menuAlteracao(int vet[]);
void printBarraY();
void imprimir(int a[]);
int selecionarIndex(int vetor[], int cor);
void reprint(int vetor[]);
void bubbleSort(int vet[]);
void trocarBubble(int vet[], int l, int r);
void imprimirLayout(int vet[]);
void apagarColuna(int index);
void alterarVelocidade();
void quickSort(int vet[], int low, int high);
int partition(int vet[], int low, int high);
void swap(int *a, int *b);


//FUNÇÃO PRINCIPAL 
int main(){
	
	maximize_window();
	get_size_window(&D_X, &D_Y);
	ShowConsoleCursor(false);
	
	//definições iniciais
	X_INICIAL = LARGURA_MENU + (D_X-LARGURA_MENU-TAMANHO)/2; // -> começa a impressao das barras
	MAX_AMOSTRA = D_X - LARGURA_MENU - OFFSET_X;  // -> tamanho maximo da amostra
	VALOR_MAXIMO = D_Y - 1;  // ->  valor maximo de cada item da amostra
	if(VALOR_MAXIMO>99)
		VALOR_MAXIMO = 99;

	// começa o programa
	mainMenu();
	
	return 0;
}


//----FUNÇÕES DO MENU----//
void mainMenu(){
	char opc;

	do{
	//Menu inicial
	printf("Bem-vindo ao visualizador de algoritmos de ordenacao\n");
	printf("<1> Insertion Sort\n<2> Merge Sort\n<3> Bubble Sort\n<4> Quick Sort\n<5> Sair\n");
	opc=getch();
		switch(opc){
			case '1':
				menuAlgoritmo("Insertion");
				break;
			case '2':
				menuAlgoritmo("Merge");
				break;
			case '3':
				menuAlgoritmo("Bubble");
				break;
			case '4':
				menuAlgoritmo("Quick");
				break;
			case '5':
				exit(0);
			default:
				system("cls"); //-> se nao limpar a tela buga!
		}
	}while(1);
}

void menuAlgoritmo(char algoritmo[]){
	char opc, controle='1';
	int *vetor;
	
	vetor = gerarVetor();
	do{
		imprimirLayout(vetor);
		//Menu que será mostrado após selecionar um dos algoritmos
		printf("Algoritmo selecionado: %s Sort\nTamanho da amostra: %d\tVelocidade: %d%%\n", algoritmo, TAMANHO, VELOCIDADE);
		printf("<1> Iniciar ordenacao\n<2> Alterar tamanho\n<3> Alterar velocidade\n<4> Modificar amostra\n<5> Gerar nova amostra aleatoria\n<6> Voltar\n");
		opc=getch();
		
			switch(opc){
				case '1':
					visualizarAlgoritmo(algoritmo, vetor);
					break;
				case '2':
					alterarTamanho();
					vetor = gerarVetor(TAMANHO);
					break;
				case '3':
					alterarVelocidade();
					break;
				case '4':
					menuAlteracao(vetor);
					vetor = converterVetor();  // converte para array após as alterações
					freeList();  // libera a memoria ocupada pela lista linkada
					break;
				case '5':
					apagarVetor(0, TAMANHO);
					vetor = gerarVetor();
					break;
				case '6':
					system("cls");
					controle = '0';
					break;
				default:
					system("cls");  // -> se a tela nao for limpa sempre, ela buga (?!)
			}
	}while(controle=='1');
	free(vetor); 
}

// A maneira que encontrei para fazer as operações na lista foi convertela para uma lista linkada e depois converter para 
// um array novamente.
void menuAlteracao(int vet[]){
	bool sair=false;
	char op;
	int index, novo_valor;

	copy(vet, TAMANHO);  // -> converte o vetor para uma lista linkada para realizara as operaçoes	
	do{
		imprimirLayout(converterVetor());
		printf("<1> Substituir\n<2> Remover\n<3> Adicionar\n<4> Voltar\n\nValor minimo: %d\nValor maximo: %d", 1, VALOR_MAXIMO);
		op = getch();
		switch(op){
			case '1':
				index = selecionarIndex(converterVetor(), 2);  // -> seleciona o index com as setas
				GotoXY(0, OFFSET_Y-1);
				printf("Novo valor: ");
				scanf("%d", &novo_valor);
				
				// caso index -> 0, preciso usar a funcao de remover e adicionar primeiro, nao da pra usar o index -> 0 no adicionar e remover em dado index
				if(novo_valor<=VALOR_MAXIMO && novo_valor>0){
					if(index == 0){  
						removerPrimeiro();
						adicionarPrimeiro(novo_valor);
					}
					else{
						remover(index);
						adicionar(index, novo_valor);
					}
				}
				break;
			case '2':
				if(lenLinkedList()>MIN_AMOSTRA){
					index = selecionarIndex(converterVetor(), 1);
					if(index == 0)
						removerPrimeiro();
					else
						remover(index);
				}
				break;
			case '3':
				if(lenLinkedList()<MAX_AMOSTRA){
					GotoXY(0, OFFSET_Y-1);
					printf("Novo valor: ");
					scanf("%d", &novo_valor);
					if(novo_valor<=VALOR_MAXIMO && novo_valor>0)
						adicionarUltimo(novo_valor);
				}
				break;
			case '4':
				sair = true;
				system("cls");
				break;
		}
		// redefinição dos valores 
		TAMANHO = lenLinkedList();
		X_INICIAL = LARGURA_MENU + (D_X-LARGURA_MENU-TAMANHO)/2;
	}while(sair==false);
}

void imprimirLayout(int vet[]){
	system("cls");
	visualizarVetor(vet);  // -> barras
	printBarraY();  // -> barra vertical do menu
	imprimir(vet);  // -> vetor numérico
}

// imprime o vetor numério abaixo do menu.
void imprimir(int a[]){
	int x=0, i;
	
	int pular_linha=0;
	for(i=0;i<TAMANHO;i++){
		GotoXY(x, OFFSET_Y + pular_linha);
		if(a[i]<10)
			printf("0%d", a[i]);
		else
			printf("%d", a[i]);
		x+=3;
		if(x>=LARGURA_MENU-1){
			pular_linha++;
			x = 0;
		}
	}
	GotoXY(0, 0);
}

// Altera o tamanho da amostra
void alterarTamanho(){
	int coord_x = 0, coord_y = OFFSET_Y-1, aux;
 
	GotoXY(coord_x, coord_y);
	printf(VERMELHO "(%d - %d) -> " RESET, MIN_AMOSTRA, MAX_AMOSTRA);
	ShowConsoleCursor(true);
	fflush(stdin);
	scanf("%d", &aux);
	if((aux >= MIN_AMOSTRA) && (aux <= MAX_AMOSTRA))
		TAMANHO = aux;
	ShowConsoleCursor(false); 
	// redefiniçao
	X_INICIAL = LARGURA_MENU + (D_X-LARGURA_MENU-TAMANHO)/2;
}

void alterarVelocidade(){
	int coord_x = 0, coord_y = OFFSET_Y-1;
	float aux;
 
	GotoXY(coord_x, coord_y);
	printf(VERMELHO "(%d%% - %d%%) -> " RESET, VEL_MIN, VEL_MAX);
	ShowConsoleCursor(true);
	fflush(stdin);
	scanf("%f", &aux);
	if((aux>=10) && (aux <= 999))
		VELOCIDADE = aux;
	ShowConsoleCursor(false); 
}


//Funcao usada para selecionar um valor no menu de modificação de amostra
int selecionarIndex(int vetor[], int cor){
	int x=0, y=OFFSET_Y, valor, index=0, index_max=13; //index_max -> 13 valores do vetor por linha
	char c;
	bool parar = false;
	
	trocarColuna(index, vetor[index], true); 
	// Quando um botão é pressionado, apaga o anterior e printa o background no novo index
	while(parar==false){
		GotoXY(x,y);
		
		switch(cor){
			case 1:
				if(vetor[index]>9)
					printf(VERMELHO_BG "%d" RESET, vetor[index]);
				else
					printf(VERMELHO_BG "0%d" RESET, vetor[index]);
				break;
			case 2:
				if(vetor[index]>9)
					printf(VERDE_BG "%d" RESET, vetor[index]);
				else
					printf(VERDE_BG "0%d" RESET, vetor[index]);
				break;
		}

		if(kbhit()){
			c = getch();
			trocarColuna(index, vetor[index], false);
			GotoXY(x,y);
			// ENTER -> retorna a funcao sem apagar o anterior
			if(c != ENTER){
				if(vetor[index]>9)
					printf("%d", vetor[index]);
				else
					printf("0%d", vetor[index]);
			}
			// x+=3 pois sao 3 valores de x-> unidade, dezena e espaço separando o proximo numero
			switch(c){
				case ENTER:
					parar = true;
					break;
				case K_D:
					if(index+index_max<TAMANHO){
						index+=index_max;
						y++;
					}
					break;
				case K_U:
					if(y>OFFSET_Y){
						index-=index_max;
						y--;
					}
					break;
				case K_L:
					if(x>0){
						index--;
						x-=3;
					}
					break;
				case K_R:
					if(index<TAMANHO-1 && x<LARGURA_MENU-OFFSET_X){
						index++;
						x+=3;
					break;
					}
				}
			trocarColuna(index, vetor[index], true);
		}
	}
	return index;
}

void printBarraY(){
	int i;
	
	for(i=0;i<=D_Y;i++){
		GotoXY(LARGURA_MENU, i);
		printf("%c", BARRA_Y);
	}
	GotoXY(0,0);
}

//----ALGORITMOS DE ODERNACAO---///

// chama a funcao de ordenação
void visualizarAlgoritmo(char algoritmo[], int vetor[]){

	if(strcmp(algoritmo, "Insertion") == 0) //strcmp -> compara duas strings e retorna 0 se forem iguais
		insertionSort(vetor);
	else if((strcmp(algoritmo, "Merge") == 0))
		mergeSort(vetor, 0, TAMANHO-1);
	else if((strcmp(algoritmo, "Bubble") == 0))
		bubbleSort(vetor);
	else if((strcmp(algoritmo, "Quick") == 0))
		quickSort(vetor, 0, TAMANHO - 1);
	
	GotoXY(0, 0);  // volta o cursor para o inicio após a ordenação
}

void bubbleSort(int vet[]){
	int i, j, temp;
	
	for(i=0;i<TAMANHO;i++){
		visualizarVetor(vet);
		for(j=0;j<TAMANHO-i-1;j++){
			if(vet[j]>vet[j+1]){
				temp = vet[j];
				vet[j] = vet[j+1];
				vet[j+1] = temp;
			}
			trocarBubble(vet, j, j+1);
		}
	}
}

void insertionSort(int vetor[]){
	int i, j, key;
	  
    for (i = 1; i < TAMANHO; i++) {
    	visualizarVetor(vetor);
        key = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > key) {
        	trocarColuna(j+1, vetor[j], false);  //swap é feito antes
            vetor[j + 1] = vetor[j];
            j = j - 1;
            trocarColuna(j+1, key, true);  //e depois. Se fzr os dois juntos o efeito não é tão interessante
            vetor[j + 1] = key;
            Sleep(VELOCIDADE/2);
        }
    }
}

// fonte -> https://www.programiz.com/dsa/merge-sort
// deixei os comentários originais 
// Merge two subarrays L and M into arr
void merge(int a[], int p, int q, int r) {

	// Create L ? A[p..q] and M ? A[q+1..r]
	int n1 = q - p + 1;
	int n2 = r - q;
	int L[n1], M[n2], i, j, k = p;
	
	for (i = 0; i < n1; i++)
		L[i] = a[p + i];
	for (j = 0; j < n2; j++)
    	M[j] = a[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  i = 0;
  j = 0;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
	while (i < n1 && j < n2) {
		if (L[i] <= M[j]) {
			a[k] = L[i];
			i++;
	}
		else {
      		a[k] = M[j];
			j++;
    }
    	k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
	while (i < n1) {
		a[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		a[k] = M[j];
    	j++;
    	k++;
	}
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int a[], int l, int r) {
	if (l < r) {
	    // m is the point where the array is divided into two subarrays
	    int m = l + (r - l) / 2;
		
	    mergeSort(a, l, m);
	    mergeSort(a, m + 1, r);
	
	    // Merge the sorted subarrays
	    merge(a, l, m, r);
	    
	    trocarVetor(a, l, r);
	}
}

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;	
}

int partition(int vet[], int low, int high)
{
	int pivot = vet[high]; // -> posicao a direita
	trocarColuna(high, pivot, 3);
	int i = (low - 1); // -> posicao do menor elemento, essa posicao é guardada para trocar os valores 
	int j;
	
	for(j = low; j <= high - 1; j++)
	{
		if(vet[j] < pivot)
		{
			i++; 
			swap(&vet[i], &vet[j]); // coloca todos os numeros menores que o pivo para a esquerda
		}
	}
	swap(&vet[i + 1], &vet[high]);  //a posicao i+1 é a posicao do primeiro valor que é maior ou igual ao pivo, essa instrução posiciona o pivo no lugar correto
	// assim, os valores maiores estarão para a direita e os menores estarão para a esquerda
	return (i + 1); //retorna a posicao do pivot
}

void quickSort(int vet[], int low, int high)
{
	if(low < high)
	{
		int pi = partition(vet, low, high);
		trocarVetor(vet, low, high);
		
		quickSort(vet, low, pi - 1); 
		quickSort(vet, pi + 1, high);
	}
}
//------FUNÇÕES DE VISUALIZAÇÃO DOS ALGORITMOS------//

//imprime o vetor inteiro
void visualizarVetor(int vet[]){
	int i, j;
	//system("cls");
	
	for(i=0;i<TAMANHO;i++){
		for(j=0;j<vet[i];j++){
			GotoXY(X_INICIAL+i, D_Y-j-1);
			printf("%c", CARACTERE);
		}
	}
	GotoXY(0, 0);
}

//função que apaga uma coluna e printa uma nova com valor diferente
void trocarColuna(int index, int valor_atual, int cor){
	//index = do valor no vetor, valor_ant = anterior, valor_atual.., cor = true -> vermelho / false -> normal
	int i;
	
	apagarColuna(index);
	
	for(i=0;i<valor_atual;i++){
		GotoXY(X_INICIAL+index, D_Y-i-1);
		switch(cor){
			case 0:
				printf("%c", CARACTERE);
				break;
			case 1:
				printf(VERMELHO "%c" RESET, CARACTERE);
				break;
			case 2:
				printf(VERDE "%c" RESET, CARACTERE);
				break;
			case 3:
				printf(AZUL "%c" RESET, CARACTERE);
				break;
		}
	}
}

// Apaga uma coluna
void apagarColuna(int index){
	int i;
	
	for(i=0;i<VALOR_MAXIMO;i++){
		GotoXY(X_INICIAL+index, D_Y-i-1);
		printf(" ");
	}
}

// Apaga um vetor
void apagarVetor(int l, int r){
	int i, j;
	
	for(i=l;i<r;i++){
		for(j=0;j<=VALOR_MAXIMO;j++){
			GotoXY(X_INICIAL+i, D_Y-j-1);
			printf(" ");
		}
	}
}

// Função usada para trocar os valores das colunas do algoritmo Bubble Sort
void trocarBubble(int vet[], int l, int r){
	int i, j;
	Sleep(VELOCIDADE/4);
	
	apagarVetor(l, r);
	for(i=l;i<=r;i++){
		for(j=0;j<vet[i];j++){
			GotoXY(X_INICIAL+i, D_Y-j-1);
			if(i==r)
				printf(VERMELHO "%c" RESET, CARACTERE);
			else
				printf("%c", CARACTERE);
		}
	}
	
}

// Troca os valores de um vetor [l...r] alterando a velocidade
void trocarVetor(int vet[], int l, int r){
	int i, j;
	int lenSubvetor = r-l;
	
	for(i=l;i<=r;i++){
		if(lenSubvetor>=TAMANHO/6)
			Sleep(VELOCIDADE/4);
		else
			Sleep(VELOCIDADE/2);
		
		trocarColuna(i, vet[i], 1);
		if(i>0)
			trocarColuna(i-1, vet[i-1], 0);
	}
	trocarColuna(r, vet[r], 0);
}

//----GERA AMOSTRA----//
int* gerarVetor(){
	//funcao calloc para armazenar o vetor no heap para poder utilizar em outro escopo
	int *vetor = calloc(TAMANHO, sizeof(int)), i; 
	
	/* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
	com o valor da função time(NULL). Desta forma, a cada execução o valor 
	da "semente" será diferente.
	*/
	srand(time(NULL));
	
	for(i=0;i<TAMANHO;i++)
		vetor[i] = 1 + (rand() % VALOR_MAXIMO);  // valores aleatorios de 1 - VALOR_MAXIM
	
	return vetor;
}


