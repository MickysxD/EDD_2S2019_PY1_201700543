
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ABB.h"
#include "NodoABB.h"
#include "Filtros.h"

using namespace std;

ABB *arbol = new ABB();
NodoABB *imagen;
Filtros *fil = new Filtros();

void menu();
void insertarImagen();
void agregarConfig(NodoABB *actual, string direccion);
void agregarCapa(NodoABB *actual, string ncapa, string direccion);
void escogerImagen();
void filtros();
void edicion();
void exportarCSS();
void exportarHTML();
void reportes();
string hex(string codigo);
string RGBToHex(int rNum, int gNum, int bNum);

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

	cout << "-------------------- Menu PhotGen++ --------------------\n\n";
	cout << "1. Insertar Imagen\n";
	cout << "2. Seleccionar Imagen\n";
	cout << "3. Aplicar Filtros\n";
	cout << "4. Ediccion Manual\n";
	cout << "5. Exportar Imagen\n";
	cout << "6. Reportes\n\n";
	cout << "Ingrese el numero a de la accion a realizar: ";
	cin >> eleccion;
	cout << "\n-------------------- Menu PhotGen++ --------------------\n";
	cout << "\n\n\n\n\n\n\n\n\n";


	switch (eleccion)
	{
		case 1:
			insertarImagen();
			break;

		case 2:
			escogerImagen();
			break;

		case 3:
			filtros();
			break;

		case 4:
			edicion();
			break;

		case 5:
			cout << "-------------------- Exportar Imagen --------------------\n\n";
			if (imagen != NULL)
			{
				exportarHTML();
				exportarCSS();
				cout << "	Termino de exportar\n";
			}
			else
			{
				cout << "	Imagen sin seleccionar\n";
			}
			cout << "\n\n-------------------- Exportar Imagen --------------------\n\n\n\n\n\n\n\n\n\n";
			break;

		case 6:
			exit(0);
			break;

		default:
			break;
	}
}

void insertarImagen() {
	cout << "-------------------- Insertar Imagen --------------------\n\n";
	string direccion;
	cout << "	Ingrese la direccion del archivo csv: ";
	cin >> direccion;
	cout << "\n";

	NodoABB *actual = new NodoABB();
	vector<string> lista;
	size_t found;
	string st;

	vector<string> nombre;
	found = direccion.find_last_of(".");

	if (found != 4294967295)
	{
		nombre.push_back(direccion.substr(0, found));
		nombre.push_back(direccion.substr(found, direccion.length()));

		st = nombre[0];
		found = st.find_last_of("/");

		actual->nombreImagen = st.substr(found + 1, st.length());
	}
	else
	{
		direccion = "";
		cout << "ERROR: extencion del archivo (" << direccion << ") no valido \n";
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
		cout << "ERROR: archivo no encontrado";
	}

	arbol->agregar(actual);

	cout << "\n\n-------------------- Insertar Imagen --------------------\n\n\n\n\n\n\n\n\n";
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

	
	if (found != 4294967295)
	{
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
							if (i == 0)
							{
								nueva->crearY(fila + 1);
							}
							if (fila == 0)
							{
								nueva->crearX(i + 1);
							}
							nueva->agregarNodo(i + 1, fila + 1, hex(lista[i]));
						}
					}

					fila += 1;

				}
				//nueva->graficar(ncapa);
				actual->listaCapas->agregarNodo(nombre[0], stoi(ncapa), nueva);
			}
			else if (direccion != "")
			{
				cout << "ERROR: " << direccion << " archivo no encontrado\n";
			}
		}
	}
}

void escogerImagen() {

	cout << "-------------------- Escoger Imagen --------------------\n\n";
	int x = 1;
	arbol->inorder(arbol->root, &x);
	string direccion;
	cout << "\n		Ingrese el numero de imagen a elegir: ";
	cin >> direccion;
	cout << "\n\n";

	int f = stoi(direccion);
	imagen = arbol->buscar(arbol->root, f);


	if (imagen == NULL)
	{
		cout << "ERROR: Imagen no encontrada";
	}

	cout << "\n\n-------------------- Escoger Imagen --------------------\n\n\n\n\n\n\n\n\n";
}

