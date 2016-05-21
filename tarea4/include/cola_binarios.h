/*
  Módulo de definición de `cola_binarios`.

  `cola_binarios` es una estructura lineal con comportamiento FIFO cuyos
   elementos son de tipo `binario`.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_BINARIO_H
#define _COLA_BINARIO_H

#include "binario.h"

struct rep_cola_binarios; // representación de `cola_binarios`, definida en
                          // `cola_binarios.cpp`.
typedef rep_cola_binarios *cola_binarios;

/*
  Devuelve una cola_binarios vacía (sin elementos).
 */
cola_binarios crear_cola_binarios();

/*
  Encola `b` en `c`.
 */
void encolar(const binario b, cola_binarios &c);

/*
  Remueve de `c` el elemento que está en el frente.
  No libera la memoria del elemento removido.
  Si es_vacia_cola_binarios(c) no hace nada.
 */
void desencolar(cola_binarios &c);

/*
  Devuelve `true` si `c` es vacía (no tiene elementos), o `false` en otro caso.
 */
bool es_vacia_cola_binarios(const cola_binarios c);

/*
  Devuelve el elemento que está en el frente de `c`.
  Precondición: ! es_vacia_cola_binarios(c);
 */
binario frente(const cola_binarios c);

/*
  Libera la memoria asignada a `c`, pero NO la de sus elementos.
 */
void liberar_cola_binarios(cola_binarios &c);

#endif
