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

		bool bandera = false;
		bool entra = true;
		bool igual = false;

		while (entra) {
			if (temp->noCapa == nuevo->noCapa)
			{
				igual = true;
			}
			else if (temp->noCapa > nuevo->noCapa) {
				bandera = true;
				entra = false;
			}
			else if (temp->siguiente != NULL) {
				temp = temp->siguiente;
			}
			else {
				entra = false;
			}
		}

		if (igual)
		{
			temp->anterior->siguiente = nuevo;
			nuevo->anterior = temp->anterior;
			if (temp->siguiente != NULL)
			{
				nuevo->siguiente = temp->siguiente;
				temp->siguiente->anterior = nuevo;
			}
		}
		else if (bandera) {
			nuevo->siguiente = temp;
			temp->anterior->siguiente = nuevo;
			nuevo->anterior = temp->anterior;
			temp->anterior = nuevo;
		}
		else {
			temp->siguiente = nuevo;
			nuevo->anterior = temp;
		}

		
	}
}

Capas::~Capas()
{
}
