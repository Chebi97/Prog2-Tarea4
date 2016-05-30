#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"
#include "../include/pila.h"
#include "../include/cola_binarios.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

struct nodeb {
  binario arbol;
  nodeb *siguiente;
};

struct rep_cola_binarios {
  nodeb *inicio;
  nodeb *final;
};

/*
 Devuelve una cola_binarios vacía (sin elementos).
 */
cola_binarios crear_cola_binarios() {
  cola_binarios res = new rep_cola_binarios;
  res->inicio = res->final = NULL;
  return res;
}

/*
 Encola `b` en `c`.
 */
void encolar(const binario b, cola_binarios &c) {
  nodeb *ains = new nodeb;
  ains->arbol = b;
  ains->siguiente = NULL;
  if (es_vacia_cola_binarios(c)) {
    c->final = ains;
    c->inicio = ains;
  } else {
    c->final->siguiente = ains;
    c->final = ains;
  }
}

/*
 Remueve de `c` el elemento que está en el frente.
 No libera la memoria del elemento removido.
 Si es_vacia_cola_binarios(c) no hace nada.
 */
void desencolar(cola_binarios &c) {
  if (!es_vacia_cola_binarios(c)) {
    nodeb *aux = c->inicio->siguiente;
    delete c->inicio;
    c->inicio = aux;
  }
  if (es_vacia_cola_binarios(c)) {
    c->final = NULL;
  }
}

/*
 Devuelve `true` si `c` es vacía (no tiene elementos), o `false` en otro caso.
 */
bool es_vacia_cola_binarios(const cola_binarios c) {
  bool res = c->inicio == NULL;
  return res;
}

/*
 Devuelve el elemento que está en el frente de `c`.
 Precondición: ! es_vacia_cola_binarios(c);
 */
binario frente(const cola_binarios c) {
  binario res = c->inicio->arbol;
  return res;
}

/*
 Libera la memoria asignada a `c`, pero NO la de sus elementos.
 */
void liberar_cola_binarios(cola_binarios &c) {
  while (!es_vacia_cola_binarios(c)) {
    desencolar(c);
  }
  delete c;
  c = NULL;
}
