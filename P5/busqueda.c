/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ordenarLista.h"

void solucionFin(int res){
   printf("\nFin de la busqueda\n");
    if (res)
      printf("Se ha llegado al objetivo\n");
   else
      printf("No se ha llegado al objetivo\n");
}
void dispNodo(tNodo *nodo){
    dispEstado(nodo->estado);
    printf("\n");
}
void dispCamino(tNodo *nodo){
    if (nodo->padre==NULL){
        printf("\n Desde el inicio\n");
        dispEstado(nodo->estado);
    }
    else {
        dispCamino(nodo->padre);
         dispOperador(nodo->operador);
        dispEstado(nodo->estado);
    }
}

void dispSolucion(tNodo *nodo){
   printf("Profundidad=%d\n",nodo->profundidad);
   printf("Coste=%d\n",nodo->costeCamino);
   dispCamino(nodo);
}


/* Crea el nodo ra�z. */
tNodo *nodoInicial(){
   tNodo *inicial=(tNodo *) malloc(sizeof(tNodo));
   inicial->estado=estadoInicial();
   inicial->padre=NULL;
   inicial->costeCamino=0;
   inicial->profundidad=0;
   return inicial;
}

LISTA expandir(tNodo *nodo){
    unsigned op;
    LISTA sucesores=VACIA;
    tNodo *nuevo=calloc(1,sizeof(tNodo));
    tEstado *s;
    for (op=1; op<=NUM_OPERADORES;op++){
        if (esValido(op,nodo->estado)){
                        //s=(tEstado *)calloc(1,sizeof(tEstado));
            s = aplicaOperador(op,nodo->estado);
            nuevo->estado=s;
            nuevo->padre=nodo;
            nuevo->operador=op;
            nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
            nuevo->profundidad=nodo->profundidad+1;
            nuevo->valHeuristica = heuristica(nuevo->estado);
            InsertarUltimo(&sucesores,  (tNodo *) nuevo, (sizeof (tNodo)));
        }
    }
    return sucesores;
}

int repetido(tNodo* e, LISTA L){
    int es_repe = 0;
    LISTA aux = L;
    tNodo* i = (tNodo*)malloc(sizeof(tNodo));

    while(!esVacia(aux) && !es_repe){
        ExtraerPrimero(aux, i, sizeof(tNodo));
        if(iguales(e->estado, i->estado))
            es_repe = 1;
        aux = aux->next;
    }

    return es_repe;
}

int repetidoA(tNodo* e, LISTA L){
    int es_repe = 0;
    LISTA aux = L;
    tNodo* i = (tNodo*)malloc(sizeof(tNodo));

    while(!esVacia(aux) && !es_repe){
        ExtraerPrimero(aux, i, sizeof(tNodo));
        if(iguales(e->estado, i->estado) && e->valHeuristica + e->profundidad >= i->valHeuristica + e->profundidad)
            es_repe = 1;
        aux = aux->next;
    }

    return es_repe;
}

int busquedaAnc(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){ 
        visitados++;
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        objetivo=testObjetivo(Actual->estado);
        if (!objetivo){
            Sucesores = expandir(Actual);
            Abiertos=Concatenar(Abiertos,Sucesores);
      }
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaProf(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){ 
        visitados++;
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        objetivo=testObjetivo(Actual->estado);
        if (!objetivo){
            Sucesores = expandir(Actual);
            Abiertos=Concatenar(Sucesores,Abiertos);
      }
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaAncRepe(){
    int objetivo=0, visitados=0, repetidos = 0, repetida = 0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Cerrados = VACIA;
    LISTA Sucesores= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){ 
        visitados++;
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        objetivo=testObjetivo(Actual->estado);
        repetida = repetido(Actual, Cerrados);

        if(!repetida && !objetivo){
            Sucesores = expandir(Actual);
            Abiertos=Concatenar(Abiertos,Sucesores);
            InsertarUltimo(&Cerrados, Actual, sizeof(tNodo));
        } 
        else
            repetidos++;       
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    printf("\nRepetidos= %d\n", repetidos);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaProfRepe(){
    int objetivo=0, visitados=0, repetidos = 0, repetida = 0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Cerrados = VACIA;
    LISTA Sucesores= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){ 
        visitados++;
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        objetivo=testObjetivo(Actual->estado);
        repetida = repetido(Actual, Cerrados);

        if(!repetida && !objetivo){
            Sucesores = expandir(Actual);
            Abiertos=Concatenar(Sucesores,Abiertos);
            InsertarUltimo(&Cerrados, Actual, sizeof(tNodo));
        } 
        else
            repetidos++;       
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    printf("\nRepetidos= %d\n", repetidos);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaProfLimit(int limite){
    int objetivo=0, visitados=0, repetidos = 0, repetida = 0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Cerrados = VACIA;
    LISTA Sucesores= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){ 
        visitados++;
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        objetivo=testObjetivo(Actual->estado);
        repetida = repetido(Actual, Cerrados);

        if(!repetida && !objetivo && Actual->profundidad < limite){
            Sucesores = expandir(Actual);
            Abiertos=Concatenar(Sucesores,Abiertos);
            InsertarUltimo(&Cerrados, Actual, sizeof(tNodo));
        } 
        else
            repetidos++;       
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    printf("\nRepetidos= %d\n", repetidos);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaProfIter(int limite){
    int objetivo=0, visitados=0, repetidos = 0, repetida = 0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Cerrados = VACIA;
    LISTA Sucesores= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){ 
        visitados++;
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);

        if(Actual->profundidad == limite + 1)   //Ya hemos recorrido todos los estados que quedaban por encima de la profundidad limite
            limite *= 2;

        objetivo=testObjetivo(Actual->estado);
        repetida = repetido(Actual, Cerrados);

        if(!repetida && !objetivo){
            Sucesores = expandir(Actual);
            if(Actual->profundidad < limite)    //Si hemos llegado a la profundidad límite, concatenamos al final, si no, al principio
                Abiertos=Concatenar(Sucesores,Abiertos);
            else
                Abiertos=Concatenar(Abiertos,Sucesores);
            InsertarUltimo(&Cerrados, Actual, sizeof(tNodo));
        } 
        else
            repetidos++;       
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    printf("\nRepetidos= %d\n", repetidos);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaVoraz(){
    int objetivo=0, visitados=0, repetidos = 0, repetida = 0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Cerrados = VACIA;
    LISTA Sucesores= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){ 
        visitados++;
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        objetivo=testObjetivo(Actual->estado);
        repetida = repetido(Actual, Cerrados);

        if(!repetida && !objetivo){
            Sucesores = expandir(Actual);
            Abiertos=ordenarLista(Abiertos,Sucesores, 0);
            InsertarUltimo(&Cerrados, Actual, sizeof(tNodo));
        } 
        else
            repetidos++;       
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    printf("\nRepetidos= %d\n", repetidos);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaA(){
    int objetivo=0, visitados=0, repetidos = 0, repetida = 0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Cerrados = VACIA;
    LISTA Sucesores= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){ 
        visitados++;
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        objetivo=testObjetivo(Actual->estado);
        repetida = repetidoA(Actual, Cerrados);

        if(!repetida && !objetivo){
            Sucesores = expandir(Actual);
            Abiertos=ordenarLista(Abiertos,Sucesores, 1);
            InsertarUltimo(&Cerrados, Actual, sizeof(tNodo));
        } 
        else
            repetidos++;       
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    printf("\nRepetidos= %d\n", repetidos);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}