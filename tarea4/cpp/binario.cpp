#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"
#include "../include/uso_lista_arboles.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>

struct rep_binario {
  info_t dato;
  rep_binario *izq;
  rep_binario *der;
};
/*
static void crear_balanceado_aux(const lst, localizador &loc, binario &b){
  if (!es_vacia_lista(lst)){
    nat alturader = altura_binario(b->der);
    nat alturaizq = altura_binario(b->izq);
    if (alturaizq == alturader)){
      insertar_en_binario(info_lista(loc, lst), b)
    } else {
      if (alturaizq == alturader+1){
        insertar_en_binario(info_lista(loc, lst), b->izq);
      }
      if (1 + alturaizq == alturader){
        insertar_en_binario(info_lista(loc, lst), b->der);
      }
    }
    loc = siguiente(loc, lst);
    crear_balanceado_aux(lst, loc, b);
  }
}


binario crear_balanceado(const lista lst){
  localizador loc = inicio_lista;
  binario res = crear_binario();
  crear_balanceado_aux(lst, loc, res);
  return res;
}
*/


nat longitud(const lista lst) {
  nat res = 0;
  localizador cursor = inicio_lista(lst);
  while(cursor != NULL) {
    res++;
    cursor = siguiente(cursor, lst);
  }
  return res;
}

static void crear_balanceado_aux(lista &lst, binario &b) {
  if (!es_vacia_lista(lst)) {
    if (longitud(lst) <= 2) {
      localizador finlst;
      while (!es_vacia_lista(lst)) {
        insertar_en_binario(info_lista(final_lista(lst), lst), b);
        finlst = final_lista(lst);
        remover_de_lista(finlst, lst);
      }
    } else {
      nat pos = longitud(lst)/2 + 1;
      localizador root = inicio_lista(lst);
      for (int i = 0; i > pos; i++) {
        root = siguiente(root, lst);
      }
      insertar_en_binario(info_lista(root, lst), b);
      lista m1 = separar_segmento(inicio_lista(lst), anterior(root, lst), lst);
      lista m2 = separar_segmento(siguiente(root, lst), final_lista(lst), lst);
      remover_de_lista(root, lst);
      crear_balanceado_aux(m1, b->izq);
      crear_balanceado_aux(m2, b->der);

      delete m1;
      delete m2;
      delete lst;
    }
  }
}

binario crear_balanceado(const lista lst) {
  binario res = crear_binario();
  lista lstcpy = segmento_lista(inicio_lista(lst), final_lista(lst), lst);
  crear_balanceado_aux(lstcpy, res);
  return res;
}

//auxiliar para kesimo y linealizacion
void pasar_binario_alista(const binario b, lista &l){
  
  if (b!=NULL && !es_vacio_binario(b)){
    pasar_binario_alista(izquierdo(b), l);
    insertar_despues(raiz_binario(b), final_lista(l), l);
    pasar_binario_alista(derecho(b), l);
  }

}
lista linealizacion(const binario b){
    lista res = crear_lista();
    pasar_binario_alista(b, res); //revisar orden
    return res;
}
binario kesimo_subarbol(const nat k, const binario b) {
//asumo que comparte memoria
  lista listabinario = crear_lista();
  pasar_binario_alista(b, listabinario);
  localizador kesima_raiz = inicio_lista(listabinario);
  for(nat j=1; j< k; j++){ 
      kesima_raiz = siguiente(kesima_raiz, listabinario);
  }
  binario res = buscar_subarbol(texto_info(info_lista(kesima_raiz, listabinario)), b);
  return res;

}


binario crear_binario() {
  binario res = NULL;
  return res;
}

static binario cons(info_t i, binario izq, binario der) {
  binario res = new rep_binario;
  res->dato = copiar_info(i);
  res->izq = izq;
  res->der = der;
  return res;
}

