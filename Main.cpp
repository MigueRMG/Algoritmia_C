#include <iostream>
#include <vector>
#include <string>
#include "Ordenacion.h"

using namespace std;

int main(int argc, char const *argv[])
{
   
   int n = 40; 
   int *arr = new int[n]{4,2,4,8,2,3,5,7,9,0,4,2,4,8,2,3,5,7,9,0,4,2,4,8,2,3,5,7,9,0,4,2,4,8,2,3,5,7,9,0};
   Ordenacion ordenar(arr,n);
   ordenar.quickSort_M(0,n-1);   

    for (int i = 0; i < n; i++)
    {
        cout<<arr[i];
    }  
    cout<<endl;

    delete[] arr;
   
    return 0;
}
