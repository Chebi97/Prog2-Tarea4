/*
  Módulo de implementación de 'lista'.
  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/lista.h"
#include "../include/info.h"

#include <stddef.h>

// nodo con punteros al anterior y al siguiente
struct nodo {
  info_t dato;
  nodo *anterior;
  nodo *siguiente;
};

// lista implementada con cabecera con punteros al incio y al final
struct rep_lista {
  nodo *inicio;
  nodo *final;
};

lista crear_lista() {
  // se obtiene espacio para la cabecera
  // la lista vacía no es NULL
  lista res = new rep_lista;
  res->inicio = res->final = NULL;
  return res;
}

void insertar_antes(const info_t i, const localizador loc, lista &lst) {
  nodo *nuevo = new nodo;
  nuevo->dato = i;
  if (es_vacia_lista(lst)) {
    // nuevo es el único nodo, por lo que es el inicio y el final
    lst->inicio = lst->final = nuevo;
    nuevo->anterior = nuevo->siguiente = NULL;
  } else {
    nuevo->siguiente = loc;
    nuevo->anterior = loc->anterior;
    loc->anterior = nuevo;

    if (loc == lst->inicio)
      lst->inicio = nuevo;
    else
      nuevo->anterior->siguiente = nuevo;
  }
}

void insertar_despues(const info_t i, const localizador loc, lista &lst) {
  nodo *nuevo = new nodo;
  nuevo->dato = i;
  if (es_vacia_lista(lst)) {
    lst->inicio = lst->final = nuevo;
    nuevo->anterior = nuevo->siguiente = NULL;
  } else {
    nuevo->anterior = loc;
    nuevo->siguiente = loc->siguiente;
    loc->siguiente = nuevo;

    if (loc == lst->final)
      lst->final = nuevo;
    else
      nuevo->siguiente->anterior = nuevo;
  }
}

lista segmento_lista(const localizador desde, const localizador hasta,
                     const lista lst) {
  lista res = crear_lista();
  if (!es_vacia_lista(lst)) {
    localizador loc = desde;
    while (loc != hasta->siguiente) {
      // ERROR: compartiría memoria
      // info_t info = loc->dato;

      // ERROR: compartiría memoria
      // info_t info = crear_info(numero_info(loc->dato),
      // texto_info(loc->dato));

      info_t info = crear_info(numero_info(loc->dato),
                               copiar_texto(texto_info(loc->dato)));
      insertar_despues(info, final_lista(res), res);
      loc = siguiente(loc, lst);
    }
  }
  return res;
}

bool es_localizador_lista(const localizador loc) { return loc != NULL; }

bool localizador_pertenece_a_lista(const localizador loc, const lista lst) {
  bool res = false;
  localizador cursor = lst->inicio;
  while ((!res) && (es_localizador_lista(cursor))) {
    if (cursor == loc)
      res = true;
    else
      cursor = cursor->siguiente;
  }
  return res;
}

localizador siguiente_clave(const int clave, const localizador loc,
                            const lista lst) {
  localizador res;
  if (es_vacia_lista(lst))
    res = NULL;
  else {
    res = loc;
    bool encontrado = false;
    while ((!encontrado) && (res != NULL)) {
      if (numero_info(res->dato) == clave)
        encontrado = true;
      else
        res = res->siguiente;
    }
  }
  return res;
}

localizador anterior_clave(const int clave, const localizador loc,
                           const lista lst) {
  localizador res;
  if (es_vacia_lista(lst)){
    res = NULL;
  }
  else {
    res = loc;
    bool encontrado = false;
    while ((!encontrado) && (res != NULL)) {
      if (numero_info(res->dato) == clave) {
        encontrado = true;
      }
      else
        res = res->anterior;
    }
  }
  return res;
}


void mover_antes(localizador loc1, localizador loc2, lista &lst) {
  // En esta versión no se solicita memoria para crear nodos, sino que
  // se mueve todo el nodo que es accedido con `loc2`.
  if (loc1 != loc2) {
    // La creación de una lista requiere espacio para la cabecera que habrá
    // que liberar al final.
    lista sgm = separar_segmento(loc2, loc2, lst);

    // El segemento (de un elemento) se inserta antes de `loc1`.
    // Es lo que se haría si existiera la funcióm insertar_segmento_antes
    // excepto en que acá no es necesario contemplar el caso en que la lista
    // es vacía ya que se sabe que loc1 != loc2
    sgm->inicio->anterior = loc1->anterior;
    sgm->final->siguiente = loc1;
    if (es_inicio_lista(loc1, lst)) {
      lst->inicio = sgm->inicio;
    } else {
      loc1->anterior->siguiente = sgm->inicio;
    }
    loc1->anterior = sgm->final;

    // Se libera la memoria de la cabecera de la lista, ya vacía.
    delete sgm;
  }
}


void insertar_segmento_despues(lista &sgm, const localizador loc, lista &lst) {
  if (es_vacia_lista) {
    lst = sgm;
  }
  else {
    loc->siguiente->anterior = sgm->final;
    sgm->final->siguiente = loc->siguiente;
    loc->siguiente = sgm->inicio;
    sgm->inicio->anterior = loc;
  }
  sgm->inicio = NULL;
  sgm->final = NUL;
}

lista separar_segmento(localizador desde, localizador hasta, lista &lst) {
  lista res = NULL;
  if (!es_lista_vacia(lst)) {
    res->inicio = desde;
    res->final = hasta;

    desde->anterior->siguiente = hasta->siguiente;
    hasta->siguiente->anterior = desde->anterior;

    res->inicio->anterior = NULL;
    res->final->siguiente = NULL;
  }
  return res;
}

void remover_de_lista(localizador &loc, lista &lst) {
  delete[] loc->dato->texto->caracteres;
  loc->siguiente->anterior = loc->anterior;
  loc->anterior->siguiente = loc->siguiente;
  delete loc;
}

void liberar_lista(lista &lst) {
  if (!es_vacia_lista(lst)) {

    localizador aux = lst->inicio;
    delete[] aux->dato->texto->caracteres;

    while (siguiente(aux, lst) != NULL) {
      aux = siguiente(aux, lst);
      delete[] aux->dato->texto->caracteres;
      delete aux->anterior->siguiente;
      delete aux->anterior;
    }
    delete aux;
    delete lst->inicio;
    delete lst->final;
  }
  delete lst;
}

bool es_vacia_lista(const lista lst) {
  bool res = lst->inicio == NULL;

  return res;
}

bool es_inicio_lista(const localizador loc, const lista lst) {
  bool res = loc == lst->inicio;

  return res;
}

bool es_final_lista(const localizador loc, const lista lst) {
  bool res = loc == lst->final;

  return res;
}


localizador inicio_lista(const lista lst) {
  localizador res = lst->inicio;

  return res;
}

localizador final_lista(const lista lst) {
  localizador res = lst->final;

  return res;
}

localizador siguiente(const localizador loc, const lista lst) {
  localizador res = loc->siguiente;

  return res;
}

localizador anterior(const localizador loc, const lista lst) {
  localizador res = loc->anterior;

  return res;
}

bool precede_en_lista(const localizador l1, const localizador l2,
                   const lista lst) {
  bool res = l1 == l2;
  while ( && l1->siguiente != NULL) {
    l1 = siguiente(l1, lst);
    res = l1 == l2;
  }
  return res;
}

info_t info_lista(const localizador loc, const lista lst) {
  info_t res = loc->dato;

  return res;
}

void cambiar_en_lista(const info_t i, const localizador loc, lista &lst) {
  loc->dato = i;
}

void intercambiar(const localizador loc1, const localizador loc2, lista &lst) {
  info_t aux = loc1->dato;
  loc1->dato = loc2->dato;
  loc2->dato = aux;
}

