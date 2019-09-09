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
	Nodo* buscarDia(string dia);
	Nodo* buscarHora(string hora);

	Nodo* agregarDia(Nodo *dia, Nodo *cabeza);
	Nodo* agregarHora(Nodo *hora, Nodo *cabeza);
	Nodo* crearDia(string dia);
	Nodo* crearHora(string hora);

	void agregarA(string dia, string hora, string actividad);
	void imprimir();
	void imprimird(string dia);
	void csv(string dia);
	void graficar();

	~Matriz();
};

