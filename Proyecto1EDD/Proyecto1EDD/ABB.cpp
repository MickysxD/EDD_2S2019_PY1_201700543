#include "pch.h"
#include "ABB.h"


ABB::ABB()
{
	this->root = NULL;
}

void ABB::agregar(NodoABB *nuevo) {
	if (this->root == NULL)
	{
		this->root = nuevo;
	}
	else
	{
		recursivoAgregar(nuevo, this->root);
	}
}

void ABB::recursivoAgregar(NodoABB *nuevo, NodoABB *root) {
	if (nuevo->nombreImagen < root->nombreImagen) // sub-arbol izq
	{
		if (root->izq != NULL)
		{
			recursivoAgregar(nuevo, root->izq);
		}
		else
		{
			root->izq = nuevo;
		}
	}else if (nuevo->nombreImagen > root->nombreImagen) // sub-arbol der
	{
		if (root->der != NULL)
		{
			recursivoAgregar(nuevo, root->der);
		}
		else
		{
			root->der = nuevo;
		}
	}
}

ABB::~ABB()
{
}
