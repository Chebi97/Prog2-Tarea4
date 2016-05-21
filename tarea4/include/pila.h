/*
  Módulo de definición de `pila`.

  `pila` es una estructura lineal acotada con comportamiento LIFO cuyos
   elementos son de tipo `texto_t`.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_H
#define _PILA_H

#include "texto.h"

struct rep_pila; // representación de `pila`, definida en `pila.cpp`.
typedef rep_pila *pila;

/*
  Devuelve una pila vacía (sin elementos) que puede tener hasta `tamanio`
  elementos.
 */
pila crear_pila(const nat tamanio);

/*
  Apila `t` en `p`.
  Si es_llena_pila(p) no hace nada.
 */
void apilar(const texto_t t, pila &p);

/*
  Remueve de `p` el elemento que está en la cima.
  No libera la memoria del elemento removido.
  Si es_vacia_pila(p) no hace nada.
 */
void desapilar(pila &p);

/*
  Devuelve `true` si `p` es vacía (no tiene elementos), o `false` en otro caso.
 */
bool es_vacia_pila(const pila p);

/*
  Devuelve `true` si la cantidad de elementos en `p` es `tamanio` (siendo
  `tamanio` el valor del parámetro con que fue creada `p`), o `false` en otro
  caso.
 */
bool es_llena_pila(const pila p);

/*
  Devuelve el elemento que está en la cima de `p`.
  Precondición: ! es_vacia_pila(p);
 */
texto_t cima(const pila p);

/*
  Libera la memoria asignada a `p` y la de todos sus elementos.
 */
void liberar_pila(pila &p);

#endif
