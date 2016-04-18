
/*
  Módulo principal de la tarea 3.

Intérprete de comandos para probar los módulos.

Están definidos una lista 'lst', un binario `b` y un finitario `f`.

Cada comando tiene un nombre y una lista (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido;
- se cumplen las precondiciones de las operaciones invocadas.

Si un parámetro debe ser de tipo info_t su formato cumple con lo descrito en
`info_a_texto` del módulo `info`, con el agregado de que no puede incluir el
 símbolo ')'.
Una secuencia de elementos de un tipo es terminada por un espacio en blanco
seguido de un punto.

Descripción de los comandos:

Fin
   Termina el programa
# comentario
   Imprime nueva línea.
insertar_lista secuencia_info_t .
   Inserta en `lst` cada elemento de la secuencia leída.
recorrido
   recorre `lst` imprimiendo sus elementos.
segmentos clave1 clave2
   manipula la sublista de `lst` desde la primera aparición de `clave1` hasta
   la última aparición de `clave2`, donde `clave1` y `clave2` son enteros.
modificar_lista clave1 clave2
   modifica `lst`, utilizando las apariciones de los enteros `clave1` y
   `clave2`.
ordenar_lista
   realiza algunas operaciones sobre `lst`.
filtrado_lista clave criterio
   realiza algunas operaciones sobre `lst` con el entero `clave` y `criterio`.
reversa_lista dato1 dato2
   realiza algunas operaciones sobre `lst` con los enteros `dato1` y `dato2`.

insertar_binario secuencia_info_t .
   Inserta en `b` cada elemento de la secuencia leída.
remover_binario secuencia_texto_t .
   Remueve de `b` cada elemento de la secuencia leída.
filtrar_binario clave criterio
   Invoca filtrar_binario en `b` con los parámetros leídos.
cantidad_caminos secuencia_info_t .
   Invoca cantidad_caminos en `b` con la secuencia leída.
buscar_camino secuencia_info_t .
   Invoca buscar_camino  en `b` con la secuencia leída.
buscar_subarbol patron
   Invoca buscar_subarbol  en `b` con el patrón leído.
kesimo_subarbol cantidad
   Invoca kesimo_subarbol en `b` con la cantidad leída.
finitario info secuencia_enteros_mayores_que_0 .
   Inserta `info` en `f`.
   Con la secuencia de enteros se establece de que nodo será hijo.
   Por ejemplo
   finitario (3,t) 3 1 2 .
   inserta (3,t) como el segundo hijo del primer hijo del tercer hijo de `f`.
   Se asume que cada número de la secuencia, excepto el último, es mayor que
   cero y menor o igual que la cantidad de hijos del nodo que le corresponde.
   El último número puede ser mayor que la cantidad de hijos del nodo en que
   se va a insertar `info`
   Si `f` es vacío la secuencia es ignorada.
liberar_estructuras
   libera la memoria asignada a `lst`, `b` y `f` y los vuelve a crear.



  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/utils.h"
#include "include/texto.h"
#include "include/info.h"
#include "include/lista.h"
#include "include/binario.h"
#include "include/uso_lista_arboles.h"
#include "include/finitario.h"

#define MAX_RESTO_LINEA 200
#define MAX_LARGO_PALABRA 30

// mensajes
const texto_t msg_fin = cadena_a_texto("Fin.");
const texto_t msg_cmd_no_reconocido = cadena_a_texto("Comando no reconocido.");

const texto_t prompt = char_a_texto('>');

const texto_t fin_comando = cadena_a_texto(".");

/* Estructura para identificar el nombre de comando */
enum enum_cmd_t {
  cmd_fin,
  cmd_comentario,
  cmd_ins_lista,
  cmd_recorrido_lista,
  cmd_segmentos_lista,
  cmd_modificar_lista,
  cmd_ordenar_lista,
  cmd_filtrado_lista,
  cmd_reversa_lista,
  cmd_ins_binario,
  cmd_rmv_binario,
  cmd_flt_binario,
  cmd_cnt_caminos,
  cmd_bsc_camino,
  cmd_bsc_subarbol,
  cmd_k_subarbol,
  cmd_finitario,
  cmd_liberar_estructuras,
  no_reconocido
};
const nat cant_com = no_reconocido;

struct enum_nombre_cmd {
  const enum_cmd_t enum_cmd;
  const char *nombre_cmd;
};

