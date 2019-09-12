#include "pch.h"
#include "Capas.h"
#include "NodoCapa.h"


Capas::Capas()
{
}

void Capas::agregarNodo(NodoCapa *nuevo)
{
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
