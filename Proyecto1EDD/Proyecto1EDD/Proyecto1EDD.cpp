
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
void exportarCSSM(NodoCapa *primero);
void exportarHTML();
void exportarHTMLC();
void exportarHTMLM(NodoCapa *primero);
void reportes();
void escalaN();
void escalaG();
void espejoX();
void espejoY();
void espejoD();
void collage();
void mosaico();
void arbolR();
void nodoR();
void nodoL();
void arbolT();
void filtrosR();
void listaFiltros();
void filtroCapa();
NodoCapa* exportar();
string RGB(string codigo);
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
	system("cls");

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
		cout << "\n-------------------- Reportes --------------------\n\n";

		if (arbol->root != NULL)
		{
			reportes();
		}
		else
		{
			cout << "	ERROR: no hay imagenes cargadas\n";
		}

		cout << "\n-------------------- Reportes --------------------\n\n\n\n\n\n\n\n\n\n";
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
	else if (eleccion == "7")
	{
		mosaico();
		cout << "\n		Filtro realizado con Exito\n";
	}

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
					exportarCSSC(imagen->listaCapas->primero);
					exportarHTMLC();
				}
				else if (temp->id == 7)
				{
					exportarCSSM(retorno);
					exportarHTMLM(retorno);
				}
				else
				{
					exportarCSS(retorno);
					exportarHTML();
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
						exportarCSSC(imagen->listaCapas->primero);
						exportarHTMLC();
					}
					else if (temp->id == 7)
					{
						exportarCSSM(retorno);
						exportarHTMLM(retorno);
					}
					else
					{
						exportarCSS(retorno);
						exportarHTML();
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
	string nombre = "Exports/" + imagen->nombreImagen + ".html";
	lectura.open(nombre, ios::out);

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

	system(nombre.c_str());
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
							lectura << "{background: rgb(" << RGB(col->codigo) << ");}\n\n";
						}
						else
						{
							lectura << ".pixel:nth-child(" << pos << ") ";
							lectura << "{background: rgb(" << RGB(col->codigo) << ");}\n\n";
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
	
	string eleccion;

	cout << "1. Reporte del Arbol\n";
	cout << "2. Reporte de Capa\n";
	cout << "3. Reporte Lineal de Capa\n";
	cout << "4. Reporte Transversal del Arbol \n";
	cout << "5. Reporte de Filtros\n";
	cout << "\n	Ingrese el numero a de la accion a realizar: ";
	cin >> eleccion;
	cout << endl;

	
	if (eleccion == "1")
	{
		arbolR();
	}
	else if (eleccion == "2")
	{
		nodoR();
	}
	else if (eleccion == "3")
	{
		nodoL();
	}
	else if (eleccion == "4")
	{
		arbolT();
	}
	else if (eleccion == "5")
	{
		if (fil->primero != NULL)
		{
			filtrosR();
		}
		else
		{
			cout << "\n	ERROR: no hay filtros aplicados\n";
		}
	}
	else
	{
		cout << "\n	Eleccion no valida\n";
	}

}

void arbolR(){
	ofstream grafica;

	grafica.open("arbol.dot", ios::out);

	if (!grafica.fail()) {
		grafica << "digraph grafico{\nnode [shape = record];\ngraph [nodesep = 1];\nrankdir=TB;\n";

		string nombre = arbol->graficar(arbol->root);
		
		grafica << nombre;

		grafica << "}";

		grafica.close();

		system("dot -Tjpg arbol.dot -o arbol.jpg");

		system("arbol.jpg");

	}

}

void nodoR() {
	int x = 1;
	if (arbol->root != NULL)
	{
		arbol->inorder(arbol->root, &x);
		string direccion;
		cout << "\n		Ingrese el numero de imagen a elegir: ";
		cin >> direccion;
		cout << "\n";

		int f = stoi(direccion);
		NodoABB *retorno = arbol->buscar(arbol->root, f);


		if (retorno != NULL) {
			NodoCapa *temp = retorno->listaCapas->primero;

			while (temp != NULL)
			{
				cout << temp->noCapa << ". " << temp->nombreCapa << "\n";
				temp = temp->siguiente;
			}

			string ncapa;
			cout << "\n		Escriba el numero de la capa a Graficar: ";
			cin >> ncapa;

			temp = retorno->listaCapas->primero;

			while (temp != NULL)
			{
				if (temp->noCapa == stoi(ncapa))
				{
					temp->capa->graficar(temp->nombreCapa);
					break;
				}
				else
				{
					temp = temp->siguiente;
				}

			}
			if (retorno == NULL)
			{
				cout << "\n		ERROR: no a sido posible Graficar\n";
			}
			else
			{
				cout << "\n			Graficado con exito\n";
			}

		}
	}
	else
	{
		cout << "\nERROR: No hay imagenes cargadas\n";
	}
}