/*
  Asociación entre nombre de comando y enumerado.
 */
const enum_nombre_cmd cmds[] = {
    {cmd_fin, "Fin"},
    {cmd_comentario, "#"},
    {cmd_ins_lista, "insertar_lista"},
    {cmd_recorrido_lista, "recorrido"},
    {cmd_segmentos_lista, "segmentos"},
    {cmd_modificar_lista, "modificar_lista"},
    {cmd_ordenar_lista, "ordenar_lista"},
    {cmd_filtrado_lista, "filtrado_lista"},
    {cmd_reversa_lista, "reversa_lista"},
    {cmd_ins_binario, "insertar_binario"},
    {cmd_rmv_binario, "remover_binario"},
    {cmd_flt_binario, "filtrar_binario"},
    {cmd_cnt_caminos, "cantidad_caminos"},
    {cmd_bsc_camino, "buscar_camino"},
    {cmd_bsc_subarbol, "buscar_subarbol"},
    {cmd_k_subarbol, "kesimo_subarbol"},
    {cmd_finitario, "finitario"},
    {cmd_liberar_estructuras, "liberar_estructuras"}};

/*
  Devuelve el identificador de comando leido desde la entrada estándar.
 */
enum_cmd_t identificador_comando() {
  enum_cmd_t res = no_reconocido;
  texto_t nom_com = leer_palabra(MAX_LARGO_PALABRA);

  bool encontrado = false;
  nat i = cmd_fin; // = 0
  while ((!encontrado) && (i < cant_com)) {
    texto_t nom_item = cadena_a_texto(cmds[i].nombre_cmd);
    if (igual == comparar_texto(nom_com, nom_item)) {
      res = cmds[i].enum_cmd;
      encontrado = true;
    } else {
      i++;
    }
    liberar_texto(nom_item);
  }
  liberar_texto(nom_com);
  return res;
} // identificador_comando

/*
  Incrementa el contador de comandos y muestra el prompt.
 */
void mostrar_prompt(nat &cont_comandos) {
  cont_comandos++;
  texto_t cont_com_txt = int_a_texto(cont_comandos);
  escribir_texto(cont_com_txt);
  escribir_texto(prompt);
  liberar_texto(cont_com_txt);
} // mostrar_prompt

/*
 Imprime `txt` seguido de nueva línea.
 */
void imprimir_con_nl(texto_t txt) {
  escribir_texto(txt);
  escribir_nueva_linea();
} // imprimir_nl

/*
  Lee desde la entrada estándar un texto y devuelve su conversión a entero.
 */
int leer_int() {
  texto_t txt_int = leer_palabra(MAX_LARGO_PALABRA);
  int res = texto_a_int(txt_int);
  liberar_texto(txt_int);
  return res;
} // leer_int

/*
  Imprime `n` seguido de nueva línea.
 */
void imprimir_int(int n) {
  texto_t txt_int = int_a_texto(n);
  imprimir_con_nl(txt_int);
  liberar_texto(txt_int);
} // imprimir_int

/*
  Lee una lista de info_t desde la entrada estándar. Después de cada elemento
  hay un espacio en blanco. Termina con un punto.
 */
lista leer_lista() {
  lista res = crear_lista();
  info_t info = leer_info(MAX_LARGO_PALABRA);
  while (es_valida_info(info)) {
    insertar_despues(info, final_lista(res), res);
    info = leer_info(MAX_LARGO_PALABRA);
  }
  liberar_info(info);
  return res;
} // leer_lista

