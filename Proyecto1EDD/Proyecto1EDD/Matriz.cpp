#include "pch.h"
#include "Matriz.h"
#include "pch.h"
#include <string>
#include <cstring>
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
	rot->x = 0;
	rot->y = 0;
	rot->codigo = "Root";
	this->root = rot;
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
		}else if (tem->siguiente != NULL) {
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
		else if (tem->abajo != NULL) {
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
		nuevo = this->agregarX(nuevo, nodoY);
		nuevo = this->agregarY(nuevo, nodoX);

	}
	else if (nodoX != NULL && nodoY != NULL) {
		nuevo = this->agregarX(nuevo, nodoY);
		nuevo = this->agregarY(nuevo, nodoX);
	}

}

void Matriz::modificarNodo(int x, int y, string codigo)
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
		nuevo = this->agregarX(nuevo, nodoY);
		nuevo = this->agregarY(nuevo, nodoX);

	}
	else if (nodoX != NULL && nodoY != NULL) {
		nuevo = this->agregarX(nuevo, nodoY);
		nuevo = this->agregarY(nuevo, nodoX);
	}

}

void Matriz::graficar(string nombre) {
	ofstream grafica;

	grafica.open(nombre + ".dot", ios::out);

	if (!grafica.fail()) {
		grafica << "digraph {" << endl << "node [shape = rectangle, height=0.5, width=1.2];" << endl << "graph [nodesep = 1];" << endl << "rankdir=TB;" << endl;

		Nodo *tempA = this->root;
		Nodo *temp = this->root;
		bool primero = true;

		while (tempA != NULL)
		{
			if (tempA == this->root)
			{
				if (temp == this->root) {
					grafica << "\"" << temp->x << "-" << temp->y << "\"[label=\"" << temp->codigo << "\"];" << endl;
					temp = temp->abajo;
				}
				else if(temp != NULL)
				{
					grafica << "\"" << temp->x << "-" << temp->y << "\"[label=\"" << temp->y << "\"];" << endl;
					temp = temp->abajo;
				}
				else
				{
					tempA = tempA->siguiente;
					temp = tempA;
				}
			}
			else {
				if (primero)
				{
					grafica << "\"" << temp->x << "-" << temp->y << "\"[label=\"" << temp->x << "\"];" << endl;
					temp = temp->abajo;
					primero = false;
				}
				else if (temp != NULL) {
					grafica << "\"" << temp->x << "-" << temp->y << "\"[label=\"" << temp->codigo << "\"];" << endl;
					temp = temp->abajo;
				}
				else
				{
					tempA = tempA->siguiente;
					temp = tempA;
					primero = true;
				}
			}
		}

		tempA = this->root;
		temp = tempA;
		
		
		while (tempA != NULL)
		{
			if (tempA == this->root)
			{
				//imprime primer nodo con abajo y derecho
				if (temp == this->root) {
					grafica << "\"" << temp->x << "-" << temp->y << "\"->\"" << temp->siguiente->x << "-" << temp->siguiente->y << "\"[dir=both];" << endl;
					grafica << "\"" << temp->x << "-" << temp->y << "\"->\"" << temp->abajo->x << "-" << temp->abajo->y << "\"[dir=both];" << endl;
					temp = temp->abajo;
				}
				else {
					//imprime nodo derecho
					if (temp->siguiente != NULL)
					{
						grafica << "\"" << temp->x << "-" << temp->y << "\"->\"" << temp->siguiente->x << "-" << temp->siguiente->y << "\"[dir=both];" << endl;
					}

					//imprime nodo abajo
					if (temp->abajo != NULL)
					{
						grafica << "\"" << temp->x << "-" << temp->y << "\"->\"" << temp->abajo->x << "-" << temp->abajo->y << "\"[dir=both];" << endl;
						temp = temp->abajo;
					}
					else
					{
						tempA = tempA->siguiente;
						temp = tempA;
					}

				}

			}
			else
			{
				//imprime primer nodo cabezera con arriba 
				if (tempA == temp) {

					//imprime nodo derecho
					if (temp->siguiente != NULL)
					{
						grafica << "\"" << temp->x << "-" << temp->y << "\"->\"" << temp->siguiente->x << "-" << temp->siguiente->y << "\"[dir=both];" << endl;
					}

					//imprime nodo abajo

					if (temp->abajo != NULL){
						grafica << "\"" << temp->x << "-" << temp->y << "\"->\"" << temp->abajo->x << "-" << temp->abajo->y << "\"[dir=both];" << endl;
						temp = temp->abajo;
					}
					else
					{
						tempA = tempA->siguiente;
						temp = tempA;
					}
				}
				else
				{

					if (temp->siguiente != NULL)//imprime nodo derecho
					{
						grafica << "\"" << temp->x << "-" << temp->y << "\"->\"" << temp->siguiente->x << "-" << temp->siguiente->y << "\"[dir=both];" << endl;
					}

					//grafica << "\"" << temp->actividad << "\"->" << temp->arriba->dia << ";" << endl; //imprime nodo arriba

					if (temp->abajo != NULL)//imprime nodo abajo
					{
						grafica << "\"" << temp->x << "-" << temp->y << "\"->\"" << temp->abajo->x << "-" << temp->abajo->y << "\"[dir=both];" << endl;
						temp = temp->abajo;
					}
					else
					{
						tempA = tempA->siguiente;
						temp = tempA;
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

				grafica << "\"" << temp->x << "-" << temp->y << "\" ";
				temp = temp->siguiente;

				while (temp != NULL)
				{
					grafica << "\"" << temp->x << "-" << temp->y << "\" ";
					temp = temp->siguiente;
				}

				grafica << "};" << endl;
				tempA = tempA->abajo;
				temp = tempA;
			}
			else {
				grafica << "{ rank=same; ";

				grafica << "\"" << temp->x << "-" << temp->y << "\" ";
				temp = temp->siguiente;

				while (temp != NULL)
				{
					grafica << "\"" << temp->x << "-" << temp->y << "\" ";
					temp = temp->siguiente;
				}

				grafica << "};" << endl;
				tempA = tempA->abajo;
				temp = tempA;
			}
		}

		grafica << "}";

		grafica.close();

		string creacion = "dot -Tjpg " + nombre + ".dot -o " + nombre + ".jpg";
		system(creacion.c_str());

		creacion = nombre + ".jpg";
		system(creacion.c_str());

	}

}

Matriz::~Matriz()
{
}
