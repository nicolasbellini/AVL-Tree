#include "Common.h"
#include "Network.h"
#include "Map.h"
#include "Stack.h"

struct NetworkRepr {
    Map flechas;
    Stack acciones;
};

//La cantidad de elementos de acciones es como minimo la cant de elemtos en flechas y como maximo el doble - 1.
//Invariante de representacion: las ids de accciones deben existir tambien en flechas.
//Acciones contiene ids que funcionan como claves en el map flechas.

//Retorna una network vacia.
Network emptyN() {
    Network net = new NetworkRepr;
    net->acciones = emptyS();
    net->flechas = emptyM();
    return net;
}

//Agrega un elemento a la red, con el identificador id. Precondición:
//el elemento no está en la red aún.
void addN(Network net, Id id) {
    insertM(net->flechas,id,id);
    pushS(net->acciones,id);
}

//Devuelve verdadero si el elemento está en la red.
bool elemN(Network net, Id id) {
    int v;
    return lookupM(net->flechas, id, v);
}

//Propocito: Devuelve el representante del id.
//Precondicion: ID se encuentra en el map.
int lastConnected(Map m, Id id){
    int k = id;
    int v;
    lookupM(m,k,v);
    while(k != v){
        k = v;
        lookupM(m,k,v);
        }
    return k;
}

//Devuelve verdadero si id1 e id2 identifican a
//dos elementos de la red que están conectados, ya sea directa o indirectamente. Precondición: id1 e id2
//identifican a dos elementos de la red.
bool connectedN(Network net, Id id1, Id id2) {
    int a = lastConnected(net->flechas,id1);
    int b = lastConnected(net->flechas,id2);
    return a==b;
}

//Establece una conexión directa entre dos elementos
//de la red. Si los elementos ya están conectados (ya sea directa o indirectamente), esta acción no tiene efecto.
//Precondición: id1 e id2 identifican a dos elementos de la red.
void connectN(Network net, Id id1, Id id2) {
    Map m = net->flechas;
    int a = lastConnected(m,id1);
    int b = lastConnected(m,id2);
    if (!connectedN(net,id1,id2)){
        insertM(m,a,b);
        pushS(net->acciones,a);
    }
}

//Deshace la última acción, que puede consistir en agregar un elemento o en
//conectar dos elementos. Precondición: debe haber habido una última acción.
void undoN(Network net) {
    Map m = net->flechas;
    int k = topS(net->acciones);
    popS(net->acciones);
    int v;
    lookupM(m,k,v);
    if (k==v){
        removeM(m,k);
    }
    else{
        insertM(m,k,k);
    }
}

//Libera toda la memoria usada por la red de elementos.
void destroyN(Network net) {
    destroyM(net->flechas);
    destroyS(net->acciones);
    delete net;
}
