#include "Common.h"
#include "Stack.h"

struct StackRepr {
    int maxPush;
    int nextPush;
    int* elems;

};

//Crea un stack vacio.
Stack emptyS(){
    Stack s = new StackRepr;
    s->nextPush = 0;
    s->elems = new int[10];
    s->maxPush = 10;
    return s;
}

//Devuelve el tamaño del stack.
int sizeS(Stack s) {
    return s->nextPush;
}

//Propocito: borrar el stack.
void destroyS(Stack s) {
    delete []s->elems;
    delete s;
}

//Propocito: crea un nuevo array con el doble de capacidad.
// y pasa todos los elementos del viejo al nuevo.
//Precondicion: el Stack s debe tener elementos hasta su maxPush.
void expandArray(Stack s){
        int oldMax = s->maxPush;
        s->maxPush = s->maxPush * 2;
        int* newArray = new int[s->maxPush];
        for (int i = 0; i< oldMax; i++){
            newArray[i] = s->elems[i];
        }
        delete []s->elems;
        s->elems = newArray;
}

// Si el array esta lleno crea uno nuevo con el doble de capacidad y luego asigna el nuevo elemento.
void pushS(Stack s, int x) {
    if (s->nextPush >= s->maxPush) {
       expandArray(s);
    }
    s->elems[s->nextPush] = x;
    s->nextPush++;
}

// Desapila el tope de la pila. Precondición: la pila no está vacía.
int topS(Stack s) {
    return s->elems[s->nextPush - 1];
}

//Desapila el topo de la pila.
void popS(Stack s) {
    s->nextPush--;
}


