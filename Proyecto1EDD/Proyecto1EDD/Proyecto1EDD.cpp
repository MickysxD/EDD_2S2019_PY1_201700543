
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
void exportarCSS(NodoCapa *primero);
void exportarCSSC(NodoCapa *primero);
void exportarHTML();
void exportarHTMLC();
void reportes();
void escalaN();
void escalaG();
void espejoX();
void espejoY();
void espejoD();
void collage();
NodoCapa* exportar();
string hex(string codigo);
string RGBToHex(int rNum, int gNum, int bNum);
string cx, cy;

int main()
{

	while (true)
	{
		menu();
	}
}

void menu() {
	string eleccion;

	cout << "-------------------- Menu PhotGen++ --------------------\n\n";
	cout << "1. Insertar Imagen\n";
	cout << "2. Seleccionar Imagen\n";
	cout << "3. Aplicar Filtros\n";
	cout << "4. Ediccion Manual\n";
	cout << "5. Exportar Imagen\n";
	cout << "6. Reportes\n";
	cout << "7. Salir\n";
	cout << "\nIngrese el numero a de la accion a realizar: ";
	cin >> eleccion;
	cout << endl;
	cout << "\n-------------------- Menu PhotGen++ --------------------\n\n\n\n\n\n\n\n\n\n";

	if (eleccion == "1")
	{
		insertarImagen();
	}
	else if (eleccion == "2") 
	{
		escogerImagen();
	}
	else if (eleccion == "3")
	{
		cout << "-------------------- Filtros --------------------\n\n";
		if (imagen != NULL)
		{
			filtros();
		}
		else
		{
			cout << "	Imagen sin seleccionar\n";
		}
		cout << "\n-------------------- Filtros --------------------\n\n\n\n\n\n\n\n\n\n";
	}
	else if (eleccion == "4")
	{
		cout << "-------------------- Edicion Manual --------------------\n\n";
		if (imagen != NULL)
		{
			edicion();
		}
		else
		{
			cout << "	Imagen sin seleccionar\n";
		}
		cout << "\n-------------------- Edicion Manual --------------------\n\n\n\n\n\n\n\n\n\n";
	}
	else if (eleccion == "5")
	{
		cout << "-------------------- Exportar Imagen --------------------\n\n";
		if (imagen != NULL)
		{
			NodoCapa *primero = exportar();
			if (primero != NULL)
			{
				cout << "\n	Exportado con exito\n";
			}
			else
			{
				cout << "	ERROR: Seleccion no valida\n";
			}
			
		}
		else
		{
			cout << "	Imagen sin seleccionar\n";
		}
		cout << "\n-------------------- Exportar Imagen --------------------\n\n\n\n\n\n\n\n\n\n";
	}
	else if (eleccion == "6")
	{
		exit(0);
	}
	else if (eleccion == "7")
	{
		exit(0);
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
		found = direccion.find_last_of("/");
		if (found != 4294967295)
		{
			nombre.push_back(direccion.substr(0, found));
			st = direccion.substr(found + 1, direccion.length());
			found = st.find_last_of(".");
			nombre.push_back(st.substr(0, found));
			nombre.push_back(st.substr(found, st.length()));
			if (nombre[2] == ".csv")
			{
				actual->nombreImagen = nombre[0];
				nombre[0] = nombre[0] + "/";
			}
			else
			{
				direccion = "";
			}
			
		}
	}
	else
	{
		direccion = "";
		cout << "\nERROR: extencion del archivo no valido \n";
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
					agregarConfig(actual, nombre[0]+lista[i+1]);
				}
				else
				{
					agregarCapa(actual, lista[i], nombre[0] + lista[i+1]);
				}
			}
			else
			{
				if (lista[i+1].compare("0") == 0 && lista[i].compare("config.csv") == 0)
				{
					agregarConfig(actual, nombre[0] + lista[i]);
				}
				else
				{
					agregarCapa(actual, lista[i+1], nombre[0] + lista[i]);
				}
			}
			i++;
		}
		arbol->agregar(actual);
		cout << "\n		Imagen cargada con exito\n";
	}
	else if(direccion != "")
	{
		cout << "\nERROR: archivo no encontrado\n";
	}

	cout << "\n-------------------- Insertar Imagen --------------------\n\n\n\n\n\n\n\n\n";
}

