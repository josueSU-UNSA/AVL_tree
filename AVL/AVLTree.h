#include "Node.h"
#include <iostream>
#include <fstream>
using namespace std;
template<class T>
class AVLTree{
    private:
        Node<T>*m_pRoot;
        void Add(Node<T>*&pAux,T value,bool &val){

            if(!pAux){
                pAux=new Node<T>(value);
                return;
            }
            else if(pAux->value==value){
                val=false;
                return;
            }
            Add(pAux->m_pSig[pAux->value<value],value,val);

            //Esta condicional la usamos para detener la recursion de pila y no modificar los FE de aquellos nodos que no participan en las rotaciones

            if(val){
                (pAux->value<value)?pAux->FE++:pAux->FE--;
                if(!pAux->FE)val=false;
            }

            //Aqui acaba las modificaciones de los FE una vez insertado
            //--------------------------------------------------------------

            //Desde aqui se realiza las rotaciones a partir de los FE
            if(pAux->FE==2){
                if(pAux->m_pSig[1]->FE==-1)this->RDI(pAux);
                else this->RDD(pAux);
                val=false;
            }
            else if(pAux->FE==-2){
                if(pAux->m_pSig[0]->FE==1)this->RID(pAux);
                else this->RII(pAux);
                val=false;
            }
            //Aqui acaba las rotaciones de los FE
        }

        void print(Node<T>*pAux){
            if(!pAux)return;
            if(pAux->m_pSig[0])cout<<pAux->value<<" FE: "<<pAux->FE<<" -> "<<pAux->m_pSig[0]->value<<" FE: "<<pAux->m_pSig[0]->FE<<endl;
            if(pAux->m_pSig[1])cout<<pAux->value<<" FE: "<<pAux->FE<<" -> "<<pAux->m_pSig[1]->value<<" FE: "<<pAux->m_pSig[1]->FE<<endl;
            print(pAux->m_pSig[0]);
            print(pAux->m_pSig[1]);
        }

        void RDI(Node<T>*&p){
            Node<T>*q=p->m_pSig[1];
            Node<T>*r=q->m_pSig[0];
            p->m_pSig[1]=r->m_pSig[0];
            q->m_pSig[0]=r->m_pSig[1];
            r->m_pSig[0]=p;
            r->m_pSig[1]=q;

            if(!r->FE)p->FE=q->FE=0;//cuando p no tiene un hijo izq

            else {//quiere decir que p tiene un hijo izq y q tiene un hijo derecho

                if(r->FE==-1){//si el hijo de r ess izq
                    //existe un hijo derecho para q
                    q->FE=1;
                    r->FE=0;
                    p->FE=0;
                }
                else{//cuando el FE es 1
                    //existe un hijo derecho para q
                    q->FE=0;
                    r->FE=0;
                    p->FE=-1;
                }

            }

            p=r;//coloca el r como la punta del triangulo

        }

        void RID(Node<T>*&p){
            Node<T>*q=p->m_pSig[0];
            Node<T>*r=q->m_pSig[1];
            p->m_pSig[0]=r->m_pSig[1];
            q->m_pSig[1]=r->m_pSig[0];
            r->m_pSig[1]=p;
            r->m_pSig[0]=q;
            
            //no tiene ningun hijo el r
            if(!r->FE)p->FE=q->FE=0;

            else{//p tiene un hijo derecho y q tiene un hijo izq
                if(r->FE==-1){//si el r tiene un hijo izq
                    p->FE=1;
                    q->FE=0;
                    r->FE=0;
                }
                else{//si el FE de r es 1
                    p->FE=0;
                    q->FE=-1;
                    r->FE=0;
                }
            }

            p=r;//colocamos el r como punta del triangulo provocado por la rotacion
        }

        void RDD(Node<T>*&p){
            Node<T>*q=p->m_pSig[1];
            p->m_pSig[1]=q->m_pSig[0];
            q->m_pSig[0]=p;

            //entara a esta 1ra condiciona cuando "q" no tenga un hijo izq es decir "p" no tiene un hijo izq  y mucho menos el "r" q es el posterior "q" , se coloca p xq la rotacion ya esta hecha y el hijo izq de q se traslado hacia esta parte
            if(!p->m_pSig[1])q->FE=p->FE=0;
            else{//quiere decir q "p" tiene un hijo izq y "q" un hijo izq 
                p->FE=0;
                q->FE=0;
            }

            p=q;//"q" asume la punta del triangulo

        }

        void RII(Node<T>*&p){
            Node<T>*q=p->m_pSig[0];
            p->m_pSig[0]=q->m_pSig[1];
            q->m_pSig[1]=p;

            //esto pasa cuando "q" no tiene  un hijo dcho y "p" no tiene un hijo dcho
            if(!p->m_pSig[0])q->FE=p->FE=0;
            else{//si "q" tiene un hijo dcho antes de la rotacion quiere decir q "p" tiene un hijo dcho
                q->FE=0;
                p->FE=0;
            }

            p=q;
        }



        void graficar(Node<T>* nodo, ofstream &archivo){
            if(!nodo) return;
            if(nodo->m_pSig[0]){
                archivo << nodo->value << "--" << nodo->m_pSig[0]->value << ";\n";
            }
            if(nodo->m_pSig[1]){
                archivo << nodo->value << "--" << nodo->m_pSig[1]->value << ";\n";
            }
            graficar(nodo->m_pSig[0], archivo);
            graficar(nodo->m_pSig[1], archivo);
        }

    public:
        AVLTree(){
            this->m_pRoot=0;
        }
        void Add(T value){
            bool val=true;
            this->Add(this->m_pRoot,value,val);
        }
        void print(){
            this->print(this->m_pRoot);
        }
        void graficar(){
            if(!this->m_pRoot) return;
            ofstream archivo;
            archivo.open("grafo.dot");
            archivo << "graph A{\n";
            graficar(this->m_pRoot,archivo);
            archivo << "\n}";
            archivo.close();
            system("dot grafo.dot -o grafo.png -Tpng");
            system("grafo.png");
        }

};