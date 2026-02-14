#ifndef MENUCOMISIONES_H
#define MENUCOMISIONES_H

#include "Tipos.h"
#include "SubMenuDisenos.h"
#include "SubMenuDisenadores.h"
#include "SubMenuComisiones.h"
#include "NVInterfaz.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//Prototipos
void MenuComisiones(TaDisenos, int *, TaDisenadores, int *, TaVentas *, int );

/* ******
* Procedimiento: MenuComisiones
* Fecha: 18/06/2025
* Objetivo: Mostrar el men� de el m�dulo de comisiones
* Par�metros: Dise�os, total de dise�os, dise�adores, total de dise�adores
******/
void MenuComisiones(TaDisenos aDisenos, int *eTotalDisenos, TaDisenadores aDisenadores, int *eTotalDisenadores,TaVentas *aVentas, int eTotalVentas) {

	int eOpcion, eId;
    TrDiseno rDiseno;
	char sMensaje[50];
	
	do {

		system("cls");
		system("color 2F");
    	MarcoPantalla();
   		Marco(4, 1, 24, 118);
   	 	
		sprintf(sMensaje, "MEN%c COMISIONES", 233);
		Centrar(sMensaje, 2);
		Mensaje(10, 54, "1. Dise%cos", 164);
		Mensaje(11, 54, "2. Dise%cadores", 164);
		Mensaje(12, 54, "3. Comisiones");
		Mensaje(13, 54, "0. Regresar");

		Mensaje(16, 50, "Seleccione una opci%cn: ", 162);
		eOpcion = LeerEntero(16, 73, 1);

		switch (eOpcion) {

			case 1:
				SubMenuDisenos(aDisenos, eTotalDisenos);
				break;

			case 2:
				SubMenuDisenadores(aDisenadores, eTotalDisenadores);
				break;
				
			case 3:
				SubMenuComisiones(aDisenadores, eTotalDisenadores, aDisenos, eTotalDisenos, aVentas, eTotalVentas);
				break;

			case 0:
				break;

			default:
				Error(1);
				getch();
		}

	} while(eOpcion != 0);

} //MenuComisiones

#endif