void agregarConfig(NodoABB *actual, string direccion) {
	
	size_t found;

	vector<string> nombre;
	found = direccion.find_last_of(".");

	nombre.push_back(direccion.substr(0, found));
	nombre.push_back(direccion.substr(found, direccion.length()));
	
	if (nombre[1] != ".csv")
	{
		cout << "\nERROR: extencion del archivo (" << direccion << ") no valido \n";
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
		cout << "\nERROR: "<< direccion <<" archivo no encontrado\n";
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
			cout << "\nERROR: extencion del archivo (" << direccion << ") no valido \n";
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
							nueva->agregarNodo(i + 1, fila + 1, lista[i]);
						}
					}

					fila += 1;

				}
				//nueva->graficar(ncapa);
				found = nombre[0].find_last_of("/");
				actual->listaCapas->agregarNodo(nombre[0].substr(found+1, nombre[0].length()), stoi(ncapa), nueva);
			}
			else if (direccion != "")
			{
				cout << "\nERROR: " << direccion << " archivo no encontrado\n";
			}
		}
	}
}

void escogerImagen() {

	cout << "-------------------- Escoger Imagen --------------------\n\n";
	int x = 1;
	if (arbol->root != NULL)
	{
		arbol->inorder(arbol->root, &x);
		string direccion;
		cout << "\n		Ingrese el numero de imagen a elegir: ";
		cin >> direccion;
		cout << "\n";

		int f = stoi(direccion);
		imagen = arbol->buscar(arbol->root, f);


		if (imagen == NULL)
		{
			cout << "\nERROR: Imagen no encontrada\n";
		}
		else
		{
			fil = new Filtros();
		}
	}
	else
	{
		cout << "\nERROR: No hay imagenes cargadas\n";
	}
	

	cout << "\n-------------------- Escoger Imagen --------------------\n\n\n\n\n\n\n\n\n";
}

void filtros() {
	string eleccion;

	cout << "\n1. Negativo\n";
	cout << "2. Escala de Grises\n";
	cout << "3. X-Espejo\n";
	cout << "4. Y-Espejo\n";
	cout << "5. Doble-Espejo\n";
	cout << "6. Collage\n";
	cout << "7. Mosaico\n";
	cout << "\nIngrese el numero a de la accion a realizar: ";
	cin >> eleccion;
	cout << "\n";


	if (eleccion == "1")
	{
		escalaN();
		cout << "\n		Filtro realizado con Exito\n";
	}
	else if (eleccion == "2")
	{
		escalaG();
		cout << "\n		Filtro realizado con Exito\n";
	}
	else if (eleccion == "3")
	{
		espejoX();
		cout << "\n		Filtro realizado con Exito\n";
	}
	else if (eleccion == "4")
	{
		espejoY();
		cout << "\n		Filtro realizado con Exito\n";
	}
	else if (eleccion == "5")
	{
		espejoD();
		cout << "\n		Filtro realizado con Exito\n";
	}
	else if (eleccion == "6")
	{
		collage();
		cout << "\n		Filtro realizado con Exito\n";
	}
	/*
	case 7:
		mosaico();
		break;
	*/

}

