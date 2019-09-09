#include "pch.h"
#include "Nodo.h"
#include <string>

using namespace std;

Nodo::Nodo()
{
}

Nodo::Nodo(int x, int y, string codigo)
{
	this->x = x;
	this->y = y;
	this->codigo = codigo;
}

Nodo::~Nodo()
{
}