bool insertar_en_binario(const info_t i, binario &b) {

  bool res = false;

  if (es_vacio_binario(b)){
    b = cons(i, crear_binario(), crear_binario());
    res = true;
    return res;
  } else {
    comp_t comparacion = comparar_texto(texto_info(i), texto_info(b->dato));
    switch (comparacion) {
        case igual: {
          res = false;
        break;
      } case mayor: {
          if (es_vacio_binario(b->der)) {
            binario insertado = cons(i, crear_binario(), crear_binario());
            b->der = insertado;
            res = true;
          } else {
           res = insertar_en_binario(i, b->der);
        }
        break;
      } case menor:{
          if (es_vacio_binario(b->izq)) {
            binario insertado = cons(i, crear_binario(), crear_binario());
            b->izq = insertado;
            res = true;
          } else {
           res = insertar_en_binario(i, b->izq);
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

  binario res;
  binario fder, fizq;
  info_t imayor, raiz;

  if (!es_vacio_binario(b)) {
    fizq = crear_filtrado(clave, criterio, b->izq);
    fder = crear_filtrado(clave, criterio, b->der);
    raiz = b->dato;
    switch (criterio){
      case menor: {
        if (numero_info(raiz) < clave) {
          res = cons(raiz, fizq, fder);
        } else if (es_vacio_binario(fizq)) {
          res = fder;
        } else if (es_vacio_binario(fder)) {
          res = fizq;
        } else {
          imayor = remover_mayor(fizq);
          res = cons(imayor, fizq, fder);
        }
        break;
      }
      case mayor: {
        if (numero_info(raiz) > clave) {
          res = cons(raiz, fizq, fder);
        } else if (es_vacio_binario(fizq)) {
          res = fder;
        } else if (es_vacio_binario(fder)) {
          res = fizq;
        } else {
          imayor = remover_mayor(fizq);
          res = cons(imayor, fizq, fder);
        }
        break;
      }
      case igual: {
        if (numero_info(raiz) == clave) {
          res = cons(raiz, fizq, fder);
        } else if (es_vacio_binario(fizq)) {
          res = fder;
        } else if (es_vacio_binario(fder)) {
          res = fizq;
        } else {
          imayor = remover_mayor(fizq);
          res = cons(imayor, fizq, fder);
        }
      break;
      }
    }
  } else {
    res = NULL;
  }
    return res;
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
        if (es_vacio_binario(b->der) && es_vacio_binario(b->izq)) {
          liberar_info(b->dato);
          delete b;
          b = crear_binario();
        } else if (es_vacio_binario(b->der)) {
          binario temp = b;
          b = b->izq;
          liberar_info(temp->dato);
          delete temp;
        } else if (es_vacio_binario(b->izq)) {
          binario temp = b;
          b = b->der;
          liberar_info(temp->dato);
          delete temp;
        } else {
          info_t temp = b->dato;
          b->dato = remover_mayor(b->izq);
          liberar_info(temp);
        }
        break;
      }
      case mayor: {
        remover_de_binario(t, b->izq);
        break;
      }
      case menor: {
        remover_de_binario(t, b->der);
        break;
      }
    }
  }
}


void liberar_binario(binario &b) {
  if (!es_vacio_binario(b)) {
    remover_de_binario(texto_info(b->dato), b);
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
  binario res = crear_binario();
  if (!es_vacio_binario(b)) {
    comp_t comparacion = comparar_texto(texto_info(b->dato), t);
    switch (comparacion) {
      case igual: {
        res = b;
        break;
      }
      case mayor: {
        res = buscar_subarbol(t, b->izq);
        break;
      }
      case menor: {
        res = buscar_subarbol(t, b->der);
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
      if (siguiente(inicio_lista(l), l) != NULL) {
        lista lTail = segmento_lista(siguiente(inicio_lista(l), l), final_lista(l), l);
        res = cantidad_de_caminos(lTail, b->der) + cantidad_de_caminos(lTail, b->izq);
        liberar_lista(lTail);
      } else {
        if (es_vacio_binario(b->der) && es_vacio_binario(b->izq)) {
          res = 1;
        }
      }
    }
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

static camino_t buscar_camino_aux(const lista l, const binario b, camino_t &c) {
  if (!es_vacia_lista(l) && !es_vacio_binario(b)) {
    if ( comparar_texto(texto_info(info_lista(inicio_lista(l), l)), texto_info(b->dato)) == igual) {
      if (siguiente(inicio_lista(l), l) != NULL) {
        lista lTail = segmento_lista(siguiente(inicio_lista(l), l), final_lista(l), l);
        if (comparar_texto(texto_info(info_lista(inicio_lista(lTail), lTail)), texto_info(b->dato)) == mayor) {
          c.ramas[c.cantidad_ramas] = der;
          c.cantidad_ramas++;
          buscar_camino_aux(lTail, b->der, c);
        } else {
          c.ramas[c.cantidad_ramas] = izq;
          c.cantidad_ramas++;
          buscar_camino_aux(lTail, b->izq, c);
        }
        liberar_lista(lTail);
      } else {
        if (es_vacio_binario(b->der) && es_vacio_binario(b->izq)) {
          c.existe = true;
        }
      }
    }
  }
  return c;
}

camino_t buscar_camino(const lista l, const binario b) {
  camino_t res;
  res.existe = false;
  res.cantidad_ramas = 0;
  res.ramas = new rama_t[longitud(l) - 1];

  if (!es_vacia_lista(l) && !es_vacio_binario(b)) {
    res = buscar_camino_aux(l, b, res);
  }

  return res;
}

static void imprimir_binario_aux(const binario b, nat a) {
  if (!es_vacio_binario(b)) {
      if (es_vacio_binario(b->izq) && es_vacio_binario(b->der)) {
        for (nat i = 0; i < a; i++)
          printf("%s", "-");
        escribir_texto(info_a_texto(b->dato));
        printf("\n");
      } else if (b->der == NULL) {
        for (nat i = 0; i < a; i++)
          printf("%s", "-");
        escribir_texto(info_a_texto(b->dato));
        printf("\n");
        a++;
        imprimir_binario_aux(b->izq, a);
        a--;                               //puede no ser necesario
      } else if (b->izq == NULL) {
        a++;
        imprimir_binario_aux(b->der, a);
        a--;
        for (nat i = 0; i < a; i++)
          printf("%s", "-");
        escribir_texto(info_a_texto(b->dato));
        printf("\n");
      } else {
        a++;
        imprimir_binario_aux(b->der, a);
        a--;
        for (nat i = 0; i < a; i++)
          printf("%s", "-");
        escribir_texto(info_a_texto(b->dato));
        printf("\n");
        a++;
        imprimir_binario_aux(b->izq, a);
        a--;                                 //puede no ser necesario
      }
    }
}

void imprimir_binario(const binario b) {
  imprimir_binario_aux(b, 0);
}
