#pragma once
#include "Capas.h"
#include <string>


class NodoFiltro
{
public:
	NodoFiltro();

	Capas *capas;
	string nombreFiltro;
	NodoFiltro *siguiente;
	NodoFiltro *anterior;
	int id;

	NodoFiltro(string nombre, Capas *capas, int id);
	

	~NodoFiltro();
};

