/*
  Módulo de implementación de 'info'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/info.h"
#include "../include/texto.h"

#include <stdio.h>
#include <assert.h>
#include <limits.h>

struct rep_info {
  int numero;
  texto_t texto;
};

info_t crear_info(const int n, const texto_t t) {
  info_t res = new rep_info;
  res->numero = n;
  res->texto = t;
  return res;
}

info_t copiar_info(const info_t i) {
  return crear_info(i->numero, copiar_texto(i->texto));
}

void liberar_info(info_t &i) {
  liberar_texto(i->texto);
  delete (i);
}

int numero_info(const info_t i) { return i->numero; }

texto_t texto_info(const info_t i) { return i->texto; }

bool es_valida_info(const info_t i) { return i->numero != INT_MAX; }

/*
  Devuelve un texto_t formado por la concatenacion del dato numerico de `i`,
  el string "," y el dato de texto de `i` encerrados entre parentesis.
  El elemento devuelto no comparte memoria con `i`.
   Ejemplos:
   (4,a)
   (56,jojo)
 */
texto_t info_a_texto(const info_t i) {
  texto_t res;
  texto_t tmp1, tmp2, tmp3;

  texto_t abre_p = char_a_texto('(');
  texto_t cierra_p = char_a_texto(')');
  texto_t coma = char_a_texto(',');

  texto_t entero = int_a_texto(i->numero);
  texto_t texto = copiar_texto(i->texto);

  tmp1 = concatenar_texto(abre_p, entero);
  tmp2 = concatenar_texto(tmp1, coma);
  tmp3 = concatenar_texto(tmp2, texto);
  res = concatenar_texto(tmp3, cierra_p);
  liberar_texto(tmp1);
  liberar_texto(tmp2);
  liberar_texto(tmp3);

  liberar_texto(abre_p);
  liberar_texto(cierra_p);
  liberar_texto(coma);
  liberar_texto(entero);
  liberar_texto(texto);
  return res;
}

/*
  Lee texto desde la entrada estándar. Si tiene formato de `info_t` (ver
  info_a_texto) lo devuelve convertido en `info_t`. En otro caso devuelve una
  `info_t` con un  dato numérico = INT_MAX y dato de texto vacío.
  Precondición: hay texto para leer, que no incluye el símbolo ')' y tiene a
  lo sumo `max` caracteres.
 */
info_t leer_info(nat max) {
  info_t res;
  int num;
  char abre;
  char cadena[max];
  scanf(" %c", &abre);
  if (abre != '(') {
    // Si el primer símbolo NO es un paréntesis de apertura entonces lo que
    // se está leyendo no cumple el formato.
    res = crear_info(INT_MAX, cadena_a_texto(""));
  } else {
    // busca un entero (que aloja en `num`), una coma, una cadena que no
    // incluya el paréntesis de cierre (que aloja en `cadena`) y un
    // paréntesis de cierre.
    scanf("%d,%[^)]) ", &num, cadena);
    res = crear_info(num, cadena_a_texto(cadena));
  }
  return res;
}
