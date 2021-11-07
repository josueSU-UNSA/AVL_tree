#ifndef __AVL_H__
#define __AVL_H__
#include <iostream>
#include <fstream>
#include <list>
using namespace std;
template<typename  T>
class Nodo {
    public:
        T dato;
        int fe;  // factor de equilibrio
        Nodo<T>*   izquierdo;
        Nodo<T>*   derecho;

        Nodo<T>(T dato);
};
template<typename T>
class AVL_Tree {
    private:
        Nodo<T>* raiz;
    public:
        AVL_Tree(){
            raiz=0;
        }
        Nodo<T>* buscar(T dato, Nodo<T>* raiz);
        int   obtenerFE(Nodo<T>* nodo);
        Nodo<T>* rotacionIzquierda(Nodo<T>* nodo);
        Nodo<T>* rotacionDerecha(Nodo<T>* nodo);
        Nodo<T>* rotacionDobleIzquierda(Nodo<T>* nodo);
        Nodo<T>* rotacionDobleDerecha(Nodo<T>* nodo);
        Nodo<T>* insertarNodo(Nodo<T>* nuevo, Nodo<T>* subArbol);
        void  Add(T dato);
        void  inOrden(Nodo<T>* nodo);
        void  preOrden(Nodo<T>* nodo );
        void  postOrden(Nodo<T>* nodo);

