#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm.h>

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
    b->dato = i;
    b->izq = b->der = NULL;
    res = true;
    return res;
  } else {
    comp_t comparacion = comparar_texto(texto_info(i), texto_info(b->dato));
    switch (comparacion) {
      case igual: {
        res = false;
      break;
    } case mayor: {
        if (b->der== NULL){
          binario insertado = crear_binario();
          insertado->dato = i;
          b->der = insertado;
          res = true;
        } else {
          insertar_en_binario(i, b->der);
      }
      break;
    } case menor:{
        if (b->izq == NULL){
          binario insertado = crear_binario();
          insertado->dato = i;
          b->izq = insertado;
          res = true;
        } else {
          insertar_en_binario(i, b->izq);
        }
      break;
      }
    }
  }
  return res;
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
  binario buscador;
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
                AZ (buscador != NULL){
                  buscador = buscador->der;
                }
              mayor = buscador->dato;
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

bool es_vacio_binario(const binario b) {
  bool res = b == NULL;
  return res;
}

void remover_de_binario(const texto_t t, binario &b) {
  if (!es_vacio_binario(b)) {
    comp_t comparacion = comparar_texto(texto_info(b->dato), t);
    switch (comparacion) {
      case igual: {
        if (b->der == NULL) {
          binario izq = b->izq;
          liberar_info(b->dato);
          delete (b);
          b = izq;
        } else if (b->izq == NULL) {
          binario der = b->der;
          liberar_info(b->dato);
          delete (b);
          b = der;
        } else {
          liberar_info(b->dato);
          b->dato = remover_mayor(b->izq);
        }
        break;
      }
      case mayor: {
        remover_de_binario(t, b->izq);
        break;
      }
      case menor:{
        remover_de_binario(t, b->der);
        break;
      }
    }
  }
}

void liberar_binario(binario &b) {
  if(!es_vacio_binario(b)){
    info_t aux = remover_mayor(b);
    liberar_info(aux);
    liberar_binario(b);
  }
}

info_t raiz_binario(const binario b) {
  info_t res = b->dato;
  return res;
}

binario izquierdo(const binario b) {
  binario res = b->izq;
  return res;
}

binario derecho(const binario b) {
  binario res = b->der;
  return res;
}

binario buscar_subarbol(const texto_t t, const binario b) {
  binario res = NULL;
  if (!es_vacio_binario(b)) {
    comp_t comparacion = comparar_texto(texto_info(b->dato), t);
    switch (comparacion) {
      case igual: {
        res = b;
        break;
      }
      case mayor: {
        buscar_subarbol(t, b->izq);
        break;
      }
      case menor: {
        buscar_subarbol(t, b->der);
        break;
      }
    }
  }
  return res;
}

nat altura_binario(const binario b) {
  nat res = 0;
  if (!es_vacio_binario(b)) {
    res = 1 + std::max(altura_binario(b->der), altura_binario(b->izq));
  }
  return res;
}

nat cantidad_binario(const binario b) {
  nat res = 0;
  if (!es_vacio_binario(b)) {
    res = 1 + cantidad_binario(b->der) + cantidad_binario(b->izq);
  }
  return res;
}

nat cantidad_de_caminos(const lista l, const binario b) {
  nat res = 0;
  if (!es_vacia_lista(l) && !es_vacio_binario(b)) {
    if (numero_info(info_lista(inicio_lista(l), l)) == numero_info(b->dato)) {
      lista lTail = segmento_lista(siguiente(inicio_lista(l), l), final_lista(l), l);
      res = cantidad_de_caminos(lTail, b->der) + cantidad_de_caminos(lTail, b->izq);
    }
  } else if (es_vacia_lista(l) && es_vacio_binario(b)) {
    res = 1;
  }
  return res;
}

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

static camino_t buscar_camino_aux(const lista l, const binario b, camino_t c);

camino_t buscar_camino_aux(const lista l, const binario b, camino_t c) {

    if (!es_vacia_lista(l) && !es_vacio_binario(b)) {
      if (texto_info(info_lista(inicio_lista(l), l)) == texto_info(b->dato)) {
        lista lTail = segmento_lista(siguiente(inicio_lista(l), l), final_lista(l), l);
        if (!es_vacia_lista(lTail)) {
          if (texto_info(info_lista(inicio_lista(lTail),l)) > texto_info(b->dato)) {
            c.ramas[c.cantidad_ramas] = der;
            c.cantidad_ramas++;
            buscar_camino_aux(lTail, b->der, c);
          } else {
            c.ramas[c.cantidad_ramas] = izq;
            c.cantidad_ramas++;
            buscar_camino_aux(lTail, b->izq, c);
          }
        }
      }
    } else if (!es_vacia_lista(l) && !es_vacio_binario(b)) {
      c.existe = true;
    }
    return c;
  }

camino_t buscar_camino(const lista l, const binario b) {
  camino_t res;
  res.existe = false;
  res.cantidad_ramas = 0;

  res = buscar_camino_aux(l, b, res);

  return res;
}

static void imprimir_binario_aux(const binario b, nat a);

void imprimir_binario_aux(const binario b, nat a) {
  if (!es_vacio_binario(b)) {
      if (b->izq == NULL && b->der == NULL) {
        for (nat i = 0; i < a; i++)
          printf("%c", "-");
        escribir_texto(info_a_texto(b->dato));
        printf("\n");
        a--;
      } else if (b->der == NULL) {
        for (nat i = 0; i < a; i++)
          printf("%c", "-");
        escribir_texto(info_a_texto(b->dato));
        printf("\n");
        a++;
        imprimir_binario(b->izq);
      } else if (b->izq == NULL) {
        a++;
        imprimir_binario(b->der);
        a--;
        for (nat i = 0; i < a; i++)
          printf("%c", "-");
        escribir_texto(info_a_texto(b->dato));
        printf("\n");
      } else {
        a++;
        imprimir_binario(b->der);
        a--;
        nat i = 0;
        for (nat i = 0; i < a; i++)
          printf("%c", "-");
        escribir_texto(info_a_texto(b->dato));
        printf("\n");
        a++;
        imprimir_binario(b->izq);
        a--;
      }
    }
}


void imprimir_binario(const binario b) {
  imprimir_binario_aux(b, 0);
}


