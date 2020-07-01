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
void limpiar_salto(Tstring cadena)
{
	int tam;
	tam = strlen(cadena);
	if (cadena[tam - 1] == '\n')
	{
		cadena[tam - 1] = '\0';
	}
}

//Valida la existencia de una categoria y retorna su posicion en el vector
int validar_existencia_categoria(Tstring categoria, Tcategoria Vcategorias, int cont_categorias)
{
	int posicion = -1, i = 0;

	limpiar_salto(categoria);

	while (posicion == -1 && i < cont_categorias)
	{
		if (strcmp(categoria, Vcategorias[i]) == 0)
		{
			posicion = i;
		}
		i++;
	}

	return posicion;
}

//Valida la existencia de una palabra y retorna la posicion del vector en la fila de la categoria correspondiente.
int validar_existencia_palabra(Tstring palabra, Tpalabra_pista palabras, int indice_categoria, int cont_palabras[MAX_CAT])
{
	int posicion = -1, i = 0;

	limpiar_salto(palabra);

	while (posicion == -1 && i < cont_palabras[indice_categoria])
	{
		if (strcmp(palabra, palabras[indice_categoria][i]) == 0)
		{
			posicion = i;
		}
		i++;
	}
	
	return posicion;
}

//Validar Palabra o Categoria.(LONGITUD Y MAYUSCULA).
bool validar_long_mayus(Tstring palabra_categoria)
{
	bool validacion = true;
	limpiar_salto(palabra_categoria);
	
	//Validacion de caracteres (mas de 4 letras y menos de 50)
	if (strlen(palabra_categoria) < 5 || strlen(palabra_categoria) > 49)
	{
		validacion = false;
	}
	else
	{
		//Validacion de mayuscula
		int i = 0;
		while (validacion && i < strlen(palabra_categoria))
		{
			if (palabra_categoria[i] != 32 && (palabra_categoria[i] < 65 || palabra_categoria[i] > 90))
			{
				validacion = false;
			}
			i++;
		}
	}
	return validacion;
}

//Ingreso Categoria.
void ingresar_categoria(Tcategoria Vcategorias, int *cont_categorias)
{
	bool ingreso_listo, categoria_valida_longitud_mayuscula;
	int categoria_valida_existencia = 0;
	Tstring categoria_aux;
	char opcion;
		
	ingreso_listo = false;
	while (ingreso_listo == false)
	{
		//Ingresar categoria.
		do
		{
			printf("Ingresa una categoria:\n");
			fgets(categoria_aux, MAX_STR, stdin);
			fflush(stdin);
			//Validacion de longitud y caracteres en mayuscula.
			categoria_valida_longitud_mayuscula = validar_long_mayus(categoria_aux);
			if (!categoria_valida_longitud_mayuscula)
			{
				printf("La categoria debe estar en mayusculas y tener entre 5 y 49 caracteres\n");
			}
			//Validacion de existencia.
			categoria_valida_existencia = validar_existencia_categoria(categoria_aux, Vcategorias, *cont_categorias);
			if (categoria_valida_existencia != -1)
			{
				printf("La categoria ya existe.\n");
			}

		} while (!categoria_valida_longitud_mayuscula || categoria_valida_existencia != -1);

		//Registrar categoria.
		strcpy(Vcategorias[*cont_categorias], categoria_aux);
		*cont_categorias = *cont_categorias + 1;

		//Chequear si el usuario desea ingresar otra categoria.
		do
		{
			printf("Deseas ingresar otra categoria(s/n)?\n");
			scanf("%c", &opcion);
			fflush(stdin);
			if (opcion == 'n')
			{
				ingreso_listo = true;
			}
		} while (opcion != 's' && opcion != 'n');

		//Limpiar pantalla
		system("@cls||clear");
	}
	system("PAUSE");
}

