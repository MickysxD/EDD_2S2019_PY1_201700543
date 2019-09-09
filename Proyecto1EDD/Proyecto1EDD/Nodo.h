#pragma once
#include <string>

using namespace std;

class Nodo
{
public:
	string dia;
	string hora;
	string actividad;
	int x;
	int y;

	Nodo *siguiente;
	Nodo *anterior;
	Nodo *arriba;
	Nodo *abajo;

	Nodo();
	void adia(string dia);
	void ahora(string hora);


	~Nodo();
};