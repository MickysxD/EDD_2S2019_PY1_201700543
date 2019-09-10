#include "pch.h"
#include "NodoCapa.h"
#include <string>

NodoCapa::NodoCapa()
{

}

NodoCapa::NodoCapa(string nombreCapa) {
	this->nombreCapa = nombreCapa;
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
