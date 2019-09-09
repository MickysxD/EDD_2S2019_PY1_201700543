#pragma once
#include "Nodo.h"

using namespace std;

class Matriz
{
public:
	Matriz();

	Nodo *root;
	int contador;

	Matriz();
	Nodo* buscarX(int x);
	Nodo* buscarY(int y);

	Nodo* agregarX(Nodo *dia, Nodo *cabeza);
	Nodo* agregarY(Nodo *hora, Nodo *cabeza);
	Nodo* crearX(int x);
	Nodo* crearY(int y);

	void agregarNodo(int x, int y, string codigo);
	void imprimir();
	void csv(string direccion);
	void graficar();

	~Matriz();
};

