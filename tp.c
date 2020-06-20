#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_STR 50
#define MAX_CAT 20
#define MAX_PAL 20

typedef char Tstring[MAX_STR];
typedef Tstring Tcategoria[MAX_CAT];
typedef Tstring Tpalabra_pista[MAX_CAT][MAX_PAL];

//Limpia el \n agregado por fgets
void limpiar_salto(Tstring cadena) {
	int tam;
	tam=strlen(cadena);
	if(cadena[tam-1]=='\n') {
		cadena[tam-1]='\0';		
	}
}

//Valida la existencia de una categoria y retorna la posicion del vector
int validar_existencia_categoria(Tstring categoria, Tcategoria Vcategorias, int cont_categorias) {
	int posicion=-1, i=0, len;

	limpiar_salto(categoria);
	
	while(posicion==-1 && i<cont_categorias) {
		if(strcmp(categoria, Vcategorias[i])==0) {
			posicion=i;
		}
		i++;
	}
	
	return posicion;
}

//Validacion de palabras
bool validar_palabra(Tstring palabra) {
	bool palabra_valida=true;
	
	limpiar_salto(palabra);
	
	if(strlen(palabra)<=5 || strlen(palabra)>=51) {
		palabra_valida=false;
	} else {
		int i=0;
		while(palabra_valida && i<strlen(palabra)) {
			if(palabra[i]!=32 && (palabra[i]<65 || palabra[i]>90)) {
				palabra_valida=false;
			}
			i++;
		}
	}
	
	return palabra_valida;
}

//Ingreso  palabras, pista y asignacion de categoria.
void ingresar_palabras(Tcategoria Vcategorias, Tpalabra_pista palabras, Tpalabra_pista pistas, int cont_categorias, int cont_palabras[MAX_PAL]) {
	bool ingreso_listo, palabra_valida;
	int i=0, indice_categoria;
	char opcion, categoria_aux[MAX_STR];
	Tstring palabra_aux, pista_aux;
	
	ingreso_listo=false;
	while(ingreso_listo==false) {
		//Ingresar palabra
		do {
			printf("Ingresa una palabra:\n");
			fgets(palabra_aux, MAX_PAL, stdin);
			fflush(stdin);
			palabra_valida=validar_palabra(palabra_aux);
			if(!palabra_valida) {
				printf("La palabra debe estar en mayusculas y tener entre 5 y 49 caracteres\n");
			}
		} while(!palabra_valida);
		
		//Ingresar pista
		printf("Ingresa una pista para la palabra:\n");
		fgets(pista_aux, MAX_PAL, stdin);
		fflush(stdin);
		limpiar_salto(pista_aux);
		
		//Asignar categoria
		do {
			printf("Asigna una categoria a la palabra:\n");
			fgets(categoria_aux, MAX_PAL, stdin);
			fflush(stdin);
			indice_categoria=validar_existencia_categoria(categoria_aux, Vcategorias, cont_categorias);
			if(indice_categoria==-1) {
				printf("La categoria ingresada no existe.\n");
			}
		} while(indice_categoria==-1);
		
		//Insertar variables auxiliares un su matriz correspondiente e incrementar contador
		strcpy(palabras[indice_categoria][cont_palabras[indice_categoria]], palabra_aux);
		strcpy(pistas[indice_categoria][cont_palabras[indice_categoria]], pista_aux);
		cont_palabras[indice_categoria]++;
		
		//Chequear si el usuario desea ingresar otra palabra
		do {
			printf("Deseas ingresar otra palabra(s/n)?\n");
			scanf("%c", &opcion);
			fflush(stdin);
			if(opcion=='n') {
				ingreso_listo=true;
			}
		} while(opcion!='s' && opcion!='n');
		
		//Limpiar pantalla
		system("@cls||clear");
		i++;
	}
}

int main() {
	Tcategoria Vcategorias; //Vector de categorias
	Tpalabra_pista palabras, pistas; //Matrices de palabras y pistas respectivamente
	int cont_categorias=0, cont_palabras[MAX_CAT]; //Contadores
	
	return 0;
}