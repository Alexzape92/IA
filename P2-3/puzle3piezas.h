#ifndef PUZLE3PIEZAS_H_
#define PUZLE3PIEZAS_H_

#define A 0
#define B 1
#define C 2

#define ARRIBA_A 1
#define ABAJO_A 2
#define IZQUIERDA_A 3
#define DERECHA_A 4
#define ARRIBA_B 5
#define ABAJO_B 6
#define IZQUIERDA_B 7
#define DERECHA_B 8
#define ARRIBA_C 9
#define ABAJO_C 10
#define IZQUIERDA_C 11
#define DERECHA_C 12
#define N 6
#define NUM_OPERADORES 12

typedef struct {
    int filas[3], columnas[3];  //posición de los representantes de las piezas
} tEstado;

//Posiciones obstáculos
static int filas_obs[3] = {0, 1, 3};
static int columnas_obs[3] = {0, 0, 3};

static int filas_inicial[] = {3, 4, 1};
static int columnas_inical[] = {1, 4, 3};

static int filas_final[] = {4, 5, 4};
static int columnas_final[] = {1, 3, 5};


tEstado* crearEstado(int fs[], int cs[]);
tEstado* estadoInicial();
tEstado* estadoObjetivo();
int esValido(unsigned op, tEstado* estado);
tEstado* aplicaOperador(unsigned op, tEstado* estado);
int iguales(tEstado *s, tEstado *t);
int testObjetivo(tEstado *estado);

#endif