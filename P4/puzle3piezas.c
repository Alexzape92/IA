#include "puzle3piezas.h"

tEstado* crearEstado(int fs[], int cs[]){
    tEstado *estado = (tEstado*)malloc(sizeof(tEstado));
    for(int i = 0; i < 3; i++)
        estado->filas[i] = fs[i];
    for(int i = 0; i < 3; i++)
        estado->columnas[i] = cs[i];
    
    return estado;
}

tEstado* estadoInicial(){
    return crearEstado(filas_inicial, columnas_inical);
}

tEstado* estadoObjetivo(){
    return crearEstado(filas_final, columnas_final);
}

int coste(unsigned op, tEstado *estado){
   return 1;
}

int esValido(unsigned op, tEstado *estado){
    int result = 1;
    switch(op){
        case ARRIBA_A:
            if(estado->filas[A] - 2 < 0)    //Se sale por arriba
                result = 0;
            for(int i = 0; i < 3; i++){     //Choca con un obstáculo?
                if(estado->filas[A] - 2 == filas_obs[i])
                    result = 0;
                if(estado->filas[A] - 1 == filas_obs[i] && estado->columnas[A] - 1 == columnas_obs[i])
                    result = 0;
                if(estado->filas[A] - 1 == filas_obs[i] && estado->columnas[A] + 1 == columnas_obs[i])
                    result = 0;
            }
            
            if(estado->filas[A] - 2 == estado->filas[B] && estado->columnas[A] == estado->columnas[B])
                result = 0;
            if(estado->filas[A] - 2 == estado->filas[B] && estado->columnas[A] == estado->columnas[B] - 1)
                result = 0;
            if(estado->filas[A] - 2 == estado->filas[B] && estado->columnas[A] == estado->columnas[B] + 1)
                result = 0;
            if(estado->filas[A] - 1 == estado->filas[B] && estado->columnas[A] == estado->columnas[B] - 1)
                result = 0;
            if(estado->filas[A] - 1 == estado->filas[B] && estado->columnas[A] == estado->columnas[B] + 1)
                result = 0;
            
            if(estado->filas[A] - 2 == estado->filas[C] - 1 && estado->columnas[A] == estado->columnas[C])
                result = 0;
            if(estado->filas[A] - 1 == estado->filas[C] - 1 && estado->columnas[A] == estado->columnas[C] - 1)
                result = 0;
            if(estado->filas[A] - 1 == estado->filas[B] - 1 && estado->columnas[A] == estado->columnas[C] + 1)
                result = 0;
            
            break;
        case ABAJO_A:
        case IZQUIERDA_A:
        case DERECHA_A:
        case ARRIBA_B:
        case ABAJO_B:
        case IZQUIERDA_B:
        case DERECHA_B:
        case ARRIBA_C:
        case ABAJO_C:
        case IZQUIERDA_C:
        case DERECHA_C:
    }
}