/*
  Módulo principal ejemplos_letra.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/utils.h"
#include "include/texto.h"
#include "include/info.h"
#include "include/lista.h"
#include "include/binario.h"
#include "include/finitario.h"
#include "include/uso_lista_arboles.h"

#include <stdio.h>

int main() {

  binario b;
  finitario f, h;
  lista lst;
  info_t info;
  texto_t txt;
  bool res;
  camino_t cam;

  // insertar_en_binario
  printf("insertar_en_binario. \n");
  // primer ejemplo
  printf("1:\n");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("u"));
  insertar_en_binario(info, b);
  imprimir_binario(b);
  liberar_binario(b);

  // segundo ejemplo
  printf("2:\n");
  b = crear_binario();
  info = crear_info(8, cadena_a_texto("a"));
  insertar_en_binario(info, b);
  info = crear_info(2, cadena_a_texto("d"));
  insertar_en_binario(info, b);
  info = crear_info(3, cadena_a_texto("t"));
  insertar_en_binario(info, b);
  imprimir_binario(b);

  // tercer ejemplo
  printf("3:\n");
  info = crear_info(5, cadena_a_texto("d"));
  res = insertar_en_binario(info, b);
  imprimir_binario(b);
  liberar_binario(b);
  if (!res)
    liberar_info(info);

  // remover_de_binario
  printf("remover_de_binario. \n");
  // primer ejemplo
  printf("1:\n");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("k"));
  insertar_en_binario(info, b);
  txt = cadena_a_texto("j");
  remover_de_binario(txt, b);
  imprimir_binario(b);
  liberar_binario(b);
  liberar_texto(txt);

  // segundo ejemplo
  printf("2:\n");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("k"));
  insertar_en_binario(info, b);
  info = crear_info(2, cadena_a_texto("m"));
  insertar_en_binario(info, b);
  txt = cadena_a_texto("m");
  remover_de_binario(txt, b);
  imprimir_binario(b);
  liberar_binario(b);
  liberar_texto(txt);

  // tercer ejemplo
  printf("3:\n");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("k"));
  insertar_en_binario(info, b);
  info = crear_info(2, cadena_a_texto("a"));
  insertar_en_binario(info, b);
  info = crear_info(5, cadena_a_texto("x"));
  insertar_en_binario(info, b);
  info = crear_info(4, cadena_a_texto("l"));
  insertar_en_binario(info, b);
  info = crear_info(1, cadena_a_texto("n"));
  insertar_en_binario(info, b);
  info = crear_info(3, cadena_a_texto("m"));
  insertar_en_binario(info, b);
  info = crear_info(7, cadena_a_texto("z"));
  insertar_en_binario(info, b);
  txt = cadena_a_texto("x");
  remover_de_binario(txt, b);
  imprimir_binario(b);
  liberar_binario(b);
  liberar_texto(txt);

  // altura_binario
  printf("altura_binario. \n");
  // primer ejemplo
  printf("1:");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("b"));
  insertar_en_binario(info, b);
  printf("%d \n", altura_binario(b));
  liberar_binario(b);

  // segundo ejemplo
  printf("2:");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("b"));
  insertar_en_binario(info, b);
  info = crear_info(5, cadena_a_texto("d"));
  insertar_en_binario(info, b);
  printf("%d \n", altura_binario(b));
  liberar_binario(b);

  // tercer ejemplo
  printf("3:");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("b"));
  insertar_en_binario(info, b);
  info = crear_info(5, cadena_a_texto("d"));
  insertar_en_binario(info, b);
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_binario(info, b);
  info = crear_info(7, cadena_a_texto("t"));
  insertar_en_binario(info, b);
  info = crear_info(2, cadena_a_texto("a"));
  insertar_en_binario(info, b);
  printf("%d \n", altura_binario(b));
  liberar_binario(b);

  // buscar_subarbol
  printf("buscar_subarbol. \n");
  // primer ejemplo
  printf("1:\n");
  b = crear_binario();
  info = crear_info(4, cadena_a_texto("g"));
  insertar_en_binario(info, b);
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_binario(info, b);
  info = crear_info(7, cadena_a_texto("k"));
  insertar_en_binario(info, b);
  info = crear_info(3, cadena_a_texto("a"));
  insertar_en_binario(info, b);
  info = crear_info(1, cadena_a_texto("e"));
  insertar_en_binario(info, b);
  info = crear_info(8, cadena_a_texto("i"));
  insertar_en_binario(info, b);
  info = crear_info(6, cadena_a_texto("p"));
  insertar_en_binario(info, b);
  info = crear_info(2, cadena_a_texto("d"));
  insertar_en_binario(info, b);
  info = crear_info(8, cadena_a_texto("h"));
  insertar_en_binario(info, b);
  info = crear_info(4, cadena_a_texto("m"));
  insertar_en_binario(info, b);

  txt = cadena_a_texto("i");
  binario sub = buscar_subarbol(txt, b);
  imprimir_binario(sub);
  liberar_binario(b);
  liberar_texto(txt);

  // imprimir_binario
  printf("imprimir_binario. \n");
  // primer ejemplo
  printf("1:\n");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("b"));
  insertar_en_binario(info, b);
  imprimir_binario(b);
  liberar_binario(b);

  // segundo ejemplo
  printf("2:\n");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("b"));
  insertar_en_binario(info, b);
  info = crear_info(5, cadena_a_texto("d"));
  insertar_en_binario(info, b);
  imprimir_binario(b);
  liberar_binario(b);

  // tercer ejemplo
  printf("3:\n");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("b"));
  insertar_en_binario(info, b);
  info = crear_info(5, cadena_a_texto("d"));
  insertar_en_binario(info, b);
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_binario(info, b);
  info = crear_info(7, cadena_a_texto("t"));
  insertar_en_binario(info, b);
  info = crear_info(2, cadena_a_texto("a"));
  insertar_en_binario(info, b);
  imprimir_binario(b);
  liberar_binario(b);

  // cantidad_de_caminos
  printf("cantidad_de_caminos. \n");
  lst = crear_lista();
  info = crear_info(3, cadena_a_texto("u"));
  insertar_despues(info, final_lista(lst), lst);
  info = crear_info(2, cadena_a_texto("c"));
  insertar_despues(info, final_lista(lst), lst);

  // primer ejemplo
  printf("1:");
  b = crear_binario();
  info = crear_info(3, cadena_a_texto("b"));
  insertar_en_binario(info, b);
  printf("%d \n", cantidad_de_caminos(lst, b));

  // segundo ejemplo
  printf("2:");
  info = crear_info(2, cadena_a_texto("d"));
  insertar_en_binario(info, b);
  printf("%d \n", cantidad_de_caminos(lst, b));

  // tercer ejemplo
  printf("3:");
  info = crear_info(2, cadena_a_texto("a"));
  insertar_en_binario(info, b);
  printf("%d \n", cantidad_de_caminos(lst, b));

  // cuarto ejemplo
  printf("4:");
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_binario(info, b);
  printf("%d \n", cantidad_de_caminos(lst, b));

  liberar_binario(b);
  liberar_lista(lst);

  // buscar_camino
  printf("buscar_camino. \n");
  lst = crear_lista();
  info = crear_info(4, cadena_a_texto("b"));
  insertar_despues(info, final_lista(lst), lst);

  // primer ejemplo
  printf("1:");
  b = crear_binario();
  info = crear_info(1, cadena_a_texto("b"));
  insertar_en_binario(info, b);
  cam = buscar_camino(lst, b);
  txt = camino_a_texto(cam);
  escribir_texto(txt);
  escribir_nueva_linea();
  delete[] cam.ramas;

  // segundo ejemplo
  printf("2:");
  info = crear_info(5, cadena_a_texto("d"));
  insertar_despues(info, final_lista(lst), lst);
  cam = buscar_camino(lst, b);
  txt = camino_a_texto(cam);
  escribir_texto(txt);
  escribir_nueva_linea();
  delete[] cam.ramas;

  // tercer ejemplo
  printf("3:");
  info = crear_info(2, cadena_a_texto("d"));
  insertar_en_binario(info, b);
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_binario(info, b);
  cam = buscar_camino(lst, b);
  txt = camino_a_texto(cam);
  escribir_texto(txt);
  escribir_nueva_linea();
  delete[] cam.ramas;

  // cuarto ejemplo
  printf("4:");
  info = crear_info(3, cadena_a_texto("c"));
  insertar_despues(info, final_lista(lst), lst);
  info = crear_info(2, cadena_a_texto("a"));
  insertar_en_binario(info, b);
  info = crear_info(7, cadena_a_texto("t"));
  insertar_en_binario(info, b);
  cam = buscar_camino(lst, b);
  txt = camino_a_texto(cam);
  escribir_texto(txt);
  escribir_nueva_linea();
  delete[] cam.ramas;

  liberar_binario(b);
  liberar_lista(lst);

  // filtrar_binario
  printf("filtrar_binario. \n");
  // primer ejemplo
  printf("1:\n");
  b = crear_binario();
  info = crear_info(5, cadena_a_texto("g"));
  insertar_en_binario(info, b);
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_binario(info, b);
  info = crear_info(7, cadena_a_texto("k"));
  insertar_en_binario(info, b);
  info = crear_info(3, cadena_a_texto("b"));
  insertar_en_binario(info, b);
  info = crear_info(1, cadena_a_texto("e"));
  insertar_en_binario(info, b);
  info = crear_info(8, cadena_a_texto("i"));
  insertar_en_binario(info, b);
  info = crear_info(6, cadena_a_texto("p"));
  insertar_en_binario(info, b);
  info = crear_info(9, cadena_a_texto("a"));
  insertar_en_binario(info, b);
  info = crear_info(2, cadena_a_texto("d"));
  insertar_en_binario(info, b);
  info = crear_info(8, cadena_a_texto("h"));
  insertar_en_binario(info, b);
  info = crear_info(4, cadena_a_texto("m"));
  insertar_en_binario(info, b);

  binario flt = crear_filtrado(5, menor, b);
  imprimir_binario(flt);
  liberar_binario(b);
  liberar_binario(flt);

  // insertar_en_finitario
  printf("insertar_en_finitario. \n");
  f = crear_finitario();

  // primer ejemplo
  printf("1:");
  info = crear_info(2, cadena_a_texto("a"));
  insertar_en_finitario(info, 1, f);
  imprimir_finitario(f);

  // segundo ejemplo
  printf("2:");
  info = crear_info(7, cadena_a_texto("t"));
  insertar_en_finitario(info, 2, f);
  imprimir_finitario(f);

  // tercer ejemplo
  printf("3:");
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_finitario(info, 1, f);
  imprimir_finitario(f);

  // cuarto ejemplo
  printf("4:");
  info = crear_info(1, cadena_a_texto("v"));
  insertar_en_finitario(info, 4, f);
  imprimir_finitario(f);

  liberar_finitario(f);

  // hijo

  printf("hijo. \n");
  // primer ejemplo
  printf("1:");
  f = crear_finitario();
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_finitario(info, 1, f);
  h = hijo(1, f);
  imprimir_finitario(h);
  liberar_finitario(f);

  // segundo ejemplo
  printf("2:");
  f = crear_finitario();
  info = crear_info(2, cadena_a_texto("a"));
  insertar_en_finitario(info, 1, f);
  info = crear_info(7, cadena_a_texto("c"));
  insertar_en_finitario(info, 1, f);
  h = hijo(2, f);
  imprimir_finitario(h);
  liberar_finitario(f);

  // tercer ejemplo
  printf("3:");
  f = crear_finitario();
  info = crear_info(1, cadena_a_texto("b"));
  insertar_en_finitario(info, 1, f);
  info = crear_info(2, cadena_a_texto("a"));
  insertar_en_finitario(info, 1, f);
  info = crear_info(2, cadena_a_texto("d"));
  insertar_en_finitario(info, 1, f);
  h = hijo(1, f);
  info = crear_info(7, cadena_a_texto("z"));
  insertar_en_finitario(info, 1, h);
  h = hijo(2, f);
  info = crear_info(1, cadena_a_texto("v"));
  insertar_en_finitario(info, 1, h);
  info = crear_info(7, cadena_a_texto("t"));
  insertar_en_finitario(info, 1, h);
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_finitario(info, 1, h);

  h = hijo(2, f);
  imprimir_finitario(h);

  // cuarto ejemplo
  printf("4:");
  finitario h2 = hijo(3, h);
  imprimir_finitario(h2);

  liberar_finitario(f);

  // nivel
  f = crear_finitario();
  info = crear_info(1, cadena_a_texto("b"));
  insertar_en_finitario(info, 1, f);
  info = crear_info(2, cadena_a_texto("a"));
  insertar_en_finitario(info, 1, f);
  info = crear_info(2, cadena_a_texto("d"));
  insertar_en_finitario(info, 1, f);

  h = hijo(1, f);
  info = crear_info(7, cadena_a_texto("z"));
  insertar_en_finitario(info, 1, h);

  h = hijo(2, f);
  info = crear_info(1, cadena_a_texto("v"));
  insertar_en_finitario(info, 1, h);
  info = crear_info(7, cadena_a_texto("t"));
  insertar_en_finitario(info, 1, h);
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_finitario(info, 1, h);

  printf("nivel. \n");
  // primer ejemplo
  printf("1:");
  lst = nivel(1, f);
  imprimir_lista(lst);
  liberar_lista(lst);

  // segundo ejemplo
  printf("2:");
  lst = nivel(2, f);
  imprimir_lista(lst);
  liberar_lista(lst);

  // tercer ejemplo
  printf("3:");
  lst = nivel(3, f);
  imprimir_lista(lst);
  liberar_lista(lst);

  liberar_finitario(f);

  // kesimo_subarbol
  printf("kesimo_subarbol. \n");
  // primer ejemplo
  printf("1:\n");
  b = crear_binario();
  info = crear_info(15, cadena_a_texto("b"));
  insertar_en_binario(info, b);
  sub = kesimo_subarbol(1, b);
  imprimir_binario(sub);

  // segundo ejemplo
  printf("2:\n");
  info = crear_info(-1, cadena_a_texto("d"));
  insertar_en_binario(info, b);
  sub = kesimo_subarbol(2, b);
  imprimir_binario(sub);

  // tercer ejemplo
  printf("3:\n");
  info = crear_info(34, cadena_a_texto("a"));
  insertar_en_binario(info, b);
  info = crear_info(10, cadena_a_texto("c"));
  insertar_en_binario(info, b);
  info = crear_info(7, cadena_a_texto("t"));
  insertar_en_binario(info, b);
  sub = kesimo_subarbol(4, b);
  imprimir_binario(sub);

  liberar_binario(b);

  // imprimir_finitario
  printf("imprime_finitario. \n");
  // primer ejemplo
  printf("1:\n");

  f = crear_finitario();
  info = crear_info(1, cadena_a_texto("b"));
  insertar_en_finitario(info, 1, f);
  info = crear_info(2, cadena_a_texto("a"));
  insertar_en_finitario(info, 1, f);
  info = crear_info(2, cadena_a_texto("d"));
  insertar_en_finitario(info, 1, f);
  h = hijo(1, f);
  info = crear_info(7, cadena_a_texto("z"));
  insertar_en_finitario(info, 1, h);
  h = hijo(2, f);
  info = crear_info(1, cadena_a_texto("v"));
  insertar_en_finitario(info, 1, h);
  info = crear_info(7, cadena_a_texto("t"));
  insertar_en_finitario(info, 1, h);
  info = crear_info(4, cadena_a_texto("c"));
  insertar_en_finitario(info, 1, h);

  imprimir_finitario(f);
  liberar_finitario(f);

  return 0;
}
