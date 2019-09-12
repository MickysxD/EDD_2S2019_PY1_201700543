#include "pch.h"
#include "Capas.h"
#include "NodoCapa.h"
#include <string>

Capas::Capas()
{
	this->primero == NULL;
}

void Capas::agregarNodo(string nombreCapa, int noCapa, Matriz *capa)
{
	NodoCapa *nuevo = new NodoCapa(nombreCapa, noCapa, capa);
	if (this->primero == NULL)
	{
		this->primero = nuevo;
	}
	else
	{
		NodoCapa *temp = this->primero;
		if (temp->siguiente == NULL)
		{
			temp->siguiente = nuevo;
		}
	}
}

Capas::~Capas()
{
}
