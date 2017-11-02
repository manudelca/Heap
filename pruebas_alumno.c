#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //para el random
#define TAM_EN_VOLUMEN 100
/* ******************************************************************
 *                   FUNCIONES AUXILIARES
 * *****************************************************************/

int comparar(const void *a,const void *b){
	const int* valor_1 = a;
	const int* valor_2 = b;
	if (*valor_1 > *valor_2) return 1;
	else if (*valor_1 < *valor_2) return -1;
	return 0;
}


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_heap_vacio(void){
	printf("1) PRUEBAS HEAP VACÍO.\n");
	
	heap_t* h = heap_crear(comparar);
	
	print_test("Crear heap vacío", h != NULL);
	print_test("El heap está vacío", heap_esta_vacio(h));
	/*Pruebo ver el máximo del heap devuelve NULL*/
	print_test("Ver el max del heap devuelve NULL",!heap_ver_max(h));
	/*Pruebo desdesencolar la heap vacía y devuelve false*/
	print_test("Desencolar con el heap vacío devuelve false ",!heap_desencolar(h));
	/*Destruyo el heap*/
	heap_destruir(h,NULL);
}

void pruebas_heap_insertar(void){
	printf("\n2) PRUEBAS HEAP DESENCOLAR Y ENCOLAR VARIOS ELEMENTOS.\n");
	heap_t* h = heap_crear(comparar);

    /*Valores a desencolar*/
	int v1 = 1, v2 = 2, v3= 3, v4= 4, v5= 5, v6= 6;

	/*Pruebo desencolar elementos*/
	print_test ("Heap_encolar número 5", heap_encolar(h,&v5));
	print_test ("Heap_encolar número 1", heap_encolar(h,&v1));
	print_test ("Heap_encolar número 3", heap_encolar(h,&v3));
	print_test ("Heap_encolar número 6", heap_encolar(h,&v6));
	print_test ("Heap_encolar número 2", heap_encolar(h,&v2));
	print_test ("Heap_encolar número 4", heap_encolar(h,&v4));


	/*Pruebo que el heap está vacío devuelve false*/
	print_test("El heap no está vacío", !heap_esta_vacio(h));
	/*Pruebo que el heap cantidad devuelve 6*/
	print_test("El heap tiene cantidad 6", heap_cantidad(h) == 6);
	/*Pruebo ver el máximo */
	print_test("Ver max devuelve el valor 6",heap_ver_max(h) == &v6);
	/*Pruebo desdesencolar los elementos*/
	int *aux = heap_desencolar(h);
	print_test("Elemento desencolado es 6 ", *aux == v6);
	print_test("Ver max devuelve el valor 5",heap_ver_max(h) == &v5);

	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 5", *aux == v5);
	print_test("Ver max devuelve el valor 4",heap_ver_max(h) == &v4);

	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 4", *aux == v4);
	print_test("Ver max devuelve el valor 3",heap_ver_max(h) == &v3);

	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 3", *aux == v3);
	print_test("Ver max devuelve el valor 2",heap_ver_max(h) == &v2);

	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 2", *aux == v2);
	print_test("Ver max devuelve el valor 1",heap_ver_max(h) == &v1);

	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 1  ", *aux == v1);
	print_test("Ver max devuelve NULL",heap_ver_max(h) == NULL);

	/*Pruebo que el heap esté vacía luego de desencolar todos los elementos*/
	print_test("El heap ahora está vacío", heap_esta_vacio(h));
	print_test("El heap tiene cantidad 0", heap_cantidad(h) == 0);
	print_test("Desencolar devuelve NULL", heap_desencolar(h) == NULL);

	heap_destruir (h,NULL);
}

void prueba_heap_redimensionar_en_vol(void){
	printf("\n3.a) PRUEBAS HEAP REDIMENSIONAR CON VOLUMEN.\n");
	/*Pruebo desencolar y desdesencolar cantidad mayor al tamaño inicial de la heap */
	printf("**Redimensionando heap encolando 100 elementos. Último valor encolado 99.**\n");
	heap_t* h = heap_crear(comparar);

	int valores[100];
	for (int i = 0; i<100; i++){
		valores[i] = i;
		heap_encolar(h, &valores[i]);
	}

	/*Pruebo ver el tope*/
	int* aux_int = heap_ver_max(h);
	print_test("Prueba ver que el máx sea el valor 99.",*aux_int == 99);

	/*Desapilo la heap*/
	printf("**Desencolando 100 elementos.**\n");
	for (int i= 0; i<100; i++){
		heap_desencolar(h);
	}

	/*Pruebo ver el tope de la heap vacía*/
	print_test("Ver el tope de la heap devuelve NULL.",!heap_ver_max(h));
	/*Pruebo que el heap esté vacío*/
	print_test("El heap está vacío.", heap_esta_vacio(h));
	/*Destruyo el heap*/
	heap_destruir(h, NULL);

}

