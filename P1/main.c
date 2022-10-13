#include "puzle.h"
#include <stdlib.h>

int main() {
    int op;
    tEstado *n,*a;
    a=estadoInicial();
    dispEstado(a);
    for (op=1; op<=NUM_OPERADORES; op++) {
        if (esValido(op, a)){
            n=aplicaOperador(op,a);
            dispOperador(op);
            dispEstado(n);
            free(n);
        }
    }
    free(a);

}