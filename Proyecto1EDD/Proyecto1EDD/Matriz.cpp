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

Nodo* Matriz::buscarDia(string dia)
{
	Nodo *temp = this->root->siguiente;
	while (temp != NULL) {
		if (dia.compare(temp->dia) == 0)
		{
			return temp;
		}
		temp = temp->siguiente;
	}

	return temp;
}

Nodo* Matriz::buscarHora(string hora)
{
	Nodo *temp = this->root->abajo;
	while (temp != NULL) {
		if (hora.compare(temp->hora) == 0)
		{
			return temp;
		}
		temp = temp->abajo;
	}

	return temp;
}

Nodo* Matriz::agregarDia(Nodo *dia, Nodo *cabeza)
{
	Nodo *tem = cabeza;
	Nodo *nuevo = dia;
	bool bandera = false;
	bool entra = true;

	while (entra) {
		if (tem->x == nuevo->x) {
			tem->y = nuevo->y;
			tem->dia = nuevo->dia;
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


	/*
	if(tem == NULL){
		this->root->siguiente = nuevo;
		return *nuevo;
	}else {
		Nodo *ant = tem;
		while(tem != NULL){
			if(nuevo->id > tem->id){
				ant = tem;
				tem = tem->siguiente;
			}else if(tem->id > nuevo->id){
				nuevo->siguiente = tem;
				ant->siguiente = nuevo;
				return *nuevo;
			}
		}
	}
	return *nuevo;
	*/

}

Nodo* Matriz::agregarHora(Nodo *hora, Nodo *cabeza)
{
	Nodo *tem = cabeza;
	Nodo *nuevo = hora;
	bool bandera = false;
	bool entra = true;

	while (entra) {
		if (tem->y == nuevo->y) {
			tem->x = nuevo->x;
			tem->hora = nuevo->hora;
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


	/*
	if(tem == NULL){
		this->root->siguiente = nuevo;
		return *nuevo;
	}else {
		Nodo *ant = tem;
		while(tem != NULL){
			if(nuevo->id > tem->id){
				ant = tem;
				tem = tem->siguiente;
			}else if(tem->id > nuevo->id){
				nuevo->siguiente = tem;
				ant->siguiente = nuevo;
				return *nuevo;
			}
		}
	}
	return *nuevo;
	*/

}

Nodo* Matriz::crearDia(string dia) {
	Nodo *adia = new Nodo();
	adia->adia(dia);
	Nodo *cabeza = this->root;
	return this->agregarDia(adia, cabeza);
}

Nodo* Matriz::crearHora(string hora) {
	Nodo *ahora = new Nodo();
	ahora->ahora(hora);
	Nodo *cabeza = this->root;
	return this->agregarHora(ahora, cabeza);
}

void Matriz::agregarA(string dia, string hora, string actividad)
{
	Nodo *nuevo = new Nodo();
	nuevo->actividad = actividad;
	nuevo->adia(dia);
	nuevo->ahora(hora);

	Nodo *diaa = this->buscarDia(dia);
	Nodo *horaa = this->buscarHora(hora);

	if (diaa == NULL && horaa == NULL) {
		diaa = this->crearDia(dia);
		horaa = this->crearHora(hora);
		nuevo = this->agregarDia(nuevo, horaa);
		nuevo = this->agregarHora(nuevo, diaa);

	}
	else if (diaa != NULL && horaa == NULL) {
		horaa = this->crearHora(hora);
		nuevo = this->agregarDia(nuevo, horaa);
		nuevo = this->agregarHora(nuevo, diaa);

	}
	else if (diaa == NULL && horaa != NULL) {
		diaa = this->crearDia(dia);
		nuevo = this->agregarDia(nuevo, horaa);
		nuevo = this->agregarHora(nuevo, diaa);

	}
	else if (diaa != NULL && horaa != NULL) {
		nuevo = this->agregarDia(nuevo, horaa);
		nuevo = this->agregarHora(nuevo, diaa);
	}

}

void Matriz::imprimir()
{
	Nodo *dia = this->root->siguiente;
	while (dia != NULL) {
		Nodo *actividad = dia->abajo;
		cout << "Dia: " << actividad->dia << endl;
		while (actividad != NULL) {
			cout << "	Hora: " << actividad->hora << "		Actividad: " << actividad->actividad << endl;
			actividad = actividad->abajo;
		}
		dia = dia->siguiente;
	}
}

void Matriz::imprimird(string dia)
{

	Nodo *diat = this->root->siguiente;
	while (dia.compare(diat->dia) != 0) {

		diat = diat->siguiente;
	}

	if (diat != NULL) {
		Nodo *actividad = diat->abajo;
		cout << "Dia: " << actividad->dia << endl;
		while (actividad != NULL) {
			cout << "	Hora: " << actividad->hora << "		Actividad: " << actividad->actividad << endl;
			actividad = actividad->abajo;
		}
	}
	else
	{
		cout << "Dia no existe " << endl;
	}

}

void Matriz::csv(string dia) {

	ifstream lectura;
	lectura.open(dia, ios::in);

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
