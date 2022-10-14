//----TODO---//
// 2 - Mostrar os numeros do vetor sendo ordenados na tela junto com o grafico -> de preferencia com um background vermelho no numero que esta sendo movido
// 3 - valores maximos dinamicos
// 4 - velocidade -> alteravel pelo usuario ou com rela��o ao algoritmo/tamanho da amostra?
// 5 - implementar o restante dos algoritmos


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

//setas
#define K_D 80
#define K_U 72
#define K_L 75
#define K_R 77


//Tempo que o programa esperar� a cada itera��o das ordena��o, garantindo um efeito visual. 
//LEMBRETE: pode ser implementado uma velocidade din�mica dependendo do usuario ou do algoritmo
//!!MUDAR AQUI PARA DEIXAR O PROGRAMA MAIS RAPIDO!!
#define VELOCIDADE 200

//Para trocar a cor das colunas no terminal
#define VERMELHO "\x1b[31m"
#define RESET "\x1b[0m"

//Para trocar a cor do background no terminal
#define VERMELHO_BG "\x001b[41;1m"
#define VERDE_BG "\x001b[42;1m"

//----VARIAVEIS GLOBAIS----//
//Dimens�es
int D_X, D_Y;
//tamanho da amostra
int TAMANHO=20;
//coordenada onde come�a a impress�o do vetor gr�fico
int X_INICIAL;
//tamanho maximo da amostra e valor maximo de um valor da amostra
int MAX_AMOSTRA, VALOR_MAXIMO;

//Linked list para fazer altera�oes no vetor
struct node {
    int data;
    struct node *next;
};
struct node *head;


//assinatura das fun��es
void menuAlgoritmo(char algoritmo[]);  //lembrete: fazer altera��es para dipensar o uso de ponteiros nos menus
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
int selecionarValor(int vetor[], int vermelho);

//FUN��O PRINCIPAL
int main(){
	
	maximize_window();
	get_size_window(&D_X, &D_Y);
	ShowConsoleCursor(false);
	
	//defini��es dos padr�es
	X_INICIAL = LARGURA_MENU + (D_X-LARGURA_MENU-TAMANHO)/2;
	MAX_AMOSTRA = D_X - LARGURA_MENU - OFFSET_X;
	VALOR_MAXIMO = D_Y - 1; // O MENOS 1 DO SANTO -> preciso controlar o valor maximo ainda n ta implementado
	mainMenu();
	
	return 0;
}


//FUN��ES DO MENU
void mainMenu(){
	char controle = '1', opc;
	
	do{
	//Menu inicial
	printf("Bem-vindo ao visualizador de algoritmos de ordenacao\n");
	printf("<1> Insertion Sort\n<2> Merge Sort\n<3> Bubble Sort\n<4> Sair\n");
	opc=getch();
		
		//da clear na tela e chama a funcao escolhida
		switch(opc){
			case '1':
				system("cls");
				menuAlgoritmo("Insertion");
				break;
			case '2':
				system("cls");
				menuAlgoritmo("Merge");
				break;
			case '3':
				system("cls");
				menuAlgoritmo("Bubble");
				break;
			case '4':
				exit(0);
			default:
				system("cls");
				printf("OPCAO INVALIDA!\n<1> Para Reiniciar <2> Para sair\n");
				controle = getch();
				system("cls");
		}
	}while(controle=='1');
}

void menuAlgoritmo(char algoritmo[]){
	char opc, controle='1';
	int *vetor;
	bool aleatorio=true, parar=false;
	
	do{
		//Menu que ser� mostrado ap�s selecionar um dos algoritmos
		if(!aleatorio && !parar){
			vetor = converterVetor();
			freeList();
		}
		else if(aleatorio && !parar)
			vetor = gerarVetor(TAMANHO);
		visualizarVetor(vetor);
		printBarraY();
		imprimir(vetor);
		printf("Algoritmo selecionado: %s Sort\nTamanho da amostra: %d\n", algoritmo, TAMANHO);
		printf("<1> Iniciar ordenacao\n<2> Alterar tamanho da amostra\n<3> Modificar amostra\n<4> Gerar nova amostra aleatoria\n<5> Voltar\n");
		opc=getch();
		
			switch(opc){
				case '1':
					system("cls");
					visualizarAlgoritmo(algoritmo, vetor);
					parar = true;
					break;
				case '2':
					alterarTamanho();
					break;
				case '3':
					menuAlteracao(vetor);
					aleatorio = false;
					break;
				case '4':
					apagarVetor(vetor);
					parar = false;
					aleatorio = true;
					break;
				case '5':
					system("cls");
					controle = '0';
					break;
				default:
					system("cls");
					printf("OPCAO INVALIDA!\n<1> Para Reiniciar <2> Para sair\n");
					controle = getch();
					system("cls");
			}
	}while(controle=='1');
	free(vetor);  //nao esquecer de liberar a memoria apos alocar manualmente no gerarVetor();
}

void menuAlteracao(int vet[]){
	bool sair=false;
	char op;
	int index, novo_valor;
	copy(vet);
	
	do{
		system("cls");
		visualizarVetor(converterVetor());
		printBarraY();
		//printlist();
		imprimir(converterVetor(vet));
		printf("<1> Substituir\n<2> Remover\n<3> Adicionar\n<4> Voltar\n");
		op = getch();
		switch(op){
			case '1':
				index = selecionarValor(converterVetor(), 2);
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
				index = selecionarValor(converterVetor(), 1);
				if(index == 0)
					removerPrimeiro();
				else
					remover(index);
				break;
			case '3':
				GotoXY(0, OFFSET_Y-1);
				printf("Valor: ");
				scanf("%d", &novo_valor);
				adicionarUltimo(novo_valor);
				break;
			case '4':
				sair = true;
				break;
		}
		TAMANHO = lenLinkedList();
		X_INICIAL = LARGURA_MENU + (D_X-LARGURA_MENU-TAMANHO)/2;
	}while(sair==false);
}

