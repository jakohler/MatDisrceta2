#include <stdlib.h>
#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"
#include "time.h"
#include <stdbool.h>


int main(int argc, char *argv[]){

  if(argc != 4){
    printf("Introdujo mal la cantidad de parametros\n");
    return 0;
  }

  Grafo G = ConstruccionDelGrafo();
  u32 Nvertices = NumeroDeVertices(G);
  u32 Nlados = NumeroDeLados(G);
  u32 delta = Delta(G);
  printf("vertice: %d\n", Nvertices);
  printf("lado: %d\n", Nlados);
  printf("delta: %d\n", delta);


  time_t start;
  time_t end;
  start = time(NULL);
  printf("-----------------------------------\n");

  u32* Orden = calloc(Nvertices, sizeof(u32));
  u32* Coloreo = calloc(Nvertices, sizeof(u32));
  u32* Coloreo_final = calloc(Nvertices, sizeof(u32));
  u32* key = calloc(Nvertices, sizeof(u32));
  u32 cantidad_colores = 0;
  u32 cant_colores_ant = UINT32_MAX;
  u32 cantidad_greedys = 0;
  u32 alpha = atoi(argv[1]);
  u32 beta = atoi(argv[2]);
  u32 p = atoi(argv[3]);
  srand(p);

  u32* ColoreoBip = Bipartito(G);

  if(ColoreoBip != NULL && Nvertices <= 101){
    for (u32 i = 0; i < Nvertices; i++) {
      if(ColoreoBip[i] == 1){
        printf("Parte 1: %d\n", i);
      }
    }
    for (u32 j = 0; j < Nvertices; j++) {
      if(ColoreoBip[j] == 2){
        printf("Parte 2: %d\n", j);
      }
    }
  }

  for (u32 i = 0; i < alpha + 2; i++) {
    if (i == 0) {
      for (u32 i = 0; i < Nvertices; i++) {
        Orden[i] = i;
      }
    } else if (i == 1) {
      for (u32 i = 0; i < Nvertices; i++) {
        key[i] = Grado(i, G);
      }
      OrdenFromKey(Nvertices, key, Orden);
    } else{
      AleatorizarKeys(Nvertices, rand(), key);
      OrdenFromKey(Nvertices, key, Orden);
    }
    for (u32 j = 0; j < beta; j++){
      OrdenFromKey(Nvertices, Coloreo, Orden);
      cantidad_colores = Greedy(G, Orden, Coloreo);
      printf("cantidad de colores: %d\n", cantidad_colores);
      if(cantidad_colores > cant_colores_ant){
        printf("No se cumple el teorema del VIT");
        return 0;
      }
      cant_colores_ant = cantidad_colores;
      ///////////////////
      free(key);
      key = PermutarColores(Nvertices, Coloreo, rand());
      OrdenFromKey(Nvertices, key, Orden);
      cantidad_colores = Greedy(G, Orden, Coloreo);
      printf("cantidad de colores: %d\n", cantidad_colores);
      if(cantidad_colores > cant_colores_ant){
        printf("No se cumple el teorema del VIT");
        return 0;
      }
      cant_colores_ant = cantidad_colores;
      //////////////////
      free(key);
      key = RecoloreoCardinalidadDecrecienteBC(Nvertices, Coloreo);
      OrdenFromKey(Nvertices, key, Orden);
      cantidad_colores = Greedy(G, Orden, Coloreo);
      printf("cantidad de colores: %d\n", cantidad_colores);
      if(cantidad_colores > cant_colores_ant){
        printf("No se cumple el teorema del VIT");
        return 0;
      }
      cant_colores_ant = cantidad_colores;
    }
  }

  for (u32 i = 0; i < Nvertices; i++) {
    Coloreo_final[i] = Coloreo[i]; 
  }

  for (u32 i = 0; i < alpha + 1; i++) {
    for (u32 j = 0; j < beta; j++){
      OrdenFromKey(Nvertices, Coloreo_final, Orden);
      cantidad_colores = Greedy(G, Orden, Coloreo_final);
      printf("cantidad de colores: %d\n", cantidad_colores);
      if(cantidad_colores > cant_colores_ant){
        printf("No se cumple el teorema del VIT");
        return 0;
      }
      cant_colores_ant = cantidad_colores;
      ///////////////////
      free(key);
      key = PermutarColores(Nvertices, Coloreo_final, rand());
      OrdenFromKey(Nvertices, key, Orden);
      cantidad_colores = Greedy(G, Orden, Coloreo_final);
      printf("cantidad de colores: %d\n", cantidad_colores);
      if(cantidad_colores > cant_colores_ant){
        printf("No se cumple el teorema del VIT");
        return 0;
      }
      cant_colores_ant = cantidad_colores;
      //////////////////
      free(key);
      key = RecoloreoCardinalidadDecrecienteBC(Nvertices, Coloreo_final);
      OrdenFromKey(Nvertices, key, Orden);
      cantidad_colores = Greedy(G, Orden, Coloreo_final);
      printf("cantidad de colores: %d\n", cantidad_colores);
      if(cantidad_colores > cant_colores_ant){
        printf("No se cumple el teorema del VIT");
        return 0;
      }
      cant_colores_ant = cantidad_colores;
    }
  }

  cantidad_greedys = (alpha + 2)*3*beta + (alpha + 1)*3*beta;

  printf("cantidad de colores final: %d\n", cantidad_colores);
  printf("cantidad de Greedys: %d\n", cantidad_greedys);
  free(key);
  free(Coloreo);
  free(Coloreo_final);
  free(Orden);

  DestruccionDelGrafo(G);

  end = time(NULL);
  printf("%ld s  %ld m %ld s\n",(end - start), (end - start) / 60, (end - start) % 60 );
  return 0;
}
