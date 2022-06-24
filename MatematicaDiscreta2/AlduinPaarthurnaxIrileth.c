#include <stdlib.h>
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "FuncionesAux.h"
#include <stdbool.h>

int ComSortPS(const void *a, const void *b) {
  const u32 *aInt = *(const u32 **) a;
  const u32 *bInt = *(const u32 **) b;
  return aInt[1] - bInt[1];
}

int ComSortPF(const void *a, const void *b) {
  const u32 *aInt = *(const u32 **) a;
  const u32 *bInt = *(const u32 **) b;
  return bInt[0] - aInt[0];
}

void FreeAux(u32** key_aux, u32 n){
  for (u32 h = 0; h < n; h++){
    free(key_aux[h]);
  }
  free(key_aux);
}

u32 NumColores(u32* Coloreo, u32 n){
  u32 num = 0;

  for (u32 i = 0; i < n; i++){
    if (Coloreo[i] > num){
      num = Coloreo[i];
    }
  }

  return (num + 1);
}

bool ColoreoPropio(Grafo G, u32* Coloreo){
  u32 num_vertices = NumeroDeVertices(G);
  u32 vertice, grado, vecino;
  for (u32 i = 0; i < num_vertices; i++) {
    vertice = i;
    grado = Grado(vertice, G);
    for (u32 j = 0; j < grado; j++) {
      vecino = IndiceONVecino(j, vertice, G);
      if (Coloreo[vecino] == Coloreo[vertice]) {
        printf("El coloreo no es propio");
        return false;
      }
    }
  }

  return true;
}

char OrdenFromKey(u32 n,u32* key,u32* Orden){
  char error = 0;
  // creamos un arreglo 2xnum_lados
  u32 **key_aux = (u32 **)calloc(n, sizeof(u32*));

  for (u32 i = 0; i < n; i++){
    key_aux[i] = calloc(2, sizeof(u32));
  }
  for (u32 j = 0; j < n; j++){
    key_aux[j][0] = key[j];
    key_aux[j][1] = j;
  }

  qsort(key_aux, n, sizeof(u32*), ComSortPF);

  if(key_aux == NULL){
    error = 1;
  }

  int k = 0;
  for (int p = (n-1); p >= 0; p--){
    Orden[k] = key_aux[p][1];
    k++;
  }

  FreeAux(key_aux, n);

  return error;
}

void AleatorizarKeys(u32 n,u32 R,u32* key){
  srand(R);
  for (u32 i = 0; i < n; i++){
    key[i] = rand() % n;
  }
}

u32* PermutarColores(u32 n,u32* Coloreo,u32 R){
  u32 cant_colores = NumColores(Coloreo, n);
  u32 *coloreo_nuevo = calloc(n, sizeof(u32));
  u32 *perm_colores = calloc(cant_colores, sizeof(u32));
  u32 swap_aux, rand_num;
  srand(R);
  for (u32 i = 0; i < cant_colores; i++){
    perm_colores[i] = i;
  }
  for (u32 i = 0; i < cant_colores; i++){
    rand_num = rand() % cant_colores;
    swap_aux = perm_colores[i];
    perm_colores[i] = perm_colores[rand_num];
    perm_colores[rand_num] = swap_aux;
  }
  for (u32 j = 0; j < n; j++){
    coloreo_nuevo[j] = perm_colores[Coloreo[j]];
  }

  if(coloreo_nuevo == NULL){
    return NULL;
  }

  free(perm_colores);

  return coloreo_nuevo;
}

u32* RecoloreoCardinalidadDecrecienteBC(u32 n,u32* Coloreo){
  u32 cant_colores = NumColores(Coloreo, n);
  u32 *coloreo_nuevo = calloc(n, sizeof(u32));
  u32 **cuenta_colores = (u32 **)calloc(cant_colores, sizeof(u32*));

  for (u32 i = 0; i < cant_colores; i++){
    cuenta_colores[i] = calloc(2, sizeof(u32));
  }
  for (u32 j = 0; j < cant_colores; j++){
    cuenta_colores[j][1] = j;
  }
  for (u32 i = 0; i < n; i++) {
    cuenta_colores[Coloreo[i]][0]++;
  }

  qsort(cuenta_colores, cant_colores, sizeof(u32*), ComSortPF);

  for (u32 i = 0; i < cant_colores; i++) {
    cuenta_colores[i][0] = i;
  }
  qsort(cuenta_colores, cant_colores, sizeof(u32*), ComSortPS);

  for (u32 i = 0; i < n; i++) {
    coloreo_nuevo[i] = cuenta_colores[Coloreo[i]][0];
  }

  if(coloreo_nuevo == NULL){
    return NULL;
  }

  FreeAux(cuenta_colores, cant_colores);

  return coloreo_nuevo;
}

