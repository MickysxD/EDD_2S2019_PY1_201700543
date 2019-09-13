#include "pch.h"
#include "ABB.h"
#include <iostream>

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
	else
	{
		cout << "Ya existe una imagen con el nombre: " << nuevo->nombreImagen << endl;
	}
}

void ABB::inorder(NodoABB *root, int *pos) {
	if (root->izq != NULL)
	{
		inorder(root->izq, pos);
	}
	cout << (*pos) << ". "<< root->nombreImagen << endl;
	root->idt = pos;
	(*pos)++;
	if (root->der != NULL)
	{
		inorder(root->der, pos);
	}
}

NodoABB* ABB::buscar(NodoABB *root, int posb) {
	if (root->idt == (*posb)) {
	
	}
	if (root->izq != NULL)
	{
		buscar(root->izq, posb);
	}
	if ((*posb) == *root->idt)
	{
		cout << "Elegido: " << root->nombreImagen;
		(*posb)++;
		return root;
	}
	if (root->der != NULL)
	{
		buscar(root->der, posb);
	}
}



ABB::~ABB()
{
}