void edicion() {
	NodoCapa *retorno = NULL;
	cout << "\n0. Normal\n";

	if (fil->primero != NULL)
	{
		NodoFiltro *temp = fil->primero;
		cout << temp->id << ". " << temp->nombreFiltro << "\n";
		temp = temp->siguiente;
		while (temp != fil->primero)
		{
			cout << temp->id << ". " << temp->nombreFiltro << "\n";
			temp = temp->siguiente;
		}
	}

	string eleccion;
	cout << "\n		Escriba el numero de la imagen a Editar: ";
	cin >> eleccion;

	if (eleccion == "0")
	{
		retorno = imagen->listaCapas->primero;
	}
	else
	{
		if (fil->primero != NULL)
		{
			NodoFiltro *temp = fil->primero;
			if (stoi(eleccion) == temp->id)
			{
				retorno = temp->capas->primero;

				temp = temp->siguiente;
			}
			else {
				temp = temp->siguiente;
			}
			while (temp != fil->primero)
			{
				if (stoi(eleccion) == temp->id)
				{
					retorno = temp->capas->primero;

					temp = temp->siguiente;
				}
				else {
					temp = temp->siguiente;
				}
			}
		}
	}

	if (retorno != NULL) {
		NodoCapa *temp = retorno;
		
		while (temp != NULL)
		{
			cout << temp->noCapa << ". " << temp->nombreCapa << "\n";
			temp = temp->siguiente;
		}

		string x,y, ncapa, rgb;
		cout << "\n		Escriba el numero de la capa a Editar: ";
		cin >> ncapa;

		temp = retorno;

		while (temp != NULL)
		{
			if (temp->noCapa == stoi(ncapa))
			{
				cout << "\n		Escriba la coordenda en X: ";
				cin >> x;
				cout << "\n		Escriba la coordenda en Y: ";
				cin >> y;
				cout << "\n		Escriba el codigo RGB: ";
				cin >> rgb;

				temp->capa->agregarNodo(stoi(x), stoi(y), rgb);
				retorno = temp;
				temp = temp->siguiente;
			}
			else
			{
				temp = temp->siguiente;
			}
			
		}
		if (retorno == NULL)
		{
			cout << "\n		ERROR: no a sido posible modificar\n";
		}
		else
		{
			cout << "\n			Modificado con exito\n";
		}

	}
}

NodoCapa* exportar() {
	NodoCapa *retorno = NULL;
	cout << "\n0. Normal\n";

	if (fil->primero != NULL)
	{
		NodoFiltro *temp = fil->primero;
		cout << temp->id << ". " << temp->nombreFiltro << "\n";
		temp = temp->siguiente;
		while (temp != fil->primero)
		{
			cout << temp->id <<". " << temp->nombreFiltro << "\n";
			temp = temp->siguiente;
		}
	}

	string eleccion;
	cout << "\n		Escriba el numero de la imagen a imprimir: ";
	cin >> eleccion;

	if (eleccion == "0")
	{
		retorno = imagen->listaCapas->primero;
		exportarHTML();
		exportarCSS(retorno);
	}
	else
	{
		if (fil->primero != NULL)
		{
			NodoFiltro *temp = fil->primero;
			if (stoi(eleccion) == temp->id)
			{
				retorno = temp->capas->primero;

				if (temp->id == 6)
				{
					exportarHTMLC();
					exportarCSSC(retorno);
				}
				else
				{
					exportarHTML();
					exportarCSS(retorno);
				}
				temp = temp->siguiente;
			}
			else {
				temp = temp->siguiente;
			}
			while (temp != fil->primero)
			{
				if (stoi(eleccion) == temp->id)
				{
					retorno = temp->capas->primero;
					
					if (temp->id == 6)
					{
						exportarHTMLC();
						exportarCSSC(retorno);
					}
					else
					{
						exportarHTML();
						exportarCSS(retorno);
					}
					temp = temp->siguiente;
				}
				else {
					temp = temp->siguiente;
				}
			}
		}
	}
	return retorno;
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
			
		for (int i = 0; i < imagen->image_height * imagen->image_width; i++)
		{
			lectura << "	<div class=\"pixel\"></div>\n";
		}
			
		lectura << "</div>\n";
		lectura << "</body>\n";
		lectura << "</html>\n";

	}
	else
	{
		cout << "ERROR: Error con el html\n";
	}
}