//Ingreso  palabras, pista y asignacion de categoria.
void ingresar_palabras(Tcategoria Vcategorias, Tpalabra_pista palabras, Tpalabra_pista pistas, int cont_categorias, int cont_palabras[MAX_PAL], int *tot_palabras)
{
	bool ingreso_listo, palabra_valida;
	int indice_categoria, palabra_valida_existencia = 0;
	char opcion;
	Tstring palabra_aux, pista_aux, categoria_aux;
	
	if(cont_categorias>0) {
		ingreso_listo = false;
		while (ingreso_listo == false)
		{
			//Asignar categoria
			do
			{
				printf("Asigna una categoria a la palabra:\n");
				fgets(categoria_aux, MAX_STR, stdin);
				fflush(stdin);
				indice_categoria = validar_existencia_categoria(categoria_aux, Vcategorias, cont_categorias);
				if (indice_categoria == -1)
				{
					printf("La categoria ingresada no existe.\n");
				}
			} while (indice_categoria == -1);
	
			//Ingresar palabra
			do
			{
				printf("Ingresa una palabra:\n");
				fgets(palabra_aux, MAX_STR, stdin);
				fflush(stdin);
				//Validacion de longitud y cantidad de caracteres.
				palabra_valida = validar_long_mayus(palabra_aux);
				if (!palabra_valida)
				{
					printf("La palabra debe estar en mayusculas y tener entre 5 y 49 caracteres\n");
				}
				//Validacion de existencia.
				palabra_valida_existencia = validar_existencia_palabra(palabra_aux, palabras, indice_categoria, cont_palabras);
				if (palabra_valida_existencia != -1)
				{
					printf("La palabra ya existe.\n");
				}
			} while (!palabra_valida || palabra_valida_existencia != -1);
	
			//Ingresar pista
			printf("Ingresa una pista para la palabra:\n");
			fgets(pista_aux, MAX_STR, stdin);
			fflush(stdin);
			limpiar_salto(pista_aux);
	
			//Insertar variables auxiliares en su matriz correspondiente e incrementar contadores
			strcpy(palabras[indice_categoria][cont_palabras[indice_categoria]], palabra_aux);
			strcpy(pistas[indice_categoria][cont_palabras[indice_categoria]], pista_aux);
			cont_palabras[indice_categoria]++;
			*tot_palabras=*tot_palabras+1;
	
			//Chequear si el usuario desea ingresar otra palabra
			do
			{
				printf("Deseas ingresar otra palabra(s/n)?\n");
				scanf("%c", &opcion);
				fflush(stdin);
				if (opcion == 'n')
				{
					ingreso_listo = true;
				}
			} while (opcion != 's' && opcion != 'n');
	
			//Limpiar pantalla
			system("@cls||clear");
		}
	} else {
		printf("No existe ninguna categoria, debes ingresar al menos una antes de ingresar las palabras.\n");
	}
	system("PAUSE");
}

//Muestra palabras en orden alfabetico
void mostrar_alfabeticamente(Tpalabra_pista palabras, int indice_categoria, int cont_palabras[MAX_PAL])
{
	int i, j;
	Tstring palabra_aux;

	//Ordenar con burbujeo
	for (i = 1; i < cont_palabras[indice_categoria]; i++)
	{
		for (j = 0; j < cont_palabras[indice_categoria] - i; j++)
		{
			if (strcmp(palabras[indice_categoria][j], palabras[indice_categoria][j + 1]) == 1)
			{
				strcpy(palabra_aux, palabras[indice_categoria][j]);
				strcpy(palabras[indice_categoria][j], palabras[indice_categoria][j + 1]);
				strcpy(palabras[indice_categoria][j + 1], palabra_aux);
			}
		}
	}

	//Mostrar en pantalla vector ordenado
	for (i = 0; i < cont_palabras[indice_categoria]; i++)
	{
		printf("%s\n", palabras[indice_categoria][i]);
	}
}

//Muestra categorias en orden alfabetico
void mostrar_categorias_alfabeticamente(Tcategoria Vcategorias, int cont_categorias)
{
	int i, j;
	Tstring categoria_aux;

	//Ordenar con burbujeo
	for (i = 1; i < cont_categorias; i++)
	{
		for (j = 0; j < cont_categorias - i; j++)
		{
			if (strcmp(Vcategorias[j], Vcategorias[j + 1]) == 1)
			{
				strcpy(categoria_aux, Vcategorias[j]);
				strcpy(Vcategorias[j], Vcategorias[j + 1]);
				strcpy(Vcategorias[j + 1], categoria_aux);
			}
		}
	}

	//Mostrar en pantalla vector ordenado
	for (i = 0; i < cont_categorias; i++)
	{
		printf("%s\n", Vcategorias[i]);
	}
	
	system("PAUSE");
}

void listar_palabras_de_categoria(Tcategoria Vcategorias, Tpalabra_pista palabras, int cont_palabras[MAX_PAL], int cont_categorias)
{
	Tstring categoria_aux;
	int indice_categoria;

	//Ingresar categoria
	do
	{
		printf("Ingresa una categoria:\n");
		fgets(categoria_aux, MAX_STR, stdin);
		fflush(stdin);
		indice_categoria = validar_existencia_categoria(categoria_aux, Vcategorias, cont_categorias);
		if (indice_categoria == -1)
		{
			printf("La categoria ingresada no existe.\n");
		}
	} while (indice_categoria == -1);

	//Limpiar pantalla
	system("@cls||clear");

	mostrar_alfabeticamente(palabras, indice_categoria, cont_palabras);
	
	system("PAUSE");
}

//Mostrar todas las palabras por cantidad de caracteres en orden descendente.
void mostrar_todas_las_palabras(Tpalabra_pista palabras, int tot_palabras, int cont_categorias, int cont_palabras[MAX_CAT])
{
	int i, j, k = 0;
	Tstring palabras_todas[tot_palabras], palabra_aux;

	//Paso las palabras de la matriz a un vector.
	for (i = 0; i < cont_categorias; i++)
	{
		for (j = 0; j < cont_palabras[i]; j++)
		{
			strcpy(palabras_todas[k], palabras[i][j]);
			k++;
		}
	}

	//Ordenamiento por insercion.
	for (i = 1; i < tot_palabras; i++)
	{
		j = i;
		while (j > 0 && strlen(palabras_todas[j]) < strlen(palabras_todas[j - 1]))
		{
			strcpy(palabra_aux, palabras_todas[j]);
			strcpy(palabras_todas[j], palabras_todas[j - 1]);
			strcpy(palabras_todas[j - 1], palabra_aux);
			j--;
		}
	}

	//Muestro ordenamiento descendentemente.
	for (i = tot_palabras - 1; i >= 0; i--)
	{
		printf("%s\n", palabras_todas[i]);
	}
	
	system("PAUSE");
}

