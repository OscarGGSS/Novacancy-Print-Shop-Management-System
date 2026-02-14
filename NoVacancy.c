/* ******
* Programa: NoVacancy.c
* Autor: Infosauridos
* Fecha: 19/06/2025
* Objetivo: Implementar un sistema automatizado para gestionar ventas, dise�os, comisiones e insumos. 
* Compilador: Dev-C++ 5.11
* Versi�n: 0.1
****** */

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include "MenuVentas.h"
#include "MenuComisiones.h"
#include "Insumos.h"
#include "NVInterfaz.h"

// Arreglo de insumos y contador
Insumo insumos[MAX_INSUMOS];
int totalInsumos = 0;

//Programa Principal
int main() {
	
	//Variables
	TaVentas aVentas = {0};
	TaClientes aClientes = {0};
    int eTotalVentas;
    int eTotalClientes;
    int eOpcion;
    TaDisenos aDisenos;
    int eTotalDisenos = -1;
    TaDisenadores aDisenadores;
    int eTotalDisenadores = -1;
    
    //Inicializaciones
    eTotalVentas = 0;
    eTotalClientes = -1;
    
    //Cargas
	CargarClientes(aClientes, &eTotalClientes);
    CargarVentas(aVentas, &eTotalVentas);
    cargarInsumosDesdeArchivo();
	LeerDisenosDesdeArchivo(aDisenos, &eTotalDisenos);
	LeerDisenadoresDesdeArchivo(aDisenadores, &eTotalDisenadores);
	
    AjustarTamanoConsola(120, 30);
   
    do {
    	
        PantallaNoVacancy();
        
        Mensaje(9, 54, "1. Ventas");
        Mensaje(10, 54, "2. Comisiones");
        Mensaje(11, 54, "3. Insumos");
		Mensaje(12, 54, "0. Salir");

        Mensaje(16, 50, "Seleccione una opci%cn: ", 162);
        eOpcion = LeerEntero(16, 73, 1); //Valida entero
	
		switch (eOpcion) {
           
		    case 1: MenuVentas(&aVentas, &eTotalVentas, &aClientes, &eTotalClientes);
                	break;
            
			case 2: MenuComisiones(aDisenos, &eTotalDisenos, aDisenadores, &eTotalDisenadores, &aVentas, eTotalVentas);
    				break;
                
            case 3: MenuInsumos();
    				break;
                   
			case 0: Centrar("Saliendo del programa...", 26);
					break;
			
            default: Error(1); //Error (opci�n no v�lida)
                	 getch();

        }
        
    } while(eOpcion != 0);
    
	return 0;
	
}
