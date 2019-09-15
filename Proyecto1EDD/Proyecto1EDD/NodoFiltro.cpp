#include "pch.h"
#include "NodoFiltro.h"


NodoFiltro::NodoFiltro()
{
}

NodoFiltro::NodoFiltro(string nombreFiltro, Capas *capas, int id)
{
	this->nombreFiltro = nombreFiltro;
	this->capas = capas;
	this->id = id;
}

NodoFiltro::~NodoFiltro()
{
}
