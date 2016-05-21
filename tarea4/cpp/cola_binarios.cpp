/*
  Módulo de funciones de `cola_binarios`.

  `cola_binarios` es una estructura lineal con comportamiento FIFO cuyos
   elementos son de tipo `binario`.
 */

struct rep_cola_binarios{
  nodeb *inicio;
  nodeb *final;
};

struct nodeb{
  binario *arbol;
  nodeb *anterior;
}


/*
  Devuelve una cola_binarios vacía (sin elementos).
 */
cola_binarios crear_cola_binarios(){
  cola_binarios res = new rep_cola_binarios;
  res->arbol = res->anterior = NULL;
}

/*
  Encola `b` en `c`.
 */
void encolar(const binario b, cola_binarios &c){
  nobeb* ains = new nodeb;
  ains->arbol = b;
  ains->anterior = NULL;
  c->final->anterior = ains;
  c->final = ains;
}

/*
  Remueve de `c` el elemento que está en el frente.
  No libera la memoria del elemento removido.
  Si es_vacia_cola_binarios(c) no hace nada.
 */
void desencolar(cola_binarios &c){
  if (!es_vacia_cola_binarios(c)){
      nodeb aux = c->incio->anterior;
      delete c->incio;
      c->inicio = aux;
  }
}

/*
  Devuelve `true` si `c` es vacía (no tiene elementos), o `false` en otro caso.
 */
bool es_vacia_cola_binarios(const cola_binarios c){
  bool res = c->incio == NULL;
  return res;
}

/*
  Devuelve el elemento que está en el frente de `c`.
  Precondición: ! es_vacia_cola_binarios(c);
 */
binario frente(const cola_binarios c){
  binario res = c->inicio->arbol;
  return res;
}

/*
  Libera la memoria asignada a `c`, pero NO la de sus elementos.
 */
void liberar_cola_binarios(cola_binarios &c){
  while (!es_vacia_cola_binarios(c)){
    desencolar(c);
  }
}

#endif
