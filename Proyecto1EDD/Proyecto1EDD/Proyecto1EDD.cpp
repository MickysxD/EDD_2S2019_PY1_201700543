
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
void agregarConfig(NodoABB *actual, string direccion);
void agregarCapa(NodoABB *actual, string ncapa, string direccion);

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
	string st;

	vector<string> nombre;
	found = direccion.find_last_of(".");

	nombre.push_back(direccion.substr(0, found));
	nombre.push_back(direccion.substr(found, direccion.length()));

	if (nombre[1] != ".csv")
	{
		direccion = "";
		cout << "ERROR: extencion del archivo (" << direccion << ") no valido \n";
	}
	else
	{
		st = nombre[0];
		found = st.find_last_of("/");

		actual->nombreImagen = st.substr(found+1, st.length());
	}

	ifstream lectura;
	lectura.open(direccion, ios::in);

	bool ordenado = true;

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
			if (lista[i].compare("Layer") == 0 && lista[i + 1].compare("File") == 0)
			{
				ordenado = true;
			}
			else if (lista[i].compare("File") == 0 && lista[i + 1].compare("Layer") == 0)
			{
				ordenado = false;
			}
			else if (ordenado)
			{

				if (lista[i].compare("0") == 0 && lista[i+1].compare("config.csv") == 0)
				{
					agregarConfig(actual, lista[i+1]);
				}
				else
				{
					agregarCapa(actual, lista[i], lista[i+1]);
				}
			}
			else
			{
				if (lista[i+1].compare("0") == 0 && lista[i].compare("config.csv") == 0)
				{
					agregarConfig(actual, lista[i]);
				}
				else
				{
					agregarCapa(actual, lista[i+1], lista[i]);
				}
			}
			i++;
		}
	}
	else if(direccion != "")
	{
		cout << "ERROR: archivo no encontrado\n";
	}

	arbol->agregar(actual);

	cout << "-------------------- Insertar Imagen --------------------\n\n\n\n\n\n\n\n\n";
}

void agregarConfig(NodoABB *actual, string direccion) {
	
	size_t found;

	vector<string> nombre;
	found = direccion.find_last_of(".");

	nombre.push_back(direccion.substr(0, found));
	nombre.push_back(direccion.substr(found, direccion.length()));
	
	if (nombre[1] != ".csv")
	{
		cout << "ERROR: extencion del archivo (" << direccion << ") no valido \n";
		direccion = "";
	}

	ifstream lectura;
	lectura.open(direccion, ios::in);

	if (!lectura.fail()) {

		for (string linea; getline(lectura, linea); )
		{
			vector<string> lista;
			found = linea.find(",");

			while (found != 4294967295) {
				lista.push_back(linea.substr(0, found));
				linea = linea.substr(found + 1, linea.length());
				found = linea.find(",");
			}

			lista.push_back(linea.substr(0, linea.length()));

			for (int i = 0; i < lista.size(); i++)
			{
				if (lista[i].compare("image_width") == 0)
				{
					actual->image_width = stoi(lista[i + 1]);
				}
				else if (lista[i].compare("image_height") == 0)
				{
					actual->image_height = stoi(lista[i + 1]);
				}
				else if (lista[i].compare("pixel_width") == 0)
				{
					actual->pixel_width = stoi(lista[i + 1]);
				}
				else if (lista[i].compare("pixel_height") == 0)
				{
					actual->pixel_height = stoi(lista[i + 1]);
				}
			}

		}

	}
	else if (direccion != "")
	{
		cout << "ERROR: "<< direccion <<" archivo no encontrado\n";
	}
}

void agregarCapa(NodoABB *actual, string ncapa, string direccion) {
	Matriz *nueva = new Matriz();
	
	size_t found;

	vector<string> nombre;
	found = direccion.find_last_of(".");

	nombre.push_back(direccion.substr(0, found));
	nombre.push_back(direccion.substr(found, direccion.length()));
	
	if (nombre[1] != ".csv")
	{
		cout << "ERROR: extencion del archivo (" << direccion << ") no valido \n";
		direccion = "";
	}
	else {

		ifstream lectura;
		lectura.open(direccion, ios::in);

		if (!lectura.fail()) {
			int fila = 0;
			for (string linea; getline(lectura, linea); )
			{
				vector<string> lista;
				found = linea.find(",");

				while (found != 4294967295) {
					lista.push_back(linea.substr(0, found));
					linea = linea.substr(found + 1, linea.length());
					found = linea.find(",");
				}

				lista.push_back(linea.substr(0, linea.length()));

				for (int i = 0; i < lista.size(); i++)
				{
					if (lista[i].compare("x") != 0)
					{
						nueva->agregarNodo(i, fila, lista[i]);
					}
				}

				fila += 1;

			}

		}
		else if (direccion != "")
		{
			cout << "ERROR: " << direccion << " archivo no encontrado\n";
		}
	}

	nueva->graficar();

	actual->listaCapas->agregarNodo(nombre[0], stoi(ncapa), nueva);
}