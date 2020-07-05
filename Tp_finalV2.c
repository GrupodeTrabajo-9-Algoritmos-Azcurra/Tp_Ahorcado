#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#define max_caracteres 50
#define max_categorias 20
#define max_palabras 20
#define max_intentos 6


typedef char cadena[max_caracteres];
typedef cadena Tcategoria[max_categorias];
typedef cadena Tpalabra_pista[max_categorias][max_palabras];

typedef struct {
    int identificador;
    cadena nombre_participantes;
    int puntaje_actual;
    int puntaje_total;
}Participantes;

typedef struct {
    int identificador;
    int puntaje;
}Valor;

//Limpia el \n agregado por fgets
void limpiar_salto(cadena cadena)
{
	int tam;
	tam = strlen(cadena);
	if (cadena[tam - 1] == '\n')
	{
		cadena[tam - 1] = '\0';
	}
}

//Declarar funcion "partida" para usarla en "menu_ingreso"
void partida(Tpalabra_pista palabras, Tpalabra_pista pistas, int cont_palabras[max_categorias], int cont_categorias, int tot_palabras);

/*
MODULOS DEL MENU DE INGRESO Y LISTADO
*/

//Valida la existencia de una categoria y retorna su posicion en el vector
int validar_existencia_categoria(cadena categoria, Tcategoria Vcategorias, int cont_categorias)
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
int validar_existencia_palabra(cadena palabra, Tpalabra_pista palabras, int indice_categoria, int cont_palabras[max_categorias])
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

//Validar que el caracter ingresado como pista este contenido en la palabra
bool validar_pista(cadena pista, cadena palabra) {
	bool pista_valida=true;

	if(strlen(pista)!=1 || strstr(palabra, pista)==0 || pista[0]==32) {
		pista_valida=false;
	}

	return pista_valida;
}

//Validar Palabra o Categoria.(LONGITUD Y MAYUSCULA).
bool validar_long_mayus(cadena palabra_categoria)
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
	cadena categoria_aux;
	char opcion;

	ingreso_listo = false;
	while (ingreso_listo == false)
	{
		//Ingresar categoria.
		do
		{
			printf("Ingresa una categoria:\n");
			fgets(categoria_aux, max_caracteres, stdin);
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
			if (opcion == 'n' || opcion == 'N')
			{
				ingreso_listo = true;
			}
		} while (opcion != 's' && opcion != 'n' && opcion != 'S' && opcion != 'N');

		//Limpiar pantalla
		system("@cls||clear");
	}
	system("PAUSE");
}

//Ingreso  palabras, pista y asignacion de categoria.
void ingresar_palabras(Tcategoria Vcategorias, Tpalabra_pista palabras, Tpalabra_pista pistas, int cont_categorias, int cont_palabras[max_palabras], int *tot_palabras)
{
	bool ingreso_listo, palabra_valida, pista_valida;
	int indice_categoria, palabra_valida_existencia = 0;
	char opcion;
	cadena palabra_aux, pista_aux, categoria_aux;

	if(cont_categorias>0) {
		ingreso_listo = false;
		while (ingreso_listo == false)
		{
			//Asignar categoria
			do
			{
				printf("Asigna una categoria a la palabra:\n");
				fgets(categoria_aux, max_caracteres, stdin);
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
				fgets(palabra_aux, max_caracteres, stdin);
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
			do
			{
				printf("Ingresa una pista para la palabra:\n");
				fgets(pista_aux, max_caracteres, stdin);
				fflush(stdin);
				limpiar_salto(pista_aux);

				//Validacion de la pista
				pista_valida = validar_pista(pista_aux, palabra_aux);
				if (!pista_valida)
				{
					printf("La pista debe ser un caracter contenido en la palabra\n");
				}

			} while (!pista_valida);

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
				if (opcion == 'n' || opcion == 'N')
				{
					ingreso_listo = true;
				}
			} while (opcion != 's' && opcion != 'n' && opcion != 'S' && opcion != 'N');

			//Limpiar pantalla
			system("@cls||clear");
		}
	} else {
		printf("No existe ninguna categoria, debes ingresar al menos una antes de ingresar las palabras.\n");
	}
	system("PAUSE");
}

