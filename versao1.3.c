//----TODO---//
// 1 - Manipulação do vetor (remover, adicionar, substituir) -> colocar uns efeitos graficos aq também
// 2 - Mostrar os numeros do vetor sendo ordenados na tela junto com o grafico -> de preferencia com um background vermelho no numero que esta sendo movido
// 3 - valores maximos dinamicos
// 4 - velocidade -> alteravel pelo usuario ou com relação ao algoritmo/tamanho da amostra?


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#define MIN_AMOSTRA 5 //tamanho minimo da amostra
#define CARACTERE 219

//Tempo que o programa esperará a cada iteração das ordenação, garantindo um efeito visual. 
//LEMBRETE: pode ser implementado uma velocidade dinâmica dependendo do usuario ou do algoritmo
//!!MUDAR AQUI PARA DEIXAR O PROGRAMA MAIS RAPIDO!!
#define VELOCIDADE 200

//Para trocar a cor das colunas no terminal
#define VERMELHO "\x1b[31m"
#define RESET "\x1b[0m"


//----VARIAVEIS GLOBAIS----//
//Dimensões
int D_X, D_Y;
//tamanho da amostra
int TAMANHO=20;
//coordenada onde começa a impressão do vetor gráfico
int X_INICIAL;
//tamanho maximo da amostra e valor maximo de um valor da amostra
int MAX_AMOSTRA, VALOR_MAXIMO;

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

//FUNÇÃO PRINCIPAL
int main(){
	
	maximize_window();
	get_size_window(&D_X, &D_Y);
	ShowConsoleCursor(false);
	
	//definições dos padrões
	X_INICIAL = D_X/2 - TAMANHO/2;
	MAX_AMOSTRA = D_X - 4; //4 -> offeset de 2 pra esquerda e 2 pra direita
	VALOR_MAXIMO = D_Y - 7;  // valor maximo até 1 antes da primeira linha do menu
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
		int *vetor = gerarVetor(TAMANHO);
		visualizarVetor(vetor);
		printf("Algoritmo selecionado: %s Sort\nTamanho da amostra: %d\n", algoritmo, TAMANHO);
		printf("<1> Iniciar ordenacao\n<2> Alterar tamanho da amostra\n<3> Modificar amostra\n<4> Gerar nova amostra aleatoria\n<5> Voltar\n");
		opc=getch();
		
			switch(opc){
				case '1':
					system("cls");
					visualizarAlgoritmo(algoritmo, vetor);
					break;
				case '2':
					alterarTamanho();
					X_INICIAL = D_X/2 - TAMANHO/2;
					system("cls");
					break;
				case '3':
					//modificarAmostra(vetor);
				case '4':
					apagarVetor(vetor);
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
		free(vetor);  //nao esquecer de liberar a memoria apos alocar manualmente no gerarVetor();
	}while(controle=='1');
	
}

//FUNCOES DE MANIPULACAO DA AMOSTRA
int* gerarVetor(){
	//funcao calloc para armazenar o vetor no heap para poder utilizar em outro escopo
	int *vetor = calloc(TAMANHO, sizeof(int)), i; 
	
	/* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
	com o valor da função time(NULL). Desta forma, a cada execução o valor 
	da "semente" será diferente.
	*/
	srand(time(NULL));
	
	for(i=0;i<TAMANHO;i++)
		vetor[i] = 1 + (rand() % VALOR_MAXIMO);
	
	return vetor;
}

//Altera o tamanho da amostra
void alterarTamanho(){
	system("cls");
	ShowConsoleCursor(true);
	printf("Tamanho atual da amostra: %d\n", TAMANHO);
	printf("Digite o novo tamanho (5 a %d): ", MAX_AMOSTRA);
	scanf("%d", &TAMANHO);
	while((TAMANHO < MIN_AMOSTRA) | (TAMANHO > MAX_AMOSTRA)){
		system("cls");
		printf("Numero invalido, por favor selecione um numero entre 5 e 100...\n");
		scanf("%d", &TAMANHO);	
	}
	ShowConsoleCursor(false);
}


//----ALGORITMOS DE ODERNACAO---///

//gera um vetor aleatório e chama a funcao de ordenação
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

//retorna o tamanho do console
void get_size_window(int *col, int *row){
    CONSOLE_SCREEN_BUFFER_INFO cmd;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmd);
    *col = cmd.srWindow.Right - cmd.srWindow.Left +1;
    *row = cmd.srWindow.Bottom - cmd.srWindow.Top +1;
}

//imprime o vetor inteiro
void visualizarVetor(int *vet){
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
//funciona de forma parecido ao swapValor, porém apaga e printa um grupo de colunas ao invés
//de cada uma indivudalmente
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

//maxima a tela no inicio do programa, necessário visualmente
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

//--auxiliar---//
void imprimir(int a[]){
	int i;
	
	for(i=0;i<TAMANHO;i++)
		printf("%d ", a[i]);
	
}
