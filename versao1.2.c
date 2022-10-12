#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#define VALOR_MAXIMO 30 //valor maximo de um numero do vetor que será ordenado. !!IMPLEMENTAR UMA FUNCAO QUE DETERMINE O VALOR MAXIMO COM RELACAO NAS DIMENSOES!!
#define MAX_AMOSTRA 100 //tamanho maximo da amostra !!IMPLEMENTAR UMA FUNCIONALIDADE PARECIDA COM A QUE SERA IMPLEMENTADA NO VALO_MAXIMO!!
#define MIN_AMOSTRA 5 //tamanho minimo da amostra
#define CARACTERE 219

//Tempo que o programa esperará a cada iteração das ordenação, garantindo um efeito visual. 
//LEMBRETE: pode ser implementado uma velocidade dinâmica dependendo do usuario ou do algoritmo
//!!MUDAR AQUI PARA DEIXAR O PROGRAMA MAIS RAPIDO!!
#define VELOCIDADE 100

//Para trocar a cor das colunas no terminal
#define VERMELHO "\x1b[31m"
#define RESET "\x1b[0m"

//Dimensões
int D_X, D_Y;
//tamanho da amostra
int tamanho=20;


//assinatura das funções
void menuAlgoritmo(char algoritmo[]);  //lembrete: fazer alterações para dipensar o uso de ponteiros nos menus
void mainMenu();
int* gerarVetor();
void get_size_window(int *col, int *row);
void visualizarAlgoritmo(char algoritmo[]);
void GotoXY(int x, int y);
void maximize_window();
void alterarTamanho(); 
void visualizarVetor(int vet[]);
void insertionSort(int a[]);
void mergeSort(int a[], int l, int r);
void swapValor(int index, int valor_ant, int valor_atual, bool cor);
void imprimir(int a[]);

//funções criada para garantir o efeito visual do algoritmo MERGE, talvez acha uma maneira de implementar
//o efeito visual usando apenas as funções já feitas para o insertion, ou uma combinação delas...
//mas funciona! !falta implementar as cores das troca!
void apagarColunas(int vet[], int index_l, int index_r);
void visualizarColunas(int vet[], int index_l, int index_r);
void swapMerge(int vet[], int l, int r);

//FUNÇÃO PRINCIPAL
int main(){
	
	maximize_window();
	get_size_window(&D_X, &D_Y);
	mainMenu();
	
	return 0;
}


//FUNÇÕES DO MENU
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
	
	do{
	//Menu que será mostrado após selecionar um dos algoritmos
	printf("Algoritmo selecionado: %s Sort\nTamanho da amostra: %d\n", algoritmo, tamanho);
	printf("<1> Visualizar algoritmo\n<2> Alterar tamanho da amostra\n<3> Voltar\n");
	opc=getch();
	
		switch(opc){
			case '1':
				system("cls");
				visualizarAlgoritmo(algoritmo);
				break;
			case '2':
				alterarTamanho();
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
int* gerarVetor(){
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

//Altera o tamanho da amostra
void alterarTamanho(){
	system("cls");
	printf("Tamanho atual da amostra: %d\n", tamanho);
	printf("Digite o novo tamanho (5 a 100 inclusive): ");
	scanf("%d", &tamanho);
	while((tamanho < MIN_AMOSTRA) | (tamanho > MAX_AMOSTRA)){
		system("cls");
		printf("Numero invalido, por favor selecione um numero entre 5 e 100...\n");
		scanf("%d", &tamanho);	
	}
}


//----ALGORITMOS DE ODERNACAO---///

//gera um vetor aleatório e chama a funcao de ordenação
void visualizarAlgoritmo(char algoritmo[]){
	int *vetor = gerarVetor(tamanho);
	
	if(strcmp(algoritmo, "Insertion") == 0) //strcmp -> compara duas strings e retorna 0 se forem iguais
		insertionSort(vetor);
	else if((strcmp(algoritmo, "Merge") == 0)){
		visualizarVetor(vetor);
		mergeSort(vetor, 0, tamanho);
	}
		
	
	GotoXY(0, 0);
	free(vetor);  //nao esquecer de liberar a memoria apos alocar manualmente no gerarVetor();
}

//algoritmo INSERTION
void insertionSort(int vetor[]){
	int i, j, key;
	  
    for (i = 1; i < tamanho; i++) {
    	visualizarVetor(vetor);
        key = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > key) {
        	swapValor(j+1, vetor[j+1], vetor[j], false);  //swap é feito antes
            vetor[j + 1] = vetor[j];
            j = j - 1;
            swapValor(j+1, vetor[j+1], key, true);  //e depois. Se fzr os dois juntos o efeito não é tão interessante
            vetor[j + 1] = key;
            Sleep(VELOCIDADE);
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

//retorna o tamanho do console colxrow
void get_size_window(int *col, int *row){
    CONSOLE_SCREEN_BUFFER_INFO cmd;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmd);
    *col = cmd.srWindow.Right - cmd.srWindow.Left +1;
    *row = cmd.srWindow.Bottom - cmd.srWindow.Top +1;
}

//imprime o vetor inteiro
void visualizarVetor(int *vet){
	int i, j, x_inicial;
	//system("cls");
	
	x_inicial = D_X/2 - tamanho/2;
	for(i=0;i<tamanho;i++){
		for(j=0;j<vet[i];j++){
			GotoXY(x_inicial+i, D_Y-j-1);
			printf("%c", CARACTERE);
		}
	}
	GotoXY(0, 0);
}

void apagarColunas(int vet[], int index_l, int index_r){
	int i, j, x_inicial;

	x_inicial = D_X/2 - tamanho/2;
	for(i=index_l;i<=index_r;i++){
		for(j=0;j<VALOR_MAXIMO;j++){
			GotoXY(x_inicial+i, D_Y-j-1);
			printf(" ");
		}
	}
}

void visualizarColunas(int vet[], int index_l, int index_r){
	int i, j, x_inicial;

	x_inicial = D_X/2 - tamanho/2;
	for(i=index_l;i<=index_r;i++){
		for(j=0;j<vet[i];j++){
			GotoXY(x_inicial+i, D_Y-j-1);
			printf("%c", CARACTERE);
		}
	}
	
}

//função que apaga uma coluna e printa uma nova com valor diferente
void swapValor(int index, int valor_ant, int valor_atual, bool cor){
	//index = do valor no vetor, valor_ant = anterior, valor_atual.., cor = true -> vermelho / false -> normal
	int x_inicial = D_X/2 - tamanho/2;
	int i;
	
	for(i=0;i<valor_ant;i++){
		GotoXY(x_inicial+index, D_Y-i-1);
		printf(" ");
	}
	if(!cor){
		for(i=0;i<valor_atual;i++){
			GotoXY(x_inicial+index, D_Y-i-1);
			printf("%c", CARACTERE);
		}
	}
	else{
		for(i=0;i<valor_atual;i++){
			GotoXY(x_inicial+index, D_Y-i-1);
			printf(VERMELHO "%c" RESET, CARACTERE);
		}
	}
}

//funciona de forma parecido ao swapValor, porém apaga e printa um grupo de colunas ao invés
//de cada uma indivudalmente
void swapMerge(int vet[], int l, int r){
	//l -> left index, r -> right index
	apagarColunas(vet, l, r);
	visualizarColunas(vet, l, r);
	Sleep(VELOCIDADE);
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

//maxima a tela no inicio do programa, necessário visualmente
void maximize_window(){
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

//--auxiliar---//
void imprimir(int a[]){
	int i;
	
	for(i=0;i<tamanho;i++)
		printf("%d ", a[i]);
	
}
