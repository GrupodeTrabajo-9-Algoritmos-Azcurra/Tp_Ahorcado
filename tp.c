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

//Valida la existencia de una categoria y retorna la posicion del vector
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

//Validar Palabra o Categoria.(LONGITUD Y MAYUSCULA).
bool validar_palabra_categoria(Tstring palabra_categoria)
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

//Ingreso Categoria.
void ingresar_categoria(Tstring categoria, Tcategoria Vcategorias, int cont_categorias)
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
			categoria_valida_longitud_mayuscula = validar_palabra_categoria(categoria_aux);
			if (!categoria_aux)
			{
				printf("La categoria debe estar en mayusculas y tener entre 5 y 49 caracteres\n");
			}
			categoria_valida_existencia = validar_existencia_categoria(categoria_aux, Vcategorias, cont_categorias);
			if (categoria_valida_existencia != -1)
			{
				printf("La categoria ya existe.\n");
			}

		} while (!categoria_valida_longitud_mayuscula || categoria_valida_existencia != -1);

		//Registrar categoria.
		strcpy(Vcategorias[cont_categorias], categoria_aux);
		cont_categorias = cont_categorias + 1;

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
}

//Ingreso  palabras, pista y asignacion de categoria.
void ingresar_palabras(Tcategoria Vcategorias, Tpalabra_pista palabras, Tpalabra_pista pistas, int cont_categorias, int cont_palabras[MAX_PAL], int tot_palabras)
{
	bool ingreso_listo, palabra_valida;
	int indice_categoria;
	char opcion;
	Tstring palabra_aux, pista_aux, categoria_aux;

	ingreso_listo = false;
	while (ingreso_listo == false)
	{
		//Ingresar palabra
		do
		{
			printf("Ingresa una palabra:\n");
			fgets(palabra_aux, MAX_STR, stdin);
			fflush(stdin);
			palabra_valida = validar_palabra_categoria(palabra_aux);
			if (!palabra_valida)
			{
				printf("La palabra debe estar en mayusculas y tener entre 5 y 49 caracteres\n");
			}
		} while (!palabra_valida);

		//Ingresar pista
		printf("Ingresa una pista para la palabra:\n");
		fgets(pista_aux, MAX_STR, stdin);
		fflush(stdin);
		limpiar_salto(pista_aux);

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

		//Insertar variables auxiliares un su matriz correspondiente e incrementar contador
		strcpy(palabras[indice_categoria][cont_palabras[indice_categoria]], palabra_aux);
		strcpy(pistas[indice_categoria][cont_palabras[indice_categoria]], pista_aux);
		cont_palabras[indice_categoria]++;
		tot_palabras++;

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
}

void mostrar_alfabeticamente(Tpalabra_pista palabras, int indice_categoria, int cont_palabras[MAX_PAL])
{
	int i, j;
	Tstring palabra_aux;

	//Ordenar con burbujeo
	for (i = 1; i < cont_palabras; i++)
	{
		for (j = 0; j < cont_palabras - i; j++)
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
	for (i = 0; i < cont_palabras; i++)
	{
		printf("%s\n", palabras[indice_categoria][j]);
	}
}

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
		printf("%s\n", Vcategorias[j]);
	}
}

void listar_palabras_de_categoria(Tcategoria Vcategorias, Tpalabra_pista palabras, int cont_palabras[MAX_PAL], int cont_categorias)
{
	Tstring categoria_aux;
	int indice_categoria;

	//Ingresar categoria
	do
	{
		printf("Ingresa una categoria para mostrar su listado de palabras:\n");
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
}

//Mostrar todas las palabras en orden descendente.
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
	for (i = tot_palabras - 1; i > 0; i--)
	{
		printf("%s", palabras_todas[i]);
	}
}



bool verificar_letra(Tstring letra, Tstring formando_palabra, Tstring letras_error, Tstring palabra)
{
    int i = 0;
    if ((((int)letra[0]>64)&&((int)letra[0]<91)) || (((int)letra[0]>96)&&((int)letra[0]<123)))
    {
        if (strstr(palabra, strlwr(letra)) == NULL)
        {
            if (strstr(letras_error, strlwr(letra)) == NULL)
            {
                strncat(letras_error, strlwr(letra),1);
                imprimir_letra("0", letras_error);
            }else{
                printf("Letra ya ingresada.\n");
            }
        }
        else
        {
            if (strstr(formando_palabra, strlwr(letra)) == NULL)
            {
                imprimir_letra(strlwr(letra));
                for(i=0; i < cantida_letras(palabra, strlwr(letra)); i++)
                {
                    strncat(formando_palabra,strlwr(letra),1);
                }
            }else{
                printf("Letra ya ingresada.\n");
            }
        }
        return true;
    }
    return false;
}

void imprimir_ahorcado(Tstring palabra)
{
    Tstring letra, formando_palabra, letras_error;
    int i =0, j = -1;                           //Esto se deberia poner en una funcion
    Tstring palabra_arreglada;
    for(i = 0; i<strlen(palabra); i++)
    {
        if (palabra[i] != ' ')
        {
            j++;
            palabra_arreglada[j] = palabra[i];
        }
    }
    strcpy(palabra_arreglada, strlwr(palabra_arreglada));                       //Hasta aca, pero no se como devolver una cadena por funcion
    bool victoria = false, max_palabras = false;
    while ((victoria == false) && (max_palabras == false))
    {
        printf("Ingrese una letra: ");
        scanf("%s", letra);
        fflush(stdin);
        while(verificar_letra(letra, formando_palabra, letras_error, palabra_arreglada) == false){
            printf("Ingrese nuevamente: ");
            scanf("%s", letra);
            fflush(stdin);
        }
        if (strlen(letras_error) >= 6)
        {
            max_palabras = true;
        }
        if (strlen(palabra_arreglada) == strlen(formando_palabra))
        {
            victoria = true;
        }
    }
}

void imprimir_letra(Tstring letra, Tstring letras_error)
{
    int i = 0;
    if (letra[0] != '0')
    {
        printf("Letra correcta\n");
    }else{
        printf("%s\n", letras_error);
    }
}


int cantida_letras(Tstring palabra, Tstring letra)
{
    int i = 0, contador = 0;
    for(i=0; i< (int)strlen(palabra);i++)
    {
        if (palabra[i] == letra[0])
        {
            contador++;
        }
    }
    return contador;
}



int main()
{
	Tcategoria Vcategorias;											   //Vector de categorias.
	Tpalabra_pista palabras, pistas;								   //Matrices de palabras y pistas respectivamente.
	int tot_palabras = 0, cont_categorias = 0, cont_palabras[MAX_CAT]; //Contador de palabras, de categorias y de palabras por categoria.
	//imprimir_ahorcado("Palabra para jugar");
	return 0;
}
