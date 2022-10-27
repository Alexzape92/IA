/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puzle.h"



tEstado *crearEstado(int puzle[N][N])
{
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, ficha;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
      {
         ficha=puzle[i][j];
         estado->celdas[i][j]=ficha;

         if(ficha == 0){   //Guardamos la posición si es el hueco vacío
            estado->fila = i;
            estado->col =j;
         }
      }
   return estado;
}


tEstado *estadoInicial()
{
   return crearEstado(puzle_inicial);
}


tEstado *estadoObjetivo()
{
   return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado *estado)
{
   return 1;
}

/* VISUALIZACI�N DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado)
{
   int i,j;

   for (i=0; i<N; i++)
   {
      for (j=0; j<N; j++)
         printf("%d",estado->celdas[i][j]);
      printf("\n");
   }
   printf("\n");
}


void dispOperador(unsigned op)
{
   switch(op)
   {
      case ARRIBA:    printf("Movimiento ARRIBA:\n"); break;
      case ABAJO:     printf("Movimiento ABAJO:\n"); break;
      case IZQUIERDA: printf("Movimiento IZQUIERDA:\n"); break;
      case DERECHA:   printf("Movimiento DERECHA:\n"); break;
   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

// Funci�n auxiliar para comprobar si dos puzles tienen las fichas colocadas en el mismo orden en el tablero
int iguales(tEstado *s, tEstado *t)  //
{
   int ig = 1, i = 0, j = 0;
   while(ig == 1 && i < N){
      if(s->celdas[i][j] != t->celdas[i][j])
         ig = 0;
      if(j < N-1)
         j++;
      if(j == N - 1){
         j = 0; i++;
      }
   }
   return ig;
}


int testObjetivo(tEstado *estado)
{
return iguales(estado, estadoObjetivo());
}


int esValido(unsigned op, tEstado *estado)
{
   int result = 1;
   int fila = estado->fila, columna = estado->col;
   switch(op){
      case ARRIBA: if(fila == 0) result = 0; break;
      case DERECHA: if(columna == N-1) result = 0; break;
      case IZQUIERDA: if(columna == 0) result = 0; break;
      case ABAJO: if(fila == N-1) result = 0; break;
   }

   return result;
}


tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
   tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
   memcpy(nuevo, estado,sizeof(tEstado));  // Hace una copia del estado
   int fila = nuevo->fila, columna = nuevo->col;
    
   switch(op){
      case ARRIBA: 
         nuevo->celdas[fila][columna] = nuevo->celdas[fila-1][columna];
         nuevo->celdas[fila-1][columna] = 0;
         nuevo->fila--;
         break;
      case DERECHA: 
         nuevo->celdas[fila][columna] = nuevo->celdas[fila][columna+1];
         nuevo->celdas[fila][columna+1] = 0;
         nuevo->col++;
         break;
      case IZQUIERDA: 
         nuevo->celdas[fila][columna] = nuevo->celdas[fila][columna-1];
         nuevo->celdas[fila][columna-1] = 0;
         nuevo->col--;
         break;
      case ABAJO: 
         nuevo->celdas[fila][columna] = nuevo->celdas[fila+1][columna];
         nuevo->celdas[fila+1][columna] = 0;
         nuevo->fila++;
         break;
   }
return nuevo;
}




