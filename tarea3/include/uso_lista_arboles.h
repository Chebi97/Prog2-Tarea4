/*
  Módulo de definición de `uso_lista_arboles`.

  Se definen funciones sobre listas y árboles.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _USO_LISTA_ARBOLES_H
#define _USO_LISTA_ARBOLES_H

#include "utils.h"
#include "texto.h"
#include "info.h"
#include "lista.h"
#include "binario.h"
#include "finitario.h"

/*
  Devuelve `true` si en `lst` hay un elemento cuyo dato numérico es `i`,
  o `false` en otro caso.
 */
bool pertenece(const int i, const lista lst);

/*
  Devuelve la cantidad de elementos de `lst`.
 */
nat longitud(const lista lst);

/*
  Devuelve la cantidad de elementos de `lst` cuyo dato numérico es `i`.
 */
nat cantidad(const int i, const lista lst);

/*
  Devuelve `true` si los datos numéricos de los elementos de `l1` son iguales
  uno a uno con los de los elementos de `l2` (es decir, son los mismos números
  y en el mismo orden), o `false` en otro caso.
  Si es_vacia_lista(l1) y es_vacia_lista(l2) devuelve `true`.
 */
bool son_numeros_iguales(const lista l1, const lista l2);

/*
  Devuelve `true` si `lst` está ordenada de forma no decreciente (= creciente de
  manera no estricta) según  los datos numéricos de sus elementos, o `false`
  en otro caso.
  Si es_vacia_lista (lst), devuelve `true`.
 */
bool esta_ordenada(const lista lst);

/*
  Devuelve el resultado de concatenar `l2` después de `l1`.
  La lista resultado no comparte memoria ni con `l1` ni con `l2`.
 */
lista concatenar(const lista l1, const lista l2);

/*
  Devuelve la lista que tiene todos los elementos de `lst` pero en orden
  inverso.
  La lista resultado no comparte memoria con `lst`.
 */
lista reversa(const lista lst);

/*
  Devuelve el localizador que accede al primer elemento, empezando desde el
  inicio de `lst` y anterior a `loc`, cuyo dato numérico es mayor que el del
  elemento que se accede desde `loc`.
  Si ninguno de los elementos anteriores es mayor devuelve `loc`.
  Precondición: ! es_vacia_lista (lst), pertenece_localizador_lista (loc, lst)
  y `lst` está ordenada de manera creciente (no estricta) según su dato
  numérico desde el inicio hasta el anterior a `loc`.
 */
localizador primer_mayor(const localizador loc, const lista lst);

/*
  Mueve el elemento al que se accede con `loc` dejéndolo inmediatamente antes
  de los elementos cuyos datos numéricos son mayores que dicho elemento.
  El valor de `loc` queda ideterminado.
  Si el dato numérico de `loc` es mayor o igual que el los de los que lo
  preceden no hace nada.
  Precondición: ! es_vacia_lista (lst), pertenece_localizador_lista (loc, lst)
  y `lst` está ordenada de manera creciente (no estricta) según su dato
  numérico desde el inicio hasta el anterior a `loc`.
 */
void retroceder(localizador loc, lista &lst);

/*
  Se ordena `lst` de manera creciente según los datos numéricos de sus
  elementos.
  Si los datos numéricos de dos elementos son iguales, se mantiene el orden
  relativo que tenían dichos elementos inicialmente.
  No se debe obtener ni devolver memoria de manera dinámica.
  Si es_vacia_lista (lst) no hace nada.
 */
void ordenar(lista &lst);

/*
  Elimina los elementos con datos numéricos repetidos, conservando el primero
  de ellos.
  Libera la memoria de los elementos que elimina.
  Precondición: esta_ordenada (lst).
 */
void unificar(lista &lst);

/*
  Devuelve una lista con todos los elementos de `l1` y `l2` ordenada de manera
  creciente segun sus datos numéricos.
  Si hay elementos cuyos datos numéricos son iguales, los elementos de `l1`
  quedan antes de los de `l2`.
  La lista resultado no comparte memoria ni con `l1` ni con `l2`.
  Precondición: esta_ordenada (l1) y esta_ordenada (l2).
 */
lista mezcla(const lista l1, const lista l2);

/*
  Cambia todas las ocurrencias de `original` por `nuevo` en los elementos
   de `lst`. No debe quedar memoria inaccesible.
 */
void cambiar_todos(const int original, const int nuevo, lista &lst);

/*
  Devuelve una lista con los elementos que cumplen
  "numero_info (elemento) criterio clave".
  El orden relativo de los elementos en la lista resultado debe ser el mismo
  que en `lst`.
  Si es_vacia_lista (lst), `clave` y `criterio` son ignorados, y se devuelve la
  lista vacía.
  La lista resultado no comparte memoria con `lst`.
 */
lista filtrado(const int clave, const comp_t criterio, const lista lst);

/*
  Devuelve la lista de elementos de `lst` que cumplen
  "menor <= numero_info (elemento) <= mayor".
  El orden relativo de los elementos en la lista resultado debe ser el mismo
  que en `lst`.
  La lista resultado no comparte memoria con `lst`.
  Precondición: esta_ordenada (lst), `menor` <= `mayor`,
  pertenece (menor, lst), pertenece (mayor, lst).
 */
lista sublista(const nat menor, const nat mayor, const lista lst);

/*
  Imprime los elementos de `lst` de la siguiente forma:
  (dn de pos1,dt de pos1)(dn de pos2,dt de pos2)(dn de pos3,dt de pos3) ...
  donce `dn` es el dato numérico y `dt` es el dato de texto.
  Antes de terminar, se debe imprimir un fin de linea.
  Si es_vacia_lista(lst) solo se imprime el fin de línea.
 */
void imprimir_lista(const lista lst);

/*
  Devuelve el subárbol que tiene como raíz al nodo que, según la propiedad de
  orden de los árboles `binario`, está en el k-ésimo lugar de `b`.
  Precondición: 1 <= k <= cantidad_binario(b).
 */
binario kesimo_subarbol(const nat k, const binario b);

/*
  Imprime cada nivel de `f`, en orden creciente de nivel, segun
  criterios y formatos descriptos en `nivel` y en `imprimir_lista`.
  Si es_vacio_finitario(f) solo se imprime el fin de línea.
 */
void imprimir_finitario(const finitario f);

#endif
