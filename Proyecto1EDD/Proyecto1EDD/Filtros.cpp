#include "pch.h"
#include "Filtros.h"
#include "Capas.h"
#include "NodoFiltro.h"


Filtros::Filtros()
{
	this->primero == NULL;
}

void Filtros::agregarNodo(string nombreFiltro, Capas *capas)
{
	NodoFiltro *nuevo = new NodoFiltro(nombreFiltro, capas);
	if (this->primero == NULL)
	{
		this->primero = nuevo;
	}
	else
	{
		NodoFiltro *temp = this->primero;

		bool bandera = false;
		bool entra = true;
		bool igual = false;

		while (entra) {
			if (temp->nombreFiltro == nuevo->nombreFiltro)
			{
				igual = true;
			}
			else if (temp->nombreFiltro > nuevo->nombreFiltro) {
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


Filtros::~Filtros()
{
}