int main() {
  lista lst = crear_lista();
  binario b = crear_binario();
  finitario f = crear_finitario();

  nat cont_comandos = 0;
  bool salir = false;
  while (!salir) {

    mostrar_prompt(cont_comandos);
    enum_cmd_t enum_com = identificador_comando();

    // procesar el comando
    switch (enum_com) {
    case cmd_fin:
      salir = true;
      imprimir_con_nl(msg_fin);
      break;
    case cmd_comentario:
      escribir_nueva_linea();
      break;
    case cmd_ins_lista: {
      info_t info = leer_info(MAX_LARGO_PALABRA);
      while (es_valida_info(info)) {
        insertar_despues(info, final_lista(lst), lst);
        info = leer_info(MAX_LARGO_PALABRA);
      }
      liberar_info(info);
      texto_t txt = cadena_a_texto("primero");
      info = crear_info(0, txt);
      insertar_antes(info, inicio_lista(lst), lst);
      imprimir_lista(lst);
      break;
    }
    case cmd_recorrido_lista: {
      if (!es_vacia_lista(lst)) {
        localizador loc = inicio_lista(lst);
        while (es_localizador_lista(loc)) {
          texto_t txt = info_a_texto(info_lista(loc, lst));
          escribir_texto(txt);
          liberar_texto(txt);
          loc = siguiente(loc, lst);
        }
        loc = final_lista(lst);
        while (es_localizador_lista(loc)) {
          texto_t txt = info_a_texto(info_lista(loc, lst));
          escribir_texto(txt);
          liberar_texto(txt);
          loc = anterior(loc, lst);
        }
        escribir_nueva_linea();
      }
      break;
    }
    case cmd_segmentos_lista: {
      int clave1 = leer_int();
      int clave2 = leer_int();
      localizador desde = siguiente_clave(clave1, inicio_lista(lst), lst);
      localizador hasta = anterior_clave(clave2, final_lista(lst), lst);
      if (es_localizador_lista(desde) && es_localizador_lista(hasta) &&
          precede_en_lista(desde, hasta, lst)) {
        lista sgm = separar_segmento(desde, hasta, lst);
        lista copia = segmento_lista(inicio_lista(sgm), final_lista(sgm), sgm);
        imprimir_lista(sgm);
        liberar_lista(sgm);
        insertar_segmento_despues(copia, final_lista(lst), lst);
        liberar_lista(copia);
        imprimir_lista(lst);
      }
      break;
    }
    case cmd_modificar_lista: {
      int clave1 = leer_int();
      int clave2 = leer_int();
      localizador loc1 = siguiente_clave(clave1, inicio_lista(lst), lst);
      localizador loc2 = anterior_clave(clave2, final_lista(lst), lst);
      if (es_localizador_lista(loc1) && es_localizador_lista(loc2)) {
        intercambiar(loc1, loc2, lst);
        imprimir_lista(lst);
        if (!es_inicio_lista(loc2, lst)) {
          localizador ant = anterior(loc2, lst);
          lista prefijo = segmento_lista(inicio_lista(lst), ant, lst);
          if (esta_ordenada(prefijo))
            retroceder(loc2, lst);
          liberar_lista(prefijo);
        }
        imprimir_lista(lst);
      }
      break;
    }
    case cmd_ordenar_lista: {
      nat len_lst = longitud(lst);
      imprimir_int(len_lst);
      localizador loc = inicio_lista(lst);
      for (nat i = 0; i < len_lst / 2 - 1; i++)
        loc = siguiente(loc, lst);
      lista primera = segmento_lista(inicio_lista(lst), loc, lst);
      lista segunda =
          segmento_lista(siguiente(loc, lst), final_lista(lst), lst);

      lista concat = concatenar(primera, segunda);
      imprimir_lista(concat);
      liberar_lista(concat);

      if (son_numeros_iguales(primera, segunda)) {
        imprimir_lista(primera);
      }

      if (!esta_ordenada(primera))
        ordenar(primera);
      if (!esta_ordenada(segunda))
        ordenar(segunda);

      lista mzc = mezcla(primera, segunda);
      imprimir_lista(mzc);

      unificar(mzc);
      imprimir_lista(mzc);
      liberar_lista(mzc);
      liberar_lista(primera);
      liberar_lista(segunda);
      break;
    }
    case cmd_filtrado_lista: {
      int clave = leer_int();
      texto_t palabra = leer_palabra(MAX_LARGO_PALABRA);
      comp_t criterio = texto_a_comp(palabra);
      liberar_texto(palabra);
      if (pertenece(clave, lst)) {
        imprimir_int(cantidad(clave, lst));
      }
      lista flt = filtrado(clave, criterio, lst);
      imprimir_lista(flt);
      liberar_lista(flt);
      break;
    }
    case cmd_reversa_lista: {
      int dato1 = leer_int();
      int dato2 = leer_int();
      if (esta_ordenada(lst) && pertenece(dato1, lst) &&
          pertenece(dato2, lst) && dato1 < dato2) {
        lista sub = sublista(dato1, dato2, lst);
        imprimir_lista(sub);
        lista rev = reversa(sub);
        imprimir_lista(rev);
        cambiar_todos(dato1, dato2, rev);
        imprimir_lista(rev);
        liberar_lista(sub);
        liberar_lista(rev);
      }
      break;
    }

    case cmd_ins_binario: {
      info_t info = leer_info(MAX_LARGO_PALABRA);
      while (es_valida_info(info)) {
        bool inserto = insertar_en_binario(info, b);
        if (!inserto)
          liberar_info(info);
        info = leer_info(MAX_LARGO_PALABRA);
      }
      liberar_info(info);
      escribir_nueva_linea();
      imprimir_binario(b);
      if (!es_vacio_binario(b)) {
        imprimir_int(altura_binario(izquierdo(b)));
        imprimir_int(cantidad_binario(derecho(b)));
      }
      break;
    }
    case cmd_rmv_binario: {
      texto_t palabra = leer_palabra(MAX_LARGO_PALABRA);
      while (comparar_texto(fin_comando, palabra) != igual) {
        remover_de_binario(palabra, b);
        liberar_texto(palabra);
        palabra = leer_palabra(MAX_LARGO_PALABRA);
      }
      liberar_texto(palabra);
      escribir_nueva_linea();
      if (!es_vacio_binario(b)) {
        info_t mayor = remover_mayor(b);
        texto_t txt_mayor = info_a_texto(mayor);
        imprimir_con_nl(txt_mayor);
        liberar_texto(txt_mayor);
        liberar_info(mayor);
      }
      imprimir_binario(b);
      break;
    }
    case cmd_flt_binario: {
      int clave = leer_int();
      texto_t palabra = leer_palabra(MAX_LARGO_PALABRA);
      comp_t criterio = texto_a_comp(palabra);
      liberar_texto(palabra);
      binario flt = crear_filtrado(clave, criterio, b);
      escribir_nueva_linea();
      imprimir_binario(flt);
      liberar_binario(flt);
      break;
    }
    case cmd_cnt_caminos: {
      lista lst = leer_lista();
      imprimir_int(cantidad_de_caminos(lst, b));
      liberar_lista(lst);
      break;
    }
    case cmd_bsc_camino: {
      lista lst = leer_lista();
      camino_t camino = buscar_camino(lst, b);
      texto_t txt_cam = camino_a_texto(camino);
      imprimir_con_nl(txt_cam);
      liberar_lista(lst);
      delete[] camino.ramas;
      liberar_texto(txt_cam);
      break;
    }
    case cmd_bsc_subarbol: {
      texto_t palabra = leer_palabra(MAX_LARGO_PALABRA);
      binario sub = buscar_subarbol(palabra, b);
      escribir_nueva_linea();
      imprimir_binario(sub);
      liberar_texto(palabra);
      break;
    }
    case cmd_k_subarbol: {
      int k = leer_int();
      binario sub = kesimo_subarbol(k, b);
      if (!es_vacio_binario(sub)) {
        texto_t palabra = info_a_texto(raiz_binario(sub));
        imprimir_con_nl(palabra);
        liberar_texto(palabra);
      }
      break;
    }
    case cmd_finitario: {
      if (!es_vacio_finitario(f)) {
        texto_t t = info_a_texto(raiz_finitario(f));
        imprimir_con_nl(t);
        liberar_texto(t);
      }
      imprimir_finitario(f);
      imprimir_int(altura_finitario(f));
      nat nvl = 1;
      info_t info = leer_info(MAX_LARGO_PALABRA);
      if (es_vacio_finitario(f))
        insertar_en_finitario(info, 1, f);
      else {
        nvl++;
        finitario padre = f;
        int pos = leer_int();
        int ant = leer_int();
        while (ant != 0) {
          nvl++;
          padre = hijo(pos, padre);
          pos = ant;
          ant = leer_int();
        }
        insertar_en_finitario(info, pos, padre);
      }
      lista lst_nivel = nivel(nvl, f);
      imprimir_lista(lst_nivel);
      liberar_lista(lst_nivel);
      break;
    }
    case cmd_liberar_estructuras: {
      liberar_lista(lst);
      lst = crear_lista();
      liberar_binario(b);
      b = crear_binario();
      liberar_finitario(f);
      f = crear_finitario();
      break;
    }

    default:
      imprimir_con_nl(msg_cmd_no_reconocido);
      break;
    } // switch
    texto_t resto_linea = leer_resto_linea(MAX_RESTO_LINEA);
    liberar_texto(resto_linea);
  } // while

  liberar_lista(lst);
  liberar_binario(b);
  liberar_finitario(f);
  return 0;
}
