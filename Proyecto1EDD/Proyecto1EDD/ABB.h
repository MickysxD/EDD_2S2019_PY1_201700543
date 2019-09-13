#pragma once
#include "NodoABB.h"
#include <vector>

class ABB
{
public:
	ABB();

	NodoABB *root;

	void agregar(NodoABB *nuevo);
	void recursivoAgregar(NodoABB *nuevo, NodoABB *root);
	void inorder(NodoABB *root, int *pos);
	NodoABB *buscar(NodoABB *root, int posb);
	~ABB();
};

