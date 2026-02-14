#ifndef MENUVENTAS_H
#define MENUVENTAS_H

#include "Tipos.h"
#include "SubMenuClientes.h"
#include "SubMenuVentas.h"
#include "NVInterfaz.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//Prototipos
void MenuVentas(TaVentas *, int *, TaClientes *, int *);


/* ******
* Procedimiento: MenuVentas
* Autor: Zuri G
* Fecha: 13/06/2025
* Objetivo: Mostrar el menú de el módulo de ventas
* Parámetros: Ventas, total de ventas, clientes, total de clientes
******/

void MenuVentas(TaVentas *aVentas, int *eTotalVentas, TaClientes *aClientes, int *eTotalClientes) {

	//Variables
	int eOpcion;
	char sMensaje[50];

	do {

		Pantalla4();
		sprintf(sMensaje, "MEN%c VENTAS Y CLIENTES", 233);
		Centrar(sMensaje, 2);
		Mensaje(10, 54, "1. Clientes");
		Mensaje(11, 54, "2. Ventas");
		Mensaje(12, 54, "0. Regresar");

		Mensaje(16, 50, "Seleccione una opci%cn: ", 162);
		eOpcion = LeerEntero(16, 73, 1);

		switch (eOpcion) {

			case 1: SubMenuClientes(*aClientes, eTotalClientes);
					break;

			case 2: SubMenuVentas(aVentas, eTotalVentas, *aClientes, *eTotalClientes);
					break;

			case 0: break;

			default: Error(1);
					 getch();
		}

	} while(eOpcion != 0);

} //MenuVentas

#endif
