#ifndef ORDENACION_H
#define ORDENACION_H

class Ordenacion
{
    public:  
    Ordenacion(int *a,int b); 
    ~Ordenacion(); 
    
    void insertion (int prim,int ult);
    void insertion_S (int prim,int ult);         //S-simplificado
    void selection (int prim,int ult);
    void selection_M (int prim,int ult);         //M-modificado para no intercambiar los iguales
    void brickSort (int prim,int ult);
    void shakerSort (int prim,int ult);    
    void bubble (int prim,int ult); 
    void shellSort (int prim, int ult);       
    void shellSort_S (int prim, int ult);       //S-simplificado    
    void mergeSort (int prim, int ult);
    void mergeSort_M (int prim, int ult);       //M-modificado para usar otro ordenamiento cuando es pequenno
    void quickSort (int prim, int ult);
    void quickSort_C (int prim, int ult);       //C-CodeLearn
    void quickSort_M (int prim, int ult);       //M-modificado para usar otro ordenamiento cuando es pequenno
    void binSort (int prim, int ult);
    void radix (int prim, int ult);
    
    private:
    int const n;
    int *arr;
    int *aux;    
    int posMax(int i,int j);
    int posMin(int i,int j);   
    void combinar(int p1, int u1, int p2, int u2);
    int pivote_AM (int prim, int ult);                            //A-aleatorio M-modificado para salir si esta ordenado
    void pivote_AM3 (int prim, int ult, int *pd, int *pi);         //A-aleatorio M-modificado para salir si esta ordenado 3-divide el arreglo en 3 menores-iguales-mayores
    int pivote_P (int prim, int ult);                             //P-primer elemento
    
};

#endif // ORDENACION_H