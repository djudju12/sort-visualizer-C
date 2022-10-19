#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#define MIN_AMOSTRA 5 //tamanho minimo da amostra
#define CARACTERE 219
#define LARGURA_MENU 40
#define OFFSET_X 4
#define OFFSET_Y 8
#define BARRA_Y 186
#define VELOCIDADE 100

//teclas ASCII
#define K_D 80
#define K_U 72
#define K_L 75
#define K_R 77
#define ENTER 13


//Para trocar a cor das colunas no terminal
#define VERMELHO "\x1b[31m"
#define RESET "\x1b[0m"

//Para trocar a cor do background no terminal
#define VERMELHO_BG "\x001b[41;1m"
#define VERDE_BG "\x001b[42;1m"

//----VARIAVEIS GLOBAIS----//
//Dimensões
int D_X, D_Y;
//tamanho da amostra
int TAMANHO=20;
//coordenada onde começa a impressão do vetor gráfico
int X_INICIAL;
//tamanho maximo da amostra e valor maximo de um valor da amostra
int MAX_AMOSTRA, VALOR_MAXIMO;

//Linked list para fazer alteraçoes no vetor
struct node {
    int data;
    struct node *next;
};
struct node *head;


//assinatura das funções
void menuAlgoritmo(char algoritmo[]);  //lembrete: fazer alterações para dipensar o uso de ponteiros nos menus
void mainMenu();
int* gerarVetor();
void get_size_window(int *col, int *row);
void visualizarAlgoritmo(char algoritmo[], int vetor[]);
void GotoXY(int x, int y);
void maximize_window();
void alterarTamanho(); 
void visualizarVetor(int vet[]);
void insertionSort(int a[]);
void mergeSort(int a[], int l, int r);
void swapValor(int index, int valor_ant, int valor_atual, bool cor);
void imprimir(int a[]);
void swapMerge(int vet[], int l, int r);
void ShowConsoleCursor(bool showFlag);
void apagarVetor(int vetor[]);
void menuAlteracao(int vet[]);
void copy(int array[]);
void printlist();
void removerPrimeiro();
void remover(int index);
void adicionar(int index, int valor);
void adicionarPrimeiro(int valor);
void adicionarUltimo(int valor);
int* converterVetor();
void freeList();
void printBarraY();
void imprimir(int a[]);
int selecionarIndex(int vetor[], int cor);
void reprint(int vetor[]);
void bubbleSort(int vet[]);
void swapBubble(int vet[], int l, int r);
void imprimirLayout(int vet[]);

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
	printf("<1> Insertion Sort\n<2> Merge Sort\n<3> Bubble Sort\n<4> Sair\n");
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
		printf("Algoritmo selecionado: %s Sort\nTamanho da amostra: %d\n", algoritmo, TAMANHO);
		printf("<1> Iniciar ordenacao\n<2> Alterar tamanho da amostra\n<3> Modificar amostra\n<4> Gerar nova amostra aleatoria\n<5> Voltar\n");
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
					menuAlteracao(vetor);
					vetor = converterVetor();  // converte para array após as alterações
					freeList();  // libera a memoria ocupada pela lista linkada
					break;
				case '4':
					apagarVetor(vetor);
					vetor = gerarVetor();
					break;
				case '5':
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

	copy(vet);  // -> converte o vetor para uma lista linkada para realizara as operaçoes	
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

//----FUNCOES DE MANIPULACAO DA AMOSTRA----//
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

//Altera o tamanho da amostra
void alterarTamanho(){
	int coord_x = 23, coord_y = 1;
 
 	//tratamento do erro de digitação
	bool typo=false;  
	do{
		GotoXY(coord_x, coord_y);
		if(typo){
			printf(VERMELHO "(%d - %d)" RESET, MIN_AMOSTRA, MAX_AMOSTRA);
		}
		printf(VERMELHO " -> " RESET);
		ShowConsoleCursor(true);
		scanf("%d", &TAMANHO);
		typo = true;
	}while((TAMANHO < MIN_AMOSTRA) | (TAMANHO > MAX_AMOSTRA));
	system("cls");
	ShowConsoleCursor(false); 
	// redefiniçao
	X_INICIAL = LARGURA_MENU + (D_X-LARGURA_MENU-TAMANHO)/2;
}


//----ALGORITMOS DE ODERNACAO---///

