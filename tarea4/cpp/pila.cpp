struct rep_pila {
  nat altura;
  nat altura_maxima;
  node *tope;
};

struct node {
  texto_t texto;
  node *siguiente;
};


/*
  Devuelve una pila vacía (sin elementos) que puede tener hasta `tamanio`
  elementos.
 */
pila crear_pila(const nat tamanio){
    
    pila res = new rep_pila;
    res->altura = 0;
    res->altura_maxima = tamanio;
    res->tope = NULL;
}

/*
  Apila `t` en `p`.
  Si es_llena_pila(p) no hace nada.
 */
void apilar(const texto_t t, pila &p){
    if (!es_llena_pila(p)){
        node *res = new node;
        res->texto = t;
        res->siguiente = p->tope;
        p->tope = res;
        p->altura++;
    }
}

/*
  Remueve de `p` el elemento que está en la cima.
  No libera la memoria del elemento removido.
  Si es_vacia_pila(p) no hace nada.
 */
void desapilar(pila &p){
    node* aux = p->tope;
    delete p->tope;
    p->tope->siguiente = aux;
}

/*
  Devuelve `true` si `p` es vacía (no tiene elementos), o `false` en otro caso.
 */
bool es_vacia_pila(const pila p){
  bool res = p->tope == NULL;
  return res;
}

/*
  Devuelve `true` si la cantidad de elementos en `p` es `tamanio` (siendo
  `tamanio` el valor del parámetro con que fue creada `p`), o `false` en otro
  caso.
 */
bool es_llena_pila(const pila p){
  bool res = p->altura_maxima == p->altura;
  retunr res;
}

/*
  Devuelve el elemento que está en la cima de `p`.
  Precondición: ! es_vacia_pila(p){}
 */
texto_t cima(const pila p){
  return p->tope;
}

/*
  Libera la memoria asignada a `p` y la de todos sus elementos.
 */
void liberar_pila(pila &p){
  while (!es_vacia_pila){
    texto_t aux = p->tope->texto;
    desapilar(p);
    liberar_texto(aux);
  }
}
