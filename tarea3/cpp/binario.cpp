#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct rep_binario {
  info_t dato;
  rep_binario *izq;
  rep_binario *der;
};

binario crear_binario() {

  binario res = new rep_binario;

  res->dato = new rep_texto;
  res->izq = NULL;
  res->der = NULL;

  return res;

}

bool insertar_en_binario(const info_t i, binario &b) {

  bool res = false;

  if (es_vacio_binario(b)){
    return res;
  } else {
    b->dato = i;
    res = true;
    return res;
  }

}

info_t remover_mayor(binario &b) {
  info_t res;
  if (b->der == NULL) {
    res = b->dato;
    binario izq = b->izq;
    delete (b);
    b = izq;
  } else {
    res = remover_mayor(b->der);
  }
  return res;
}

binario crear_filtrado(const int clave, comp_t criterio, const binario b) {

  binario fderecho, fizquierdo, res;
  binario res = crear_binario();
  binario *buscador;
  info_t raizbin, mayor;

  if (es_vacio_binario(b)){
    return res; //que sea vacio significa que no tiene un elemento cargado o que apunta a null?
  } else {
    fderecho = crear_filtrado(clave, criterio, b->der);
    fizquierdo = crear_filtrado(clave, criterio, b->izq);
    raizbin = raiz_binario(b);
    switch (clave) {
      case menor:{
        if (numero_info(raizbin) < clave){
          insertar_en_binario(raizbin, res);
          res->izq = fderecho;
          res->der = fizquierdo;
          return res;
        } else {
          if (es_vacio_binario(fizquierdo)){
            liberar_binario(fizquierdo);
            return fderecho;
          } else {
            if (es_vacio_binario(fderecho)){
              liberar_binario(fderecho);
              return fizquierdo;
            } else {
              buscador = b->izq; //no hay un mayor para arboles en este programa de m***?
                while (buscador != NULL){
                  buscador = buscador->der;
                }
              mayor = buscador->dato
              remover_mayor(fizquierdo);
              insertar_en_binario(mayor, res);
              res->izq = fderecho;
              res->der = fizquierdo;
              return res;
            }
          }
        }
        break;
      }
      case igual:{
        if (b->dato = clave){

        }
        break;
      }
      case menor:{
        if (b->dato > clave){

        }
        break;
      }
    }

  }

}

/*void remover_de_binario(const texto_t t, binario &b) {}

void liberar_binario(binario &b) {}

bool es_vacio_binario(const binario b) {}

info_t raiz_binario(const binario b) {}

binario izquierdo(const binario b) {}

binario derecho(const binario b) {}

binario buscar_subarbol(const texto_t t, const binario b) {}

nat altura_binario(const binario b) {}

nat cantidad_binario(const binario b) {}

nat cantidad_de_caminos(const lista l, const binario b) {}
*/
/*
  Auxiliar para camino_a_texto.
 */
static void agregar_rama(char *cadena, rama_t r) {
  switch (r) {
  case izq:
    strcat(cadena, "I");
    break;
  case der:
    strcat(cadena, "D");
    break;
  }
}

texto_t camino_a_texto(const camino_t c) {
  texto_t res;
  // espacio suficiente para "No existe" o para cada rama y la coma y la
  // cantidad, el guión y los paréntesis.
  char cadena[c.cantidad_ramas * 2 + 10];
  if (!c.existe) {
    strcpy(cadena, "No existe");
  } else {
    sprintf(cadena, "%d", c.cantidad_ramas);
    strcat(cadena, "-(");
    if (c.cantidad_ramas > 0) {
      agregar_rama(cadena, c.ramas[0]);
      for (nat i = 1; i < c.cantidad_ramas; i++) {
        strcat(cadena, ",");
        agregar_rama(cadena, c.ramas[i]);
      }
    }
    strcat(cadena, ")");
  }
  res = cadena_a_texto(cadena);
  return res;
}

/*camino_t buscar_camino(const lista l, const binario b) {}

void imprimir_binario(const binario b) {}*/
