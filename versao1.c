/*
Falta:
1 - Implementar os algoritmos de fato em suas devidas funçoes
2 - Implementar o modo de visualizacao dos algoritmos 
3 - Implementar uma maneira de controlar a velocidade das iteraçoes
4 - Implementar outras funcoes como REALIZAR NOVAMENTE/REALIZAR NOVAMENTE COM UM NOVO VETOR/VOLTAR PARA O MENU DO ALGORITMO/
	VOLTAR PARA O MENU PRINCIPAL
5 - Implementar o menu de caracteristicas do algoritmo
6 - NAO ESQUECER DE LIBERAR A MEMÓRIA APOS USAR CALLOC!!!
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define VALOR_MAXIMO 50 //valor maximo de um numero do vetor que será ordenado 
#define MAX_AMOSTRA 100 //tamanho maximo da amostra
#define MIN_AMOSTRA 5 //tamanho minimo da amostra


//Dimensões
int D_X, D_Y;
//tamanho da amostra
int tamanho=5;

void menuAlgoritmo(char *algoritmo, int *amostra);
void mainMenu(int *tamanho);
int* gerarVetor(int tamanho);
void get_size_window(int *col, int *row);
void visualizarAlgoritmo(char *algoritmo, int tamanho);
void GotoXY(int x, int y);
void maximize_window();
void alterarTamanho(int **amostra);
void visualizarVetor(int *vet, int tamanho);
void insertionSort(int a[], int tamanho);
void mergeSort(int a[], int l, int r);
void swapValor(int index, int valor_ant, int valor_atual, int tamanho);

//FUNÇÃO PRINCIPAL
int main(){
	
	maximize_window();
	mainMenu(&tamanho);
	
	return 0;
}


//FUNÇÕES DO MENU
void mainMenu(int *tamanho){
	char controle = '1', opc;
	
	do{
	//Menu inicial
	printf("Bem-vindo ao visualizador de algoritmos de ordenacao\n");
	printf("<1> Insertion Sort\n<2> Merge Sort\n<3> Bubble Sort\n<4> Sair\n");
	opc=getch();
	
		switch(opc){
			case '1':
				system("cls");
				menuAlgoritmo("Insertion", tamanho);
				break;
			case '2':
				system("cls");
				menuAlgoritmo("Merge", tamanho);
				break;
			case '3':
				system("cls");
				menuAlgoritmo("Bubble", tamanho);
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

void menuAlgoritmo(char *algoritmo, int *tamanho){
	char opc, controle='1';
	
	do{
	//Menu que será mostrado após selecionar um dos algoritmos
	printf("Algoritmo selecionado: %s Sort\nTamanho da amostra: %d\n", algoritmo, *tamanho);
	printf("<1> Visualizar algoritmo\n<2> Alterar tamanho da amostra\n<3> Voltar\n");
	opc=getch();
	
		switch(opc){
			case '1':
				visualizarAlgoritmo(algoritmo, *tamanho);
				break;
			case '2':
				alterarTamanho(&tamanho);
				system("cls");
				break;
			case '3':
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
	
}

//FUNCOES DE MANIPULACAO DA AMOSTRA
int* gerarVetor(int tamanho){
	//funcao calloc para armazenar o vetor no heap para poder utilizar em outro escopo
	int *vetor = calloc(tamanho, sizeof(int)), i; 
	
	/* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
	com o valor da função time(NULL). Desta forma, a cada execução o valor 
	da "semente" será diferente.
	*/
	srand(time(NULL));
	
	for(i=0;i<tamanho;i++)
		vetor[i] = 1 + (rand() % VALOR_MAXIMO);
	
	return vetor;
}

void alterarTamanho(int **amostra){
	
	system("cls");
	printf("Tamanho atual da amostra: %d\n", **amostra);
	printf("Digite o novo tamanho (5 a 100 inclusive): ");
	scanf("%d", *amostra);
	//fiquei confuso sobre essa parada de ponteiro para um ponteiro, porem funcionou
	while((**amostra < MIN_AMOSTRA) | (**amostra > MAX_AMOSTRA)){
		system("cls");
		printf("Numero invalido, por favor selecione um numero entre 5 e 100...\n");
		scanf("%d", *amostra);	
	}
}


//ALGORITMOS DE ODERNACAO
void visualizarAlgoritmo(char *algoritmo, int tamanho){
	int *vetor = gerarVetor(tamanho);
	
	if(strcmp(algoritmo, "Insertion") == 0)
		insertionSort(vetor, tamanho);
	else if((strcmp(algoritmo, "Merge") == 0)){
		mergeSort(vetor, 0, tamanho);
	}
		
	
	printf("%d", vetor[1]);
	free(vetor);
}

void insertionSort(int vetor[], int tamanho){
	int i, j, key;
	visualizarVetor(vetor, tamanho);
	  
    for (i = 1; i < tamanho; i++) {
        key = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > key) {
        	swapValor(j+1, vetor[j+1], vetor[j], tamanho);
            vetor[j + 1] = vetor[j];
            j = j - 1;
            swapValor(j+1, vetor[j+1], key, tamanho);
            Sleep(100);
            vetor[j + 1] = key;
        }
    }
}

void swapValor(int index, int valor_ant, int valor_atual, int tamanho){
	int x_inicial = D_X/2 - tamanho/2;
	int i;
	
	for(i=0;i<valor_ant;i++){
		GotoXY(x_inicial+index, D_Y-i-1);
		printf(" ");
	}
	for(i=0;i<valor_atual;i++){
		GotoXY(x_inicial+index, D_Y-i-1);
		printf("#");
	}
	
}

// Merge two subarrays L and M into arr
void merge(int a[], int p, int q, int r) {

	// Create L ? A[p..q] and M ? A[q+1..r]
	int n1 = q - p + 1;
	int n2 = r - q;

	int L[n1], M[n2], i, j, k = p;;
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
	}
}

//FUNÇOES DO CONSOLE
void get_size_window(int *col, int *row){
    CONSOLE_SCREEN_BUFFER_INFO cmd;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmd);
    *col = cmd.srWindow.Right - cmd.srWindow.Left +1;
    *row = cmd.srWindow.Bottom - cmd.srWindow.Top +1;
}

void visualizarVetor(int *vet, int tamanho){
	int i, j, x_inicial;
	Sleep(100);
	system("cls");
	
	get_size_window(&D_X, &D_Y);
	x_inicial = D_X/2 - tamanho/2;
	for(i=0;i<tamanho;i++){
		for(j=0;j<vet[i];j++){
			GotoXY(x_inicial+i, D_Y-j-1);
			printf("#");
		}
	}
	GotoXY(0, 0);
}

void GotoXY(int x, int y){
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}

void maximize_window(){
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

