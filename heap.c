#include "heap.h"
#include <stdin.h>
#define TAM_INI 40

struct heap{
  void** arreglo;
  size_t cantidad;
  size_t capacidad;
  cmp_func_t comparar;
}

/*Recibe la posicion de un elemento del arreglo y devuelve la posicion del hijo izquierdo*/
size_t encontrar_hizq(size_t i){
  return 2*i+1
}
/*Recibe la posicion de un elemento del arreglo y devuelve la posicion del hijo derecho*/
size_t encontrar_hder(size_t i){
  return 2*i+2
}
/*Recibe la posicion de un elemento del arreglo y devuelve la posicion del padre*/
size_t encontrar_padre(size_t i){
  return (i-2)/2
}

/*Recibe dos posiciones y swapea los elementos que se encuentran en ellos.
  Pre: las posiciones son validas.*/
void swap(heap,i,j){
  void* aux=heap->arreglo[i];
  heap->arreglo[i]=heap->arreglo[j];
  heap->arreglo[j]=aux;
  return;
}

/*Redimensiona el heap al tam_nuevo pasado por parametro. Devuelve false en caso
de error.*/
bool redimensionar(heap_t* heap, size_t tam_nuevo){
  void** arreglo_nuevo=realloc(sizeof(void*)*tam_nuevo);
  if(!arreglo_nuevo)
    return false;
  heap->arreglo=arreglo_nuevo;
  heap->capacidad=tam_nuevo;
  return true;
}

void upheap(heap_t* heap,size_t posicion){
  if(posicion==0)
    return;
  size_t pos_padre=encontrar_padre(posicion);
  if(heap->comparar(heap->arreglo[posicion],heap->arreglo[pos_padre]) > 0){
    swap(heap,posicion,pos_padre);
    upheap(heap,pos_padre);
  }
  return;
}


heap_t* heap_crear(cmp_func_t cmp){
  if(!cmp)
    return NULL;
  heap_t heap=malloc(sizeof(heap_t));
  if(!heap)
    return NULL;
  void** arreglo=malloc(sizeof(void*)*TAM_INI);
  if(!arreglo){
    free(heap);
    return NULL;
  }
  heap->cantidad=0;
  heap->capacidad=TAM_INI;
  heap->comparar=cmp;
  return heap;
}

void heap_destruir(heap_t* heap, void destruir_elemento(void* e)){
  for(size_t i=0; i<cantidad && destruir_elemento; i++){
    actual=heap->arreglo[i];
    destruir_elemento(actual);
  }
  free(heap->arreglo);
  free(heap);
  return;
}

bool heap_esta_vacio(const heap_t* heap){
  return heap->cantidad==0;
}

bool heap_encolar(heap_t *heap, void *elem){
  if(heap->cantidad==heap->capacidad){
    if(!redimensionar(heap->arreglo,REDIMENSION))
      return false;
  }
  heap->arreglo[cantidad]=elem;
  upheap(heap,cantidad);
  heap->cantidad++;
  return true;
}

void* heap_ver_max(const heap_t* heap){
  return heap->arreglo[0] ? heap->arreglo[0] : NULL;
}
