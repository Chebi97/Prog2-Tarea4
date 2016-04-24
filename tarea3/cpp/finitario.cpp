#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/uso_lista_arboles.h"
#include "../include/finitario.h"

#include <stdlib.h>
#include <algorithm>

struct rep_finitario {
  info_t dato;
  rep_finitario *primer_hijo;
  rep_finitario *sig_hermano;
};

finitario crear_finitario() {
	finitario res = NULL;
	return res;
}

/* Recibe un arbol vacio y lo inicializa con un nodo i
 * sus ramas son NULL
*/
static void inicializar_finitario(const info_t i, finitario &f) {
  f = new rep_finitario;
  f->dato = i;
  f->primer_hijo = NULL;
  f->sig_hermano = NULL;
}

void insertar_en_finitario(const info_t i, const nat k, finitario &f) {

  if (!es_vacio_finitario(f)) {
    if (es_vacio_finitario(f->primer_hijo)) {
      inicializar_finitario(i, f->primer_hijo);
    } else {
      if (k == 1) {
        finitario aux = f->primer_hijo;
        f->primer_hijo = crear_finitario();
        inicializar_finitario(i, f->primer_hijo);
        f->sig_hermano = aux;
      } else {
        finitario buscador = f->primer_hijo;
        nat j = k;
        while (!es_vacio_finitario(buscador->sig_hermano) && 2 < j) {
          j--;
          buscador = buscador->sig_hermano;
        }
        finitario aux = buscador->sig_hermano;
        buscador->sig_hermano = crear_finitario();
        inicializar_finitario(i, buscador->sig_hermano);
        buscador->sig_hermano->sig_hermano = aux;
      }
    }
  } else {
    inicializar_finitario(i, f);
  }
}
		 



void liberar_finitario(finitario &f) {
  if (!es_vacio_finitario(f)) {
    if (!es_vacio_finitario(f->sig_hermano)) {
      liberar_finitario(f->sig_hermano);
    }
    if (!es_vacio_finitario(f->primer_hijo)) {
      liberar_finitario(f->primer_hijo);
    }
    liberar_info(f->dato);
    delete f;
  }
}

bool es_vacio_finitario(const finitario f) {
	bool res = f == NULL;
	return res;
}

info_t raiz_finitario(const finitario f) {
//asumo que comparte memoria
	info_t res = f->dato;
	return res;

}

finitario hijo(const nat k, const finitario f) {

//asumo que comparte memoria
  nat j = k;
  finitario res;
  finitario buscador = f;
  if (es_vacio_finitario(f->primer_hijo)) {
    buscador = f->primer_hijo;
    while (!es_vacio_finitario(buscador->sig_hermano) && 1 < j) {
      j--;
      buscador = buscador->sig_hermano;
    }
    res = buscador;
  } else {
    res = NULL;
  }
  return res;
}

static void nivel_aux(nat k, const finitario f, lista &l) {
  nat j = k; //asumo que el primer nivel es 1
  if (!es_vacio_finitario(f)) {
    if (j == 1) {
      insertar_despues(copiar_info(f->dato), final_lista(l), l);
      nivel_aux(j, f->sig_hermano, l);
    } else {
      nivel_aux(--j, f->primer_hijo, l);
      nivel_aux(j, f->sig_hermano, l);
    }
  }
}

lista nivel(nat k, const finitario f) {
  lista res = crear_lista();
  if (altura_finitario(f) >= k) {
    nivel_aux(k, f, res);
    ordenar(res);
  }
  return res;

}

nat altura_finitario(const finitario f) {
  nat res = 0;
  if (!es_vacio_finitario(f)) {
    res = std::max((altura_finitario(f->primer_hijo)+1), altura_finitario(f->sig_hermano));
  }
  return res;
}
