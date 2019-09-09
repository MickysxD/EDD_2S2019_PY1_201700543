#include "pch.h"
#include "Nodo.h"
#include <string>

using namespace std;

Nodo::Nodo()
{
}

void Nodo::adia(string dia)
{
	this->dia = dia;

	if (dia.compare("lunes") == 0) {
		this->x = 1;
	}
	else if (dia.compare("martes") == 0) {
		this->x = 2;
	}
	else if (dia.compare("miercoles") == 0) {
		this->x = 3;
	}
	else if (dia.compare("jueves") == 0) {
		this->x = 4;
	}
	else if (dia.compare("viernes") == 0) {
		this->x = 5;
	}
	else if (dia.compare("sabado") == 0) {
		this->x = 6;
	}
	else if (dia.compare("domingo") == 0) {
		this->x = 7;
	}
	else {
		this->x = 0;
	}
}

void Nodo::ahora(string hora)
{
	this->hora = hora;

	if (hora.compare("1") == 0) {
		this->y = 1;
	}
	else if (hora.compare("2") == 0) {
		this->y = 2;
	}
	else if (hora.compare("3") == 0) {
		this->y = 3;
	}
	else if (hora.compare("4") == 0) {
		this->y = 4;
	}
	else if (hora.compare("5") == 0) {
		this->y = 5;
	}
	else if (hora.compare("6") == 0) {
		this->y = 6;
	}
	else if (hora.compare("7") == 0) {
		this->y = 7;
	}
	else if (hora.compare("8") == 0) {
		this->y = 8;
	}
	else if (hora.compare("9") == 0) {
		this->y = 9;
	}
	else if (hora.compare("10") == 0) {
		this->y = 10;
	}
	else if (hora.compare("11") == 0) {
		this->y = 11;
	}
	else if (hora.compare("12") == 0) {
		this->y = 12;
	}
	else if (hora.compare("13") == 0) {
		this->y = 13;
	}
	else if (hora.compare("14") == 0) {
		this->y = 14;
	}
	else if (hora.compare("15") == 0) {
		this->y = 15;
	}
	else if (hora.compare("16") == 0) {
		this->y = 16;
	}
	else if (hora.compare("17") == 0) {
		this->y = 17;
	}
	else if (hora.compare("18") == 0) {
		this->y = 18;
	}
	else if (hora.compare("19") == 0) {
		this->y = 19;
	}
	else if (hora.compare("20") == 0) {
		this->y = 20;
	}
	else if (hora.compare("21") == 0) {
		this->y = 21;
	}
	else if (hora.compare("22") == 0) {
		this->y = 22;
	}
	else if (hora.compare("23") == 0) {
		this->y = 23;
	}
	else {
		this->y = 0;
	}
}

Nodo::~Nodo()
{
}