//Muestra palabras en orden alfabetico
void mostrar_alfabeticamente(Tpalabra_pista palabras, int indice_categoria, int cont_palabras[max_palabras], int cont_categorias)
{
	int i, j;
	cadena palabra_aux;
	Tpalabra_pista palabras_aux;

	//Copiar contenido de palabras a palabras_aux para no perder el orden en la matriz inicial
	for (i = 0; i < cont_categorias; i++)
	{
		for (j = 0; j < cont_palabras[i]; j++)
		{
			strcpy(palabras_aux[i][j], palabras[i][j]);
		}
	}

	//Ordenar con burbujeo
	for (i = 1; i < cont_palabras[indice_categoria]; i++)
	{
		for (j = 0; j < cont_palabras[indice_categoria] - i; j++)
		{
			if (strcmp(palabras_aux[indice_categoria][j], palabras_aux[indice_categoria][j + 1]) == 1)
			{
				strcpy(palabra_aux, palabras_aux[indice_categoria][j]);
				strcpy(palabras_aux[indice_categoria][j], palabras_aux[indice_categoria][j + 1]);
				strcpy(palabras_aux[indice_categoria][j + 1], palabra_aux);
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
	cadena categoria_aux;
	Tcategoria Vcategorias_aux;

	//Copiar contenido de Vcategorias a Vcategorias_aux para no perder el orden en el vector inicial
	for (i = 0; i < cont_categorias; i++)
	{
		strcpy(Vcategorias_aux[i], Vcategorias[i]);
	}

	//Ordenar con burbujeo
	for (i = 1; i < cont_categorias; i++)
	{
		for (j = 0; j < cont_categorias - i; j++)
		{
			if (strcmp(Vcategorias_aux[j], Vcategorias_aux[j + 1]) == 1)
			{
				strcpy(categoria_aux, Vcategorias_aux[j]);
				strcpy(Vcategorias_aux[j], Vcategorias_aux[j + 1]);
				strcpy(Vcategorias_aux[j + 1], categoria_aux);
			}
		}
	}

	//Mostrar en pantalla vector ordenado
	for (i = 0; i < cont_categorias; i++)
	{
		printf("%s\n", Vcategorias_aux[i]);
	}

	system("PAUSE");
}

//Listar palabras de una categoria ordenadas alfabeticamente
void listar_palabras_de_categoria(Tcategoria Vcategorias, Tpalabra_pista palabras, int cont_palabras[max_palabras], int cont_categorias)
{
	cadena categoria_aux;
	int indice_categoria;

	//Ingresar categoria
	do
	{
		printf("Ingresa una categoria:\n");
		fgets(categoria_aux, max_caracteres, stdin);
		fflush(stdin);
		indice_categoria = validar_existencia_categoria(categoria_aux, Vcategorias, cont_categorias);
		if (indice_categoria == -1)
		{
			printf("La categoria ingresada no existe.\n");
		}
	} while (indice_categoria == -1);

	//Limpiar pantalla
	system("@cls||clear");

	mostrar_alfabeticamente(palabras, indice_categoria, cont_palabras, cont_categorias);

	system("PAUSE");
}

//Mostrar todas las palabras por cantidad de caracteres en orden descendente.
void mostrar_todas_las_palabras(Tpalabra_pista palabras, int tot_palabras, int cont_categorias, int cont_palabras[max_categorias])
{
	int i, j, k = 0;
	cadena palabras_todas[tot_palabras], palabra_aux;

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
void menu_listado(Tcategoria Vcategorias, Tpalabra_pista palabras, Tpalabra_pista pistas, int cont_categorias, int cont_palabras[max_palabras], int tot_palabras)
{
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

	switch(opcion_menu_listado){
		case 1://Mostrar categorias ordenadas alfabeticamente en forma ascendente
			mostrar_categorias_alfabeticamente(Vcategorias, cont_categorias);
			system("@cls||clear");
			menu_listado(Vcategorias, palabras, pistas, cont_categorias, cont_palabras, tot_palabras);
			break;
		case 2:	//Mostrar palabras ordenadas por cantidad de caracteres en forma descendente
			mostrar_todas_las_palabras(palabras, tot_palabras, cont_categorias, cont_palabras);
			system("@cls||clear");
			menu_listado(Vcategorias, palabras, pistas, cont_categorias, cont_palabras, tot_palabras);
			break;
		case 3://Ingresar una categoria y mostrar todas las palabras ordenadas alfabeticamente
			listar_palabras_de_categoria(Vcategorias, palabras, cont_palabras, cont_categorias);
			system("@cls||clear");
			menu_listado(Vcategorias, palabras, pistas, cont_categorias, cont_palabras, tot_palabras);
			break;
		case 4:
			//Continuar al juego
			partida(palabras, pistas, cont_palabras, cont_categorias, tot_palabras);
			break;
		default:
			//Opcion invalida
			printf("La opcion ingresada no es valida, intentalo de nuevo.\n\n");
			menu_listado(Vcategorias, palabras, pistas, cont_categorias, cont_palabras, tot_palabras);
			break;
	}
}

//Menu para el ingreso de categorias, palabras y pistas
void menu_ingreso(Tcategoria Vcategorias, Tpalabra_pista palabras, Tpalabra_pista pistas, int cont_palabras[max_palabras], int *cont_categorias, int *tot_palabras)
{
	int opcion_menu_ingreso;

	//Ingreso de opcion
	printf("MENU DE INGRESO. Ingresa una opcion para continuar:\n");
	printf("1 -> Ingresar categorias\n");
	printf("2 -> Ingresar palabras\n");
	printf("3 -> Continuar al menu de listados\n");
	scanf("%i", &opcion_menu_ingreso);
	fflush(stdin);
	system("@cls||clear");

	switch(opcion_menu_ingreso){
		case 1: //Ingresar categorias
			ingresar_categoria(Vcategorias, cont_categorias);
			system("@cls||clear");
			menu_ingreso(Vcategorias, palabras, pistas, cont_palabras, cont_categorias, tot_palabras);
			break;
		case 2: //Ingresar palabras
			ingresar_palabras(Vcategorias, palabras, pistas, *cont_categorias, cont_palabras, tot_palabras);
			system("@cls||clear");
			menu_ingreso(Vcategorias, palabras, pistas, cont_palabras, cont_categorias, tot_palabras);
			break;
		case 3: //Continuar al menu de listados
			if(*tot_palabras==0) {
				printf("Debes ingresar al menos una palabra para continuar.\n\n");
				menu_ingreso(Vcategorias, palabras, pistas, cont_palabras, cont_categorias, tot_palabras);
			} else {
				menu_listado(Vcategorias, palabras, pistas, *cont_categorias, cont_palabras, *tot_palabras);
			}
			break;
		default: //Opcion invalida
			printf("La opcion ingresada no es valida, intentalo de nuevo.\n\n");
			menu_ingreso(Vcategorias, palabras, pistas, cont_palabras, cont_categorias, tot_palabras);
			break;
	}
}

/*
MODULOS DEL FUNCIONAMIENTO DEL JUEGO
*/

/*DIBUJO AHORCADO */

void gancho_cabeza(int veces_errado)
{
	printf(" _____\n");
	printf("|     |\n");
	printf("|     ");
	if (veces_errado>=1)
		printf("O\n");
	else
		printf("\n");
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
}

/*Partes juntas*/
void dibujo_colgado(int veces_errado)
{
	gancho_cabeza(veces_errado);
	torso(veces_errado);
	piernas_y_base(veces_errado);
}


/*Partida*/


int ascii(char letra)    // Esta función es en el caso de que no corresponda el valor de las letras con el de la tabla ASCII
{
	int letra_en_ascii;
	switch(letra){
		case 'Ñ': letra_en_ascii=165;
		break;
		case 'Á': letra_en_ascii=181;
		break;
		case 'É': letra_en_ascii=144;
		break;
		case 'Í': letra_en_ascii=214;
		break;
		case 'Ó': letra_en_ascii=224;
		break;
		case 'Ú': letra_en_ascii=233;
		break;
		case 'ñ': letra_en_ascii=164;
		break;
		case 'á': letra_en_ascii=160;
		break;
		case 'é': letra_en_ascii=130;
		break;
		case 'í': letra_en_ascii=161;
		break;
		case 'ó': letra_en_ascii=162;
		break;
		case 'ú': letra_en_ascii=163;
		break;
	}

	return letra_en_ascii;
}


//Entrada de una cadena
void input_string(cadena palabra)
{
	fflush(stdin);
	fgets(palabra,max_caracteres,stdin);
	fflush(stdin);
	limpiar_salto(palabra);
}


//Busca una letra por strstr() y solo indica si esta o no
bool buscar_letra(cadena palabra_secreta,cadena letra_ingresada)
{
	bool encontrado=true;
	if (strstr(palabra_secreta,letra_ingresada)==NULL)
		encontrado=false;

	return encontrado;
}


//Inicia la cadena que se muestra al lado del colgado con _ y ' ' según corresponda
void poner_guion_bajo(cadena palabra_mostrar,cadena palabra_secreta)
{
	int posicion;
	for (posicion=0;posicion<strlen(palabra_secreta);posicion++)
		if (palabra_secreta[posicion]!=' ')
			palabra_mostrar[posicion]='_';
		else
			palabra_mostrar[posicion]=' ';
	palabra_mostrar[strlen(palabra_secreta)]='\0';

}

//Modifica y muestra la cadena que esta por debajo del colgado con las letras que se vallan ingresando
void mostras_y_modificar_letras_ingresadas(cadena letras_ingresadas,cadena letra)
{
	int auxiliar=strlen(letras_ingresadas);
	if (!buscar_letra(letras_ingresadas,letra)){
		letras_ingresadas[auxiliar]=letra[0];
		letras_ingresadas[auxiliar+1]=' ';
		letras_ingresadas[auxiliar+2]='\0';
	}
	printf("%s",letras_ingresadas);
}


//Modifica la cadena al lado del colgado con la pista y si la letra ingresada es parte de la palabra
void modificar_palabra_mostrar(cadena palabra_mostrar,cadena palabra_secreta,cadena pista,cadena letra_ingresada)
{
	int posicion;
	for (posicion=0;posicion<strlen(palabra_secreta);posicion++){
		if (palabra_secreta[posicion]==pista[0] || palabra_secreta[posicion]==letra_ingresada[0])
			palabra_mostrar[posicion]=palabra_secreta[posicion];
	}
}


//Prepara y muestra la pantalla inicial
void pantalla_inicial(cadena palabra_mostrar,cadena palabra_secreta,cadena pista,int intentos)
{
	poner_guion_bajo(palabra_mostrar,palabra_secreta);
	dibujo_colgado(intentos-1);
	modificar_palabra_mostrar(palabra_mostrar,palabra_secreta,pista,pista);
	printf("  %s\n",palabra_mostrar);
}

//Prepara y muestra la pantalla de la letra acertada
void pantalla_acertado(cadena palabra_mostrar,cadena palabra_secreta,cadena pista,cadena letra_ingresada,cadena letras_ingresadas,int intentos)
{
	modificar_palabra_mostrar(palabra_mostrar,palabra_secreta,pista,letra_ingresada);
	dibujo_colgado(intentos-1);
	printf("  %s\n\n",palabra_mostrar);
	mostras_y_modificar_letras_ingresadas(letras_ingresadas,letra_ingresada);
}

//Prepara y muestra la pantalla de la letra no acertada
void pantalla_equivocado(cadena palabra_mostrar,cadena letras_ingresadas,cadena letra_ingresada,int intentos)
{
	dibujo_colgado(intentos-1);
	printf("  %s\n",palabra_mostrar);
	printf("\n");
	mostras_y_modificar_letras_ingresadas(letras_ingresadas,letra_ingresada);
}


//Muestra la pantalla con los parametros de entrada
void pantalla_actual(cadena palabra_mostrar,cadena letras_ingresadas,int intentos)
{
	dibujo_colgado(intentos-1);
	printf("  %s\n\n",palabra_mostrar);
	printf("%s",letras_ingresadas);
}


//Indicia si la letra es una entrada valida
bool letra_valida(char letra)
{
	bool valido=false;
	if ((letra<='Z' && letra>='A') || letra==(char)ascii('Ñ') || letra==(char)ascii('Á') || letra==(char)ascii('É') || letra==(char)ascii('Í') || letra==(char)ascii('Ó') || letra==(char)ascii('Ú'))
		valido=true;

	return valido;
}


//Ingreso y validacion de letras
void input(cadena letra_ingresada,cadena palabra_mostrar,cadena letras_ingresadas,int intentos)
{
	printf("\n\n\n");
	input_string(letra_ingresada);
	while (strlen(letra_ingresada)>1 || !letra_valida(letra_ingresada[0])){
		system("@cls||clear");
		pantalla_actual(palabra_mostrar,letras_ingresadas,intentos);
		printf("\n\nPor ingrese solo una letra mayuscula:\n");
		input_string(letra_ingresada);
	}
	system("@cls||clear");
}


//Prepara y muestra la pantalla segun se pierda o se gane
void pantalla_final(cadena palabra_secreta,cadena palabra_mostrar,cadena letras_ingresadas,int intentos, int numero_jugador, Valor vec_valor[])
{
	if (intentos==max_intentos+1) {
		system("@cls||clear");
		strcpy(palabra_mostrar,palabra_secreta);
		pantalla_actual(palabra_mostrar,letras_ingresadas,intentos);
		printf("\n\n!AHORCADO¡\n\n");
		vec_valor[numero_jugador].puntaje = 10;
		system("PAUSE");
		system("@cls||clear");
	} else {
		system("@cls||clear");
		pantalla_actual(palabra_mostrar,letras_ingresadas,intentos);
		printf("\n\n!SE HA COMPLETADO LA PALABRA¡\n\n");
		vec_valor[numero_jugador].puntaje = intentos-1; //Aca a veces se genera un error y no logro descubrir porque. Dice que no puede acceder a esa direccion de memoria.
		system("PAUSE");
		system("@cls||clear");
	}
}


//Logica del juego uniendo las funciones anteriores
void juego(cadena palabra_secreta,cadena pista, int cantidad_jugadores, Valor vec_valor[])
{
    int numero_jugador = 0;
    for (numero_jugador=0; numero_jugador<cantidad_jugadores; numero_jugador++){
        int posicion,intentos=1;
        cadena palabra_mostrar,letras_ingresadas,letra_ingresada;
        letras_ingresadas[0]='\0';                                    //Inicio el string para la funcion "poner_guion_bajo"
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
        pantalla_final(palabra_secreta,palabra_mostrar,letras_ingresadas,intentos, numero_jugador, vec_valor);
    }
}
bool validar_numeros(cadena cantidad){
    int contador = 0, i;
    for (i = 0; i< strlen(cantidad); i++){
        if(isdigit(cantidad[i])){
            contador++;
        }
    }
    if ((strlen(cantidad))== contador)
        return true;
    return false;
}

bool validar_nombre(cadena nombre){
    int i = 0, contador = 0;
    for(i =0; i < strlen(nombre); i++){
        if(((nombre[i])>= 'a' && (nombre[i])<= 'z')||((nombre[i])>= 'A' && (nombre[i])<= 'Z')){
            contador++;
        }
    }
    if (contador == (strlen(nombre))){
        return true;
    }
    printf("Ingrese sin numeros, sin espacios y sin caracteres especiales.\n");
    return false;
}

int cantidad_jugadoress()
{
    cadena cantidad_jugadores;
    int resultado;
    bool seguir = true;
    while (seguir){
        printf("Ingrese la cantidad de jugadores: ");
        scanf("%s", &cantidad_jugadores);
        fflush(stdin);
        if (validar_numeros(cantidad_jugadores)){
            seguir = false;
            resultado = atoi(cantidad_jugadores);
        }
    }
    system("cls");
    return resultado;
}


int cantidad_partidass()
{
    cadena cantidad_partidas;
    int resultado;
    bool seguir = true;
    while (seguir){
        printf("Ingrese la cantidad de partidas: ");
        scanf("%s", &cantidad_partidas);
        fflush(stdin);
        if (validar_numeros(cantidad_partidas)){
            seguir = false;
            resultado = atoi(cantidad_partidas); //Transforma un string a integer
        }
    }
    system("cls");
    return resultado;
}


void cargar_jugadores(Participantes vec_jugadores[], Participantes vec_jugadores_ordenados[], int cantidad_jugadores)
{
    int i = 0, j = 1;
    cadena nombre;
    bool seguir = true;
    for (i = 0; i < cantidad_jugadores; i++){
        while (seguir){
            printf("Ingrese el nombre del jugador %i: ", i+1);
            fflush(stdin);
            fgets(nombre, max_caracteres, stdin);
            fflush(stdin);
            limpiar_salto(nombre);
            if (validar_nombre(nombre)){
                    seguir = false;
            }

        }
	    strcpy(vec_jugadores[i].nombre_participantes, nombre);
	    vec_jugadores[i].identificador = j;
	    vec_jugadores[i].puntaje_actual = 0;
	    vec_jugadores[i].puntaje_total = 0;
	    vec_jugadores_ordenados[i].identificador = vec_jugadores[i].identificador;
	    vec_jugadores_ordenados[i].puntaje_actual = vec_jugadores[i].puntaje_actual;
	    vec_jugadores_ordenados[i].puntaje_total = vec_jugadores[i].puntaje_total;
	    strcpy(vec_jugadores_ordenados[i].nombre_participantes, vec_jugadores[i].nombre_participantes);
	    j++;
	    seguir = true;
    }
}


void mostrar_estatus(Participantes vec_jugadores[], Participantes aux[1], int cantidad_jugadores, int cantidad_partidas)
{
    int i;
    if (cantidad_partidas > 1){
        printf("\n\nPartidas restantes: %d \n\n", (cantidad_partidas-1));
        for(i=0;i<cantidad_jugadores;i++){
            printf("\n\n Participante numero: %d", vec_jugadores[i].identificador);
            printf("\n Nombres: %s ", vec_jugadores[i].nombre_participantes);
            printf("\n Puntos actuales: %d ", vec_jugadores[i].puntaje_actual);
            printf("\n Puntos totales: %d\n\n\n", vec_jugadores[i].puntaje_total);
        }
    }else{
        printf("\n\n\nResultados finales:  \n\n", cantidad_partidas);
        for(i=0;i<cantidad_jugadores;i++){
            printf("\n\n Participante numero: %d", vec_jugadores[i].identificador);
            printf("\n Nombres: %s ", vec_jugadores[i].nombre_participantes);
            printf("\n Puntos actuales: %d ", vec_jugadores[i].puntaje_actual);
            printf("\n Puntos totales: %d\n\n\n", vec_jugadores[i].puntaje_total);
        }
    }
    system("PAUSE");
    system("@cls||clear");
}


void ordenar_ganador(Participantes vec_jugadores[], Participantes aux[], int cantidad_jugadores, int cantidad_partidas)
{
    int i, j;
    if (cantidad_partidas > 1){
        for(i=0;i<cantidad_jugadores;i++){
            for (j=0 ; j < cantidad_jugadores - 1; j++){
                if (vec_jugadores[j].puntaje_actual < vec_jugadores[j+1].puntaje_actual){
                    strcpy(aux[j].nombre_participantes, vec_jugadores[j].nombre_participantes);
                    strcpy(vec_jugadores[j].nombre_participantes, vec_jugadores[j+1].nombre_participantes);
                    strcpy(vec_jugadores[j+1].nombre_participantes, aux[j].nombre_participantes);
                    aux[j].puntaje_actual = vec_jugadores[j].puntaje_actual;
                    vec_jugadores[j].puntaje_actual = vec_jugadores[j+1].puntaje_actual;
                    vec_jugadores[j+1].puntaje_actual = aux[j].puntaje_actual;
                    aux[j].puntaje_total = vec_jugadores[j].puntaje_total;
                    vec_jugadores[j].puntaje_total = vec_jugadores[j+1].puntaje_total;
                    vec_jugadores[j+1].puntaje_total = aux[j].puntaje_total;
                    aux[j].identificador = vec_jugadores[i].identificador;
                    vec_jugadores[j].identificador = vec_jugadores[j+1].identificador;
                    vec_jugadores[j+1].identificador = aux[j].identificador;
                }
            }
        }
    }else{
        for(i=0;i<cantidad_jugadores;i++){
            for (j=0 ; j < cantidad_jugadores - 1; j++){
                if ((vec_jugadores[j].puntaje_total) < (vec_jugadores[j+1].puntaje_total))
                {
                    strcpy(aux[j].nombre_participantes, vec_jugadores[j].nombre_participantes);
                    strcpy(vec_jugadores[j].nombre_participantes, vec_jugadores[j+1].nombre_participantes);
                    strcpy(vec_jugadores[j+1].nombre_participantes, aux[j].nombre_participantes);
                    aux[j].puntaje_actual = vec_jugadores[j].puntaje_actual;
                    vec_jugadores[j].puntaje_actual = vec_jugadores[j+1].puntaje_actual;
                    vec_jugadores[j+1].puntaje_actual = aux[j].puntaje_actual;
                    aux[j].puntaje_total = vec_jugadores[j].puntaje_total;
                    vec_jugadores[j].puntaje_total = vec_jugadores[j+1].puntaje_total;
                    vec_jugadores[j+1].puntaje_total = aux[j].puntaje_total;
                    aux[j].identificador = vec_jugadores[i].identificador;
                    vec_jugadores[j].identificador = vec_jugadores[j+1].identificador;
                    vec_jugadores[j+1].identificador = aux[j].identificador;
                }
            }
        }
    }
}


void modificar_valores(Valor vec_valor[], Participantes vec_jugadores[], Participantes vec_jugadoresord[], int cantidad_partidas, int cantidad_jugadores)
{
    int i = 0, j = 0;
    for (j=0; j<cantidad_jugadores; j++){
        vec_jugadoresord[j].puntaje_actual = vec_valor[j].puntaje;
        vec_jugadoresord[j].puntaje_total += vec_valor[j].puntaje;
    }
    for(i=0; i<cantidad_jugadores; i++){
        vec_jugadores[i].identificador = vec_jugadoresord[i].identificador;
        vec_jugadores[i].puntaje_actual = vec_jugadoresord[i].puntaje_actual;
        vec_jugadores[i].puntaje_total = vec_jugadoresord[i].puntaje_total;
        strcpy(vec_jugadores[i].nombre_participantes, vec_jugadoresord[i].nombre_participantes);
    }
}

//Entrada de datos y ejecucion de todas las partidas
void partida(Tpalabra_pista palabras, Tpalabra_pista pistas, int cont_palabras[max_categorias], int cont_categorias, int tot_palabras)
{
	cadena palabra_secreta,pista;
	int cantidad_partidas, cantidad_jugadores, indice_categoria_aleatorio, indice_palabra_aleatorio;
    cantidad_jugadores = cantidad_jugadoress();
    cantidad_partidas = cantidad_partidass();
    Participantes participantes[cantidad_jugadores], Aux[1], participantes_ordenado[cantidad_jugadores];
    Valor valor[cantidad_jugadores];
    cargar_jugadores(participantes, participantes_ordenado, cantidad_jugadores);
    system("@cls||clear");
    while (cantidad_partidas > 0){
    	//Obtener palabra y pista de forma aleatoria
    	srand(time(NULL)); //Inicializar la semilla
		indice_categoria_aleatorio=rand() % cont_categorias;
		indice_palabra_aleatorio=rand() % cont_palabras[indice_categoria_aleatorio];
		strcpy(palabra_secreta, palabras[indice_categoria_aleatorio][indice_palabra_aleatorio]);
		strcpy(pista, pistas[indice_categoria_aleatorio][indice_palabra_aleatorio]);

	//Ejecuta el juego y despues muestra los resultados
        juego(palabra_secreta,pista, cantidad_jugadores, valor);
        modificar_valores(valor, participantes, participantes_ordenado, cantidad_partidas, cantidad_jugadores);
        ordenar_ganador(participantes, Aux, cantidad_jugadores, cantidad_partidas);
        mostrar_estatus(participantes, Aux, cantidad_jugadores, cantidad_partidas);
        cantidad_partidas--;
    }
}


int main()
{
	Tcategoria Vcategorias;											   //Vector de categorias.
	Tpalabra_pista palabras, pistas;								   //Matrices de palabras y pistas respectivamente.
	int tot_palabras = 0, cont_categorias = 0, cont_palabras[max_categorias]; //Contador de palabras, de categorias y de palabras por categoria.

	//Menu de ingreso
	menu_ingreso(Vcategorias, palabras, pistas, cont_palabras, &cont_categorias, &tot_palabras);

	return 0;
}