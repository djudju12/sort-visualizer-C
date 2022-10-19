#include <stdio.h>
#include <conio.h>
#include <math.h>
#define MAX 100

float calcula_media(float vet[], int tamanho);
int contador_media(float media,int tamanho, float vet[]);
float max_f(float vet[], int tamanho);
void salvarVetor(int tamanho, float vet[]);
void menu();
int buscarValor(float vet[], int tamanho, float valor);
int produtosFracao(float vet[], int tamanho);

int main(){

	menu();
}

void menu(){
	char op;
	float vet[MAX], media=0, max, valor;
	int tamanho, contador_acima, index;
	int sair=0;
	
	do{
		printf("<1> Salvar vetor\n<2> Calcular media\n<3> Acima da media\n<4> Valor maximo\n<5> Buscar valor\n"\
				"<6> Quantidade de numeros fracionarios\n<7> Sair\n");
		op = getch();
		switch(op){
			case '1':
				printf("Digite o tamanho do vetor: ");
				scanf("%d", &tamanho);
				salvarVetor(tamanho, vet);
				break;
			case '2':
				media = calcula_media(vet, tamanho);
				printf("%.2f\n", media);
				break;
			case '3':
				if(media==0)
					media = calcula_media(vet, tamanho);
				contador_acima = contador_media(media, tamanho, vet);
				printf("%d\n", contador_acima);
				break;
			case '4':
				max = max_f(vet, tamanho);
				printf("%f\n", max);
				break;
			case '5':
				printf("Digite o valor = ");
				scanf("%f", &valor);
				index = buscarValor(vet, tamanho, valor);
				printf("%d\n", index);
				break;
			case '6':
				printf("%d\n", produtosFracao(vet, tamanho));
				break;
			case '7':
				sair = 1;
				break;
		}
	}while(sair==0);
}

void salvarVetor(int tamanho, float vet[]){
	
	int i;
	for(i=0;i<tamanho;i++){
		printf("Valor do indice %d = ", i);
		scanf("%f", &vet[i]);
	}
	
}

float calcula_media(float vet[], int tamanho)
{
	float media, acumulador;
	int i;
	
	acumulador=0;
	for(i=0;i<tamanho;i++)
	{
		acumulador += vet[i];
	}
	
	media = acumulador/tamanho;
	return media;
}

int contador_media(float media,int tamanho, float vet[])
{
	int contador;
	int i=0;
	contador = 0;
	for(i=0;i<tamanho;i++){
		if(vet[i]>media)
			contador++;
	}
	return contador;
}

float max_f(float vet[], int tamanho)
{
	int i=0;
	
	float max=0;
	for(i=0;i<tamanho;i++){
		if(vet[i]>max)
			max = vet[i];
	}
	
	return max;
}

int buscarValor(float vet[], int tamanho, float valor)
{
	int i, index;
	
	for(i=0;i<tamanho;i++){
		if(vet[i]==valor){
			index = i;
			break;
		}
	}
	return index;
}

int produtosFracao(float vet[], int tamanho)
{
	int i, contador;
	
	contador = 0;
	for(i=0;i<tamanho;i++){
		if(fmod(vet[i], (int)vet[i]) != 0)
			contador++;
	}
	return contador;
}