void pruebas_heap_volumen(void){
	printf("\n3.b) PRUEBAS HEAP EN VOLUMEN.\n");
	heap_t* heap = heap_crear(comparar);
	bool test_encolar = true;
	bool test_desencolar = true;
	int num = 1000;
	heap_encolar(heap,&num);
	int arreglo_ent [TAM_EN_VOLUMEN];
	srand(0);
	for (int i = 0; i < TAM_EN_VOLUMEN; i++) {
    		arreglo_ent[i] = rand()%TAM_EN_VOLUMEN;
		if(!heap_encolar(heap, &arreglo_ent[i])){
			test_encolar = false;
		}
	}

	print_test ("El heap encolo ok", test_encolar);
	print_test ("El heap no está vacío", !heap_esta_vacio(heap));
	print_test ("La cantidad del heap es ok..", heap_cantidad(heap) == (TAM_EN_VOLUMEN + 1));
	int* aux_int = heap_ver_max(heap);
	print_test("Prueba ver que el máx sea el valor 1000.",*aux_int == 1000);
	printf("**Desencolando Tam_volumen elementos.**\n");
	for (int ii= 0; ii<TAM_EN_VOLUMEN; ii++){
		if(!heap_desencolar(heap)){
			test_desencolar = false;
		}
	}
	heap_desencolar(heap);
	print_test ("El heap desencolo ok", test_desencolar);
	print_test("Ver el tope de la heap devuelve NULL.",!heap_ver_max(heap));
	print_test("El heap está vacío.", heap_esta_vacio(heap));
	heap_destruir(heap, NULL);
}

void pruebas_heap_sort(size_t largo){
	printf("\n5) PRUEBAS HEAPSORT.\n");
	/*Creo un arreglo de punteros a int*/
	void* numeros[9];
	int arreglo[9] = {1, 10, 2, 3, 9, 21, 20, 4, 31};
	int arreglo_ord[9] = {1, 2, 3, 4, 9, 10, 20, 21, 31};
	bool ok = true;
	size_t pos = 0;
	while (pos <9){
		numeros[pos] = &arreglo[pos];
		pos++;
	}
	heap_sort(numeros, 9,comparar);
	pos = 0;
	while (pos < 9){
		int* n = numeros[pos];
		if (*n != arreglo_ord[pos]) {
	        ok = false;
        }
        pos++;
	}
	print_test("Prueba HeapSort. Se ordenaron 9 elementos.", ok);


	size_t numeros_2[largo];
	void* valores[largo];
	ok = true;
	size_t i;
	size_t x = largo-1;
    for (i = 0; i < largo; i++) {

    	numeros_2[i] = x;
        valores[i] = &numeros_2[i];
        x--;
    }

	heap_sort(valores, largo ,comparar);

	pos = 0;
	while (pos < largo){
		//int* n = valores[pos];
		//*n;
		pos++;
	}
	print_test("Prueba HeapSort con tres nodos.", ok);
}

void pruebas_heap_arr(void){
	printf("\n6) PRUEBAS HEAP ARR.\n");
	void* numeros[9];
	int arreglo[9] = {1, 10, 2, 3, 9, 21, 20, 4, 31};
	size_t pos = 0;
	while (pos <9){
		numeros[pos] = &arreglo[pos];
		pos++;
	}

	heap_t* h = heap_crear_arr(numeros,9,comparar);
	 /*Pruebo que el heap cantidad devuelve 6*/
	print_test("El heap tiene cantidad 9", heap_cantidad(h) == 9);

	/*Pruebo que el heap está vacío devuelve false*/
	print_test("El heap no está vacío", !heap_esta_vacio(h));

	int* aux = heap_desencolar(h);
	print_test("Elemento desencolado es 31 ", *aux == 31);
	aux = heap_ver_max(h);
	print_test("Ver max devuelve el valor 21", *aux  == 21);

	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 21 ", *aux == 21);
	aux = heap_ver_max(h);
	print_test("Ver max devuelve el valor 20", *aux  == 20);

	print_test("El heap tiene cantidad 7", heap_cantidad(h) == 7);

	heap_destruir(h, NULL);
}

void pruebas_heap_alumno() {
	pruebas_heap_vacio();
	pruebas_heap_insertar();
	prueba_heap_redimensionar_en_vol();
	pruebas_heap_volumen();
	pruebas_heap_sort(1);
	pruebas_heap_arr();

}
