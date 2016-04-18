/*
  Módulo de implementación de 'uso_listas'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/uso_lista_arboles.h"

bool esta_ordenada(const lista lst) {
  bool res = true;
  if (!es_vacia_lista(lst)) {
    localizador loc = inicio_lista(lst);
    while (res && es_localizador_lista(siguiente(loc, lst))) {
      localizador sig_loc = siguiente(loc, lst);
      if (numero_info(info_lista(loc, lst)) >
          numero_info(info_lista(sig_loc, lst)))
        res = false;
      else
        loc = siguiente(loc, lst);
    }
  }
  return res;
}

void retroceder(localizador loc, lista &lst) {
  localizador pto_ins = primer_mayor(loc, lst);
  mover_antes(pto_ins, loc, lst);
}

void unificar(lista &lst) {
  if (!es_vacia_lista(lst)) {
    localizador loc = inicio_lista(lst);
    // se cumplen las precondiciones de `siguiente`
    localizador sig_loc = siguiente(loc, lst);

    while (es_localizador_lista(sig_loc)) {
      if (numero_info(info_lista(loc, lst)) ==
          numero_info(info_lista(sig_loc, lst)))
        remover_de_lista(sig_loc, lst);
      else
        loc = sig_loc;
      sig_loc = siguiente(loc, lst);
    }
  }
}

void cambiar_todos(const int original, const int nuevo, lista &lst) {
  localizador loc = inicio_lista(lst);
  while (es_localizador_lista(loc)) {
    if (numero_info(info_lista(loc, lst)) == original) {
      info_t info = info_lista(loc, lst);
      info_t nueva_info = crear_info(nuevo, copiar_texto(texto_info(info)));
      cambiar_en_lista(nueva_info, loc, lst);
      // libera la info que no libera cambiar_en_lista
      liberar_info(info);
    }
    loc = siguiente(loc, lst);
  }
}

/*
bool pertenece(const int i, const lista lst) {
}

nat longitud(const lista lst) {
}

nat cantidad(const int i, const lista lst) {
}

bool son_numeros_iguales(const lista l1, const lista l2) {
}

lista concatenar(const lista l1, const lista l2) {
}

lista reversa(const lista lst) {
}

localizador primer_mayor(const localizador loc, const lista lst) {
}

void ordenar(lista &lst) {
}

lista mezcla(const lista l1, const lista l2) {
}

lista filtrado(const int clave, const comp_t criterio, const lista lst) {
}

lista sublista(const nat menor, const nat mayor, const lista lst) {
}

void imprimir_lista(const lista lst) {
}

binario kesimo_subarbol(const nat k, const binario b) {
}

void imprimir_finitario(const finitario f) {
}

*/
