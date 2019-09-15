#pragma once
#include "NodoFiltro.h"
#include "Matriz.h"
#include <string>
#include "Capas.h"

class Filtros
{
public:
	Filtros();
	
	NodoFiltro *primero;

	void agregarNodo(string nombreCapa, Capas *capa, int id);

	~Filtros();
};