//Menu para listar categorias y palabras
void menu_listado(Tcategoria Vcategorias, Tpalabra_pista palabras, int cont_categorias, int cont_palabras[MAX_PAL], int tot_palabras) {
	int opcion_menu_listado;
	
	//Ingreso de opcion
	printf("MENU DE LISTADO. Ingresa una opcion para continuar:\n");
	printf("1 -> Mostrar categorias ordenadas alfabeticamente en forma ascendente.\n");
	printf("2 -> Mostrar palabras ordenadas por cantidad de caracteres en forma descendente.\n");
	printf("3 -> Ingresar una categoria y mostrar todas las palabras ordenadas alfabeticamente.\n");
	printf("4 -> Continuar al juego.\n");
	scanf("%i", &opcion_menu_listado);
	fflush(stdin);
	system("@cls||clear");
	
	if(opcion_menu_listado==1) {
		//Mostrar categorias ordenadas alfabeticamente en forma ascendente
		mostrar_categorias_alfabeticamente(Vcategorias, cont_categorias);
		system("@cls||clear");
		menu_listado(Vcategorias, palabras, cont_categorias, cont_palabras, tot_palabras);
	} else if(opcion_menu_listado==2) {
		//Mostrar palabras ordenadas por cantidad de caracteres en forma descendente
		mostrar_todas_las_palabras(palabras, tot_palabras, cont_categorias, cont_palabras);
		system("@cls||clear");
		menu_listado(Vcategorias, palabras, cont_categorias, cont_palabras, tot_palabras);
	} else if(opcion_menu_listado==3) {
		//Ingresar una categoria y mostrar todas las palabras ordenadas alfabeticamente
		listar_palabras_de_categoria(Vcategorias, palabras, cont_palabras, cont_categorias);
		system("@cls||clear");
		menu_listado(Vcategorias, palabras, cont_categorias, cont_palabras, tot_palabras);
	} else if(opcion_menu_listado==4) {
		//Continuar al juego
	} else {
		//Opcion invalida
		printf("La opcion ingresada no es valida, intentalo de nuevo.\n\n");
		menu_listado(Vcategorias, palabras, cont_categorias, cont_palabras, tot_palabras);
	}
}

//Menu para el ingreso de categorias, palabras y pistas
void menu_ingreso(Tcategoria Vcategorias, Tpalabra_pista palabras, Tpalabra_pista pistas, int cont_palabras[MAX_PAL], int *cont_categorias, int *tot_palabras) {
	int opcion_menu_ingreso;
	
	//Ingreso de opcion
	printf("MENU DE INGRESO. Ingresa una opcion para continuar:\n");
	printf("1 -> Ingresar categorias\n");
	printf("2 -> Ingresar palabras\n");
	printf("3 -> Continuar al menu de listados\n");
	scanf("%i", &opcion_menu_ingreso);
	fflush(stdin);
	system("@cls||clear");
	
	if(opcion_menu_ingreso==1) {
		//Ingresar categorias
		ingresar_categoria(Vcategorias, cont_categorias);
		system("@cls||clear");
		menu_ingreso(Vcategorias, palabras, pistas, cont_palabras, cont_categorias, tot_palabras);
	} else if(opcion_menu_ingreso==2) {
		//Ingresar palabras
		ingresar_palabras(Vcategorias, palabras, pistas, *cont_categorias, cont_palabras, tot_palabras);
		system("@cls||clear");
		menu_ingreso(Vcategorias, palabras, pistas, cont_palabras, cont_categorias, tot_palabras);
	} else if(opcion_menu_ingreso==3) {
		//Continuar al menu de listados
		 menu_listado(Vcategorias, palabras, *cont_categorias, cont_palabras, *tot_palabras);
	} else {
		//Opcion invalida
		printf("La opcion ingresada no es valida, intentalo de nuevo.\n\n");
		menu_ingreso(Vcategorias, palabras, pistas, cont_palabras, cont_categorias, tot_palabras);
	}
}


int main()
{
	Tcategoria Vcategorias;											   //Vector de categorias.
	Tpalabra_pista palabras, pistas;								   //Matrices de palabras y pistas respectivamente.
	int tot_palabras = 0, cont_categorias = 0, cont_palabras[MAX_CAT]; //Contador de palabras, de categorias y de palabras por categoria.

	//Menu de ingreso
	menu_ingreso(Vcategorias, palabras, pistas, cont_palabras, &cont_categorias, &tot_palabras);
	
	return 0;
}
