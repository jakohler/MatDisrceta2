#include "AlduinPaarthurnaxIrileth.h"

u32 menor_color(u32 delta, u32* colores_usados){
  u32 color = 0;

  while (colores_usados[color] != 0 && color != delta + 1) {
    color++;
  }
  return color;
}

void limpiar_colores(u32 delta, u32* colores_usados){
  for (u32 i = 0; i < delta; i++) {
    colores_usados[i] = 0;
  }
}

u32 Greedy(Grafo G,u32* Orden,u32* Coloreo){
  u32 num_vertices = NumeroDeVertices(G);
  u32 delta = Delta(G);
  u32 grado, vecino, vertice;
  u32 cantidad_colores = 0;
  u32* colores_usados = calloc(delta + 1, sizeof(u32)); //arreglo donde se guardan los colores ya usados por los vecinos(el color es indicado por el indice)
  for (u32 i = 0; i < num_vertices; i++) {
    Coloreo[i] = UINT32_MAX;
  }

  for (u32 i = 0; i < num_vertices; i++) {
    vertice = Orden[i];
    grado = Grado(vertice, G);
    for (u32 j = 0; j < grado; j++) {
      vecino = IndiceONVecino(j, vertice, G);
      if (Coloreo[vecino] != UINT32_MAX) {
        colores_usados[Coloreo[vecino]] = 1;
      }
    }
    Coloreo[vertice] = menor_color(delta, colores_usados);
    limpiar_colores(delta, colores_usados);
  }

  for (u32 i = 0; i < num_vertices; i++) {
    if (Coloreo[i] >= cantidad_colores) {
      cantidad_colores = Coloreo[i];
    }
  }

  free(colores_usados);

  return cantidad_colores + 1;
}