// chama a funcao de ordenação
void visualizarAlgoritmo(char algoritmo[], int vetor[]){

	if(strcmp(algoritmo, "Insertion") == 0) //strcmp -> compara duas strings e retorna 0 se forem iguais
		insertionSort(vetor);
	else if((strcmp(algoritmo, "Merge") == 0)){
		mergeSort(vetor, 0, TAMANHO-1);
	}
	else if((strcmp(algoritmo, "Bubble")==0)){
		bubbleSort(vetor);
	}
	
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
			swapBubble(vet, j, j+1);
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
        	swapValor(j+1, vetor[j+1], vetor[j], false);  //swap é feito antes
            vetor[j + 1] = vetor[j];
            j = j - 1;
            swapValor(j+1, vetor[j+1], key, true);  //e depois. Se fzr os dois juntos o efeito não é tão interessante
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
	    
	    swapMerge(a, l, r);
	    Sleep(VELOCIDADE);
	}
}


//----FUNÇOES DO CONSOLE----//

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

//Funcao usada para selecionar um valor no menu de modificação de amostra
int selecionarIndex(int vetor[], int cor){
	int x=0, y=OFFSET_Y, valor, index=0, index_max=13; //index_max -> 13 valores do vetor por linha
	char c;
	bool parar = false;
	
	swapValor(index, vetor[index], vetor[index], true); 
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
			swapValor(index, vetor[index], vetor[index], false);
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
			swapValor(index, vetor[index], vetor[index], true);
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
void swapValor(int index, int valor_ant, int valor_atual, bool cor){
	//index = do valor no vetor, valor_ant = anterior, valor_atual.., cor = true -> vermelho / false -> normal
	int i;
	
	for(i=0;i<valor_ant;i++){
		GotoXY(X_INICIAL+index, D_Y-i-1);
		printf(" ");
	}
	if(!cor){
		for(i=0;i<valor_atual;i++){
			GotoXY(X_INICIAL+index, D_Y-i-1);
			printf("%c", CARACTERE);
		}
	}
	else{
		for(i=0;i<valor_atual;i++){
			GotoXY(X_INICIAL+index, D_Y-i-1);
			printf(VERMELHO "%c" RESET, CARACTERE);
		}
	}
}

//apaga um vetor
void apagarVetor(int vetor[]){
	int i, j;
	
	for(i=0;i<TAMANHO;i++){
		for(j=0;j<=VALOR_MAXIMO;j++){
			GotoXY(X_INICIAL+i, D_Y-j-1);
			printf(" ");
		}
	}
}

void swapBubble(int vet[], int l, int r){
	int i, j;
	Sleep(VELOCIDADE/4);
	
	for(i=l;i<=r;i++){
		for(j=0;j<=VALOR_MAXIMO;j++){
			GotoXY(X_INICIAL+i, D_Y-j-1);
			printf(" ");
		}
		for(j=0;j<vet[i];j++){
			GotoXY(X_INICIAL+i, D_Y-j-1);
			if(i==r)
				printf(VERMELHO "%c" RESET, CARACTERE);
			else
				printf("%c", CARACTERE);
		}
	}
	
}

// SwapValor em um array l..r, chamei de swapMerge pois os valores do Sleep foram determinados 
// conforme a ordenação do merge, se tiver que usar em outro algoritmo talvez seja necessária
// outra funcao com valores diferentes para VELOCIDADE
void swapMerge(int vet[], int l, int r){
	int i, j;
	int lenSubvetor = r-l;
	
	for(i=l;i<=r;i++){
		if(lenSubvetor>=TAMANHO/6)
			Sleep(VELOCIDADE/4);
		else
			Sleep(VELOCIDADE/2);
		swapValor(i, VALOR_MAXIMO, vet[i], true);
	}
	visualizarVetor(vet);
}

//retorna o tamanho do console
void get_size_window(int *col, int *row){
    CONSOLE_SCREEN_BUFFER_INFO cmd;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmd);
    *col = cmd.srWindow.Right - cmd.srWindow.Left +1;
    *row = cmd.srWindow.Bottom - cmd.srWindow.Top +1;
}

//move o cursor para a coordenada X, Y
void GotoXY(int x, int y){
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

//maxima a tela no inicio do programa
void maximize_window(){
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

//esconde o cursor
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

//----OPERAÇOES LINKED LIST----//

//recebe um vetor e converte para uma linked list
void copy(int array[])
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


