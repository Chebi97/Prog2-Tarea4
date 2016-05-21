/*
  Módulo de definición de `lista`.

  Lista doblemente enlazada de elementos de tipo `info_t`, con cabezal con
  punteros al inicio y al final.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _LISTA_H
#define _LISTA_H

#include "info.h"

/*
  Las variables de tipo localizador permiten acceder a los elementos en las
  estructuras que los contienen. En el caso de una lista enlazada esas
  variables son punteros a los nodos.
 */
struct nodo; // representación de `localizador`, definida en `lista.cpp`.
typedef nodo *localizador;

struct rep_lista; // representación de `lista`, definida en `lista.cpp`.
typedef rep_lista *lista;

/* ANTES EN USO_LISTA_ARBOLES */
/* Salida */
/*
  Imprime los elementos de `lst` de la siguiente forma:
  (dn de pos1,dt de pos1)(dn de pos2,dt de pos2)(dn de pos3,dt de pos3) ...
  donce `dn` es el dato numérico y `dt` es el dato de texto.
  Antes de terminar, se debe imprimir un fin de linea.
  Si es_vacia_lista(lst) solo se imprime el fin de línea.
 */
void imprimir_lista(const lista lst);

/* Constructoras */

/*
  Devuelve la lista vacía (sin elementos).
 */
lista crear_lista();

/*
  Se inserta `i` como un nuevo elemento inmediatamente antes de `loc`.
  Si es_vacia_lista (lst), entonces `loc` es ignorado e `i` se inserta como
  unico elemento de `lst`.
  El tiempo de ejecución es O(1).
  Precondición: es_vacia_lista (lst) o localizador_pertenece_a_lista (loc, lst).
 */
void insertar_antes(const info_t i, const localizador loc, lista &lst);

/*
  Se inserta `i` como un nuevo elemento inmediatamente después de `loc`.
  Si es_vacia_lista (lst), entonces `loc` es ignorado e `i` se inserta como
  unico elemento de `lst`.
  El tiempo de ejecución es O(1).
  Precondición: es_vacia_lista (lst) o localizador_pertenece_a_lista (loc, lst).
 */
void insertar_despues(const info_t i, const localizador loc, lista &lst);

/*
  Devuelve una lista con los elementos de `lst` que se encuentran entre
  `desde` y `hasta`, inclusive.
  La lista resultado no comparte memoria con `lst`.
  Si es_vacia_lista (lst) devuelve la lista vacia.
  El tiempo de ejecución es O(n), siendo `n` la cantidad de elementos en la
  lista resultado.
  Precondición: es_vacia_lista(lst) o precede_lista(desde, hasta, lst).
 */
lista segmento_lista(const localizador desde, const localizador hasta,
                     const lista lst);

/*
  Se inserta la lista `sgm` inmediatamente después de `loc` en `lst`,
  manteniendo los elementos originales y el orden relativo entre ellos.
  No se debe obtener memoria (los nodos de `sgm` pasan a ser parte de `lst`).
  Al terminar, `sgm` queda vacía.
  Si es_vacia_lista (lst), `loc` es ignorado y el segmento queda insertado.
  El tiempo de ejecución es O(1).
  Precondición: es_vacia_lista (lst) o localizador_pertenece_a_lista (loc, lst).
 */
void insertar_segmento_despues(lista &sgm, const localizador loc, lista &lst);

/*
  Devuelve una lista con los elementos de `lst` que se encuentran
  entre `desde` y `hasta`, inclusive. Ademas, quita de `lst` dichos elementos,
  manteniendo el orden de los restantes.
  Si es_vacia_lista (lst), devuelve la lista vacía.
  No se debe obtener ni devolver memoria de nodos ni de elementos.
  La lista resultado no comparte memoria con `l`.
  Los valores de `desde` y `hasta` quedan indeterminados.
  El tiempo de ejecución es O(1).
  Precondición: es_vacia_lista (lst) o precede_lista(desde, hasta, lst).
 */
lista separar_segmento(localizador desde, localizador hasta, lista &lst);

/* Destructoras */

/*
  Se quita el elemento referenciado en `loc` y se libera la memoria asignada
  al mismo y al nodo apuntado por el localizador.
  Si es_vacia_lista (lst), `loc` es ignorado y no se hace nada.
  El valor de `loc` queda indeterminado.
  El tiempo de ejecución es O(1).
  Precondición: es_vacia_lista (lst) o localizador_pertenece_a_lista (loc, lst).
 */
void remover_de_lista(localizador &loc, lista &lst);

/*
  Libera la memoria asignada a `lst` y la de todos sus elementos.
  El tiempo de ejecución es O(n), siendo `n` la cantidad de elementos de la
  lista.
 */
void liberar_lista(lista &lst);

/* Predicados */

/*
  Devuelve `true` si `lst` es vacía (no tiene elementos), o `false` en otro
  caso.
  El tiempo de ejecución es O(1).
 */
bool es_vacia_lista(const lista lst);

/*
  Devuelve `true` si `loc` es un localizador válido, o `false` en otro caso.
  En listas enlazadas un localizador no es válido si es `NULL`.
  El tiempo de ejecución es O(1).
*/
bool es_localizador_lista(const localizador loc);

