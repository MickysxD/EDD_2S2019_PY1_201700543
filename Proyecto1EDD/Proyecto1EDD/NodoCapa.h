#pragma once
#include "Matriz.h"
#include <string>

class NodoCapa
{
public:
	NodoCapa();

	NodoCapa(string nombreCapa, int noCapa, Matriz *capa);
	NodoCapa *siguiente;
	Matriz *capa;
	string nombreCapa;
	int noCapa;

	void agregarMatriz(Matriz *capa);
	void agregarSiguiente(NodoCapa *siguiente);

	~NodoCapa();
};

