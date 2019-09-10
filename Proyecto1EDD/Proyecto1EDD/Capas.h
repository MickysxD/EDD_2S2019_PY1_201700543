#pragma once
#include "NodoCapa.h"

class Capas
{
public:
	Capas();

	NodoCapa *primero;

	void agregarNodo(NodoCapa *nuevo);

	~Capas();
};

