/*
  Módulo de implementación de 'texto'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/texto.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

/*
  Se define `array_char` como un alias de `char *`, y representa los arrays de
  caracteres cuya dimensión es determinada en tiempo de ejecución.
  Los arrays son de tipo puntero a algo porque su valor es la dirección de
  memoria del primer elemento del array.
 */
typedef char *array_char;

/*
  Aquí se define la representación de `rep_texto`.
  Por lo tanto, `texto_t` es un puntero a un array de caracteres.
 */
struct rep_texto {
  array_char caracteres;
};

comp_t texto_a_comp(const texto_t txt) {
  // el texto tiene longitud 1
  assert(txt->caracteres[1] == '\0');
  // el único símbolo es un operador de comparación
  assert((txt->caracteres[0] == '<') || (txt->caracteres[0] == '=') ||
         (txt->caracteres[0] == '>'));

  comp_t res;
  if (strcmp(txt->caracteres, "<") == 0)
    res = menor;
  else if (strcmp(txt->caracteres, ">") == 0)
    res = mayor;
  else
    res = igual;
  return res;
}

texto_t texto_vacio() {
  /* El resultado es de tipo `texto_t` que es un puntero a un elemento de tipo
     `rep_texto`. Por lo tanto se necesita pedir memoria. */
  texto_t res = new rep_texto;
  res->caracteres = new char[1];
  res->caracteres[0] = '\0';
  return res;
}

texto_t char_a_texto(const char simbolo) {
  texto_t res = new rep_texto;

  /* Se necesita un array de al menos dos elementos.
     En el primero va `símbolo` y en el segundo el carácter que indica el fin
     la cadena, que es '\0';
  */
  res->caracteres = new char[2];

  /* El índice del array donde está el primer elemento es el 0. */
  res->caracteres[0] = simbolo;
  res->caracteres[1] = '\0';
  return res;
}

texto_t cadena_a_texto(const char *cadena) {
  texto_t res = new rep_texto;
  res->caracteres = new char[strlen(cadena) + 1];
  strcpy(res->caracteres, cadena);
  return res;
}

texto_t leer_palabra(const nat max) {
  texto_t res = new rep_texto;
  res->caracteres = new char[max + 1];
  scanf("%s", res->caracteres);
  return res;
}

texto_t leer_resto_linea(const nat max) {
  texto_t res = new rep_texto;

  /* Se reserva un espacio extra para el carácter de fin de cadena.*/
  res->caracteres = new char[max + 1];

  /* stdin es la entrada estándar.
     fgets lee `max - 1` caracteres o hasta enconrtrar el fin de línea (o fin
     de archivo) y los almacena en `res->caracteres`.
     Ver http://www.cplusplus.com/reference/cstdio/fgets/
  */
  fgets(res->caracteres, max, stdin);

  /* Se sustituye el carácter de fin de linea ('\n') por el de fin de cadena. */
  res->caracteres[strlen(res->caracteres) - 1] = '\0';

  return res;
}

void escribir_texto(const texto_t t) { fputs(t->caracteres, stdout); }

void escribir_nueva_linea() { fputs("\n", stdout); }

texto_t concatenar_texto(const texto_t t1, const texto_t t2) {
  texto_t res = new rep_texto;
  res->caracteres =
      new char[strlen(t1->caracteres) + strlen(t2->caracteres) + 1];
  strcpy(res->caracteres, t1->caracteres);
  strcat(res->caracteres, t2->caracteres);
  return res;
}

texto_t copiar_texto(const texto_t t) {
  texto_t res = new rep_texto;
  res->caracteres = new char[strlen(t->caracteres) + 1];
  strcpy(res->caracteres, t->caracteres);
  return res;
}

bool es_texto_vacio(const texto_t t) { return (strlen(t->caracteres) == 0); }

nat longitud_texto(const texto_t t) { return strlen(t->caracteres); }

comp_t comparar_texto(const texto_t t1, const texto_t t2) {
  comp_t res;
  int rint = strcmp(t1->caracteres, t2->caracteres);
  if (rint < 0) {
    res = menor;
  } else if (rint == 0) {
    res = igual;
  } else {
    res = mayor;
  }
  return res;
}

int texto_a_int(const texto_t t) { return (nat)atoi(t->caracteres); }

texto_t int_a_texto(const int i) {
  /* Con 10 caracteres se puede representar hasta el 9.999.999.999, que es
     mayor que 2^34, mientras que con cuatro bytes solo se puede representar
     desde -2^{31} (- 2 a la 31) hasta 2^{31} - 1 (2 a la 31 - 1).  */
  char caracteres[11];

  /* Se "imprime" `i` en el array `caracteres`.*/
  sprintf(caracteres, "%d", i);

  /* Se convierte el array a un elemento de tipo texto_t usando la función
     definida anteriormente. */
  return cadena_a_texto(caracteres);
}

void liberar_texto(texto_t &t) {
  /* Se libera la memoria pedida para el array `caracteres`, por ejemplo
     res->caracteres = new char[max+1];
     en leer_resto_linea.  */
    delete[] t->caracteres;
   /* Se libera la memoria pedida para `t`, por ejemplo
     texto_t res = new rep_texto;  */
  
    delete t;
 
}