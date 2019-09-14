#include "pch.h"
#include "NodoFiltro.h"


NodoFiltro::NodoFiltro()
{
}

NodoFiltro::NodoFiltro(string nombreFiltro, Capas *capas)
{
	this->nombreFiltro = nombreFiltro;
	this->capas = capas;
}

NodoFiltro::~NodoFiltro()
{
}
