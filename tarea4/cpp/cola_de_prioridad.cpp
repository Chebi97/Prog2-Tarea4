#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"
#include "../include/pila.h"
#include "../include/cola_de_prioridad.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

struct node {
  lista list;
  prio_t prio;
};

struct rep_cola_prioridad {
  node *array_lista;
  nat cant;    //cantidad de elementos con distinta prioridad en la cola de prioridad
  nat size;    //tamanio (maxima cantidad de elementos con distinta prioridad en la cola)
  nat *indice; //indica cantidad de array_listaentos con cierta prioridad
};

typedef rep_cola_prioridad *cola_de_prioridad;

/* Constructoras */

/*
  Devuelve una `cola_de_prioridad` en la que puede haber hasta `tamanio'
  prioridades diferentes.
 */
cola_de_prioridad crear_cp(nat tamanio) {
  cola_de_prioridad res = new rep_cola_prioridad;
  res->array_lista = new node[tamanio];
  res->indice = new nat[tamanio];
  for (nat i = 0; i <= tamanio - 1; i++) {
    res->array_lista[i].list = crear_lista();
    res->array_lista[i].prio = 0;
    res->indice[i] = 0;
  }
  res->cant = 0;
  res->size = tamanio;
  return res;
}

static void insertar_en_cp_prio(const info_t i, prio_t p, cola_de_prioridad &c, nat cursor) {
   node n = c->array_lista[cursor];
   if (n.prio == p) {
     insertar_despues(i, final_lista(n.list), n.list);
   } else if(n.prio < p) {
     insertar_en_cp_prio(i, p, c, cursor*2 + 1);
     insertar_en_cp_prio(i, p, c, cursor*2 + 2);
   }
}

void insertar_en_cp(const info_t i, prio_t p, cola_de_prioridad &c) {
  if (hay_prioridad(p,c)) {
    insertar_en_cp_prio(i, p, c, 0);
  } else {
    nat lugar = c->cant;
    c->array_lista[lugar].list = crear_lista();
    insertar_despues(i, final_lista(c->array_lista[lugar].list), c->array_lista[lugar].list);
    c->array_lista[lugar].prio = p;
    while(c->array_lista[lugar].prio < c->array_lista[lugar/2].prio) {
      node aux = c->array_lista[lugar/2];
      c->array_lista[lugar/2] = c->array_lista[lugar];
      c->array_lista[lugar] = aux;
      lugar = lugar/2;
    }
    c->cant++;
  }
  c->indice[p-1]++; //en el valor p esta el siguiente, tenemos el cero en el array
}


//Devuelve true si el lugar del heap que se pregunta tiene algun elemento
static bool existe_lugar (nat l, cola_de_prioridad c) {
  bool res = ((l <= (c->size - 1)) && (!es_vacia_lista(c->array_lista[l].list)));
  return res;
}
//Devuelve true si existe al menos uno de los dos hijos.
static bool existe_hijo (nat lugar_p, cola_de_prioridad c) {
  bool res = (existe_lugar(lugar_p*2+1, c) || existe_lugar(lugar_p*2+2, c));
  return res;
}

/*Precodicion: existe al menos uno de los dos hijos.
 * Devuelve el lugar en el heap del hijo con menor prioridad
*/
static nat lugar_hmin (nat lugar_p, cola_de_prioridad c) {
  nat res;
  if(!existe_lugar(lugar_p*2+1, c)) {
    res = lugar_p*2+2;
  } else if (!existe_lugar(lugar_p*2+2, c)) {
    res = lugar_p*2+1;
  } else {
   if (c->array_lista[lugar_p*2+1].prio < c->array_lista[lugar_p*2+2].prio) {
     res = lugar_p*2+1;
   } else {
     res = lugar_p*2+2;
   }
 }
  return res;
}

/* Destructoras */

void eliminar_prioritario(cola_de_prioridad &c) {
  if (!es_vacia_cp(c)) {
    localizador in_list = inicio_lista(c->array_lista[0].list);
    if (c->indice[c->array_lista[0].prio - 1] > 1) { //contamos el cero xa prio en el array
      remover_de_lista(in_list, c->array_lista[0].list);
      c->indice[c->array_lista[0].prio - 1]--;
    } else {
      remover_de_lista(in_list, c->array_lista[0].list);
      nat prio_aux = c->array_lista[0].prio;
      if (c->cant == 1){
        c->array_lista[0].prio = 0;
      } else {
        c->array_lista[0].list = c->array_lista[c->cant - 1].list;
        c->array_lista[0].prio = c->array_lista[c->cant - 1].prio;
        c->array_lista[c->cant - 1].list = crear_lista();
        c->array_lista[c->cant - 1].prio = 0;
/*        nat lugar = 0;
        node aux;
          while(existe_hijo(lugar, c) &&
                c->array_lista[lugar].prio > c->array_lista[lugar_hmin(lugar, c)].prio) {
            aux = c->array_lista[lugar];
            c->array_lista[lugar] = c->array_lista[lugar_hmin(lugar, c)];
            c->array_lista[lugar_hmin(lugar, c)] = aux;
            lugar = lugar_hmin(lugar, c);
        }*/
      }
      c->cant--;
      c->indice[prio_aux - 1] = 0; //ya se que no me quedan mas de esta prio.
    } //siempre quiero reordenar el arbol. Si no hay que, no entra al while.
    nat lugar = 0;
    node aux;
      while(existe_hijo(lugar, c) &&
            c->array_lista[lugar].prio > c->array_lista[lugar_hmin(lugar, c)].prio) {
        aux = c->array_lista[lugar];
        nat hmin = lugar_hmin(lugar, c);
        c->array_lista[lugar] = c->array_lista[hmin];
        c->array_lista[hmin] = aux;
        lugar = hmin;
    }
  }
}

/*
  Libera la menoria asignada a `c` y a sus elementos.
 */
void liberar_cp(cola_de_prioridad &c) {
  nat i = 0;
  while(i > c->size) {
    liberar_lista(c->array_lista[i].list);
    i++;
  }
  delete [] c->array_lista;
  delete [] c->indice;
  delete c;
}

/* Predicados */


bool es_vacia_cp(const cola_de_prioridad c) {
  bool res = c->cant == 0;
  return res;
}


bool es_llena_cp(const cola_de_prioridad c) {
  bool res = c->cant == c->size;
  return res;
}


bool hay_prioridad(const prio_t p, const cola_de_prioridad c) {
  bool res = c->indice[p - 1] != 0;
  return res;
}

lista lista_en_cp(const prio_t p, const cola_de_prioridad c) {
  lista res = crear_lista();
  nat i = 0;
  if (hay_prioridad(p, c)) {
    liberar_lista(res);
    while (c->array_lista[i].prio != p){
      i++;
    }
    res = c->array_lista[i].list;
  }
  return res;
}

/*
  Devuelve el elemento prioritario de `c`.
  Precondición ! es_vacia_cola_de_prioridad(c).
  El tiempo de ejecución es O(1).
 */
info_t prioritario(const cola_de_prioridad c) {
  return info_lista(inicio_lista(c->array_lista[0].list), c->array_lista[0].list); //el final de la lista es el ultimo insertado. preciso inicio, mas prio
}

/*
  Devuelve el valor asociado al elemento prioritario.
  Precondición ! es_vacia_cola_de_prioridad(c),
  El tiempo de ejecución es O(1).
 */
prio_t valor_prioritario(const cola_de_prioridad c) {
  return c->array_lista[0].prio;
}
