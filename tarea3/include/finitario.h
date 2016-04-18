/*
  Módulo de definición de `finitario`.

  Se definen los árboles finitarios de elementos de tipo `info_t`.
  Los hijos de cada nodo se enumeran de izquierda a derecha. El hijo de más a
  la izquierda es el primero.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _FINITARIO_H
#define _FINITARIO_H

#include "utils.h"
#include "info.h"
#include "lista.h"

struct rep_finitario; // representación de `finitario`
typedef rep_finitario *finitario;

/* Constructoras */

/*
  Devuelve un finitario vacío (sin elementos).
 */
finitario crear_finitario();

/*
  Inserta `i` en `f`.
  Si es_vacio_finitario(f), `f` pasa a ser un árbol hoja con elemento `i`.
  En otro caso, `i` pasa a ser el `k`-ésimo hijo de `f`, o el último si la
  cantidad de hijos de `f` es menor que `k` - 1. Los otros hijos de `f`
  mantienen su orden relativo.
  Precondición: `pos > 0`.
 */
void insertar_en_finitario(const info_t i, const nat k, finitario &f);

/* Destructoras */

/*
  Libera la memoria asociada a `f` y todos sus elementos.
 */
void liberar_finitario(finitario &f);

/* Predicados */

/*
  Devuelve `true` si `f`es vacío (no tiene elementos), o `false` en otro caso.
 */
bool es_vacio_finitario(const finitario f);

/* Selectoras */

/*
  Devuelve el elemento asociado a la raiz de `f`.
  Precondición: ! es_vacio_finitario(f).
 */
info_t raiz_finitario(const finitario f);

/*
  Devuelve el subárbol con raíz en el `k`-ésimo hijo `f`.
  Si `k` es mayor que la cantidad de hijos de `f` devuelve el árbol vacío.
  Precondiciones: ! es_vacio_finitario(f)` y `pos > 0`.
 */
finitario hijo(const nat k, const finitario f);

/*
  Devuelve una lista de elementos de tipo `info_t` de los nodos que están en el
  nivel `k` de `f`. La lista debe estar ordenada de manera creciente según el
  dato numérico. Para cada par de elementos con el mismo dato numérico debe
  quedar primero el que en `f` está más a la izquierda.
  La raíz está en el nivel 1.
  Devuelve la lista vacía si el árbol no tiene nodos en el nivel k.
  La lista devuelta no comparte memoria con `f`.
  Precondición: k >= 1.
 */
lista nivel(nat k, const finitario f);

/*
  Devuelve la altura de `f`.
  La altura de una árbol finitario vacío es 0.
 */
nat altura_finitario(const finitario f);

#endif
