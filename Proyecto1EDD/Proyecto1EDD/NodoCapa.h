#pragma once
#include "Matriz.h"
#include <string>

class NodoCapa
{
public:
	NodoCapa();

	NodoCapa(string nombreCapa);
	NodoCapa *siguiente;
	Matriz *capa;
	string nombreCapa;
	int id;

	void agregarMatriz(Matriz *capa);
	void agregarSiguiente(NodoCapa *siguiente);

	~NodoCapa();
};

