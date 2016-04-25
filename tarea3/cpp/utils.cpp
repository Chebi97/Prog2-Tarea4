/*
  Módulo de implementación de 'utils'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"

#include <stdio.h>

void imprimir_comp(const comp_t comp) {
  switch (comp) {
  case menor: {
    printf("<");
    break;
  }
  case igual: {
    printf("=");
    break;
  }
  case mayor: {
    printf(">");
    break;
  }
  }
}