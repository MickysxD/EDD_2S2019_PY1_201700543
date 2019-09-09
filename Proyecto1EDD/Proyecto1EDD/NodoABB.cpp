#include "pch.h"
#include "NodoABB.h"
#include <string>

using namespace std;

NodoABB::NodoABB()
{
}

NodoABB::NodoABB(string nombre)
{
	this->nombre = nombre;
}

NodoABB::NodoABB(string nombre, NodoABB *izq, NodoABB *der)
{
	this->nombre = nombre;
	this->izq = izq;
	this->der = der;
}

NodoABB::~NodoABB()
{
}
