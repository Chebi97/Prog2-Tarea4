/*
  Módulo de definición de `cola_de_prioridad`.

  Se definen las colas de prioridad en las que los elementos son de tipo
  `info_t`.
  Debe implementarse con un heap.
  La cola es acotada en cuanto a la cantidad de prioridades posibles, pero no
  en cuanto a la cantidad de elementos que contiene.
  La cantidad de prioridades es establecida en el parámetro `tamanio` de
  `crear_cola_de_prioridad`. En lo que sigue `tamanio` representa ese valor.

  El orden de prioridad de los elementos está determinado por un parámetro `p`
  de tipo `prio_t` con el que los elementos quedan asociados y que es pasado al
  insertar los elementos. El valor del parámetro `p` debe estar entre 1 y
  `tamanio`.
  Se considera que el elemento prioritario es aquel que fue insertado con un
  valor menor de `p`. Si más de un elemento cumple esa condición, el
  prioritario es el que se haya insertado primero entre los que la cumplen.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_PRIORIDAD_H
#define _COLA_PRIORIDAD_H

#include "utils.h"
#include "info.h"
#include "lista.h"

typedef nat prio_t; // tipo para el valor que determina el orden de prioridad

struct rep_cola_prioridad; // representación de `cola_de_prioridad`, definida en
                           // `cola_de_prioridad.cpp`.

typedef rep_cola_prioridad *cola_de_prioridad;

/* Constructoras */

/*
  Devuelve una `cola_de_prioridad` en la que puede haber hasta `tamanio'
  prioridades diferentes.
 */
cola_de_prioridad crear_cp(nat tamanio);

/*
  Inserta en `c` el elemento `i`, que queda asociado al valor `p`.
  El tiempo de ejecución es O(tamanio) si (hay_prioridad(p, c)),
  o O(log tamanio) si (! hay_prioridad(p, c)).
  Precondición: 1 <= `p` <= tamanio.
 */
void insertar_en_cp(const info_t i, prio_t p, cola_de_prioridad &c);

/* Destructoras */

/*
  Elimina el elemento prioritario de `c` y libera la memoria que tiene asignada.
  Si es_vacia_cola_de_prioridad(c) no hace nada.
  El tiempo de ejecución es O(log tamanio).
 */
void eliminar_prioritario(cola_de_prioridad &c);

/*
  Libera la menoria asignada a `c` y a sus elementos.
 */
void liberar_cp(cola_de_prioridad &c);

/* Predicados */

/*
  Devuelve `true` si en `c` no hay elementos, o `false` en otro caso.
  El tiempo de ejecución es O(1).
 */
bool es_vacia_cp(const cola_de_prioridad c);

/*
  Devuelve `true` si en `c` hay `tamanio` prioridades diferentes.
  El tiempo de ejecución es O(1).
 */
bool es_llena_cp(const cola_de_prioridad c);

/*
  Devuelve `true` si algún elemento de `c` está asociado al valor `p`, o `false`
  en caso contrario.
  El tiempo de ejecución es O(1).
  Precondición: 1 <= `p` <= tamanio.
 */
bool hay_prioridad(const prio_t p, const cola_de_prioridad c);

/* Selectoras */

/*
  Devuelve la lista de elementos de `c` asociados al valor `p`.
  Si no hay elementos que cumplan esa condición devuelve una lista vacia.
  Si la lista devuelta no es vacía comparte memoria con `c`.
  El tiempo de ejecución es O(tamanio).
  Precondición: 1 <= `p` <= tamanio.
 */
lista lista_en_cp(const prio_t p, const cola_de_prioridad c);

/*
  Devuelve el elemento prioritario de `c`.
  Precondición ! es_vacia_cola_de_prioridad(c).
  El tiempo de ejecución es O(1).
 */
info_t prioritario(const cola_de_prioridad c);

/*
  Devuelve el valor asociado al elemento prioritario.
  Precondición ! es_vacia_cola_de_prioridad(c),
  El tiempo de ejecución es O(1).
 */
prio_t valor_prioritario(const cola_de_prioridad c);

#endif
