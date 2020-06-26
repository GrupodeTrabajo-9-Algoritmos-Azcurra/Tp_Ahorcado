#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define max_caracteres 100
#define max_intentos 6
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



/*Partida*/

void input_char(char *letra)
{
	fflush(stdin);
	scanf("%c",&*letra);
	fflush(stdin);
	
return;	
}


void limpiar_salto(cadena palabra) {
	int tam;
	tam=strlen(palabra);
	if(palabra[tam-1]=='\n') {
		palabra[tam-1]='\0';		
	}
}


void input_string(cadena palabra)
{
	fflush(stdin);
	fgets(palabra,max_caracteres,stdin);
	fflush(stdin);
	limpiar_salto(palabra);
	
return;	
}


void validar_letra(cadena letra)
{
	while (strlen(letra)>1){
		printf("Por ingrese solo una letra\n");
		input_string(letra);
	}
	
return;	
}


bool buscar_letra(cadena palabra_secreta,cadena letra_ingresada)
{
	bool encontrado=true;
	if (strstr(palabra_secreta,letra_ingresada)==NULL)
		encontrado=false;
	
return encontrado;	
}


void poner_guion_bajo(cadena palabra_mostrar,cadena palabra_secreta)
{
	int posicion;
	for (posicion=0;posicion<strlen(palabra_secreta);posicion++)
		palabra_mostrar[posicion]='_';
	palabra_mostrar[strlen(palabra_secreta)]='\0';
	
return;	
}


void mostras_y_modificar_letras_ingresadas(cadena letras_ingresadas,cadena letra)
{
	int auxiliar=strlen(letras_ingresadas);
	if (!buscar_letra(letras_ingresadas,letra)){
		letras_ingresadas[auxiliar]=letra[0];
		letras_ingresadas[auxiliar+1]=' ';
		letras_ingresadas[auxiliar+2]='\0';	
	}
	printf("%s",letras_ingresadas);
	
return;	
}


void modificar_palabra_mostrar(cadena palabra_mostrar,cadena palabra_secreta,cadena pista,cadena letra_ingresada)
{
	int posicion;
	for (posicion=0;posicion<strlen(palabra_secreta);posicion++){
		if (palabra_secreta[posicion]==pista[0] || palabra_secreta[posicion]==letra_ingresada[0])
			palabra_mostrar[posicion]=palabra_secreta[posicion];
	}
	
return;	
}


void pantalla_inicial(cadena palabra_mostrar,cadena palabra_secreta,cadena pista,int intentos)
{
	poner_guion_bajo(palabra_mostrar,palabra_secreta);
	dibujo_colgado(intentos-1);
	modificar_palabra_mostrar(palabra_mostrar,palabra_secreta,pista,pista);
	printf("  %s\n",palabra_mostrar); 
	
return;	
}


void pantalla_acertado(cadena palabra_mostrar,cadena palabra_secreta,cadena pista,cadena letra_ingresada,cadena letras_ingresadas,int intentos)
{
			modificar_palabra_mostrar(palabra_mostrar,palabra_secreta,pista,letra_ingresada);
			dibujo_colgado(intentos-1);
			printf("  %s\n\n",palabra_mostrar);
			mostras_y_modificar_letras_ingresadas(letras_ingresadas,letra_ingresada);
	
return;	
}


void pantalla_equivocado(cadena palabra_mostrar,cadena letras_ingresadas,cadena letra_ingresada,int intentos)
{
	dibujo_colgado(intentos-1);
	printf("  %s\n",palabra_mostrar);
	printf("\n");
	mostras_y_modificar_letras_ingresadas(letras_ingresadas,letra_ingresada);
	
return;	
}


void pantalla_actual(cadena palabra_mostrar,cadena letras_ingresadas,int intentos)
{
	dibujo_colgado(intentos-1);
	printf("  %s\n\n",palabra_mostrar);	
	printf("%s",letras_ingresadas);
	
return;	
}


void input(cadena letra_ingresada,cadena palabra_mostrar,cadena letras_ingresadas,int intentos)
{
	printf("\n\n\n");
	input_string(letra_ingresada);
	while (strlen(letra_ingresada)>1){
		system("@cls||clear");	
		pantalla_actual(palabra_mostrar,letras_ingresadas,intentos);
		printf("\n\nPor ingrese solo una letra:\n");
		input_string(letra_ingresada);
	}
	system("@cls||clear");
return;
}


void pantalla_final(cadena palabra_secreta,cadena palabra_mostrar,cadena letras_ingresadas,int intentos)
{
	if (intentos==max_intentos+1){
		system("@cls||clear");
		strcpy(palabra_mostrar,palabra_secreta);
		pantalla_actual(palabra_mostrar,letras_ingresadas,intentos);
		printf("\n\n!AHORCADO¡");
	}
	else{
		system("@cls||clear");
		pantalla_actual(palabra_mostrar,letras_ingresadas,intentos);
		printf("\n\nSE HA COMPLETADO LA PALABRA");
	}
	
return;	
}


void juego_prototipo(cadena palabra_secreta,cadena pista)
{
	int posicion,intentos=1;
	cadena palabra_mostrar,letras_ingresadas,letra_ingresada;
	letras_ingresadas[0]='\0';                                    //Inicio el string
	pantalla_inicial(palabra_mostrar,palabra_secreta,pista,intentos);
	do {
		input(letra_ingresada,palabra_mostrar,letras_ingresadas,intentos);
		if (buscar_letra(palabra_secreta,letra_ingresada))
			pantalla_acertado(palabra_mostrar,palabra_secreta,pista,letra_ingresada,letras_ingresadas,intentos);	
		else {
			if (!buscar_letra(letras_ingresadas,letra_ingresada))
				intentos++;
			pantalla_equivocado(palabra_mostrar,letras_ingresadas,letra_ingresada,intentos);
	    }
	} while (intentos<=max_intentos && strcmp(palabra_mostrar,palabra_secreta)!=0);
	pantalla_final(palabra_secreta,palabra_mostrar,letras_ingresadas,intentos);
	
return;	
}






int main()
{
	cadena pista,letra_ingresada;
	cadena palabra_secreta;
	fflush(stdin);
	fgets(palabra_secreta,max_caracteres,stdin);
	fflush(stdin);
	limpiar_salto(palabra_secreta);
	scanf("%c",&pista[0]);
	fflush(stdin);
	system("@cls||clear");
	juego_prototipo(palabra_secreta,pista);
	
return 0;	
}
