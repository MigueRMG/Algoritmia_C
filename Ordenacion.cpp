/*Notas
-Los algoritmos de complejidad cuadrática, son más eficientes que los de complejidad nlogn para valores 
pequeños de n.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Ordenacion.h"

using namespace std;



Ordenacion::Ordenacion(int *a, int b): n(b), arr(a)
{     
    aux = new int[b];
}

Ordenacion::~Ordenacion()
{    
    delete[] aux;  
}

                    //Funciones utilizadas en los algoritmos de ordenacion

//param: ordenar=arreglo a ordenar, i=posicion del 1er elemento, j=posicion del ultimo elemento
//return: posicion del elemento maximo, en caso de repetirse devuelve el ultimo         
int Ordenacion::posMax(int i,int j)
{
    int posMax=i;

    for (int k = i; k <= j; k++)
    {
        if(arr[k]>arr[posMax])
        posMax=k;    
    }
    return posMax;  
}

//param: ordenar=arreglo a ordenar, i=posicion del 1er elemento, j=posicion del ultimo elemento
//return: posicion del elemento minimo, en caso de repetirse devuelve el ultimo         
int Ordenacion::posMin(int i,int j)
{
    int posMin=i;

    for (int k = i; k <= j; k++)
    {
        if(arr[k]<arr[posMin])
        posMin=k;    
    }
    return posMin;  
}


                            //ORDENACIÓN POR INSERCIÓN  
/*
-Descripcion: El método de Inserción realiza n–1 iteraciones (empieza en prim +1) sobre el vector, 
dejando ordenado el subvector ordenar[prim..i]. La forma de hacerlo es colocando en cada 
iteración el elemento x (ordenar[i]) en su sitio correcto, aprovechando el hecho de que 
el subvector ordenar[prim..i–1] ya ha sido previamente ordenado. Para esto recorre el 
vector hacia atras hasta encontrar q x sea mayor q el elemento iterado en el subvertor 
(o hasta q la posicion sea < prim) y ahi guardando x. En cada iteracion hacia atras q no
se cumplan las condiciones anteriores corre el valor del elemento de esa iteracion un 
lugar adelante.

-Uso: Es recomendable cuando el arreglo esta practicamente ordenado y es pequenno

-Complejidad: Θ(n^2) en el medio y peor caso, Θ(n) mejor caso ya q no entra al bucle interno*/

