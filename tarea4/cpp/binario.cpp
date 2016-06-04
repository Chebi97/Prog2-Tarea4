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

struct rep_binario {
  info_t dato;
  rep_binario *izq;
  rep_binario *der;
};


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
    nat l = longitud(lst);
    if (l <= 2) {
      localizador cursor = final_lista(lst);
      while (localizador_pertenece_a_lista(cursor, lst)) {
        insertar_en_binario(info_lista(cursor, lst), b);
        cursor = anterior(cursor, lst);
      }
    } else {
      nat pos = l/2;
      localizador root = inicio_lista(lst);
      for (int i = 1; i <= pos; i++) {
        root = siguiente(root, lst);
      }
      insertar_en_binario(info_lista(root, lst), b);
      lista m1 = separar_segmento(inicio_lista(lst), anterior(root, lst), lst);
      lista m2 = separar_segmento(siguiente(root, lst), final_lista(lst), lst);
      crear_balanceado_aux(m1, b->izq);
      crear_balanceado_aux(m2, b->der);

      liberar_lista(m1);
      liberar_lista(m2);
    }
  }
}

binario crear_balanceado(const lista lst) {
  binario res = crear_binario();
  lista lstcpy = segmento_lista(inicio_lista(lst), final_lista(lst), lst);
  crear_balanceado_aux(lstcpy, res);
  liberar_lista(lstcpy);
  return res;
}

static nat nivel_aux(const texto_t t, binario b, nat n) {
  nat res;
  comp_t comparacion = comparar_texto(texto_info(b->dato), t);
  switch (comparacion) {
    case igual: {
      res = n;
      break;
    }
    case mayor: {
      n++;
      res = nivel_aux(t, b->izq, n);
      break;
    }
    case menor: {
      n++;
      res = nivel_aux(t, b->der, n);
      break;
    }
  }
  return res;
}

/*
 * Devuelve el nivel del elemento con t como texto
 * Precondicion: t pertenece a b
 */
static nat nivel(const texto_t t, binario b) {
  nat res = nivel_aux(t, b, 1);
  return res;
}


static void imprimir_textos_aux(cola_binarios c, nat n_siguiente, const binario b) {
  texto_t copia = copiar_texto(texto_info((frente(c)->dato)));
  nat n_actual = nivel(copia, b);
  if (!es_vacio_binario(frente(c)->der)) {
    encolar(frente(c)->der, c);
  }
  if (!es_vacio_binario(frente(c)->izq)) {
    encolar(frente(c)->izq, c);
  }
  desencolar(c);
  if (!es_vacia_cola_binarios(c)) {
    imprimir_textos_aux(c, n_actual, b);
  }
  escribir_texto(copia);
  printf(" ");
  if (n_actual != n_siguiente) {
    printf("\n");
  }
  liberar_texto(copia);
}

void imprimir_textos(const binario b) {
  if (!es_vacio_binario(b)) {
    cola_binarios c = crear_cola_binarios();
    encolar(b, c);
    imprimir_textos_aux(c, 1, b);
    liberar_cola_binarios(c);
  }
}

//auxiliar para kesimo (comparte memoria)
void pasar_binario_alista_k(const binario b, lista &l) {
  if (b != NULL && !es_vacio_binario(b)) {
    pasar_binario_alista_k(izquierdo(b), l);
    insertar_despues(raiz_binario(b), final_lista(l), l);
    pasar_binario_alista_k(derecho(b), l);
  }
}

//auxiliar para linealizacion (no comparte memoria)
void pasar_binario_alista_l(const binario b, lista &l) {
  if (b != NULL && !es_vacio_binario(b)) {
    pasar_binario_alista_l(izquierdo(b), l);
    info_t copia = copiar_info(raiz_binario(b));
    insertar_despues(copia, final_lista(l), l);
    pasar_binario_alista_l(derecho(b), l);
  }
}

lista linealizacion(const binario b){
    lista res = crear_lista();
    pasar_binario_alista_l(b, res);
    return res;
}
binario kesimo_subarbol(const nat k, const binario b) {
//asumo que comparte memoria
  lista listabinario = crear_lista();
  pasar_binario_alista_k(b, listabinario);
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
    liberar_binario(b->izq);
    liberar_binario(b->der);
    remover_de_binario(texto_info(b->dato), b);
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
