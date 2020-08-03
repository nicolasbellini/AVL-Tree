#include "Common.h"
#include "Map.h"

typedef int Priority;

//Invariante de representacion: Debe cumplir con las invariantes de un treap.
//(Los nodos deben ser ordenador por Clave y prioridad).


Priority randomPriority() {
    return rand();
}

struct MapRepr {
    Node* root;
    int mapSize;

};

struct Node {
    Key k;
    Value v;
    Priority p;
    Node* lb;
    Node* rb;
};

//Crea un map vacio.
Map emptyM() {
    Map m = new MapRepr;
    m->mapSize = 0;
    m->root = NULL;
    return m;
}

//Retorna la cantidad de elementos.
int sizeM(Map m) {
    return m->mapSize;
}

//Retorna true si el elementos esta en el map y lo guarda en v.
bool lookupM(Map m, Key k, Value& v) {
   Node* n = m->root;
   while (n != NULL && n->k != k){
        if (n->k < k){
            n = n->rb;
        }
        else {
            n = n->lb;
        }
   }
   if (n != NULL){
    v = n->v;
    return true;
   }
   return false;
}


//Crea un nuevo nodo.
Node* newNode(Key k, Value v){
    Node* n = new Node;
    n->k = k;
    n->v = v;
    n->p = randomPriority();
    n->lb = NULL;
    n->rb = NULL;
    return n;
}

//Rota los elementos de forma que cumplan con BST. Precondicion: padre y su hijo derecho no es NULL.
Node* rotateRB(Node* padre){
    if (padre->rb->p > padre->p){
        Node* nuevoPadre = padre->rb;
        Node* lbHijo = nuevoPadre->lb;

        nuevoPadre->lb = padre;
        padre->rb = lbHijo;
        return nuevoPadre;
    }
    return padre;

}

//Rota los elementos de forma que cumplan con BST. Precondicion: padre y su hijo izquierdo no es NULL.
Node* rotateLB(Node* padre){
    if(padre->lb->p > padre->p){
        Node* nuevoPadre = padre->lb;
        Node* rbHijo = nuevoPadre->rb;

        nuevoPadre->rb = padre;
        padre->lb = rbHijo;

        return nuevoPadre;
    }
    return padre;
}

//Si el elemento existe, actualiza su valor. Si no, agrega por bst y luego ordena por prioridad.
Node* insertN(Node* n, Key k, Value v, bool& b){
    Node* aux = n;
    if (aux == NULL){
        aux = new Node;
        aux->k = k;
        aux->v = v;
        aux->p = randomPriority();
        aux->lb = NULL;
        aux->rb = NULL;
        b = true;
        return aux;
    } else if(aux->k < k){
            aux->rb = insertN(n->rb,k,v,b);
            aux = rotateRB(aux);
        }
        else if(aux->k > k){
            n->lb = insertN(aux->lb, k, v,b);
            aux = rotateLB(aux);
        }
        else{
            aux->v = v;
            b = false;
        }
    return aux;
}

//Agrega o actualiza un elemento en el mapa.
void insertM(Map m, Key k, Value v) {
        bool b;
        m->root = insertN(m->root, k, v,b);
        if (b){
            m->mapSize++;
        }
}

/*Node* deleteAndReturnMin(Node* n,Node*& minN){
    Node* aux = n;
    if (aux->lb != NULL){
        aux->lb = deleteAndReturnMin(aux->lb,minN);
    }
    else{
        minN = aux;
        return aux->rb;
    }
}*/

/*Node* removeN(Node* n, Key k){
    Node* aux = n;
    if (aux != NULL){
        if(aux->k > k){
            aux->rb = removeN(aux->rb,k);
        }

        else {
            aux->lb = removeN(aux->lb,k);
        }
    }
    if (aux->rb == NULL){
        Node* toDel = aux;
        aux = aux->lb;
        delete toDel;
        aux = aux->lb;
    }
    Node* minN;
    Node* sinMin = deleteAndReturnMin(aux->rb,&minN);
    minN->lb = aux->lb;
    minN->rb = sinMin;
    minN->p = aux->p;
    delete aux;
    return minN;

}*/

/*Node* buscarNodo(Node* raiz, Key k){
    Node* n = raiz;
    if (raiz != NULL){
        if (n->k > k){
        n = buscarNodo(n->rb,k);
        }
        else {
        n = buscarNodo(n->lb,k);
        }
        }
    return n;
}

Node* obtenerMaximoMinimo(Node* padre,Node* hijo){
    if (padre->rb == NULL){
        return padre->lb;
    }
    Node* p = padre->rb;
    Node* h = p->lb;
    if (h == NULL){
        padre->rb = p->rb;
        return p;
    }
    while (h->lb != NULL){
        p = h;
        h = h->lb;
    }
    p->lb = h->rb;
    return h;

}

void intercambiarContenido(Node* x, Node* y){
    x->k = y->k;
    x->p = y->p;
    delete y;
}

Node* removeN(Node* n, Key k){
    Node* x = buscarNodo(n, k);
    Node* m = obtenerMaximoMinimo(x,x->rb);
    intercambiarContenido(x, m);
    return x;
}
*/

//Precondicion: Node n no debe ser NULL.
//Remueve el minimo y reordena el mapa, guarda el valor del minimo y su clave en k y v.
Node* removeMin(Node* n,Key& k,Value& v){
    if (n->lb == NULL){
        k = n->k;
        v = n->v;
        Node* temp = n->rb;
        delete n;
        return temp;
    }
    else {
        n->lb = removeMin(n->lb,k,v);
        return n;
    }
}

//Precondicion: n no debe ser NULL.
//Remueve el nodo raiz y devuelve un nodo que cumpla con bst.
Node* removeRoot(Node* n){
    if (n->rb == NULL){
        Node* izq= n->lb;
        delete n;
        return izq;
    }
    else {
        Value v;
        Key k;
        n->rb = removeMin(n->rb,k,v);
        n->k = k;
        n->v = v;
        return n;
    }
}

//Elimina el nodo con clave K. Actualiza la cantidad de nodos.
//Retorna el un arbol con el nodo eliminado.
Node* removeN(Node* n, Key k,int& ms){
    if (n==NULL){
        return NULL;
    } else if (k > n->k){
        n->rb = removeN(n->rb,k,ms);
        return n;
    } else if(k < n->k){
        n->lb = removeN(n->lb,k,ms);
        return n;
    } else{
        ms--;
        return removeRoot(n);
    }
}

//Elimina el nodo con clave K.
void removeM(Map m, Key k) {
    m->root = removeN(m->root, k,m->mapSize);
}

//Destruye todos los nodos a partir de si mismo, incluyendose.
void destroyNodes(Node* n){
    if(n != NULL){
        destroyNodes(n->lb);
        destroyNodes(n->rb);
        delete n;
    }
}

//Destruye un map.
void destroyM(Map m) {
    destroyNodes(m->root);
    delete m;

}

