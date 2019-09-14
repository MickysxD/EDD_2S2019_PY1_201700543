#pragma once
#include <string>
#include "Capas.h"

using namespace std;

class NodoABB
{
public:
	string nombreImagen;
	NodoABB *izq;
	NodoABB *der;
	Capas *listaCapas;
	int idt;

	int image_width;
	int image_height;
	int pixel_width;
	int pixel_height;

	NodoABB();

	NodoABB(string nombreImagen);
	
	~NodoABB();
};

