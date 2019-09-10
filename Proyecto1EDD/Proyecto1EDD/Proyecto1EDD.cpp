
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ABB.h"
#include "NodoABB.h"

using namespace std;

ABB *arbol = new ABB();

void menu();
void insertarImagen();

int main()
{
	/*string a = "aaa";
	string b = "aa";
	string c = "aa";

	if (a < b)
	{
		cout << "b mayor a a\n";
	}
	if(a > b)
	{
		cout << "a mayor a b\n";
	}
	if (a == b)
	{
		cout << "igual\n";
	}
*/

	while (true)
	{
		menu();
	}
}

void menu() {
	int eleccion;

	cout << "-------------------- Menu PhotGen++ --------------------\n";
	cout << "1. Insertar Imagen\n";
	cout << "2. Seleccionar Imagen\n";
	cout << "3. Aplicar Filtros\n";
	cout << "4. Ediccion Manual\n";
	cout << "5. Exportar Imagen\n";
	cout << "6. Reportes\n\n";
	cout << "Ingrese el numero a de la accion a realizar: ";
	cin >> eleccion;
	cout << "-------------------- Menu PhotGen++ --------------------\n";
	cout << "\n\n\n\n\n\n\n\n\n";


	switch (eleccion)
	{
		case 1:
			insertarImagen();
			break;

		case 2:

			break;

		case 3:

			break;

		case 4:

			break;

		case 5:

			break;

		case 6:
			exit(0);
			break;

		default:
			break;
	}
}

void insertarImagen() {
	cout << "-------------------- Insertar Imagen --------------------\n";
	string direccion;
	cout << "	Ingrese la direccion del archivo csv: ";
	cin >> direccion;
	cout << "\n\n";

	NodoABB *actual = new NodoABB();
	vector<string> lista;
	size_t found;

	vector<string> nombre;
	found = direccion.find(".");

	nombre.push_back(direccion.substr(0, found));
	nombre.push_back(direccion.substr(found, direccion.length()));

	if (nombre[1] != ".csv")
	{
		direccion = "";
		cout << "ERROR: extencion del archivo no valido \n";
	}
	else
	{
		found = direccion.find("/");
		actual->nombreImagen = direccion.substr(0, found);
	}

	ifstream lectura;
	lectura.open(direccion, ios::in);

	if (!lectura.fail()) {
		
		

		for (string linea; getline(lectura, linea); )
		{
			
			found = linea.find(",");

			while (found != 4294967295) {
				lista.push_back(linea.substr(0, found));
				linea = linea.substr(found + 1, linea.length());
				found = linea.find(",");
			}

			lista.push_back(linea.substr(0, linea.length()));

		}

		for (int i = 0; i < lista.size(); i++)
		{
			if (lista[i].compare("x") != 0)
			{
				("lunes", lista[0], lista[i]);
			}
		}
	}
	else if(direccion != "")
	{
		cout << "ERROR: archivo no encontrado\n";
	}
	cout << "-------------------- Insertar Imagen --------------------\n\n\n\n\n\n\n\n\n";
}