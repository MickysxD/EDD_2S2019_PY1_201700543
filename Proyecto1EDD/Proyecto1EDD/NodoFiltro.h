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

	NodoFiltro(string nombre, Capas *capas);
	

	~NodoFiltro();
};

