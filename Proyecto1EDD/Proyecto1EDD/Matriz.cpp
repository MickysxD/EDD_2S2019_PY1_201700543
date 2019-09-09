#include "pch.h"
#include "Matriz.h"
#include "pch.h"
#include <string>
#include "Nodo.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <iterator>
#include <sstream>
#include <vector>


using namespace std;

Matriz::Matriz()
{
	Nodo *rot = new Nodo();
	rot->adia("0");
	rot->ahora("0");
	rot->actividad = "Root";
	this->root = rot;
	this->contador = 0;
}

Nodo* Matriz::buscarX(int x)
{
	Nodo *temp = this->root->siguiente;
	while (temp != NULL) {
		if (temp->x == x)
		{
			return temp;
		}
		temp = temp->siguiente;
	}

	return temp;
}

Nodo* Matriz::buscarY(int y)
{
	Nodo *temp = this->root->abajo;
	while (temp != NULL) {
		if (temp->y == y)
		{
			return temp;
		}
		temp = temp->abajo;
	}

	return temp;
}

Nodo* Matriz::agregarX(Nodo *x, Nodo *cabeza)
{
	Nodo *tem = cabeza;
	Nodo *nuevo = x;
	bool bandera = false;
	bool entra = true;

	while (entra) {
		if (tem->x == nuevo->x) {
			tem->y = nuevo->y;
			tem->codigo = nuevo->codigo;
			return tem;
		}
		else if (tem->x > nuevo->x) {
			bandera = true;
			entra = false;
		}
		if (tem->siguiente != NULL) {
			tem = tem->siguiente;
		}
		else {
			entra = false;
		}
	}

	if (bandera) {
		nuevo->siguiente = tem;
		tem->anterior->siguiente = nuevo;
		nuevo->anterior = tem->anterior;
		tem->anterior = nuevo;
	}
	else {
		tem->siguiente = nuevo;
		nuevo->anterior = tem;
	}

	return nuevo;

}

Nodo* Matriz::agregarY(Nodo *y, Nodo *cabeza)
{
	Nodo *tem = cabeza;
	Nodo *nuevo = y;
	bool bandera = false;
	bool entra = true;

	while (entra) {
		if (tem->y == nuevo->y) {
			tem->x = nuevo->x;
			tem->codigo = nuevo->codigo;
			return tem;
		}
		else if (tem->y > nuevo->y) {
			bandera = true;
			entra = false;
		}
		if (tem->abajo != NULL) {
			tem = tem->abajo;
		}
		else {
			entra = false;
		}
	}

	if (bandera) {
		nuevo->abajo = tem;
		tem->arriba->abajo = nuevo;
		nuevo->arriba = tem->arriba;
		tem->arriba = nuevo;
	}
	else {
		tem->abajo = nuevo;
		nuevo->arriba = tem;
	}

	return nuevo;

}

Nodo* Matriz::crearX(int x) {
	Nodo *nX = new Nodo();
	nX->x = x;
	Nodo *cabeza = this->root;
	return this->agregarX(nX, cabeza);
}

Nodo* Matriz::crearY(int y) {
	Nodo *nY = new Nodo();
	nY->y = y;
	Nodo *cabeza = this->root;
	return this->agregarY(nY, cabeza);
}

void Matriz::agregarNodo(int x, int y, string codigo)
{
	Nodo *nuevo = new Nodo();
	nuevo->codigo = codigo;
	nuevo->x = x;
	nuevo->y = y;

	Nodo *nodoX = this->buscarX(x);
	Nodo *nodoY = this->buscarY(y);

	if (nodoX == NULL && nodoY == NULL) {
		nodoX = this->crearX(x);
		nodoY = this->crearY(y);
		nuevo = this->agregarX(nuevo, nodoY);
		nuevo = this->agregarY(nuevo, nodoX);

	}
	else if (nodoX != NULL && nodoY == NULL) {
		nodoY = this->crearY(y);
		nuevo = this->agregarX(nuevo, nodoY);
		nuevo = this->agregarY(nuevo, nodoX);

	}
	else if (nodoX == NULL && nodoY != NULL) {
		nodoX = this->crearX(x);
		nuevo = this->agregarX(nuevo, nodoX);
		nuevo = this->agregarY(nuevo, nodoY);

	}
	else if (nodoX != NULL && nodoY != NULL) {
		nuevo = this->agregarX(nuevo, nodoX);
		nuevo = this->agregarY(nuevo, nodoY);
	}

}

void Matriz::imprimir()
{
	Nodo *nodoX = this->root->siguiente;
	while (nodoX != NULL) {
		Nodo *nodo = nodoX->abajo;
		cout << "X: " << nodo->x << endl;
		while (nodo != NULL) {
			cout << "	Y: " << nodo->y << "		Codigo: " << nodo->codigo << endl;
			nodo = nodo->abajo;
		}
		nodoX = nodoX->siguiente;
	}
}