        Nodo<T>* obtenerRaiz();
        void elemen(Nodo<T>* p, list<T>&a);
        list<T> elementos();
        void graficar(Nodo<T>* nodo, ofstream &archivo){
            if(!nodo) return;
            if(nodo->izquierdo){
                archivo << nodo->dato << "--" << nodo->izquierdo->dato<< ";\n";
            }
            if(nodo->derecho){
                archivo << nodo->dato << "--" << nodo->derecho->dato << ";\n";
            }
            graficar(nodo->izquierdo, archivo);
            graficar(nodo->derecho, archivo);
        }
        void graficar(){
            if(!this->raiz) return;
            ofstream archivo;
            archivo.open("grafoAVL.dot");
            archivo << "graph A{\n";
            graficar(this->raiz,archivo);
            archivo << "\n}";
            archivo.close();
            system("dot grafoAVL.dot -o grafo.png -Tpng");
            system("grafoAVL.png");
        }

};
template<typename T>
Nodo<T>::Nodo(T dato) {
    this->dato = dato;
    this->fe = 0;
    this->izquierdo = 0;
    this->derecho = 0;
}
template<typename T>
Nodo<T>* AVL_Tree<T>::buscar(T dato, Nodo<T>* raiz) {
    if (raiz == 0) {
        return NULL;
    } else if (raiz->dato == dato) {
        return raiz;
    } else if (raiz->dato < dato) {
        return buscar(dato, raiz->derecho);
    } else if (raiz->dato > dato) {
        return buscar(dato, raiz->izquierdo);
    }
}
template<typename T>
int AVL_Tree<T>::obtenerFE(Nodo<T>* nodo) {
    if (nodo == 0) {
        return -1;
    } else {
        return nodo->fe;
    }
}
template<typename T>
Nodo<T>* AVL_Tree<T>::rotacionIzquierda(Nodo<T>* nodo) {
    Nodo<T>* aux = nodo->izquierdo;
    nodo->izquierdo = aux->derecho;

    aux->derecho = nodo;

    nodo->fe = max(this->obtenerFE(nodo->izquierdo), this->obtenerFE(nodo->derecho)) + 1;
    aux->fe  = max(this->obtenerFE(aux->izquierdo), this->obtenerFE(aux->derecho)) + 1;

    return aux;
}
template<typename T>
Nodo<T>* AVL_Tree<T>::rotacionDerecha(Nodo<T>* nodo) {
    Nodo<T>* aux = nodo->derecho;
    nodo->derecho = aux->izquierdo;

    aux->izquierdo = nodo;

    nodo->fe = max(this->obtenerFE(nodo->izquierdo), this->obtenerFE(nodo->derecho)) + 1;
    aux->fe  = max(this->obtenerFE(aux->izquierdo), this->obtenerFE(aux->derecho)) + 1;

    return aux;
}
template<typename T>
Nodo<T>* AVL_Tree<T>::rotacionDobleIzquierda(Nodo<T>* nodo) {
    Nodo<T>* aux;

    nodo->izquierdo = this->rotacionDerecha(nodo->izquierdo);
    aux = this->rotacionIzquierda(nodo);

    return aux;
}
template<typename T>
Nodo<T>* AVL_Tree<T>::rotacionDobleDerecha(Nodo<T>* nodo) {
    Nodo<T>* aux;

    nodo->derecho = this->rotacionIzquierda(nodo->derecho);
    aux = this->rotacionDerecha(nodo);

    return aux;
}
template<typename T>
Nodo<T>* AVL_Tree<T>::insertarNodo(Nodo<T>* nuevo, Nodo<T>* subArbol) {
    Nodo<T>* nuevoPadre = subArbol;

    if (nuevo->dato < subArbol->dato) {
        if (subArbol->izquierdo == NULL) {
            subArbol->izquierdo = nuevo;
        } else {
            subArbol->izquierdo = this->insertarNodo(nuevo, subArbol->izquierdo);

            int balance = this->obtenerFE(subArbol->izquierdo) - this->obtenerFE(subArbol->derecho);

            if (balance == 2) {
                if (nuevo->dato < subArbol->izquierdo->dato) {
                    nuevoPadre = this->rotacionIzquierda(subArbol);
                } else {
                    nuevoPadre = this->rotacionDobleIzquierda(subArbol);
                }
            }

        }
    } else if (nuevo->dato > subArbol->dato) {
        if (subArbol->derecho == NULL) {
            subArbol->derecho = nuevo;
        } else {
            subArbol->derecho = this->insertarNodo(nuevo, subArbol->derecho);

            int balance = this->obtenerFE(subArbol->derecho) - this->obtenerFE(subArbol->izquierdo);

            if (balance == 2) {
                if (nuevo->dato > subArbol->derecho->dato) {
                    nuevoPadre = this->rotacionDerecha(subArbol);
                } else {
                    nuevoPadre = this->rotacionDobleDerecha(subArbol);
                }
            }
        }

    } /*else {
        cout << "Nodo<T> duplicado!" << endl;

    }*/

    // Actualizando factor de equilibrio
    if ((subArbol->izquierdo == NULL) && (subArbol->derecho != NULL)) {
        subArbol->fe = subArbol->derecho->fe + 1;
    } else if ((subArbol->derecho == NULL) && (subArbol->izquierdo != NULL)) {
        subArbol->fe = subArbol->izquierdo->fe + 1;
    } else {
        subArbol->fe = max(this->obtenerFE(subArbol->izquierdo), this->obtenerFE(subArbol->derecho)) + 1;
    }

    return nuevoPadre;
}
template<typename T>
void AVL_Tree<T>::Add(T dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);

    if (this->raiz == NULL) {
        this->raiz = nuevo;
    } else {
        this->raiz = this->insertarNodo(nuevo, raiz);
    }
}
template<typename T>
void AVL_Tree<T>::inOrden(Nodo<T>* nodo) {
    if (nodo != NULL) {
        this->inOrden(nodo->izquierdo);
        cout << nodo->dato << ", ";
        this->inOrden(nodo->derecho);
    }
}
template<typename T>
void AVL_Tree<T>::preOrden(Nodo<T>* nodo) {
    if (nodo != NULL) {
        cout << nodo->dato << ", ";
        this->preOrden(nodo->izquierdo);
        this->preOrden(nodo->derecho);
    }
}
template<typename T>
void AVL_Tree<T>::postOrden(Nodo<T>* nodo) {
    if (nodo!= NULL) {
        this->postOrden(nodo->izquierdo);
        this->postOrden(nodo->derecho);
        cout << nodo->dato << ", ";
    }
}
template<typename T>
Nodo<T>* AVL_Tree<T>::obtenerRaiz() {
    return this->raiz;
}

template<typename T>
void AVL_Tree<T>::elemen(Nodo<T>* p, list<T>&a) {
    if (p!= 0) {
        this->elemen(p->izquierdo,a);
        a.push_back(p->dato);
        this->elemen(p->derecho,a);
    }
}

template<typename T>
list<T> AVL_Tree<T>::elementos(){
    list<T> a;
    if(this->raiz != 0){
        elemen(raiz, a);
    }
    return a;
}
#endif