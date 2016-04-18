/*
  Módulo de definición de `texto`.

  'texto_t' es un puntero a una estructura (opaca, que debe definirse en
  texto.cpp) cuyo contenido es un texto (arreglo de elementos de tipo char).

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _TEXTO_H
#define _TEXTO_H

#include "utils.h"

/* representación de `texto`, definida en texto.cpp */
struct rep_texto;

/* El tipo `texto_t` es un puntero a elementos de tipo `rep_texto`. */
typedef rep_texto *texto_t;

/* **************  NUEVO  ************** */

/*
  Devuelve el resultado de convertir el contenido de `t` en comp_t.
  Precondición: el contenido de `t` es `<`, `=` o `>`.
 */
comp_t texto_a_comp(const texto_t txt);

/*
  Devuelve un `texto` cuyo contenido es vacío (de longitud 0).
 */
texto_t texto_vacio();

/*
  Devuelve un `texto` cuyo contenido es `simbolo`.
 */
texto_t char_a_texto(const char simbolo);

/*
  Devuelve un `texto` cuyo contenido es una copia de `cadena`.
  El elemento devuelto no comparte memoria con `cadena`.
  Precondición: `cadena != NULL`.
 */
texto_t cadena_a_texto(const char *cadena);

/*
  Devuelve un `texto` leído desde la entrada estándar luego de ignorar los
  espacios en blanco iniciales.
  Lee hasta encontrar un espacio en blanco.
  Precondición: la palabra tiene a lo sumo `max` caracteres.
 */
texto_t leer_palabra(const nat max);

/*
  Devuelve un `texto` leído desde la entrada estándar.
  Lee hasta encontrar el carácter de `fin de línea` o de `fin de archivo`.
  Ese carácter es leído pero no se incluye en el `texto` devuelto.
  Precondición: la línea tiene a lo sumo `max` caracteres, incluido el 'fin de
  línea' o 'fin de archivo'.
 */
texto_t leer_resto_linea(const nat max);

/*
  Escribe en la salida estándar el contenido de `t`.
 */
void escribir_texto(const texto_t t);

/*
  Inserta en la salida estándar `nueva línea` (inserta una línea y mueve el
  cursor a la primera columna de la línea insertada).
 */
void escribir_nueva_linea();

/*
  Devuelve un `texto` cuyo contenido es la concatenación de las copias de
  los de `t1` y `t2`.
  El elemento devuelto no comparte memoria ni con `t1` ni con `t2`.
 */
texto_t concatenar_texto(const texto_t t1, const texto_t t2);

/*
  Devuelve un `texto` cuyo contenido es una copia del de `t`.
  El elemento devuelto no comparte memoria con `t`.
 */
texto_t copiar_texto(const texto_t t);

/*
  Devuelve `true` si `t` es vacío o `false` en otro caso.
 */
bool es_texto_vacio(const texto_t t);

/*
  Devuelve la longitud del contenido de `t`.
 */
nat longitud_texto(const texto_t t);

/*
  Devuelve el resultado de la comparación lexicográfica de los contenidos de
  `t1` y `t2`.
 */
comp_t comparar_texto(const texto_t t1, const texto_t t2);

/*
  Devuelve el resultado de convertir el contenido de `t` en un entero.
 */
int texto_a_int(const texto_t t);

/*
 Devuelve el resultado de convertir `i` a texto_t.
 */
texto_t int_a_texto(const int i);

/*
  Libera la memoria asignada a `t`.
 */
void liberar_texto(texto_t &t);

#endif
