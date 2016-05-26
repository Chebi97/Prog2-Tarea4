
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
 #include "../include/conjunto.h"


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

conjunto interseccion(const conjunto c1, const conjunto c2){
  conjunto res =  crear_conjunto();
  lista l1 = linealizacion(c1->arbol);
  lista l2 = linealizacion(c2->arbol);
  lista aux = crear_lista();
  localizador loc1 = inicio_lista(l1);
  localizador loc2 = inicio_lista(l2);
  while (es_localizador_lista(loc1) && es_localizador_lista(loc2)){
    comp_t comparacion = comparar_texto(texto_info(info_lista(loc1, l1)), texto_info(info_lista(loc2, l2)));
     switch (comparacion) {
      case igual: {
        insertar_despues(info_lista(loc1, l1), final_lista(aux), aux);
        loc2 = siguiente(loc2, l2);
        loc1 = siguiente(loc1, l1);
        break;
      }
      case mayor: {
        loc2 = siguiente(loc2, l2);
        break;
      }
      case menor: {
        loc1 = siguiente(loc1, l1);
        break;
      }
    }
  }
  conjunto c = crear_conjunto();   // me parece que este linea es necesaria, aviso que la agregue
  c->arbol = crear_balanceado(aux);
  liberar_lista(l1);
  liberar_lista(l2);
  liberar_lista(aux);
  return c;
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

conjunto diferencia(const conjunto c1, const conjunto c2){
  conjunto res =  crear_conjunto();
  lista l1 = linealizacion(c1->arbol);
  lista l2 = linealizacion(c2->arbol);
  lista aux = crear_lista();
  localizador loc1 = inicio_lista(l1);
  localizador loc2 = inicio_lista(l2);
  while (es_localizador_lista(loc1) && es_localizador_lista(loc2)){
    comp_t comparacion = comparar_texto(texto_info(info_lista(loc1, l1)), texto_info(info_lista(loc2, l2)));
     switch (comparacion) {
      case igual: {
        loc2 = siguiente(loc2, l2);
        loc1 = siguiente(loc1, l1);
        break;
      }
      case mayor: {
        loc2 = siguiente(loc2, l2);
        break;
      }
      case menor: {
        insertar_despues(info_lista(loc1, l1), final_lista(aux), aux);
        loc1 = siguiente(loc1, l1);
        break;
      }
    }
  }
  if (es_localizador_lista(loc1)){
      while (es_localizador_lista){
          insertar_despues(info_lista(loc1, l1), final_lista(aux), aux);
          loc1 = siguiente(loc1, l1);
    }
  }
  conjunto c = crear_conjunto();         //aca lo mismo
  c->arbol = crear_balanceado(aux);
  liberar_lista(l1);
  liberar_lista(l2);
  liberar_lista(aux);
  return c;

}

/*
  Devuelve `true` si el dato de texto de algún elemento de `c` es igual a `t`,
  o `false` en otro caso.
 */
bool pertenece(const texto_t t, const conjunto c) {
  bool res = false;
  if (!es_vacio_conjunto(c)) {
    binario resaux = buscar_subarbol(t, c->arbol);
    if (!es_vacio_binario(resaux))
      res = true;
  }
  return res;
}

/*
  Devuelve `true` si `c` es vacío (no tiene elementos) o `false` en otro caso.
 */
bool es_vacio_conjunto(const conjunto c) {return (c == NULL || c->arbol == NULL);}

/*
  Libera la memoria asignada a `c` y la de todos sus elementos.
 */
void liberar_conjunto(conjunto &c){
  liberar_binario(c->arbol);
  delete c;
}
