#include "AVLTree.h"
#include<iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include "AVL.h"
using namespace std;
void test2(int n)
{ 

    
}
int main(){
    srand (10); 
    //const int N = 10;
    AVLTree<int>test;
    
    /*
    AVL_Tree<int>avlPreHecho;//la libreria AVL.h
    

    int ij = 100;
    /*while(i<1000000)B
    {
       test2(i);
       i = i*10;   
    }
    for(int i=0;i<ij;i++)//del 0 al 999
      { 
        //cout<<i<<endl;
        avlPreHecho.Add(i);
        test.Add(i);
      }
    */
        
    test.Add(500);
    test.Add(30);
    test.Add(650);
    test.Add(100);
    test.Add(550);
    test.Add(800);
    test.Add(700);
    test.Add(900);
    test.Add(680);
    test.graficar();
    //test.print();
    
    
    
    
    system("pause");
    return 0;
}
