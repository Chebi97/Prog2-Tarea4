/*
  Módulo de definición de `info`.

  `info_t` es un puntero a una estructura (que debe definirse en
  info.cpp) cuyo contenido es un dato numérico (entero) y un dato de texto.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _INFO_T
#define _INFO_T

#include "utils.h"
#include "texto.h"

struct rep_info; // representación de `info`, definida en info.cpp
typedef rep_info *info_t;

/* Constructora, destructura y selectoras de info_t. */

/*
  Devuelve un info_t tal que su dato numérico es `n` y su dato de texto
  es `t`.
 */
info_t crear_info(const int n, const texto_t t);

/*
  Devuelve una copia de `i`.
  El elemento devuelto no comparte memoria con `i`.
 */
info_t copiar_info(const info_t i);

/*
  Libera la memoria reservada por `i`.
 */
void liberar_info(info_t &i);

/*
  Devuelve el dato numérico asociado a `i`.
 */
int numero_info(const info_t i);

/*
  Devuelve el dato de texto asociado a `i`.
 */
texto_t texto_info(const info_t i);

/*
  Devuelve `true` si `i` es válida o `false` en otro caso.
  `i` no es válida cuando su valor numérico es INT_MAX.
 */
bool es_valida_info(const info_t i);

/*
  Devuelve un texto_t formado por la concatenacion del dato numérico de `i`,
  el string "," y el dato de texto de `i` encerrados entre parentesis.
  El elemento devuelto no comparte memoria con `i`.
   Ejemplos:
   (4,a)
   (56,jojo)
 */
texto_t info_a_texto(const info_t i);

/*
  Lee texto desde la entrada estándar. Si tiene formato de `info_t` (ver
  info_a_texto) lo devuelve convertido en `info_t`. En otro caso devuelve una
  `info_t` con un  dato numérico = INT_MAX y dato de texto vacío.
  Precondición: hay texto para leer, que no incluye el símbolo ')' y tiene a
  lo sumo `max` caracteres.
 */
info_t leer_info(nat max);

#endif
