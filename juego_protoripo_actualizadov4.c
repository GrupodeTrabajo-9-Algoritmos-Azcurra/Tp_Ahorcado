#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_STR 50
#define MAX_CAT 20
#define MAX_PAL 20
#define max_caracteres 100
#define max_intentos 6

typedef char Tstring[MAX_STR];
typedef Tstring Tcategoria[MAX_CAT];
typedef Tstring Tpalabra_pista[MAX_CAT][MAX_PAL];

typedef struct {
    int identificador;
    Tstring nombre_participantes;
    int puntaje_actual;
    int puntaje_total;
}Participantes;

typedef struct{
    int identificador;
    int puntaje;
}Valor;

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


void pantalla_final(cadena palabra_secreta,cadena palabra_mostrar,cadena letras_ingresadas,int intentos, int numero_jugador, Valor vec_valor[])
{
	if (intentos==max_intentos+1){
		system("@cls||clear");
		strcpy(palabra_mostrar,palabra_secreta);
		pantalla_actual(palabra_mostrar,letras_ingresadas,intentos);
		printf("\n\n!AHORCADO¡\n\n");
		vec_valor[numero_jugador].puntaje = 10;
		system("PAUSE");
		system("cls");
	}
	else{
		system("@cls||clear");
		pantalla_actual(palabra_mostrar,letras_ingresadas,intentos);
		printf("\n\nSE HA COMPLETADO LA PALABRA\n\n");
		vec_valor[numero_jugador].puntaje = intentos-1; //Aca a veces se genera un error y no logro descubrir porque. Dice que no puede acceder a esa direccion de memoria.
		system("PAUSE");
		system("cls");
	}

return;
}


void juego_prototipo(cadena palabra_secreta,cadena pista, int cantidad_jugadores, Valor vec_valor[])
{
    int numero_jugador = 0;
    for (numero_jugador=0; numero_jugador<cantidad_jugadores; numero_jugador++){
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
        pantalla_final(palabra_secreta,palabra_mostrar,letras_ingresadas,intentos, numero_jugador, vec_valor);
    }
return;
}



int cantidad_jugadoress(){
    int cantidad_jugadores;
    printf("Ingrese la cantidad de jugadores: ");
    scanf("%d", &cantidad_jugadores);
    fflush(stdin);
    return cantidad_jugadores;
}

int cantidad_partidass(){
    int cantidad_partidas;
    printf("Ingrese la cantidad de partidas: ");
    scanf("%d", &cantidad_partidas);
    fflush(stdin);
    return cantidad_partidas;
}

void cargar_jugadores(Participantes vec_jugadores[], Participantes vec_jugadores_ordenados[], int cantidad_jugadores){
    int i = 0, j = 1;
    Tstring nombre;
    for (i = 0; i < cantidad_jugadores; i++)
    {
    printf("Ingrese los nombres de los jugadores: ");
    fflush(stdin);
    scanf("%s", vec_jugadores[i].nombre_participantes);
    vec_jugadores[i].identificador = j;
    vec_jugadores[i].puntaje_actual = 0;
    vec_jugadores[i].puntaje_total = 0;
    vec_jugadores_ordenados[i].identificador = vec_jugadores[i].identificador;
    vec_jugadores_ordenados[i].puntaje_actual = vec_jugadores[i].puntaje_actual;
    vec_jugadores_ordenados[i].puntaje_total = vec_jugadores[i].puntaje_total;
    strcpy(vec_jugadores_ordenados[i].nombre_participantes, vec_jugadores[i].nombre_participantes);
    j++;
    }
}

void mostrar_estatus(Participantes vec_jugadores[], Participantes aux[1], int cantidad_jugadores, int cantidad_partidas)
{
    int i;
    if (cantidad_partidas > 1){
        printf("\n\nPartidas restantes: %d \n\n", (cantidad_partidas-1));
        for(i=0;i<cantidad_jugadores;i++)
        {
            printf("\n\n Participante numero: %d", vec_jugadores[i].identificador);
            printf("\n Nombres: %s ", vec_jugadores[i].nombre_participantes);
            printf("\n Puntos actuales: %d ", vec_jugadores[i].puntaje_actual);
            printf("\n Puntos totales: %d\n\n\n", vec_jugadores[i].puntaje_total);

        }
    }else{
        printf("\n\n\nResultados finales:  \n\n", cantidad_partidas);
        for(i=0;i<cantidad_jugadores;i++)
        {
            printf("\n\n Participante numero: %d", vec_jugadores[i].identificador);
            printf("\n Nombres: %s ", vec_jugadores[i].nombre_participantes);
            printf("\n Puntos actuales: %d ", vec_jugadores[i].puntaje_actual);
            printf("\n Puntos totales: %d\n\n\n", vec_jugadores[i].puntaje_total);

        }
    }
    system("PAUSE");
    system("cls");
}

void ordenar_ganador(Participantes vec_jugadores[], Participantes aux[], int cantidad_jugadores, int cantidad_partidas){
    int i, j;
    if (cantidad_partidas > 1){
        for(i=0;i<cantidad_jugadores;i++){
            for (int j=0 ; j < cantidad_jugadores - 1; j++){
                if (vec_jugadores[j].puntaje_actual > vec_jugadores[j+1].puntaje_actual){
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
            for (int j=0 ; j < cantidad_jugadores - 1; j++){
                if ((vec_jugadores[j].puntaje_total) > (vec_jugadores[j+1].puntaje_total))
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

void modificar_valores(Valor vec_valor[], Participantes vec_jugadores[], Participantes vec_jugadoresord[], int cantidad_partidas, int cantidad_jugadores){
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


int main()
{
    int cantidad_partidas, cantidad_jugadores;
    cantidad_jugadores = cantidad_jugadoress();
    cantidad_partidas = cantidad_partidass();
    Participantes participantes[cantidad_jugadores], Aux[1], participantes_ordenado[cantidad_jugadores];
    Valor valor[cantidad_jugadores];
    cargar_jugadores(participantes, participantes_ordenado, cantidad_jugadores);
    while (cantidad_partidas > 0){
        cadena pista,letra_ingresada;
        cadena palabra_secreta;
        fflush(stdin);
        system("cls");
        printf("Ingrese una palabra secreta: ");
        fgets(palabra_secreta,max_caracteres,stdin);
        fflush(stdin);
        limpiar_salto(palabra_secreta);
        printf("Ingrese una palabra pista: ");
        scanf("%c",&pista[0]);
        fflush(stdin);
        system("@cls||clear");
        juego_prototipo(palabra_secreta,pista, cantidad_jugadores, valor);
        modificar_valores(valor, participantes, participantes_ordenado, cantidad_partidas, cantidad_jugadores);
        ordenar_ganador(participantes, Aux, cantidad_jugadores, cantidad_partidas);
        mostrar_estatus(participantes, Aux, cantidad_jugadores, cantidad_partidas);
        cantidad_partidas--;
    }
    return 0;
}
