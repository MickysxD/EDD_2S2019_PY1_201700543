#pragma once
#include <string>

using namespace std;

class NodoABB
{
public:
	string nombre;
	NodoABB *izq;
	NodoABB *der;
	
	NodoABB();

	NodoABB(string nombre);
	NodoABB(string nombre, NodoABB *izq, NodoABB *der);

	~NodoABB();
};

