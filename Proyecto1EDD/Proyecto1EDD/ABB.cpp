#include "pch.h"
#include "ABB.h"
#include <iostream>


ABB::ABB()
{
	this->root = NULL;
}

void ABB::agregar(NodoABB *nuevo) {
	if (this->root == NULL)
	{
		this->root = nuevo;
	}
	else
	{
		recursivoAgregar(nuevo, this->root);
	}
}

void ABB::recursivoAgregar(NodoABB *nuevo, NodoABB *root) {
	if (nuevo->nombreImagen < root->nombreImagen) // sub-arbol izq
	{
		if (root->izq != NULL)
		{
			recursivoAgregar(nuevo, root->izq);
		}
		else
		{
			root->izq = nuevo;
		}
	}else if (nuevo->nombreImagen > root->nombreImagen) // sub-arbol der
	{
		if (root->der != NULL)
		{
			recursivoAgregar(nuevo, root->der);
		}
		else
		{
			root->der = nuevo;
		}
	}
	else
	{
		cout << "Ya existe una imagen con el nombre: " << nuevo->nombreImagen << endl;
	}
}

void ABB::inorder(NodoABB *root, int *pos) {
	if (root->izq != NULL)
	{
		inorder(root->izq, pos);
	}
	cout << (*pos) << ". "<< root->nombreImagen << endl;
	root->idt = *pos;
	(*pos)++;
	if (root->der != NULL)
	{
		inorder(root->der, pos);
	}
}

NodoABB* ABB::buscar(NodoABB *root, int posb) {
	NodoABB *retorno = NULL;
	if (root->izq != NULL && root->idt > posb)
	{
		retorno = buscar(root->izq, posb);
	}

	if (root->der != NULL && posb > root->idt)
	{
		retorno = buscar(root->der, posb);
	}

	if (posb == root->idt)
	{
		cout << "\nElegido: " << root->nombreImagen << endl;
		retorno = root;
	}

	return retorno;
}

string ABB::graficar(NodoABB *root) {
	string retorno, rank;
	
	if (root->izq != NULL || root->der != NULL)
	{
		retorno = "\"" + root->nombreImagen + "\"[label= \"<C0>|" + root->nombreImagen + "\\nimage_width=" + to_string(root->image_width) + "\\nimage_height=" + to_string(root->image_height) + "\\npixel_width=" + to_string(root->pixel_width) + "\\npixel_height=" + to_string(root->pixel_height) + "|<C1>\"];\n";
		rank = "{ rank=same; ";
	}
	else
	{
		retorno = "\"" + root->nombreImagen + "\"[label=\"" + root->nombreImagen + "\\nimage_width=" + to_string(root->image_width) + "\\nimage_height=" + to_string(root->image_height) + "\\npixel_width=" + to_string(root->pixel_width) + "\\npixel_height=" + to_string(root->pixel_height) + "\"];\n";

	}

	if (root->izq != NULL)
	{
		retorno = retorno + graficar(root->izq);
		retorno = retorno + "\"" + root->nombreImagen + "\":C0->\"" + root->izq->nombreImagen + "\";\n";
		rank = rank + "\"" + root->izq->nombreImagen + "\" ";
	}
	
	if (root->der != NULL)
	{
		retorno = retorno + graficar(root->der);
		retorno = retorno +  "\"" + root->nombreImagen + "\":C1->\"" + root->der->nombreImagen + "\";\n";
		rank = rank + "\"" + root->der->nombreImagen + "\" ";
	}
	
	if (root->izq != NULL || root->der != NULL)
	{
		rank = rank + "}\n";
	}
	retorno = retorno + rank;
	return retorno;
}

string ABB::inorderG(NodoABB *root, int *pos) {
	string retorno;
	
	if (root->izq != NULL)
	{
		retorno = retorno + inorderG(root->izq, pos);
	}

	retorno = retorno + "\"" + to_string(*pos) + "\"[label= \"" + root->nombreImagen + "\"];\n";
	(*pos)++;

	if (root->der != NULL)
	{
		retorno = retorno + inorderG(root->der, pos);
	}

	return retorno;
}

string ABB::preorderG(NodoABB *root, int *pos) {
	string retorno;

	retorno = retorno + "\"" + to_string(*pos) + "\"[label= \"" + root->nombreImagen + "\"];\n";
	(*pos)++;

	if (root->izq != NULL)
	{
		retorno = retorno + inorderG(root->izq, pos);
	}

	if (root->der != NULL)
	{
		retorno = retorno + inorderG(root->der, pos);
	}

	return retorno;
}

string ABB::postorderG(NodoABB *root, int *pos) {
	string retorno;

	if (root->izq != NULL)
	{
		retorno = retorno + inorderG(root->izq, pos);
	}

	if (root->der != NULL)
	{
		retorno = retorno + inorderG(root->der, pos);
	}

	retorno = retorno + "\"" + to_string(*pos) + "\"[label= \"" + root->nombreImagen + "\"];\n";
	(*pos)++;

	return retorno;
}


ABB::~ABB()
{
}