void nodoL() {
	int x = 1;
	if (arbol->root != NULL)
	{
		arbol->inorder(arbol->root, &x);
		string direccion;
		cout << "\n		Ingrese el numero de imagen a elegir: ";
		cin >> direccion;
		cout << "\n";

		int f = stoi(direccion);
		NodoABB *retorno = arbol->buscar(arbol->root, f);

		if (retorno != NULL) {
			NodoCapa *temp = retorno->listaCapas->primero;

			while (temp != NULL)
			{
				cout << temp->noCapa << ". " << temp->nombreCapa << "\n";
				temp = temp->siguiente;
			}

			string ncapa, linea;
			cout << "\n		Escriba el numero de la capa a Graficar: ";
			cin >> ncapa;

			temp = retorno->listaCapas->primero;

			while (temp != NULL)
			{
				if (temp->noCapa == stoi(ncapa))
				{
					cout << "\n1. Columnas";
					cout << "\n2. Filas";
					cout << "\n		Escriba el numero de la forma a Graficar: ";
					cin >> linea;
					if (linea == "1")
					{
						temp->capa->graficarC(temp->nombreCapa + "LinealColumna");
						break;
					}
					else if (linea == "2")
					{
						temp->capa->graficarF(temp->nombreCapa + "LinealFila");
						break;
					}
					else
					{
						cout << "\n\n	ERROR: eleccion no valida ";
					}
				}
				else
				{
					temp = temp->siguiente;
				}

			}
			if (temp == NULL)
			{
				cout << "\n		ERROR: no a sido posible graficar\n";
			}
			else
			{
				cout << "\n			Graficado con exito\n";
			}

		}
	}
	else
	{
		cout << "\nERROR: No hay imagenes cargadas\n";
	}
}

void arbolT() {
	string eleccion;
	string archivo;
	string nombre = "";
	int contador = 1;
	cout << "1. Inorder\n";
	cout << "2. Preorder\n";
	cout << "3. Postorder\n";
	cout << "\n	Ingrese el numero a de la accion a realizar: ";
	cin >> eleccion;
	cout << endl;

	if (eleccion ==  "1")
	{
		archivo = "arbolInorder";
		nombre = arbol->inorderG(arbol->root, &contador);
	}
	else if (eleccion == "2")
	{
		archivo = "arbolPreorder";
		nombre = arbol->preorderG(arbol->root, &contador);
	}
	else if (eleccion == "3")
	{
		archivo = "arbolPostorder";
		nombre = arbol->postorderG(arbol->root, &contador);
	}

	if (nombre != "")
	{
		ofstream grafica;

		grafica.open(archivo+".dot", ios::out);

		if (!grafica.fail()) {
			grafica << "digraph grafico{\nnode [shape = record];\ngraph [nodesep = 1];\nrankdir=LR;\n";

			grafica << nombre;

			for (int i = 1; i < contador-1; i++)
			{
				grafica << "\"" + to_string(i) << "\"->\"" << to_string(i+1) << "\";\n";
			}

			grafica << "}";

			grafica.close();

			string dot = "dot -Tjpg " + archivo + ".dot -o " + archivo + ".jpg";
			system(dot.c_str());
			string imagen = archivo + ".jpg";
			system(imagen.c_str());

			cout << "\n		Graficado con exito\n";
		}
		else
		{
			cout << "\n		ERROR: no se pudo  graficar";
		}
	}
	else
	{
		cout << "\n		ERROR: no se pudo  graficar";
	}
	
	

}

void filtrosR() {
	string eleccion;

	cout << "1. Lista de filtros\n";
	cout << "2. Reporte Capa de filtro\n";
	cout << "\n	Ingrese el numero a de la accion a realizar: ";
	cin >> eleccion;
	cout << endl;

	if (eleccion == "1")
	{
		listaFiltros();
	}
	else if (eleccion == "2")
	{
		filtroCapa();
	}
	else
	{
		cout << "\n	ERROR: eleccion no valida";

	}
}

