/*
  Módulo de definición de `binario`.

  Se definen los árboles binarios de búsqueda de elementos de tipo `info_t`.
  La propiedad de orden de los árboles es definida por el dato de texto de sus
  elementos.

  También se definen los tipos `rama_t` para identificar una rama saliente de
  un nodo, y `camino_t` como una secuencia de identificadores de ramas
  consecutivas.

  DEFINICIÓN. Compatibilidad entre listas y caminos en árboles:
  Dados una lista `lst` y un camino `c` en un árbol decimos que `lst` y `c`
  son compatibles  si tienen la misma cantidad de nodos, y al recorrer `lst`
  desde el inicio hacia el final y `c` desde el origen hacia sus descendientes,
  el elemento de `lst` es igual al elemento de `c`. La igualdad de los
  elementos se puede exigir o bien en los datos numéricos, o bien en los
  datos de texto.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _BINARIO_H
#define _BINARIO_H

#include "utils.h"
#include "info.h"
#include "lista.h"

struct rep_binario; // representación de `binario`
typedef rep_binario *binario;

/* Constructoras */

/*
  Devuelve un binario vacío (sin elementos).
 */
binario crear_binario();

/*
  Inserta `i` en `b` respetando la propiedad de orden definida.
  Si en `b` ya hay un elemento cuyo dato de texto es texto_info(i) no se hace
  nada.
  Devuelve `true` si se insertó `i`, o `false` en otro caso.
 */
bool insertar_en_binario(const info_t i, binario &b);

/*
  Devuelve un árbol con copias de los elementos de `b` que cumplen la condición
  "numero_info(elemento) criterio clave".
  La estructura del árbol resultado debe ser análoga a la de `b`. Esto
  significa que dados dos nodos `U` y `V` de `b` en los que se cumple la
  condición y tal que `U` es ancestro de `V`, en el árbol resultado la copia de
  `U` debe ser ancestro de la copia de `V` cuando sea posible. Esto no siempre
  se puede lograr y al mismo tiempo mantener la propiedad de orden del árbol
  en el caso en el que en un nodo `V` no se cumple la condición y en sus dos
  subárboles hay nodos en los que se cumple. En este caso, la copia del nodo
  cuyo elemento es el mayor (según la propiedad de orden definida) de los que
  cumplen la condición en el subárbol izquierdo de `V` deberá ser ancestro de
  las copias de todos los descendientes de `V` que cumplen la condición.
  (Ver ejemplos en LetraTarea3.pdf).
  El árbol resultado no comparte memoria con `b`. *)
 */
binario crear_filtrado(const int clave, comp_t criterio, const binario b);

/* Destructoras */

/*
  Devuelve el elemento mayor (según la propiedad de orden definida) de `b`.
  Remueve el nodo en el que se localiza ese elemento (libera la memoria
  asignada al nodo, pero no la del elemento).
  Precondición: ! es_vacio_binario(b).
 */
info_t remover_mayor(binario &b);

/*
  Remueve de `b` el nodo en el que el dato de texto de su elemento es `t`.
  Si en ningún nodo se cumple esa condición no se hace nada.
  Si los dos subárboles del nodo a remover son no vacíos, en sustitución del
  elemento removido debe quedar el que es el mayor (segun la propiedad de orden
  definida) en el subárbol izquierdo.
  Libera la memoria del nodo y del elemento.
 */
void remover_de_binario(const texto_t t, binario &b);

/*
  Libera la memoria asociada a `b` y todos sus elementos.
 */
void liberar_binario(binario &b);

/* Predicados */

/*
  Devuelve `true` si `b` es vacío (no tiene elementos), o `false` en otro caso.
 */
bool es_vacio_binario(const binario b);

/* Selectoras */

/*
  Devuelve el elemento asociado a la raíz de `b`.
  Precondición: ! es_vacio_binario(b).
 */
info_t raiz_binario(const binario b);

/*
  Devuelve el subárbol izquierdo de  `b`.
  Precondición: ! es_vacio_binario(b).
 */
binario izquierdo(const binario b);

/*
  Devuelve el subárbol derecho de  `b`.
  Precondición: ! es_vacio_binario(b).
 */
binario derecho(const binario b);

/*
  Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo dato de
  texto es `t`.
  Si `t` no pertenece a `b`, devuelve el árbol vacío.
 */
binario buscar_subarbol(const texto_t t, const binario b);

/*
  Devuelve la altura de `b`.
  La altura de un árbol vacío es 0.
 */
nat altura_binario(const binario b);

/*
  Devuelve la cantidad de nodos de `b`.
 */
nat cantidad_binario(const binario b);

/*
  Devuelve la cantidad de caminos de `b` que empiezan en la raíz y terminan en
  una hoja que son compatibles con `l` en los datos numéricos.
  */
nat cantidad_de_caminos(const lista l, const binario b);

/*
  Identifica una rama saliente de un nodo, es decir que indica si en un
  camino desde un nodo hacia sus descendientes se debe elegir la rama
  izquierda o la rama derecha.
 */
enum rama_t { izq, der };
typedef rama_t *array_rama;

/*
  Secuencia de ramas que representan un camino en un árbol desde un nodo hasta
  uno de sus descendientes.
  El camino puede existir o no, lo cual es indicado en el campo `existe`.
  Si un camino existe la cantidad de ramas es `cantidad_ramas`, y van
  desde ramas[0] hasta  ramas[cantidad - 1].
  Un camino de un solo nodo existe y en él `cantidad_ramas` es igual a 0 y
  la secuencia de ramas es vacía.
  En un camino que no existe los campos `ramas` y `cantidad_ramas` no son
  tenidos en cuenta.
 */
struct camino_t {
  bool existe;
  array_rama ramas;
  nat cantidad_ramas;
};

/*
  Devuelve un `texto_t` formado por `c.cantidad` seguido de `-` y entre
  paréntesis las ramas separadas entre sí por `,` si el camino exite, o
  "No existe" en otro caso.
  Las ramas se identifican con `I` o `D` si son `izq` o `der` respectivamente.
  Ejemplos:
  No existe
  0-()
  2-(I,D)
 */
texto_t camino_a_texto(const camino_t c);

/*
  Devuelve un `camino_t` con la secuencia de indicaciones a seguir para
  recorrer el camino de `b` que empieza en la raíz y termina en una hoja y
  es compatible con `l` en los datos de texto.
  Si no hay camino que cumpla lo pedido, el campo `existe` del resultado debe
  ser `false`.
 */
camino_t buscar_camino(const lista l, const binario b);

/* Salida */

/*
  Imprime los elementos de `b`, uno por línea, en orden descendente de la
  propiedad de orden de los árboles `binario`.
  Antes del elemento imprime una cantidad de guiones igual a su nivel.
  El elemento se imprime según la especificación dada en `info_a_texto`.
  El nivel de la raíz es 0.
 */
void imprimir_binario(const binario b);

#endif
