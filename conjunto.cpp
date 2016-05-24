/*
  Módulo de definición de `conjunto`.

  Se define un conjunto de elementos de tipo `info_t`.
  No puede haber dos elementos con el mismo dato de texto.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */


 #include "../include/utils.h"
 #include "../include/texto.h"
 #include "../include/info.h"
 #include "../include/lista.h"
 #include "../include/binario.h"


 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <assert.h>

struct rep_conjunto{
  binario arbol;
};


/*
  Devuelve un conjunto vacío (sin elementos).
 */
conjunto crear_conjunto(){
  conjunto res = new rep_conjunto;
  res->arbol = crear_binario();
  return res;
}

/*
  Devuelve un conjunto con los mismos elementos que están en `lst`.
  El conjunto devuelto no comparte memoria con `lst`.
  Precondición: los elementos de `lst` están en orden lexicográfico creciente
  estricto (esto es, creciente y no hay dos iguales) según sus datos de texto.
 */
conjunto construir_conjunto(const lista lst){
  conjunto c = crear_conjunto();
  binario balanceado = crear_balanceado(lst);
  c->arbol = balanceado;
  return c;
}

/*
  Incluye `i` en `c`.
  Si en `c` ya había un elemento con dato de texto igual al de `i` no hace nada.
  Devuelve `true` si se incluyó `i`, o `false` en otro caso.
 */
bool incluir(const info_t i, conjunto &c){
  bool res = insertar_en_binario(i, c->arbol);
  return res;
}

/*
  Excluye de `c` el elemento cuyo dato de texto es `t` y libera la memoria
  asignada a ese elemento.
  Si en `c` no había tal elemento no hace nada.
 */
void excluir(const texto_t t, conjunto &c){
  remover_de_binario(t, c->arbol);
}

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

static void interseccion_aux(binario b, conjunto c, conjunto &res){
  bool ains = false;
  if (!es_vacio_binario(b)){
    ains = pertenece(texto_info(raiz_binario(b)), c);
    if (ains) {
      insertar_en_binario (raiz_binario(b), res->arbol);
    }
    interseccion_aux(izquierdo(b), c, res);
    interseccion_aux(derecho(b), c, res);
  }
}

conjunto interseccion(const conjunto c1, const conjunto c2){
  conjunto res =  crear_conjunto();
  interseccion_aux(c1->arbol, c2, res);
  return res;
}

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

static void diferencia_aux(binario b, conjunto c, conjunto &res){
   bool ains = false;
   if (!es_vacio_binario(b)){
     ains = pertenece(texto_info(raiz_binario(b)), c);
     if (!ains) {
       insertar_en_binario (raiz_binario(b), res->arbol);
     }
     diferencia_aux(izquierdo(b), c, res);
     diferencia_aux(derecho(b), c, res);
   }
 }
conjunto diferencia(const conjunto c1, const conjunto c2){
  conjunto res = crear_conjunto();
  diferencia_aux(c1->arbol, c2, res);
  diferencia_aux(c2->arbol, c1, res);
  return res;
}

/*
  Devuelve `true` si el dato de texto de algún elemento de `c` es igual a `t`,
  o `false` en otro caso.
 */
bool pertenece(const texto_t t, const conjunto c){
  bool res = false;
  if (!es_vacio_conjunto(c)){
    binario resaux = buscar_subarbol(t, c->arbol);
    if (!es_vacio_binario(res_aux))
      res = true
    }
  return res;
}

/*
  Devuelve `true` si `c` es vacío (no tiene elementos) o `false` en otro caso.
 */
bool es_vacio_conjunto(const conjunto c){return (c == NULL || c->arbol == NULL)}

/*
  Libera la memoria asignada a `c` y la de todos sus elementos.
 */
void liberar_conjunto(conjunto &c){
  liberar_binario(c->arbol);
  delete c;
}
