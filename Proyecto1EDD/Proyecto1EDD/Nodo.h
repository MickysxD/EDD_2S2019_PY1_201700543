#pragma once
#include <string>

using namespace std;

class Nodo
{
public:
	string codigo;
	int x;
	int y;

	Nodo *siguiente;
	Nodo *anterior;
	Nodo *arriba;
	Nodo *abajo;

	Nodo();
	Nodo(int x, int y, string codigo);


	~Nodo();
};