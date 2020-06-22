#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define max_caracteres 100
typedef char cadena[max_caracteres];

void gancho_cabeza(int veces_errado)
{
	printf(" _____\n");		
	printf("|     |\n");
	printf("|     ");
	if (veces_errado>=1)
		printf("O\n");
	else
		printf("\n");	
return;		
}


void torso(veces_errado)
{
	printf("|    ");
	if (veces_errado>=2)
		printf("/");
	if 	(veces_errado>=3)	
		printf("|");
	if (veces_errado>=4)
		printf("\\");
		
return;		
}

void piernas_y_base(veces_errado)
{
	printf("\n|    ");
	if (veces_errado>=5)
		printf("/ ");
	if (veces_errado>=6)
		printf("\\");
	printf("\n|_______");
	printf("\n|_______|");
	
return;	
}

void dibujo_colgado(int veces_errado)
{
	gancho_cabeza(veces_errado);
	torso(veces_errado);
	piernas_y_base(veces_errado);				
		
return;	
}
/**/

void input_char(char *letra)
{
	fflush(stdin);
	scanf("%c",&*letra);
	fflush(stdin);
	
return;	
}

bool buscar_letra_ingresada(cadena palabra_secreta,char letra_ingresada)
{
	int posicion=0;
	bool encontrado=true;
	while (palabra_secreta[posicion]!=letra_ingresada && posicion<=strlen(palabra_secreta)-2)
		posicion++;
	if (posicion==strlen(palabra_secreta)-1)
		encontrado=false;
	
return encontrado;	
}


void modificar_palabra_mostrar(cadena palabra_mostrar,cadena palabra_secreta,char pista,char letra_ingresada)
{
	int posicion;
	
	for (posicion=0;posicion<strlen(palabra_secreta)-1;posicion++)
	{
		if (palabra_secreta[posicion]==pista || palabra_secreta[posicion]==letra_ingresada)
			palabra_mostrar[posicion]=palabra_secreta[posicion];
	}
return;	
}


void normalizar(cadena palabra_mostrar,cadena palabra_secreta)
{
	int posicion;
	for (posicion=0;posicion<strlen(palabra_secreta)-1;posicion++)
		palabra_mostrar[posicion]='_';
	palabra_mostrar[strlen(palabra_secreta)-1]='\0';
	
return;	
}


void mostras_y_modificar_letras_erradas(cadena letras_erradas,char letra,int intentos)
{
	letras_erradas[intentos-1]=letra;
	letras_erradas[intentos]='\0';
	printf("%s",letras_erradas);
	
return;	
}


void juego_prototipo(cadena palabra_secreta,char pista)
{
	int posicion,intentos=1,letras_acertadas=1;
	cadena palabra_mostrar,letras_erradas;
	char letra_ingresada;
	normalizar(palabra_mostrar,palabra_secreta);
	dibujo_colgado(intentos-1);
	modificar_palabra_mostrar(palabra_mostrar,palabra_secreta,pista,pista);
	printf("  %s\n",palabra_mostrar); 
	do {
		printf("\n\n");
		input_char(&letra_ingresada);
		system("@cls||clear");
		if (buscar_letra_ingresada(palabra_secreta,letra_ingresada)){
			modificar_palabra_mostrar(palabra_mostrar,palabra_secreta,pista,letra_ingresada);
			dibujo_colgado(intentos-1);
			printf("  %s\n\n",palabra_mostrar);
			printf("%s",letras_erradas);
			letras_acertadas++;
		}
		else{
			intentos++;
			dibujo_colgado(intentos-1);
			printf("  %s\n",palabra_mostrar);
			printf("\n");
			mostras_y_modificar_letras_erradas(letras_erradas,letra_ingresada,intentos);	
	    }
	} while (intentos<=6 && letras_acertadas<strlen(palabra_secreta)-1);
	
return;	
}




int main()
{
	char pista,letra_ingresada;
	cadena palabra_secreta;
	fflush(stdin);
	fgets(palabra_secreta,max_caracteres,stdin);
	fflush(stdin);
	scanf("%c",&pista);
	fflush(stdin);
	system("@cls||clear");
	juego_prototipo(palabra_secreta,pista);
	
return 0;	
}
