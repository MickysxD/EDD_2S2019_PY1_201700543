#include "pch.h"
#include "Filtros.h"
#include "Capas.h"
#include "NodoFiltro.h"


Filtros::Filtros()
{
	this->primero = NULL;
}

void Filtros::agregarNodo(string nombreFiltro, Capas *capas, int id)
{
	NodoFiltro *nuevo = new NodoFiltro(nombreFiltro, capas, id);
	if (this->primero == NULL)
	{
		this->primero = nuevo;
		this->primero->siguiente = this->primero;
		this->primero->anterior = this->primero;
	}
	else
	{
		NodoFiltro *temp = this->primero;

		bool bandera = false;
		bool entra = true;
		bool igual = false;

		while (entra) {
			if (temp->id == nuevo->id)
			{
				igual = true;
			}
			else if (temp->id > nuevo->id) {
				bandera = true;
				entra = false;
			}
			else if (temp->siguiente != this->primero) {
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
			nuevo->siguiente = temp->siguiente;
			temp->siguiente->anterior = nuevo;
		}
		else if (bandera) {
			if (temp == this->primero)
			{
				this->primero = nuevo;
			}
			nuevo->siguiente = temp;
			temp->anterior->siguiente = nuevo;
			nuevo->anterior = temp->anterior;
			temp->anterior = nuevo;
		}
		else {
			temp->siguiente = nuevo;
			nuevo->anterior = temp;
			nuevo->siguiente = this->primero;
			this->primero->anterior = nuevo;
		}

	}
}


Filtros::~Filtros()
{
}
