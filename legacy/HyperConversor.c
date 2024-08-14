/*Davi Sollar - 15/02/2024*/
/*Descrição: Programa que converte números de bases diferentes*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
	setbuf(stdout, NULL);

	char Char[36] = {'0','1','2','3','4','5','6','7','8','9','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}, Num[1000], Res[1000];
	int De = 0, i, j = 0, k = 0, Bs1, Bs2, Aux, x;
	FILE *arq = fopen("C:\\Users\\davis\\Downloads\\hyperconversor.txt", "w");

	if (arq == NULL) {
		printf("\nNão foi possível abrir o arquivo.\n");
		system("pause");
		return 1;
	}

	do {
		printf("Digite um número: ");
		scanf("%s",Num);

		printf("Digite a base desse número (2 até 36): ");
		scanf("%d",&Bs1);

		if ((Bs1 < 2) || (Bs1 > 36))
		{
			printf("\nBase inválida digitada");
			return 2;
		}

		i = strlen(Num) - 1;

		while(i >= 0)
		{
			if(Num[i] == Char[j]){
				if (j >= Bs1)
				{
					printf("\nErro! Algarismo maior ou igual a base.");
					return(1);
				}
				De = De + (j * pow(Bs1, k));
				j = 0;
				i--;
				k++;
			}
			else{
				j++;
			}
		}

		printf("Digite a base desejda (2 até 36): ");
		scanf("%d",&Bs2);

		if ((Bs2 < 2) || (Bs2 > 36))
		{
			printf("\nBase inválida digitada");
			return 3;
		}

		i++;

		while(1)
		{
			if(De == 0)
			{
				Res[i] = Char[De];
				break;
			}
			else if(De <= Bs2-1){
				Aux = De % Bs2;
				Res[i] = Char[Aux];
				De = De / Bs2;
				break;
			}

			Aux = De % Bs2;
			Res[i] = Char[Aux];
			De = De / Bs2;
			i++;
		}

		int bah = i;

		if (Bs2 == 2)
		{
			printf("\nO número transformado em binário é: ");
		}
		else if (Bs2 == 10)
		{
			printf("\nO número transformado em decimal é: ");
		}
		else if (Bs2 == 16)
		{
			printf("\nO número transformado em hexadecimal é: ");
		}
		else
		{
			printf("\nO número transformado na base %d é: ", Bs2);
		}

		for(int a = 0; i >= a; i--)
		{
			printf("%c", Res[i]);
		}

		i = bah;

		fprintf(arq,"%s, base %d -> base %d = ", Num, Bs1, Bs2);
		for(int a = 0; i >= a; i--)
		{
			fprintf(arq,"%c", Res[i]);
		}
		fprintf(arq,"\n");

		printf("\n\nAperte 0 para encerrar ou outro inteiro para continuar: ");
		scanf("%d", &x);

		if (x == 0) {
			system("cls");
			printf("Programa encerrado");
			return 0;
		}
		else{
			strcpy(Num, "");
			strcpy(Res, "");
			De = 0;
			i = 0;
			j = 0;
			k = 0;
			system("cls");
		}
	} while (1);
}
