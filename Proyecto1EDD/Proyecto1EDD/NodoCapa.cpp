#include "pch.h"
#include "NodoCapa.h"
#include <string>
#include "Matriz.h"

NodoCapa::NodoCapa()
{

}

NodoCapa::NodoCapa(string nombreCapa, int noCapa, Matriz *capa) {
	this->nombreCapa = nombreCapa;
	this->noCapa = noCapa;
	this->capa = capa;
}

void NodoCapa::agregarMatriz(Matriz *capa) {
	this->capa = capa;
}

void NodoCapa::agregarSiguiente(NodoCapa *siguiente) {
	this->siguiente = siguiente;
}

NodoCapa::~NodoCapa()
{
}
