/*
  Módulo de implementación de 'uso_listas'.
  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

/*Daniel Susviela 4894156-5
Sebastian Guerrero 5092132-1*/


#include "../include/utils.h"
#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/binario.h"
#include "../include/finitario.h"
#include "../include/uso_lista_arboles.h"

#include <stddef.h>
#include <stdio.h>

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


bool pertenece(const int i, const lista lst) { //SIGUIENTE EN FIN DE WHILE????
  bool res = false;
  localizador cursor = inicio_lista(lst);
  if (!es_vacia_lista(lst)){
    res = i == numero_info(info_lista(cursor, lst));
    while(!res && cursor != NULL){
      res = i == numero_info(info_lista(cursor, lst));
      cursor = siguiente(cursor, lst);
    }
  }
  return res;
}

nat longitud(const lista lst) {
  nat res = 0;
  localizador cursor = inicio_lista(lst);
  while(cursor != NULL) {
    res++;
    cursor = siguiente(cursor, lst);
  }
  return res;
}

nat cantidad(const int i, const lista lst) {
  nat res = 0;
  localizador cursor = inicio_lista(lst);
  while(cursor != NULL) {
    if (numero_info(info_lista(cursor, lst)) == i) {
      res++;
    }
    cursor = siguiente(cursor, lst);
  }
  return res;
}

bool son_numeros_iguales(const lista l1, const lista l2) {
  bool res = false;

  if (longitud(l1) == longitud(l2)) {
    localizador cursor1 = inicio_lista(l1);
    localizador cursor2 = inicio_lista(l2);
    while (cursor1 != NULL &&
           numero_info(info_lista(cursor1, l1)) == numero_info(info_lista(cursor2, l2))) {
      cursor1 = siguiente(cursor1, l1);
      cursor2 = siguiente(cursor2, l2);
    }
    res = (cursor1 == NULL) && (cursor2 == NULL);
  }
  return res;
}

lista concatenar(const lista l1, const lista l2) {
  lista res = segmento_lista(inicio_lista(l1), final_lista(l1), l1);
  lista lst2 = segmento_lista(inicio_lista(l2), final_lista(l2), l2);

  insertar_segmento_despues(lst2, final_lista(res), res);

  return res;
}

lista reversa(const lista lst) {
  lista res = crear_lista();
  localizador cursor = inicio_lista(res);
  info_t info = NULL;
  if (!es_vacia_lista(lst)) {
    localizador loc = inicio_lista(lst);
    while (loc != NULL) {
      info = crear_info(numero_info(info_lista(loc, lst)), copiar_texto(texto_info(info_lista(loc, lst))));
      insertar_antes(info, cursor, res);
      cursor = inicio_lista(res);
      loc = siguiente(loc, lst);
    }
  }

  return res;
}

localizador primer_mayor(const localizador loc, const lista lst) {
  localizador res = loc;
  localizador cursor = inicio_lista(lst);
  bool encontrado = false;
  while (loc != cursor && !encontrado) {
    if (numero_info(info_lista(cursor, lst)) > numero_info(info_lista(loc, lst))) {
      res = cursor;
      encontrado = true;
    }
    cursor = siguiente(cursor, lst);
  }
  return res;
}

void ordenar(lista &lst) {
  localizador cursor = inicio_lista(lst);
  while (cursor != NULL) {
    retroceder(cursor, lst);
    cursor = siguiente(cursor, lst);
  }
}

lista mezcla(const lista l1, const lista l2) {
  lista res = concatenar(l1, l2);
  ordenar(res);
  return res;
}

lista filtrado(const int clave, const comp_t criterio, const lista lst) {
  lista res = crear_lista();
  localizador cursor = inicio_lista(lst);
  localizador destino = inicio_lista(res);
  info_t info = NULL;
  switch (criterio) {
    case (menor): {
      while (cursor != NULL) {
        info = crear_info(numero_info(info_lista(cursor, lst)), copiar_texto(texto_info(info_lista(cursor, lst))));
        if (numero_info(info_lista(cursor, lst)) < clave) {
          insertar_despues(info, destino, res);
          destino = final_lista(res);
        }
        cursor = siguiente(cursor, lst);
      }
      break;
    }
    case (igual): {
      while (cursor != NULL) {
        info = crear_info(numero_info(info_lista(cursor, lst)), copiar_texto(texto_info(info_lista(cursor, lst))));
        if (numero_info(info_lista(cursor, lst)) == clave) {
          insertar_despues(info, destino, res);
          destino = final_lista(res);
        }
        cursor = siguiente(cursor, lst);
      }
      break;
    }
    case (mayor): {
      while (cursor != NULL) {
        info = crear_info(numero_info(info_lista(cursor, lst)), copiar_texto(texto_info(info_lista(cursor, lst))));
        if (numero_info(info_lista(cursor, lst)) > clave) {
          insertar_despues(info, destino, res);
          destino = final_lista(res);
        }
        cursor = siguiente(cursor, lst);
      }
      break;
    }
  }
  return res;
}

lista sublista(const nat menor, const nat mayor, const lista lst) {

  localizador finallst = final_lista(lst);
  localizador iniciolst = inicio_lista(lst);

  localizador desde = siguiente_clave(menor, iniciolst, lst);
  localizador hasta = anterior_clave(mayor, finallst, lst);  

  lista res = segmento_lista(desde, hasta, lst);


  return res;
}

void imprimir_lista(const lista lst) {
  localizador cursor = inicio_lista(lst);
  while (cursor != NULL) {
    escribir_texto(info_a_texto(info_lista(cursor, lst)));
    cursor = siguiente(cursor, lst);
  }
  printf("\n");
}
//auxiliar para kesimo
void pasar_binario_alista(const binario b, lista &l){
  
  if (b!=NULL && !es_vacio_binario(b)){
    pasar_binario_alista(izquierdo(b), l);
    insertar_despues(raiz_binario(b), final_lista(l), l);
    pasar_binario_alista(derecho(b), l);
  }

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

void imprimir_finitario(const finitario f) {

  nat altura = altura_finitario(f);
  lista imprimir = crear_lista();
  for (nat i = 1; i <= altura; i++) {
    imprimir = nivel(i, f);
    imprimir_lista(imprimir);
  }
  if (es_vacio_finitario(f)){printf("\n");}
  liberar_lista(imprimir);
}