void listaFiltros() {
	ofstream grafica;

	grafica.open("listaFiltros.dot", ios::out);

	if (!grafica.fail()) {
		grafica << "digraph grafico{\nnode [shape = record];\ngraph [nodesep = 1];\nrankdir=LR;\n";

		NodoFiltro *temp = fil->primero;

		grafica << "\"" << temp->nombreFiltro << "\"[label=\"" << temp->nombreFiltro << "\"];" << endl;
		grafica << "\"" << temp->nombreFiltro << "\"->\"" << temp->siguiente->nombreFiltro << "\"[dir=both];" << endl;

		temp = temp->siguiente;

		while (temp != fil->primero)
		{
			grafica << "\"" << temp->nombreFiltro << "\"[label=\"" << temp->nombreFiltro << "\"];" << endl;
			grafica << "\"" << temp->nombreFiltro << "\"->\"" << temp->siguiente->nombreFiltro << "\"[dir=both];" << endl;

			temp = temp->siguiente;
		}

		grafica << "}";

		grafica.close();

		system("dot -Tjpg listaFiltros.dot -o listaFiltros.jpg");
		system("listaFiltros.jpg");

		cout << "\n		Graficado con exito\n";
	}
	else
	{
		cout << "\n		ERROR: no se pudo  graficar";
	}

}

void filtroCapa() {
	if (fil->primero != NULL)
	{
		NodoFiltro *temp = fil->primero;

		cout << temp->id << "." << temp->nombreFiltro << endl;
		temp = temp->siguiente;

		while (temp != fil->primero)
		{
			cout << temp->id << "." << temp->nombreFiltro << endl;
			temp = temp->siguiente;
		}
		
		string direccion;
		cout << "\n		Ingrese el numero de imagen a elegir: ";
		cin >> direccion;
		cout << "\n";

		int f = stoi(direccion);
		Capas *retorno = NULL;

		temp = fil->primero;

		if (temp->id == f)
		{
			retorno = temp->capas;
		}

		temp = temp->siguiente;

		while (temp != fil->primero)
		{
			if (temp->id == f)
			{
				retorno = temp->capas;
				temp = temp->siguiente;
			}
			else
			{
				temp = temp->siguiente;
			}
		}


		if (retorno != NULL) {
			NodoCapa *temp = retorno->primero;

			while (temp != NULL)
			{
				cout << temp->noCapa << ". " << temp->nombreCapa << "\n";
				temp = temp->siguiente;
			}

			string ncapa;
			cout << "\n		Escriba el numero de la capa a Graficar: ";
			cin >> ncapa;

			temp = retorno->primero;

			while (temp != NULL)
			{
				if (temp->noCapa == stoi(ncapa))
				{
					temp->capa->graficar(temp->nombreCapa);
					break;
				}
				else
				{
					temp = temp->siguiente;
				}

			}
			if (retorno == NULL)
			{
				cout << "\n		ERROR: no a sido posible graficar\n";
			}
			else
			{
				cout << "\n			Graficado con exito\n";
			}

		}
	}
	else
	{
		cout << "\nERROR: No hay imagenes cargadas\n";
	}
}

