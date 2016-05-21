/*
  Módulo de definición de `conjunto`.

  Se define un conjunto de elementos de tipo `info_t`.
  No puede haber dos elementos con el mismo dato de texto.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _CONJUNTO_H
#define _CONJUNTO_H

#include "texto.h"
#include "info.h"
#include "lista.h"

struct rep_conjunto; // representación de `conjunto`, definida en
                     // `conjunto.cpp`.
typedef rep_conjunto *conjunto;

/*
  Devuelve un conjunto vacío (sin elementos).
 */
conjunto crear_conjunto();

/*
  Devuelve un conjunto con los mismos elementos que están en `lst`.
  El conjunto devuelto no comparte memoria con `lst`.
  Precondición: los elementos de `lst` están en orden lexicográfico creciente
  estricto (esto es, creciente y no hay dos iguales) según sus datos de texto.
 */
conjunto construir_conjunto(const lista lst);

/*
  Incluye `i` en `c`.
  Si en `c` ya había un elemento con dato de texto igual al de `i` no hace nada.
  Devuelve `true` si se incluyó `i`, o `false` en otro caso.
 */
bool incluir(const info_t i, conjunto &c);

/*
  Excluye de `c` el elemento cuyo dato de texto es `t` y libera la memoria
  asignada a ese elemento.
  Si en `c` no había tal elemento no hace nada.
 */
void excluir(const texto_t t, conjunto &c);

/*
  Devuelve un conjunto con los elementos cuyos datos de texto pertenecen a `c1`
  y `c2`. El  dato numérico en el conjunto devuelto debe ser el del elemento 
  de `c1`-
  El conjunto devuelto no comparte memoria ni con `c1` no con `c2`.
  El tiempo de ejecucion es O(n1 + n2 + n.log n), siendo `n1` y
  `n2` la cantidad de elementos de `c1` y `c2` respectivamente y `n` la del
  conjunto resultado.
  Mientras en el conjunto devuelto no se hagan inserciones ni remociones las
  siguientes llamadas a `pertenece` deben ejecutarse en tiempo O(log n).
 */
conjunto interseccion(const conjunto c1, const conjunto c2);

/*
  Devuelve un conjunto con los elementos de `c1` cuyos datos de texto no
  pertenecen a `c2`.
  El conjunto devuelto no comparte memoria ni con `c1` no con `c2`.
  El tiempo de ejecucion es O(n1 + n2 + n.log n), siendo `n1` y
  `n2` la cantidad de elementos de `c1` y `c2` respectivamente y `n` la del
  conjunto resultado.
  Mientras en el conjunto devuelto no se hagan inserciones ni remociones las
  siguientes llamadas a `pertenece` deben ejecutarse en tiempo O(log n).
 */
conjunto diferencia(const conjunto c1, const conjunto c2);

/*
  Devuelve `true` si el dato de texto de algún elemento de `c` es igual a `t`,
  o `false` en otro caso.
 */
bool pertenece(const texto_t t, const conjunto c);

/*
  Devuelve `true` si `c` es vacío (no tiene elementos) o `false` en otro caso.
 */
bool es_vacio_conjunto(const conjunto c);

/*
  Libera la memoria asignada a `c` y la de todos sus elementos.
 */
void liberar_conjunto(conjunto &c);

#endif