//----FUNCOES DE MANIPULACAO DA AMOSTRA----//
int* gerarVetor(){
	//funcao calloc para armazenar o vetor no heap para poder utilizar em outro escopo
	int *vetor = calloc(TAMANHO, sizeof(int)), i; 
	
	/* srand(time(NULL)) objetiva inicializar o gerador de n�meros aleat�rios
	com o valor da fun��o time(NULL). Desta forma, a cada execu��o o valor 
	da "semente" ser� diferente.
	*/
	srand(time(NULL));
	
	for(i=0;i<TAMANHO;i++)
		vetor[i] = 1 + (rand() % VALOR_MAXIMO);
	
	return vetor;
}

//Altera o tamanho da amostra
void alterarTamanho(){
	int coord_x = 23, coord_y = 1;
	
	int count=0;
	do{
			
		GotoXY(coord_x, coord_y);
		if(count!=0){
			printf(VERMELHO "(%d - %d) " RESET, MIN_AMOSTRA, MAX_AMOSTRA);
		}
		printf(VERMELHO "-> " RESET);
		ShowConsoleCursor(true);
		scanf("%d", &TAMANHO);
		count++;
	}while((TAMANHO < MIN_AMOSTRA) | (TAMANHO > MAX_AMOSTRA));
	system("cls");
	ShowConsoleCursor(false);
	X_INICIAL = LARGURA_MENU + (D_X-LARGURA_MENU-TAMANHO)/2;
}


//----ALGORITMOS DE ODERNACAO---///

//gera um vetor aleat�rio e chama a funcao de ordena��o
void visualizarAlgoritmo(char algoritmo[], int vetor[]){

	if(strcmp(algoritmo, "Insertion") == 0) //strcmp -> compara duas strings e retorna 0 se forem iguais
		insertionSort(vetor);
	else if((strcmp(algoritmo, "Merge") == 0)){
		visualizarVetor(vetor);
		mergeSort(vetor, 0, TAMANHO-1);
	}
	
	GotoXY(0, 0);
}

//algoritmo INSERTION
void insertionSort(int vetor[]){
	int i, j, key;
	  
    for (i = 1; i < TAMANHO; i++) {
    	visualizarVetor(vetor);
        key = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > key) {
        	swapValor(j+1, vetor[j+1], vetor[j], false);  //swap � feito antes
            vetor[j + 1] = vetor[j];
            j = j - 1;
            swapValor(j+1, vetor[j+1], key, true);  //e depois. Se fzr os dois juntos o efeito n�o � t�o interessante
            vetor[j + 1] = key;
            Sleep(VELOCIDADE);
        }
    }
}

// fonte -> https://www.programiz.com/dsa/merge-sort
// deixei os coment�rios originais 
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


//----FUN�OES DO CONSOLE----//

//retorna o tamanho do console
void get_size_window(int *col, int *row){
    CONSOLE_SCREEN_BUFFER_INFO cmd;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmd);
    *col = cmd.srWindow.Right - cmd.srWindow.Left +1;
    *row = cmd.srWindow.Bottom - cmd.srWindow.Top +1;
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

//fun��o que apaga uma coluna e printa uma nova com valor diferente
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

//Itera sobre um determinado subarray[l...r]
void swapMerge(int vet[], int l, int r){
	int i, j;
	int lenSubvetor = r-l;
	
	for(i=l;i<=r;i++){
		if(lenSubvetor>=TAMANHO/6)
			Sleep(VELOCIDADE/4);
		swapValor(i, VALOR_MAXIMO, vet[i], true);
	}
	visualizarVetor(vet);
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

//maxima a tela no inicio do programa, necess�rio visualmente
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

//----OPERA�OES LINKED LIST----//

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
		//GotoXY
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

//libera o espa�o da list
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

//--auxiliar---//
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
		if(x>=39){
			pular_linha++;
			x = 0;
		}
	}
	GotoXY(0, 0);
}

//essa aqui ta uma putaria, tem que dar uma limpada nela
int selecionarValor(int vetor[], int vermelho){
	int x=0, y=OFFSET_Y, valor, index=0;
	char c;
	
	while(1){
		GotoXY(x,y);
		
		switch(vermelho){
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
			GotoXY(x,y);
			if(vetor[index]>9)
				printf("%d", vetor[index]);
			else
				printf("0%d", vetor[index]);
			switch(c){
				case 13:
					GotoXY(0, OFFSET_Y-1);
					return index;
				case K_D:
					if(index+13<TAMANHO){
						index+=13;
						y++;
					}
					break;
				case K_U:
					if(y>OFFSET_Y){
						index-=13;
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
					if(index<TAMANHO-1 && x<LARGURA_MENU-4){
						index++;
						x+=3;
					break;
				}
			}
		}
	}
}

void printBarraY(){
	int i;
	
	for(i=0;i<=D_Y;i++){
		GotoXY(LARGURA_MENU, i);
		printf("%c", BARRA_Y);
	}
	GotoXY(0,0);
}
