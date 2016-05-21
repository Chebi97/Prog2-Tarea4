/*
  Módulo de definición de `binario`.

  Se definen los árboles binarios de búsqueda de elementos de tipo `info_t`.
  La propiedad de orden de los árboles es definida por el dato de texto de sus
  elementos.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _BINARIO_H
#define _BINARIO_H

#include "utils.h"
#include "info.h"
#include "lista.h"

struct rep_binario; // representación de `binario`
typedef rep_binario *binario;

/* **************  NUEVO  ************** */
/*
  Devuelve un árbol balanceado cuyo elementos son los que están contenidos en
  `lst`.
  En esta función se dice que un árbol está balanceado si
  a) es vacío;
  o
  b)
    b1) el sub-árbol izquierdo tiene la misma cantidad de elementos o uno más
      que el  subárbol derecho;
    y
    b2) los subárboles izquierdo y derecho están balanceados.

  DEFINICIÓN ALTERNATIVA DE ÁRBOL BALANCEADO
  En esta función se dice que un árbol esta balanceado si en cada nodo, la
  cantidad de elementos de su subárbol izquierdo es igual a, o 1 más que, la
  cantidad de elementos de su subárbol derecho.

  El tiempo de ejecución es O(n . log n), siendo `n` la cantidad de elementos
  de `lst`.
  Precondición: los elementos de `lst` están en orden lexicográfico creciente
  estricto según sus datos de texto.
  El árbol devuelto no comparte memoria con `lst`.
 */
binario crear_balanceado(const lista lst);

/* **************  NUEVO  ************** */
/*
 Devuelve una lista con los elementos de `b` en orden lexicográfico creciente
 según sus datos de texto.
 La lista devuelta no comparte memoria con `b`.
 El tiempo de ejecución es O(n) siendo `n` la cantidad de nodos de `b`.
 */
lista linealizacion(const binario b);

/* **************  NUEVO  ************** */
/*
  Imprime los datos de texto de los nodos de `b` en orden decreciente de
  niveles (desde las hojas hasta la raíz), un nivel por línea.
  En cada nivel los textos se imprimen en orden lexicográfico creciente.
  Después de cada texto se imprime un espacio en blanco.
  Si `b` es vacío no imprime nada.
 */
void imprimir_textos(const binario b);

/* ANTES EN USO_LISTA_ARBOLES */
/*
  Devuelve el subárbol que tiene como raíz al nodo que, según la propiedad de
  orden de los árboles `binario`, está en el k-ésimo lugar de `b`.
  Precondición: 1 <= k <= cantidad_binario(b).
 */
binario kesimo_subarbol(const nat k, const binario b);

/* Constructoras */

/*
  Devuelve un binario vacío (sin elementos).
 */
binario crear_binario();

/*
  Inserta `i` en `b` respetando la propiedad de orden definida.
  Si en `b` ya hay un elemento cuyo dato de texto es texto_info(i) no se hace
  nada.
  Devuelve `true` si se insertó `i`, o `false` en otro caso.
 */
bool insertar_en_binario(const info_t i, binario &b);

/*
  Devuelve un árbol con copias de los elementos de `b` que cumplen la condición
  "numero_info(elemento) criterio clave".
  La estructura del árbol resultado debe ser análoga a la de `b`. Esto
  significa que dados dos nodos `U` y `V` de `b` en los que se cumple la
  condición y tal que `U` es ancestro de `V`, en el árbol resultado la copia de
  `U` debe ser ancestro de la copia de `V` cuando sea posible. Esto no siempre
  se puede lograr y al mismo tiempo mantener la propiedad de orden del árbol
  en el caso en el que en un nodo `V` no se cumple la condición y en sus dos
  subárboles hay nodos en los que se cumple. En este caso, la copia del nodo
  cuyo elemento es el mayor (según la propiedad de orden definida) de los que
  cumplen la condición en el subárbol izquierdo de `V` deberá ser ancestro de
  las copias de todos los descendientes de `V` que cumplen la condición.
  (Ver ejemplos en LetraTarea3.pdf).
  El árbol resultado no comparte memoria con `b`. *)
 */
binario crear_filtrado(const int clave, comp_t criterio, const binario b);

/* Destructoras */

/*
  Devuelve el elemento mayor (según la propiedad de orden definida) de `b`.
  Remueve el nodo en el que se localiza ese elemento (libera la memoria
  asignada al nodo, pero no la del elemento).
  Precondición: ! es_vacio_binario(b).
 */
info_t remover_mayor(binario &b);

/*
  Remueve de `b` el nodo en el que el dato de texto de su elemento es `t`.
  Si en ningún nodo se cumple esa condición no se hace nada.
  Si los dos subárboles del nodo a remover son no vacíos, en sustitución del
  elemento removido debe quedar el que es el mayor (segun la propiedad de orden
  definida) en el subárbol izquierdo.
  Libera la memoria del nodo y del elemento.
 */
void remover_de_binario(const texto_t t, binario &b);

/*
  Libera la memoria asociada a `b` y todos sus elementos.
 */
void liberar_binario(binario &b);

/* Predicados */

/*
  Devuelve `true` si `b` es vacío (no tiene elementos), o `false` en otro caso.
 */
bool es_vacio_binario(const binario b);

/* Selectoras */

/*
  Devuelve el elemento asociado a la raíz de `b`.
  Precondición: ! es_vacio_binario(b).
 */
info_t raiz_binario(const binario b);

/*
  Devuelve el subárbol izquierdo de  `b`.
  Precondición: ! es_vacio_binario(b).
 */
binario izquierdo(const binario b);

/*
  Devuelve el subárbol derecho de  `b`.
  Precondición: ! es_vacio_binario(b).
 */
binario derecho(const binario b);

/*
  Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo dato de
  texto es `t`.
  Si `t` no pertenece a `b`, devuelve el árbol vacío.
 */
binario buscar_subarbol(const texto_t t, const binario b);

/*
  Devuelve la altura de `b`.
  La altura de un árbol vacío es 0.
 */
nat altura_binario(const binario b);

/*
  Devuelve la cantidad de nodos de `b`.
 */
nat cantidad_binario(const binario b);

/* Salida */

/*
  Imprime los elementos de `b`, uno por línea, en orden descendente de la
  propiedad de orden de los árboles `binario`.
  Antes del elemento imprime una cantidad de guiones igual a su nivel.
  El elemento se imprime según la especificación dada en `info_a_texto`.
  El nivel de la raíz es 0.
 */
void imprimir_binario(const binario b);

#endif