string RGB(string codigo) {
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

	string retorno = to_string(r) + "," + to_string(g) + "," + to_string(b);

	return retorno;
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

void mosaico() {
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
					mtzn->agregarNodo(col->x, col->y, col->codigo);
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

	fil->agregarNodo("Mosaico", nuevo, 7);
}

void exportarHTMLC() {
	ofstream lectura;
	string nombre = "Exports/" + imagen->nombreImagen + ".html";
	lectura.open(nombre, ios::out);

	if (!lectura.fail())
	{
		lectura << "<!DOCTYPE html>\n";
		lectura << "<html>\n";
		lectura << "<head>\n";
		lectura << "	<link rel=\"stylesheet\" href=\"" << imagen->nombreImagen << ".css\">\n";
		lectura << "</head>\n";
		lectura << "<body>\n\n";

		lectura << "<div class=\"canvasG\">\n";
		for (int i = 0; i < stoi(cx) * stoi(cy); i++)
		{
			lectura << "	<div class=\"pixelG\">\n";
			lectura << "		<div class=\"canvas\">\n";
			int t = imagen->image_height * imagen->image_width;
			for (int j = 0; j < t; j++)
			{
				lectura << "			<div class=\"pixel\"></div>\n";
			}
			lectura << "		</div>\n";
			lectura << "	</div>\n";
		}
		
		lectura << "</div>\n\n";
		lectura << "</body>\n";
		lectura << "</html>\n";

	}
	else
	{
		cout << "ERROR: Error con el html\n";
	}

	system(nombre.c_str());
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

		double wG = imagen->image_width * imagen->pixel_width;
		double hG = imagen->image_height * imagen->pixel_height;
		double w = double(wG) / double(stoi(cx));
		double h = double(hG) / double(stoi(cy));
		double pxG = w;
		double pyG = h;
		double px = double(imagen->pixel_width) / double(stoi(cx));
		double py = double(imagen->pixel_height) / double(stoi(cy));
		

		lectura << ".canvasG {\n";
		lectura << "width: " << wG << "px;\n";
		lectura << "height: " << hG << "px;\n";
		lectura << "}\n\n";

		lectura << ".canvas {\n";
		lectura << "width: " << w << "px;\n";
		lectura << "height: " << h << "px;\n";
		lectura << "}\n\n";

		lectura << ".pixelG {\n";
		lectura << "width: " << pxG << "px;\n";
		lectura << "height: " << pyG << "px;\n";
		lectura << "float: left; \n";
		lectura << "jbox-shadow: 0px 0px 1px #fff;\n";
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
						int pos = (col->y - 1)*imagen->image_width + col->x;

						if (col->abajo == NULL && fila->siguiente == NULL)
						{
							lectura << ".pixel:nth-child(" << pos << ") ";
							lectura << "{background: rgb(" << RGB(col->codigo) << ");}\n\n";
						}
						else
						{
							lectura << ".pixel:nth-child(" << pos << ") ";
							lectura << "{background: rgb(" << RGB(col->codigo) << ");}\n\n";
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

void exportarHTMLM(NodoCapa *primero) {
	ofstream lectura;
	string nombre = "Exports/" + imagen->nombreImagen + ".html";
	lectura.open(nombre, ios::out);

	if (!lectura.fail())
	{
		lectura << "<!DOCTYPE html>\n";
		lectura << "<html>\n";
		lectura << "<head>\n";
		lectura << "	<link rel=\"stylesheet\" href=\"" << imagen->nombreImagen << ".css\">\n";
		lectura << "</head>\n";
		lectura << "<body>\n\n";

		lectura << "<div class=\"canvasG\">\n";
		int t = imagen->image_height * imagen->image_width;
		for (int i = 0; i < t; i++)
		{
			lectura << "	<div class=\"pixelG\">\n";
			lectura << "		<div class=\"canvas\">\n";
			for (int j = 0; j < t; j++)
			{
				lectura << "			<div class=\"pixel\"></div>\n";
			}
			lectura << "		</div>\n";
			lectura << "	</div>\n";
		}

		lectura << "</div>\n\n";
		lectura << "</body>\n";
		lectura << "</html>\n";

	}
	else
	{
		cout << "ERROR: Error con el html\n";
	}

	system(nombre.c_str());
}

void exportarCSSM(NodoCapa *primero) {
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

		double wG = imagen->image_width * imagen->pixel_width;
		double hG = imagen->image_height * imagen->pixel_height;
		double w = imagen->pixel_width;
		double h = imagen->pixel_height;

		double pxG = w;
		double pyG = h;
		double px = double(imagen->pixel_width) / double(imagen->image_width);
		double py = double(imagen->pixel_height) / double(imagen->image_height);


		lectura << ".canvasG {\n";
		lectura << "width: " << wG << "px;\n";
		lectura << "height: " << hG << "px;\n";
		lectura << "}\n\n";

		lectura << ".canvas {\n";
		lectura << "width: " << w << "px;\n";
		lectura << "height: " << h << "px;\n";
		lectura << "}\n\n";

		lectura << ".pixelG {\n";
		lectura << "width: " << w << "px;\n";
		lectura << "height: " << h << "px;\n";
		lectura << "float: left; \n";
		lectura << "jbox-shadow: 0px 0px 1px #fff;\n";
		lectura << "}\n\n";

		lectura << ".pixel {\n";
		lectura << "opacity: 0.5;\n";
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
						int pos = (col->y - 1)*imagen->image_width + col->x;

						if (col->abajo == NULL && fila->siguiente == NULL)
						{
							lectura << ".pixel:nth-child(" << pos << ") ";
							lectura << "{background: rgb(" << RGB(col->codigo) << ");}\n\n";
						}
						else
						{
							lectura << ".pixel:nth-child(" << pos << ") ";
							lectura << "{background: rgb(" << RGB(col->codigo) << ");}\n\n";
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

		temp = primero;
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
						int pos = (col->y - 1)*imagen->image_width + col->x;

						if (col->abajo == NULL && fila->siguiente == NULL)
						{
							lectura << ".pixelG:nth-child(" << pos << ") ";
							lectura << "{background: rgb(" << RGB(col->codigo) << ");}\n\n";
						}
						else
						{
							lectura << ".pixelG:nth-child(" << pos << ") ";
							lectura << "{background: rgb(" << RGB(col->codigo) << ");}\n\n";
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
