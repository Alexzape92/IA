/*******************************************/
/* 		    BUSQUEDA.H                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#include "puzle.h"
#include "listaia.h"

#ifndef _tNodo_
#define _tNodo_
typedef struct NodoBusqueda_{
    tEstado *estado;
    unsigned operador;
    int costeCamino;
    int profundidad;
    int valHeuristica;
    struct NodoBusqueda_ *padre;
} tNodo;

#endif

int busquedaProf(void);
int busquedaAnc(void);
int busquedaAncRepe(void);
int busquedaProfRepe(void);
int busquedaProfLimit(int limite);
int busquedaProfIter(int limite);
int busquedaVoraz();
int busquedaA();
void solucionFin(int res);