/*
  Devuelve `true` si con `loc` se accede a  un elemento de `lst`, o `false` en
  otro caso.
  El tiempo de ejecución es O(n), siendo `n` la cantidad de elementos de la
  lista.
  Precondición: ! es_vacia_lista (lst).
 */
bool localizador_pertenece_a_lista(const localizador loc, const lista lst);

/*
  Devuelve `true` si `l1` es igual o precede a `l2` en `lst`, o `false` en
  otro caso.
  El tiempo de ejecución es O(n), siendo `n` la cantidad de elementos de la
  lista.
  Precondición: localizador_pertenece_a_lista(l1, lst) y
    localizador_pertenece_a_lista(l2, lst).
 */
bool precede_en_lista(const localizador l1, const localizador l2,
                      const lista lst);

/*
  Devuelve `true` si con `loc` se accede al primer elemento de `lst` o `false`
  en otro caso.
  El tiempo de ejecución es O(1).
  Precondición: ! es_vacia_lista (lst).
 */
bool es_inicio_lista(const localizador loc, const lista lst);

/*
  Devuelve `true` si con `loc` se accede al último elemento de `lst` o `false`
  en otro caso.
  El tiempo de ejecución es O(1).
  Precondición: ! es_vacia_lista (lst).
 */
bool es_final_lista(const localizador loc, const lista lst);

/* Posicionamiento */

/*
  Devuelve el localizador con el que se accede al inicio de `lst`.
  Si es_vacia_lista(lst) devuelve un localizador no válido.
  El tiempo de ejecución es O(1).
 */
localizador inicio_lista(const lista lst);

/*
  Devuelve el localizador con el que se accede al final de `lst`.
  Si es_vacia_lista(lst) devuelve un localizador no válido.
  El tiempo de ejecución es O(1).
 */
localizador final_lista(const lista lst);

/*
  Devuelve el localizador con el que se accede al elemento de `lst`
  inmediatamente  siguiente a `loc`.
  Si es_final_lista (loc, lst), devuelve un localizador no válido.
  El tiempo de ejecución es O(1).
  Precondición: ! es_vacia_lista (l) y localizador_pertenece_a_lista (loc, lst).
 */
localizador siguiente(const localizador loc, const lista lst);

/*
  Devuelve el localizador con el que se accede al elemento de `lst`
  inmediatamente  anterior a `loc`.
  Si es_inicio_lista (loc, lst), devuelve un localizador no válido.
  El tiempo de ejecución es O(1).
  Precondición: ! es_vacia_lista (l) y localizador_pertenece_a_lista (loc, lst).
 */
localizador anterior(const localizador loc, const lista lst);

/*
  Devuelve el primer localizador con el que se accede a un elemento cuyo dato
  numérico es igual a 'clave', buscando desde `loc` (inclusive) hacia el final
  de `lst`.
  Si no se encuentra o `lst` es vacía, devuelve un localizador no válido.
  El tiempo de ejecución es O(n), siendo `n` la cantidad de elementos de la
  lista.
  Precondición: es_vacia_lista (lst) o localizador_pertenece_a_lista (loc, lst).
 */
localizador siguiente_clave(const int clave, const localizador loc,
                            const lista lst);

/*
  Devuelve el primer localizador con el que se accede a un elemento cuyo dato
  numérico es igual a 'clave', buscando desde `loc` (inclusive) hacia el inicio
  de `lst`.
  Si no se encuentra o `lst` es vacia, devuelve un localizador no válido.
  El tiempo de ejecución es O(n), siendo `n` la cantidad de elementos de la
  lista.
  Precondición: es_vacia_lista (lst) o localizador_pertenece_a_lista (loc, lst).
 */
localizador anterior_clave(const int clave, const localizador loc,
                           const lista lst);

/* Selectoras */

/*
  Devuelve el elemento de `lst` al que se accede con `loc`.
  El tiempo de ejecución es O(1).
  Precondición: ! es_vacia_lista (lst) y localizador_pertenece_a_lista (loc,
  lst).
 */
info_t info_lista(const localizador loc, const lista lst);

/* Modificadoras */

/*
  Sustituye con `i` el elemento de `lst` al que se accede con `loc`.
  No destruye el elemento al que antes se accedía con `loc`.
  El tiempo de ejecución es O(1).
  Precondición: ! es_vacia_lista (lst) y localizador_pertenece_a_lista (loc,
  lst).
 */
void cambiar_en_lista(const info_t i, const localizador loc, lista &lst);

/*
  Intercambia los elementos a los que se accede con `loc1` y `loc2`.
  `loc1` y `loc2` mantienen su relación de precedencia.
  El tiempo de ejecución es O(1).
  Precondición: ! es_vacia_lista (lst)
  y localizador_pertenece_a_lista (loc1, lst)
  y localizador_pertenece_a_lista (loc2, lst).
 */
void intercambiar(const localizador loc1, const localizador loc2, lista &lst);

/*
  Mueve el elemento al que se accede con `loc2` dejándolo inmediatamente antes
  de `loc1`.
  Los valores de `loc1` y `loc2` quedan indeterminados.
  Si loc1 == loc2 no hace nada.
  El tiempo de ejecución es O(1).
  Precondición: ! es_vacia_lista (lst)
  y localizador_pertenece_a_lista (loc1, lst)
  y localizador_pertenece_a_lista (loc2, lst).
 */
void mover_antes(localizador loc1, localizador loc2, lista &lst);

#endif
