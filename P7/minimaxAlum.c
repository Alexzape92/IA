/*******************************************/
/* 		    minimaxAlum.c                  */
/*       Estrategia MiniMax                */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tictactoe.h"

int valormin(tNodo* t);
int valormax(tNodo* t);
int min(int a, int b);
int max(int a, int b);

tNodo* minimax(tNodo *t){
      int max = -100000;
      int mejorJugada = 0;
      for(int jugada = 0; jugada < N; jugada++){
            if(esValida(t, jugada)){
                  tNodo* intento = aplicaJugada(t, 1, jugada);
                  int max_actual = valormin(intento);
                  if(max_actual > max){
                        max = max_actual;
                        mejorJugada = jugada;
                  }
            }
      }

      return aplicaJugada(t, 1, mejorJugada);
}

tNodo *jugadaAdversario(tNodo *t) {
     int jugada = 0;
     printf("\nJugada ([0..8])?: ");
     scanf("%d", &jugada);
     while (!esValida(t,jugada))
     {
        printf("\n Intenta otra posicion del tablero \n");
        printf("\n");
        printf("\nJugada ([0..8])?: ");
        scanf("%d", &jugada);
     }
     t=aplicaJugada(t,-1,jugada);
     return t;
}

int valormin(tNodo* t){
      int valor_min = 100000;
      if(t->vacias == 0)
            valor_min = terminal(t);
      else{
            for(int jugada = 0; jugada < N; jugada++){
                  if(esValida(t, jugada))
                        valor_min = min(valor_min, valormax(aplicaJugada(t, -1, jugada)));
            }
      }
      return valor_min;
}

int valormax(tNodo* t){
      int valor_max = -100000;
      if(t->vacias == 0)
            valor_max = terminal(t);
      else{
            for(int jugada = 0; jugada < N; jugada++){
                  if(esValida(t, jugada))
                        valor_max = max(valor_max, valormin(aplicaJugada(t, 1, jugada)));
            }
      }
      return valor_max;
}

int min(int a, int b){
      if(a < b) return a;
      else return b;
}

int max(int a, int b){
      if(a > b) return a;
      else return b;
}