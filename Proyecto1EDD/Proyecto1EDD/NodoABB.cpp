#include "pch.h"
#include "NodoABB.h"
#include "Capas.h"
#include <string>


using namespace std;

NodoABB::NodoABB()
{
}

NodoABB::NodoABB(string nombreImagen)
{
	this->nombreImagen = nombreImagen;
	this->listaCapas = new Capas();
}

NodoABB::~NodoABB()
{
}
