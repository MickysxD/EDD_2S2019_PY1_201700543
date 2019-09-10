
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

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
	cout << "\n\n\n\n\n";


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
	string direccion;
	cout << "	Ingrese la direccion del archivo csv: ";
	cin >> direccion;
	cout << "\n\n\n\n\n";

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

			while (found != 4294967295) {
				lista.push_back(temp.substr(0, found));
				temp = temp.substr(found + 1, linea.length());
				found = temp.find(",");
			}

			lista.push_back(temp.substr(0, linea.length()));

			for (int i = 0; i < 8; i++)
			{
				if (lista[i].compare("x") != 0)
				{
					("lunes", lista[0], lista[i]);
				}
			}

		}
	}
	else
	{
		cout << "Archivo no entontrado" << endl;
	}

}