void Ordenacion::insertion ( int prim,int ult)
{
    int i;  
    int j;
    int temp;     //elemento a ordenar 

    for ( i = prim+1; i <= ult; i++)        
    {
        temp=arr[i];
        j=i-1;

        while (j>=prim && temp<arr[j])
        {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = temp;        
    }  
}

//Simplificado
void Ordenacion::insertion_S ( int prim,int ult)       
{
    int i;  
    int j;   
    
    for ( i = prim+1; i <= ult; i++)      
    {
        j=i-1;

        while (j>=prim && arr[j+1]<arr[j])
        {
            swap(arr[j+1],arr[j]);                       
            j--;
        }           
    }      
}

                            //ORDENACIÓN POR SELECCIÓN
/*
-Descripcion: En cada paso (i=prim...ult–1) este método busca el mínimo elemento del subvector
a[i..ult] y lo intercambia con el elemento en la posición i. 

-Uso: Peor algoritmo en cuanto a tiempo. Su ventaja es q posee un numero minimo de intercambios,
es recomendable su uso cuando el proceso de intercambio es muy costoso.

-Complejidad:Θ(n^2) en todos los casos*/

void Ordenacion::selection(int prim,int ult)
{
    for (int i = prim; i < ult; i++)
    {
        swap(arr[i],arr[posMin(i,ult)]);
    }    
}

//modificado para no intercambiar los iguales
void Ordenacion::selection_M(int prim,int ult)
{
    int minTemp;
    for (int i = prim; i < ult; i++)
    {
        minTemp = posMin(i,ult);
        if (arr[i] != arr[minTemp])
        {
            swap(arr[i],arr[minTemp]);
        }        
    }    
}

                            //Ordenación por Ladrillos (Bricksort)
/*
-Descripcion: Realiza el proceso contrario a seleccion.

-Uso: igual q seleccion

-Complejidad: Θ(n^2) en todos los casos
*/

void Ordenacion::brickSort(int prim,int ult)
{
    for (int i = ult; i > prim; i--)
    {
        swap(arr[i],arr[posMax(prim,i)]);
    }    
}


                            //Ordenación por Sacudidas (Shakersort)
/*
-Descripcion: union entre seleccion y bricksort

-Uso: igual q los anteriores

-Complejidad: Θ(n^2) en todos los casos
*/

void Ordenacion::shakerSort(int prim,int ult)
{
    int der = prim;
    int izq = ult;
    while (der < izq)
    {
        swap(arr[der],arr[posMin(der,izq)]);
        der++;
        if (der < izq)
        {
            swap(arr[izq],arr[posMax(der,izq)]);
            izq--;
        }              
    }   
}

                            //ORDENACIÓN BURBUJA
/*
-Descripcion: Este método de ordenación consiste en ir llevando el menor elemento hacia la posicion i 
recorriendo el vector desde ult hasta i+1 y intercambiando elementos adyacentes en cada 
iteracion j siempre q el ordenar[j-1] > ordenar[j]

-Uso: no lo uses.

-Complejidad: Θ(n^2) en el medio y peor caso, Θ(n) mejor caso, pero aunque tenga la misma complejidad
q insercion en el mejor caso, es peor q dicho ya q necesita hacer dos pasadas mientras q insercion
solo una */

void Ordenacion::bubble(int prim,int ult)
{
    for (int i = prim; i < ult; i++)
    {
        bool intercambia = false;
        for (int j = ult; j > i; j--)
        {
            if (arr[j-1] > arr[j]){
                swap(arr[j-1],arr[j]);
                intercambia = true;
            }                        
        }

        if (!intercambia)
        break;                
    }   
}

                         //ORDENACIÓN POR INCREMENTOS (SHELLSORT)
/*
-Descripcion: El método de Incrementos es una extensión muy simple y eficiente del método de Inserción, 
la potencia de este método consiste en conseguir un número de intercambios mucho menor que con la 
Inserción clásica. El algoritmo consiste dividir el vector arr en h subvectores: arr[k], arr[k+h], arr[k+2h], arr[k+3h], ...
y ordenar por inserción cada uno de esos subvectores (k=1,2,...,h–1), esto va a ir sucediendo para la
secuencia de h escogida hasta q h=1, entonces se realiza una insercion clasica ya q en este momento los 
elementos estan mas cerca de su posicion ordenada.

-Uso: Funciona mejor q insercion en el caso medio y peor, recomendable para arreglos no muy largos.

-Complejidad: Su complejidad es difícil de calcular y depende mucho de la secuencia de incrementos 
que utilice. En el caso de esta secuencia(una de las mejores) peor caso es Θ(n^(3/2)), mejor caso es
Θ(nlog^3n)*/

//simplificado
void Ordenacion::shellSort_S(int prim, int ult)
{
    int N = (ult-prim+1);    //numero de elementos
    int h =1;                //cant de subvectores a ordenar
    int i;
    int j;       

    while (h < N)            //construir secuencia h = ..., 1093, 364, 121, 40, 13, 4, 1
    {
        h = 3*h+1;
    }

    while (h > 1)
    {
        h = h/3;
        for ( i = h; i < N; i++)        
        {                       
            j=i;
            while (j>=h && arr[j+prim]<arr[j-h+prim])
            {
                swap(arr[j+prim],arr[j-h+prim]);                                          
                j-=h;       
                       
            }                                      
        }          
    }  
} 

void Ordenacion::shellSort(int prim, int ult)
{
    int N = (ult-prim+1);    //numero de elementos
    int h =1;                //cant de subvectores a ordenar
    int temp;
    int i;
    int j;    

    while (h < N)            //construir secuencia
    {
        h = 3*h+1;
    }

    while (h > 1)
    {
        h = h/3;
        for ( i = h; i < N; i++)        
        {
           temp = arr[i+prim];
           j=i;
            while (j>=h && temp<arr[j-h+prim])
            {
                arr[j+prim] = arr[j-h+prim];                
                j-=h;                
            }
            arr[j+prim] = temp;
        }          
    }      
} 

                            //ORDENACIÓN MEZCLA (MERGESORT)
/*
-Descripcion: está basado en la técnica de Divide y Vencerás, su estrategia consiste en ir dividiendo 
el vector a la mitad mediante llamadas recursivas hasta q los vectores resultantes tengan 1 elementos 
y posteriormente combinandolos de forma ordenada.

-Uso: es el algorimo  seleccionar cuando se requiere estabilidad, cuando se ordenan linkedList y 
cuando el acceso aleatorio es mas costoso q acceso secuencial(ejemplo ordenamiento externo).

-Complejidad:Θ(nlogn) en cualquiera de los casos (peor, mejor o medio). Sin embargo tiene una complejidad 
espacial en cuanto a memoria, mayor que los demás (del orden de n)*/



void Ordenacion::mergeSort (int prim, int ult)
{
    if (prim<ult)
    {
       int mitad = (prim + ult) / 2;
       mergeSort(prim,mitad);
       mergeSort(mitad+1,ult);
       combinar(prim,mitad,mitad+1,ult);
    }  
}

//modificado para usar otro ordenamiento cuando es pequenno
void Ordenacion::mergeSort_M (int prim, int ult)
{
    int peq = 5;
    if (prim<ult)
    {
        if (ult-prim <= peq)
        {
            insertion_S(prim,ult);
        }
        else
        {
            int mitad = (prim + ult) / 2;
            mergeSort_M(prim,mitad);
            mergeSort_M(mitad+1,ult);
            combinar(prim,mitad,mitad+1,ult);
        }
    }  
}

/*combina los subvectores a[p1...u1] y a[p2...u2] de una forma ordenada auxiliandose con b, sabiendo q
dichos subvectores ya estan ordenados*/
void Ordenacion::combinar(int p1, int u1, int p2, int u2)
{    
    int i = p1;
    int prim = p1;

    while (p1 <= u1 || p2 <= u2)
    {
        if (p1 > u1)
        {
            while (p2<=u2)
            {
            aux[i]=arr[p2];
            i++;
            p2++;
            }       
        }
        else if (p2 > u2)
        {
            while (p1<=u1)
            {
            aux[i]=arr[p1];
            i++;
            p1++;
            }      
        }
        else
        {
            if (arr[p1]<arr[p2])
            {
                aux[i]=arr[p1];
                i++;
                p1++;
            }
            else
            {
                aux[i]=arr[p2];
                i++;
                p2++;
            }
        }                    
    }

    for (int k = prim; k <= u2; k++)
    {
        arr[k]=aux[k];
    }
    
}

                        //ORDENACIÓN RÁPIDA DE HOARE (QUICKSORT)
/*
-Descripcion: está basado en la técnica de Divide y Vencerás, el vector a ordenar arr[prim..ult] es dividido
en dos subvectores no vacíos arr[prim..p–1] y a[p+1..ult], tal que todos los elementos del primero son 
menores que los del segundo. El elemento de índice p se denomina pivote y se calcula como parte del 
procedimiento de partición.A continuación, se repite el proceso recursivamente en los subvectores q van
surgiendo. El algoritmo puede variar en relacion de como se asigna el pivote: aleatorio, el primer 
elemento, la mediana entre 3 elementos, etc.

-Uso: Cuando no se requiere un algoritmo de ordenacion estable, esta es la mejor opcion. es probablemente
el algoritmo de ordenación más utilizado, pues es muy fácil de implementar, trabaja bien en casi todas 
las situaciones y consume en general menos recursos (memoria y tiempo) que otros métodos.

-Complejidad: rompe la filosofía de caso mejor, peor y medio de los algoritmos clásicos de ordenación, 
pues aquí tales casos no dependen de la ordenación inicial del vector, sino de la elección del pivote.
En el caso mejor y medio es Θ(nlogn), en el peor Θ(n^2)
*/

void Ordenacion::quickSort (int prim, int ult)
{    
    int p;
    if (prim < ult)
    {
        p = pivote_AM(prim,ult);        
            quickSort(prim,p-1);
            quickSort(p+1,ult);                      
    }
};

/*modificado para usar otro ordenamiento cuando es pequenno, en caso de ya estar ordenado(-1) para la 
parar recursividad, divide el arr en 3 menores-iguales-mayores q el pivote*/
void Ordenacion::quickSort_M (int prim, int ult)
{    
    int pd;                  //pivote limite derecha
    int pi;                  //pivote limite izquierda
    int peq = 5;
    if (prim < ult)
    {
        if (ult-prim <= peq)
        {
            insertion_S(prim,ult);
        }
        else
        {
            pivote_AM3(prim,ult,&pd,&pi);
            if (pd != -1 && pi != -1)
            {
                quickSort_M(prim,pd-1);
                quickSort_M(pi+1,ult);
            }    
        }                 
    }
};

//version puesta en CodeLearn
void Ordenacion::quickSort_C (int left, int right)
{
    int l = left;
    int r = right - 1;
    int size = right - left;
    if(size > 1) 
    {
        int pivot = arr[rand()%size + l];
        while(l < r) 
        {
            while(arr[r] > pivot && r > l) 
            {
                r--;
            }
            while(arr[l] < pivot && l <= r) 
            {
                l++;
            }
            if(l < r) 
            {
                swap(arr[l], arr[r]);
                l++;
            }
        } 
        quickSort_C(left, l);
        quickSort_C(r, right);
    }    
}

 /*asigna un pivote aleatorio, mueve todos los menores q el a la izq y los mayores a la derecha, devuelve
 la posicion del pivote, en caso de ya estar ordenado devuelve -1*/
int Ordenacion::pivote_AM (int prim, int ult)
{
    srand(time(0));
    int p = arr[rand() % (ult-prim) + prim]; // pivote aleatorio

    int izq = prim;
    int der = ult;
    int result;
    int posP;                 //posicion del pivote a la izquierda, para cambiarlo al final a su posicion correcta
    bool ordenado = true;     //para verificar si esta ordenado
    
    while (izq < der)
    {
        while (arr[izq] <= p && izq < ult)
        {
            if(arr[izq] == p)       //guarda la posicion del pivote
            {
                posP = izq;                            
            }
            if(izq != prim && arr[izq-1] > arr[izq] && ordenado){ //verifica si la izquierda esta ordenada
                ordenado = false;
            }
            izq++;
        }

        while (arr[der] > p)
        {
            if(der != ult && arr[der+1] < arr[der] && ordenado){ //verifica si la derecha esta ordenada
                ordenado = false;
            }            
            der--;
        }

        if (izq < der)
        {
            swap(arr[izq],arr[der]);
        }      
    }

    if (arr[der] != p)             //poner el pivote en su posicion correcta, en caso de ya estar ahi o ser igual en valor no hace falta el intercambio
    {
        swap(arr[posP],arr[der]);
    }

    if (ordenado)
    {
        result = -1;
    }
    else
    {
        result = der;
    }  

    return result;     
}

 /*asigna un pivote aleatorio, mueve todos los menores q el a la izq, iguales al medio y los mayores a 
 la derecha, devuelve por referencia pd(pivote derecha) y pi(pivote izquierda), en caso de ya estar 
 ordenado devuelve -1*/
void Ordenacion::pivote_AM3 (int prim, int ult, int *pd, int *pi)
{
    srand(time(0));
    int p = arr[rand() % (ult-prim) + prim]; // pivote aleatorio

    int izq = prim;
    int der = ult;
    int result;
    int posP;                 //posicion del pivote a la izquierda, para cambiarlo al final a su posicion correcta
    bool ordenado = true;     //para verificar si esta ordenado
    
    while (izq < der)
    {
        while (arr[izq] <= p && izq < ult)
        {
            if(arr[izq] == p)       //guarda la posicion del pivote
            {
                posP = izq;                            
            }
            if(izq != prim && arr[izq-1] > arr[izq] && ordenado){ //verifica si la izquierda esta ordenada
                ordenado = false;
            }
            izq++;
        }

        while (arr[der] > p)
        {
            if(der != ult && arr[der+1] < arr[der] && ordenado){ //verifica si la derecha esta ordenada
                ordenado = false;
            }            
            der--;
        }

        if (izq < der)
        {
            swap(arr[izq],arr[der]);
        }      
    }

    if (arr[der] != p)             //poner el pivote en su posicion correcta, en caso de ya estar ahi o ser igual en valor no hace falta el intercambio
    {
        swap(arr[posP],arr[der]);
    }

    if (ordenado)
    {
        result = -1;
    }
    else
    {
        result = der;
    }       
}

/*asigna un pivote 1er elemeno*/
int Ordenacion::pivote_P (int prim, int ult)
{
    int p = arr[prim];
    int i =prim;
    int l =ult+1;

    while (arr[i] <= p && i < ult)
    {
        i++;
    }
    while (arr[l] > p)
    {
        l--;
    }
    
    while (i < l)
    {
        swap(arr[i],arr[l]);
        while (arr[i] <= p)
        {
            i++;
        }
        while (arr[l] > p)
        {
            l--;
        }       
    }
    swap(arr[prim],arr[l]);
    
    return l;
}

                            //Ordenación por Cubetas (Binsort)
/*
-Descripcion: en cada iteración se sitúa un elemento en su posición definitiva.

-Uso: los datos a ordenar son números naturales, todos distintos y comprendidos en el intervalo [1,n].

-Complejidad: Θ(n)
*/

void Ordenacion::binSort (int prim, int ult){
    for (int i = prim; i <= ult; i++)
    {
        while (arr[i] != i)
        {
            swap(arr[i],arr[arr[i]]);
        }        
    }  
}

                             //Ordenación por Residuos (Radix)
/*
-Descripcion: en cada iteración se sitúa un elemento en su posición definitiva.

-Uso: los datos a ordenar son números naturales, todos distintos y comprendidos en el intervalo [1,n].

-Complejidad: Θ(n)
*/

void Ordenacion::radix (int prim, int ult){
    string s = to_string(3);

}















