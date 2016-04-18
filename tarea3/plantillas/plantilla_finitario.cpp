#include "../include/texto.h"
#include "../include/info.h"
#include "../include/lista.h"
#include "../include/uso_lista_arboles.h"
#include "../include/finitario.h"

#include <stdlib.h>

struct rep_finitario {
  info_t dato;
  rep_finitario *primer_hijo;
  rep_finitario *sig_hermano;
};

finitario crear_finitario() {}

void insertar_en_finitario(const info_t i, const nat k, finitario &f) {}

void liberar_finitario(finitario &f) {}

bool es_vacio_finitario(const finitario f) {}

info_t raiz_finitario(const finitario f) {}

finitario hijo(const nat k, const finitario f) {}

lista nivel(nat k, const finitario f) {}

nat altura_finitario(const finitario f) {}