void filtros() {

}

void edicion() {

}

void exportarHTML() {
	ofstream lectura;
	lectura.open("Exports/" + imagen->nombreImagen + ".html", ios::out);

	if (!lectura.fail())
	{
		lectura << "<!DOCTYPE html>\n";
		lectura << "<html>\n";
		lectura << "<head>\n";
		lectura << "	<link rel=\"stylesheet\" href=\"" << imagen->nombreImagen << ".css\">\n";
		lectura << "</head>\n";
		lectura << "<body>\n\n";
		
		lectura << "<div class=\"canvas\">\n";
			
		for (int i = 0; i < imagen->image_height * imagen->image_height; i++)
		{
			lectura << "	<div class=\"pixel\"></div>\n";
		}
			
		lectura << "</div>\n";
		lectura << "</body>\n";
		lectura << "</html>\n";

	}
	else
	{
		cout << "ERROR: Error con el html\n\n";
	}
}

void exportarCSS() {
	ofstream lectura;
	lectura.open("Exports/" + imagen->nombreImagen + ".css", ios::out);


	if (!lectura.fail())
	{
		lectura << "body {\n";
		lectura << "background: #333333;\n";
		lectura << "height: 100vh;\n";
		lectura << "display: flex;\n";
		lectura << "justify-content: center;\n";
		lectura << "align-items: center;\n";
		lectura << "}\n\n";

		int w = imagen->image_width * imagen->pixel_width;
		int h = imagen->image_height * imagen->pixel_height;

		lectura << ".canvas {\n";
		lectura << "width: " << w << "px;\n";
		lectura << "height: " << h << "px;\n";
		lectura << "}\n\n";

		lectura << ".pixel {\n";
		lectura << "width: " << imagen->pixel_width << "px;\n";
		lectura << "height: " << imagen->pixel_height << "px;\n";
		lectura << "float: left; \n";
		lectura << "jbox-shadow: 0px 0px 1px #fff;\n";
		lectura << "}\n\n";

		NodoCapa *temp = imagen->listaCapas->primero;
		while (temp != NULL) 
		{
			Matriz *mtz = temp->capa;

			if (mtz != NULL)
			{
				Nodo *fila = mtz->root;
				Nodo *col = fila->siguiente;
				col = col->abajo;
				while (fila != NULL)
				{
					
					if (col != NULL)
					{
						int pos = (col->y-1)*imagen->image_height + col->x;

						if (col->abajo == NULL && fila->siguiente == NULL)
						{
							lectura << ".pixel:nth-child(" << pos << ") ";
							lectura << "{\nbackground: #" << col->codigo << ";\n}\n\n";
						}
						else
						{
							lectura << ".pixel:nth-child(" << pos << "),\n";
						}
						col = col->abajo;
					}
					else
					{
						fila = fila->siguiente;
						if (fila != NULL)
						{
							col = fila->abajo;
						}
						else
						{
							col = NULL;
						}
					}
					
				}
			}

			temp = temp->siguiente;
		}

	}
	else
	{
		cout << "ERROR: Error con el css\n\n";
	}
}

void reportes() {

}

string hex(string codigo) {
	int r, g, b;
	string cadena = codigo;
	size_t found;

	vector<string> nombre;
	found = cadena.find("-");

	nombre.push_back(cadena.substr(0, found));
	cadena = cadena.substr(found+1, cadena.length());

	found = cadena.find("-");
	nombre.push_back(cadena.substr(0, found));
	nombre.push_back(cadena.substr(found+1, cadena.length()));

	r = stoi(nombre[0]);
	g = stoi(nombre[1]);
	b = stoi(nombre[2]);

	return RGBToHex(r, g, b);
}

string RGBToHex(int rNum, int gNum, int bNum)
{
	string result;
	char r[255];
	sprintf_s(r, "%.2X", rNum);
	result.append(r);
	char g[255];
	sprintf_s(g, "%.2X", gNum);
	result.append(g);
	char b[255];
	sprintf_s(b, "%.2X", bNum);
	result.append(b);
	return result;
}