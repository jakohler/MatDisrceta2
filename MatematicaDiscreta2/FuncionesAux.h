#ifndef _FUNCIONESAUX
#define _FUNCIONESAUX

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t u32;

//cuenta la cantidad de colores
u32 NumColores(u32* Coloreo, u32 n);

//libera memoria de un arreglo multidimensional
void FreeAux(u32** key_aux, u32 n);

//Ordena de mayor a menor la primera fila 
int ComSortPF(const void *a, const void *b);

//Ordena de mayor a menor la segunda fila 
int ComSortPS(const void *a, const void *b);

//Comprueba que el coloreo sea propio
//Funcion solo para testeo
bool ColoreoPropio(Grafo G, u32* Coloreo);

#endif