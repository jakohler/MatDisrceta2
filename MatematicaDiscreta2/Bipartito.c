#include <stdlib.h>
#include "queue.h"
#include "AlduinPaarthurnaxIrileth.h"


u32* Bipartito(Grafo G){
  u32 num_vertices = NumeroDeVertices(G);
  u32 *coloreo = calloc(num_vertices, sizeof(u32));
  u32 vertice, vecino;
  queue cola = queue_init();

  for (u32 j = 0; j < num_vertices; j++){
    if(coloreo[j] == 0){
      coloreo[j] = 1;
      queue_add(j, cola);
    }
    while (cola->first != NULL) {
      vertice = cola->first->index;
      for (u32 i = 0; i < Grado(vertice, G); i++) {
        vecino = IndiceONVecino(i, vertice, G);
        if (coloreo[vecino] == 0) {
          coloreo[vecino] = (coloreo[vertice] % 2) + 1;
          queue_add(vecino, cola);
        }
        else if (coloreo[vecino] == coloreo[vertice]) {
          printf("NO ES Bipartito\n");
          free(coloreo);
          queue_destroy(cola);
          return NULL;
        }
      }
      queue_remove(cola);
    }
  }
  queue_destroy(cola);
  printf("Es Bipartito\n");
  return coloreo;
}
