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

void registros(bool tipo_de_registro, Tcategoria Vcategorias, Tpalabra_pista palabras, Tpalabra_pista pistas, int cont_categorias, int cont_palabras[MAX_PAL], int tot_palabras)
{
	bool ingreso_listo, validacion_long_mayus;
	int validacion_existencia = 0;
	int indice_categoria, posicion;
	char opcion;
	Tstring registro_aux, categoria_aux, pista_aux, tipo;

	ingreso_listo = false;
	while (ingreso_listo == false)
	{
		//Ajustes segun el tipo de registro solicitado.
		if (tipo_de_registro)
		{
			strcpy(tipo, "Categoria");
			posicion = cont_categorias;
		}
		else
		{
			strcpy(tipo, "Palabra");
			do
			{
				printf("Asigna una categoria a la palabra:\n");
				fgets(categoria_aux, MAX_STR, stdin);
				fflush(stdin);
				indice_categoria = validar_existencia(true, registro_aux, Vcategorias, palabras, posicion, indice_categoria);
				if (indice_categoria == -1)
				{
					printf("La categoria ingresada no existe.\n");
				}
			} while (indice_categoria == -1);
			posicion = indice_categoria;
		}

		//Ingresar Categoria o Palabra.
		do
		{
			printf("Ingresa una categoria:\n");
			fgets(registro_aux, MAX_STR, stdin);
			fflush(stdin);
			//Validacion de longitud y caracteres en mayuscula.
			validacion_long_mayus = validar_long_mayus(registro_aux);
			if (!registro_aux)
			{
				printf("La %s debe estar en mayusculas y tener entre 5 y 49 caracteres\n", tipo);
			}
			//Validacion de existencia.
			validacion_existencia = validar_existencia(tipo_de_registro, registro_aux, Vcategorias, palabras, posicion, indice_categoria);
			if (validacion_existencia != -1)
			{
				printf("La %s ya existe.\n", tipo);
			}

		} while (!validacion_long_mayus || validacion_existencia != -1);

		//Registrar categoria o ingresar pista y registrar pista y palabra.
		if (tipo_de_registro)
		{
			strcpy(Vcategorias[cont_categorias], categoria_aux);
			cont_categorias = cont_categorias + 1;
		}
		else
		{
			//Ingreso pista.
			printf("Ingresa una pista para la palabra:\n");
			fgets(pista_aux, MAX_STR, stdin);
			fflush(stdin);
			limpiar_salto(pista_aux);
			//Registrar pista y palabra.
			strcpy(palabras[indice_categoria][cont_palabras[indice_categoria]], registro_aux);
			strcpy(pistas[indice_categoria][cont_palabras[indice_categoria]], pista_aux);
			cont_palabras[indice_categoria]++;
			tot_palabras++;
		}

		//Chequear si el usuario desea seguir registrando.
		do
		{
			printf("Deseas ingresar otra %s(s/n)?\n", tipo);
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
}

//Valida la existencia de una categoria y retorna la posicion del vector
int validar_existencia(bool tipo_de_registro, Tstring registro_aux, Tcategoria Vcategorias, Tpalabra_pista palabras, int posicones_a_verificar, int indice_categoria)
{
	int posicion = -1, i = 0;

	limpiar_salto(registro_aux);

	if (tipo_de_registro)
	{
		while (posicion == -1 && i < posicones_a_verificar)
		{
			if (strcmp(registro_aux, Vcategorias[i]) == 0)
			{
				posicion = i;
			}
			i++;
		}
	}
	else
	{
		while (posicion == -1 && i < posicones_a_verificar)
		{
			if (strcmp(registro_aux, palabras[indice_categoria][i]) == 0)
			{
				posicion = i;
			}
			i++;
		}
	}
	return posicion;
}

//Validar Palabra o Categoria.(LONGITUD Y MAYUSCULA).
bool validar_long_mayus(Tstring palabra_categoria)
{
	bool validacion = true;
	limpiar_salto(palabra_categoria);

	if (strlen(palabra_categoria) <= 5 || strlen(palabra_categoria) >= 51)
	{
		validacion = false;
	}
	else
	{
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

int main()
{
	Tcategoria Vcategorias;											   //Vector de categorias.
	Tpalabra_pista palabras, pistas;								   //Matrices de palabras y pistas respectivamente.
	int tot_palabras = 0, cont_categorias = 0, cont_palabras[MAX_CAT]; //Contador de palabras, de categorias y de palabras por categoria.

	return 0;
}
