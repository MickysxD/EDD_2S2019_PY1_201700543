#pragma once
#include "NodoABB.h"

class ABB
{
public:
	ABB();

	NodoABB *root;

	void agregar(NodoABB *nuevo);
	void recursivoAgregar(NodoABB *nuevo, NodoABB *root);

	~ABB();
};

