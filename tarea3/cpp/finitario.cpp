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

finitario crear_finitario() {
	finitario res = new rep_finitario;
	res->primer_hijo = NULL;
	res->sig_hermano = NULL;

}

void insertar_en_finitario(const info_t i, const nat k, finitario &f) {

	finitario buscador = f->primer_hijo;
	nat j = 1; //asumo que la altura base es 1

	if (es_vacio_finitario(buscador)){
		buscador->dato = i;
		buscador->primer_hijo = NULL;
		buscador->sig_hermano = NULL;
	} else {
		while (buscador->sig_hermano != NULL || !(j == k)){
			buscador = buscador->sig_hermano;
			j++;
		}
		buscador->dato = i;
	}
}
		 



void liberar_finitario(finitario &f) {

	finitario buscador = f;

	if (buscador->sig_hermano != NULL){
		buscador = buscador->sig_hermano;
		liberar_finitario(buscador);
			if (buscador->primer_hijo != NULL){
			buscador = buscador->primer_hijo;
			liberar_finitario(buscador);
	} else {
		if (buscador->primer_hijo != NULL){
			buscador = buscador->primer_hijo;
			liberar_finitario(buscador);
		} else {
			liberar_info(buscador->dato);
			delete buscador;
		}
	}

}

bool es_vacio_finitario(const finitario f) {

	bool res = finitario == NULL;
	return res;
}

info_t raiz_finitario(const finitario f) {

//asumo que comparte memoria
	info_t res = b->dato;
	return res;

}

finitario hijo(const nat k, const finitario f) {

//asumo que comparte memoria

	finitario res = f;
	nat i = 1; //asumo que la altura base es uno

	while ((res != NULL) || i =< k );{
			res = res->primer_hijo;
			i++;
	}
	if (i != k){
		res = NULL;
	}
	return res;


}

lista nivel(nat k, const finitario f) {
	lista res = crear_lista();
	lista memoriacolgada; /*al hacerlo de manera recursiva y armar res al principio,
							muchas veces se itera de manera recursiva pero res queda vacio.
							Para solucionarlo, lo guardamos aca, y lo borramos cada vez que salimos*/
	finitario buscador  = f;
	nat j = k; //asumo que el primer nivel es 1

	if (buscador->sig_hermano != NULL){
		buscador = buscador->sig_hermano;
		memoriacolgada  = nivel(j, buscador);
		liberar_lista(memoriacolgada);
		if (buscador->primer_hijo != NULL){
			j--;
			buscador = buscador->primer_hijo;
			memoriacolgada = nivel(j, buscador);
			liberar_lista(memoriacolgada);
		}
	} else {
		if (buscador->primer_hijo != NULL || j == 0){ /*hago que j vaya yendo a cero cada vez que bajo, como no tengo una manera de
														moverme por el nivel de un finitario, agrego el j como stop de bajar*/
			j--;
			buscador = buscador->primer_hijo;
			memoriacolgada = nivel(j, buscador);
			liberar_lista(memoriacolgada);
		} else {
			insertar_antes(buscador->dato, final_lista(res), res);
			ordenar(res);
		}
	}
return res;

}

nat altura_finitario(const finitario f) {

	nat k, res;
	k = res = 0;
	nat res = altura_finitario_aux(k, res, finitario f);
	return res;

}
nat altura_finitario_aux(nat &k, nat &res, const finitario f) {

	if (buscador->sig_hermano != NULL){
		buscador = buscador->sig_hermano;
		altura_finitario_aux(k, res, buscador);
		if (buscador->primer_hijo != NULL){
			buscador = buscador->primer_hijo;
			res = std::max(++k, res);
			altura_finitario_aux(k, res, buscador);
		}
	} else {
		if (buscador->primer_hijo != NULL){
			buscador = buscador->primer_hijo;
			res = std::max(++k, res);
			altura_finitario_aux(k, res, buscador);

		} else {
			res = std::max(++k, res);
			altura_finitario_aux(k, res, buscador);
		}
	}
}