void exportarCSS(NodoCapa *primero) {
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

		NodoCapa *temp = primero;
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
						int pos = (col->y-1)*imagen->image_width + col->x;

						if (col->abajo == NULL && fila->siguiente == NULL)
						{
							lectura << ".pixel:nth-child(" << pos << ") ";
							lectura << "{background: #" << hex(col->codigo) << ";}\n\n";
						}
						else
						{
							lectura << ".pixel:nth-child(" << pos << ") ";
							lectura << "{background: #" << hex(col->codigo) << ";}\n\n";
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
		cout << "ERROR: Error con el css\n";
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

string RGBG(string codigo) {
	int r, g, b, x;
	string cadena = codigo;
	size_t found;

	vector<string> nombre;
	found = cadena.find("-");

	nombre.push_back(cadena.substr(0, found));
	cadena = cadena.substr(found + 1, cadena.length());

	found = cadena.find("-");
	nombre.push_back(cadena.substr(0, found));
	nombre.push_back(cadena.substr(found + 1, cadena.length()));

	r = stoi(nombre[0]) * 0.299;
	g = stoi(nombre[1]) * 0.587;
	b = stoi(nombre[2]) * 0.144;

	x = r + g + b;
	cadena = to_string(x) + "-" + to_string(x) + "-" + to_string(x);

	return cadena;
}

string RGBN(string codigo) {
	int r, g, b, x;
	string cadena = codigo;
	size_t found;

	vector<string> nombre;
	found = cadena.find("-");

	nombre.push_back(cadena.substr(0, found));
	cadena = cadena.substr(found + 1, cadena.length());

	found = cadena.find("-");
	nombre.push_back(cadena.substr(0, found));
	nombre.push_back(cadena.substr(found + 1, cadena.length()));

	r = 255 - stoi(nombre[0]);
	g = 255 - stoi(nombre[1]);
	b = 255 - stoi(nombre[2]);

	cadena = to_string(r) + "-" + to_string(g) + "-" + to_string(b);

	return cadena;
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

void escalaG() {
	Capas *nuevo = new Capas();

	NodoCapa *temp = imagen->listaCapas->primero;
	while (temp != NULL)
	{
		Matriz *mtz = temp->capa;
		Matriz *mtzn = new Matriz();

		if (mtz != NULL)
		{
			Nodo *fila = mtz->root;
			Nodo *col = fila->siguiente;
			col = col->abajo;
			while (fila != NULL)
			{
				if (col != NULL)
				{
					mtzn->agregarNodo(col->x, col->y, RGBG(col->codigo));
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
		nuevo->agregarNodo(temp->nombreCapa, temp->noCapa, mtzn);

		temp = temp->siguiente;
	}

	fil->agregarNodo("Escala de grises", nuevo, 2);
}

void escalaN() {
	Capas *nuevo = new Capas();

	NodoCapa *temp = imagen->listaCapas->primero;
	while (temp != NULL)
	{
		Matriz *mtz = temp->capa;
		Matriz *mtzn = new Matriz();

		if (mtz != NULL)
		{
			Nodo *fila = mtz->root;
			Nodo *col = fila->siguiente;
			col = col->abajo;
			while (fila != NULL)
			{
				if (col != NULL)
				{
					mtzn->agregarNodo(col->x, col->y, RGBN(col->codigo));
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
		nuevo->agregarNodo(temp->nombreCapa, temp->noCapa, mtzn);

		temp = temp->siguiente;
	}

	fil->agregarNodo("Negativo", nuevo, 1);
}

void espejoX() {
	Capas *nuevo = new Capas();

	NodoCapa *temp = imagen->listaCapas->primero;
	while (temp != NULL)
	{
		Matriz *mtz = temp->capa;
		Matriz *mtzn = new Matriz();

		if (mtz != NULL)
		{
			Nodo *fila = mtz->root;
			Nodo *col = fila->siguiente;
			col = col->abajo;
			while (fila != NULL)
			{
				if (col != NULL)
				{
					mtzn->agregarNodo(imagen->image_width-col->x, col->y, col->codigo);
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
		nuevo->agregarNodo(temp->nombreCapa, temp->noCapa, mtzn);

		temp = temp->siguiente;
	}

	fil->agregarNodo("Espejo-X", nuevo, 3);
}

void espejoY() {
	Capas *nuevo = new Capas();

	NodoCapa *temp = imagen->listaCapas->primero;
	while (temp != NULL)
	{
		Matriz *mtz = temp->capa;
		Matriz *mtzn = new Matriz();

		if (mtz != NULL)
		{
			Nodo *fila = mtz->root;
			Nodo *col = fila->siguiente;
			col = col->abajo;
			while (fila != NULL)
			{
				if (col != NULL)
				{
					mtzn->agregarNodo(col->x, imagen->image_height - col->y, col->codigo);
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
		nuevo->agregarNodo(temp->nombreCapa, temp->noCapa, mtzn);

		temp = temp->siguiente;
	}

	fil->agregarNodo("Espejo-Y", nuevo, 4);
}

void espejoD() {
	Capas *nuevo = new Capas();

	NodoCapa *temp = imagen->listaCapas->primero;
	while (temp != NULL)
	{
		Matriz *mtz = temp->capa;
		Matriz *mtzn = new Matriz();

		if (mtz != NULL)
		{
			Nodo *fila = mtz->root;
			Nodo *col = fila->siguiente;
			col = col->abajo;
			while (fila != NULL)
			{
				if (col != NULL)
				{
					mtzn->agregarNodo(imagen->image_width - col->x, imagen->image_height - col->y, col->codigo);
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
		nuevo->agregarNodo(temp->nombreCapa, temp->noCapa, mtzn);

		temp = temp->siguiente;
	}

	fil->agregarNodo("Espejo-Doble", nuevo, 5);
}

void collage() {
	cout << "\n		Ingrese la coordenada en X:";
	cin >> cx;
	cout << endl;
	cout << "\n		Ingrese la coordenada en Y:";
	cin >> cy;
	cout << endl;

	Capas *nuevo = new Capas();

	NodoCapa *temp = imagen->listaCapas->primero;
	while (temp != NULL)
	{
		Matriz *mtz = temp->capa;
		Matriz *mtzn = new Matriz();

		if (mtz != NULL)
		{
			Nodo *fila = mtz->root;
			Nodo *col = fila->siguiente;
			col = col->abajo;
			while (fila != NULL)
			{
				if (col != NULL)
				{
					for (int i = 0; i < stoi(cx); i++)
					{
						for (int j = 0; j < stoi(cy); j++)
						{
							mtzn->agregarNodo(imagen->image_width*i + col->x, imagen->image_height*j + col->y, col->codigo);

						}
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
		//mtzn->graficar(temp->nombreCapa);
		nuevo->agregarNodo(temp->nombreCapa, temp->noCapa, mtzn);

		temp = temp->siguiente;
	}

	fil->agregarNodo("Collage", nuevo, 6);
}

void exportarHTMLC() {
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
		int t = imagen->image_height * imagen->image_width * stoi(cy) * stoi(cx);
		for (int i = 0; i < t; i++)
		{
			lectura << "	<div class=\"pixel\"></div>\n";
		}

		lectura << "</div>\n";
		lectura << "</body>\n";
		lectura << "</html>\n";

	}
	else
	{
		cout << "ERROR: Error con el html\n";
	}
}

void exportarCSSC(NodoCapa *primero) {
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

		int px = imagen->pixel_width / stoi(cx);
		int py = imagen->pixel_height / stoi(cy);
		int w = imagen->image_width * px * stoi(cx);
		int h = imagen->image_height * py * stoi(cy);

		lectura << ".canvas {\n";
		lectura << "width: " << w << "px;\n";
		lectura << "height: " << h << "px;\n";
		lectura << "}\n\n";

		lectura << ".pixel {\n";
		lectura << "width: " << px << "px;\n";
		lectura << "height: " << py << "px;\n";
		lectura << "float: left; \n";
		lectura << "jbox-shadow: 0px 0px 1px #fff;\n";
		lectura << "}\n\n";

		NodoCapa *temp = primero;
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
						int pos = (col->y - 1)*imagen->image_width*stoi(cx) + col->x;

						if (col->abajo == NULL && fila->siguiente == NULL)
						{
							lectura << ".pixel:nth-child(" << pos << ") ";
							lectura << "{background: #" << hex(col->codigo) << ";}\n\n";
						}
						else
						{
							lectura << ".pixel:nth-child(" << pos << ") ";
							lectura << "{background: #" << hex(col->codigo) << ";}\n\n";
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
		cout << "ERROR: Error con el css\n";
	}
}