void Matriz::csv(string direccion) {

	ifstream lectura;
	lectura.open(direccion, ios::in);

	if (!lectura.fail()) {
		int p = 0;
		for (string linea; getline(lectura, linea); )
		{
			string temp;
			vector<string> lista;
			size_t found;

			found = linea.find(",");
			lista.push_back(linea.substr(0, found));

			temp = linea.substr(found + 1, linea.length());
			found = temp.find(",");

			while (found != 4294967295) {
				lista.push_back(temp.substr(0, found));
				temp = temp.substr(found + 1, linea.length());
				found = temp.find(",");
			}

			lista.push_back(temp.substr(0, linea.length()));

			if (p == 0)
			{
				for (int i = 1; i < 8; i++)
				{
					crearDia(lista[i]);
				}
				p++;
			}
			else
			{
				for (int i = 0; i < 8; i++)
				{
					if (i == 0)
					{
						crearHora(lista[0]);
					}
					else if (lista[i].compare("x") != 0)
					{
						switch (i) {
						case 1:
							agregarA("lunes", lista[0], lista[i]);
							break;
						case 2:
							agregarA("martes", lista[0], lista[i]);
							break;
						case 3:
							agregarA("miercoles", lista[0], lista[i]);
							break;
						case 4:
							agregarA("jueves", lista[0], lista[i]);
							break;
						case 5:
							agregarA("viernes", lista[0], lista[i]);
							break;
						case 6:
							agregarA("sabado", lista[0], lista[i]);
							break;
						case 7:
							agregarA("domingo", lista[0], lista[i]);
							break;
						}
					}
				}
			}

		}
	}
	else
	{
		cout << "archivo no entontrado" << endl;
	}

}

void Matriz::graficar() {
	ofstream grafica;

	grafica.open("grafica.dot", ios::out);

	if (!grafica.fail()) {
		grafica << "digraph  Grafico {" << endl << "node [shape = rectangle];" << endl << "node[nodesep = 1];" << endl << "rankdir=TB;" << endl;

		Nodo *tempA = this->root;
		Nodo *temp = this->root;
		bool primero = true;

		while (tempA != NULL)
		{
			if (tempA == this->root)
			{
				//imprime primer nodo con abajo y derecho
				if (temp == this->root) {
					grafica << "" << temp->actividad << "->" << temp->siguiente->dia << "[dir=both];" << endl;
					grafica << "" << temp->actividad << "->" << temp->abajo->hora << "[dir=both];" << endl;
					temp = temp->abajo;
				}
				else {
					//imprime nodo arriba
					/*if (temp->arriba == this->root)
					{
						grafica << "" << temp->hora << "->" << temp->arriba->actividad << ";" << endl;
					}
					else
					{
						grafica << "" << temp->hora << "->" << temp->arriba->hora << ";" << endl;
					}*/

					//imprime nodo derecho
					if (temp->siguiente != NULL)
					{
						grafica << "" << temp->hora << "->\"" << temp->siguiente->actividad << "\"[dir=both];" << endl;
					}

					//imprime nodo abajo
					if (temp->abajo == NULL)
					{
						tempA = tempA->siguiente;
						temp = tempA;
					}
					else
					{
						grafica << "" << temp->hora << "->" << temp->abajo->hora << "[dir=both];" << endl;
						temp = temp->abajo;
					}

				}

			}
			else
			{
				//imprime primer nodo cabezera con arriba 
				if (tempA == temp) {
					//imprime nodo izquierdo
					/*if (temp->anterior == this->root)
					{
						grafica << "" << temp->dia << "->" << temp->anterior->actividad << ";" << endl;
					}
					else
					{
						grafica << "" << temp->dia << "->" << temp->anterior->dia << ";" << endl;
					}*/

					//imprime nodo derecho
					if (temp->siguiente != NULL)
					{
						grafica << "" << temp->dia << "->" << temp->siguiente->dia << "[dir=both];" << endl;
					}

					//imprime nodo abajo
					grafica << "" << temp->dia << "->\"" << temp->abajo->actividad << "\"[dir=both];" << endl;
					temp = temp->abajo;
				}
				else
				{
					//if (temp->anterior->x == 0)//imprime nodo izquierdo
					//{
					//	grafica << "\"" << temp->actividad << "\"->" << temp->anterior->hora << ";" << endl;
					//}
					//else
					//{
					//	grafica << "\"" << temp->actividad << "\"->\"" << temp->anterior->actividad << "\";" << endl;
					//}

					if (temp->siguiente != NULL)//imprime nodo derecho
					{
						grafica << "\"" << temp->actividad << "\"->\"" << temp->siguiente->actividad << "\"[dir=both];" << endl;
					}

					//grafica << "\"" << temp->actividad << "\"->" << temp->arriba->dia << ";" << endl; //imprime nodo arriba

					if (temp->abajo == NULL)//imprime nodo abajo
					{
						tempA = tempA->siguiente;
						temp = tempA;
					}
					else
					{
						grafica << "\"" << temp->actividad << "\"->\"" << temp->abajo->actividad << "\"[dir=both];" << endl;
						temp = temp->abajo;
					}
				}
			}
		}

		tempA = this->root;
		temp = tempA;

		while (tempA != NULL)
		{
			if (tempA == this->root)
			{
				grafica << "{ rank=same; ";

				grafica << temp->actividad << " ";
				temp = temp->siguiente;

				while (temp != NULL)
				{
					grafica << temp->dia << " ";
					temp = temp->siguiente;
				}

				grafica << "};" << endl;
				tempA = tempA->abajo;
				temp = tempA;
			}
			else {
				grafica << "{ rank=same; ";

				grafica << temp->hora << " ";
				temp = temp->siguiente;

				while (temp != NULL)
				{
					grafica << "\"" << temp->actividad << "\" ";
					temp = temp->siguiente;
				}

				grafica << "};" << endl;
				tempA = tempA->abajo;
				temp = tempA;
			}
		}

		grafica << "} ";


		system("dot -Tjpg grafica.dot -o grafica.jpg");
		system("grafica.jpg");

	}


	grafica.close();


}

Matriz::~Matriz()
{
}
