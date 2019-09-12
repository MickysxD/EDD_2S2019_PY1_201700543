#pragma once
#include "NodoCapa.h"

class Capas
{
public:
	Capas();

	NodoCapa *primero;

	void agregarNodo(string nombreCapa, int noCapa, Matriz *capa);

	~Capas();
};

