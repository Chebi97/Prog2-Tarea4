/*
  Módulo de definición de `utils`.

  Se define un tipo genérico, T.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _UTILS_H
#define _UTILS_H

enum comp_t { menor, igual, mayor }; // comparación

/*
 Imprime `<`, '=' o `>`  en la salida estándar si `comp` es `menor`, `igual`
 o `mayor`respectivamente.
 */
void imprimir_comp(const comp_t comp);

typedef unsigned int nat; // naturales

#endif
