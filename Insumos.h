/*********************
Modulo: Insumos.h
Autor: Ramirez Ibañez Allison Viridiana
Fecha: 17/06/2025
Objetivo: Que el sistema registre los datos de los insumos, (ID del insumo, nombre del insumo, descripción del insumo, categoría del insumo, su stock actual, costo.)
Parametros: eIdInsumo, sNombreInsumo, sDescripcionInsumo, sCategoriaInsumo, eStockInsumo, fPrecioInsumo
Valor que retorna: Mensaje que indicará "los datos del insumo no son válidos", o, de lo contrario mostrará el mensaje de "El registro se realizó correctamente"
*********************/

extern Insumo insumos[MAX_INSUMOS];
extern int totalInsumos;

// Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tipos.h"
#include <conio.h>

// Prototipos
void MenuInsumos();
void insertarInsumo();
int validarDatos(const char*, const char*, const char*, int, float);
int buscarInsumo(int);
void borrarInsumo();
void modificarInsumo();
void listarInsumos();
void consultarInsumoPorID();
void guardarInsumosEnArchivo();
void cargarInsumosDesdeArchivo();

/* ******
* Procedimiento: MenuInsumos
* Fecha: 19/06/2025
* Objetivo: Mostrar el menú de el módulo de insumos
******/
void MenuInsumos() {

	int eOpcion;
	char sMensaje[50];

	do {

		system("cls");
		system("color 8F");
		MarcoPantalla();
		Marco(4, 1, 24, 118);

		sprintf(sMensaje, "MEN%c INSUMOS", 233);
		Centrar(sMensaje, 2);
		Mensaje(9, 52, "1. Registrar insumo");
		Centrar("2. Borrar insumo", 10);
		Mensaje(11, 52, "3. Modificar insumo");
		Mensaje(12, 52, "4. Consultar insumo");
		Mensaje(13, 52, "5. Listar insumos");
		Mensaje(14, 52, "0. Regresar");
		Mensaje(16, 50, "Seleccione una opci%cn: ", 162);
		eOpcion = LeerEntero(16, 73, 1);

		switch (eOpcion) {

			case 1: system("color 07");
					system("cls");
					insertarInsumo();
					break;

			case 2: system("color 07");
					system("cls");
					borrarInsumo();
					break;

			case 3: system("color 07");
					system("cls");
					modificarInsumo();
					break;

			case 4: system("color 07");
					system("cls");
					consultarInsumoPorID();
					break;

			case 5: system("color 07");
					system("cls");
					listarInsumos();
					break;

			case 0: break;

			default: Error(1);
					 getch();
		}

	} while(eOpcion != 0);

} //MenuInsumos


void insertarInsumo() {

	Insumo insumo;
	int maxID, i;
	
	// Solicitar datos al usuario
	printf("Ingrese el nombre del insumo: ");
	scanf(" %[^\n]", insumo.sNombreInsumo); // Leer cadena con espacios
	printf("Ingrese la descripci%cn del insumo: ", 162);
	scanf(" %[^\n]", insumo.sDescripcionInsumo);
	printf("Ingrese la categor%ca del insumo: ", 161);
	scanf(" %[^\n]", insumo.sCategoriaInsumo);
	printf("Ingrese el stock actual del insumo: ");
	scanf("%d", &insumo.eStockInsumo);
	printf("Ingrese el costo del insumo: ");
	scanf("%f", &insumo.fPrecioInsumo);

	// Validar datos
	if (!validarDatos(insumo.sNombreInsumo, insumo.sDescripcionInsumo, insumo.sCategoriaInsumo, insumo.eStockInsumo, insumo.fPrecioInsumo)) {
		
		printf("\n\nError. Los datos ingresados no son v%clidos.\n", 160);
		getch();
		
	} else {

		if (totalInsumos == 0) {
    
			insumo.eIdInsumo = 1;
		
		} else {

			maxID = 0;
			
			for (i = 0; i < totalInsumos; i++) {
    			
        		if (insumos[i].eIdInsumo > maxID) {
            		
					maxID = insumos[i].eIdInsumo;
					
        		}
    		}
    	
			insumo.eIdInsumo = maxID + 1;
		
		}
		
		printf("\n\nEl registro se realiz%c correctamente. ID del insumo: %d", 162, maxID + 1);
		insumos[totalInsumos++] = insumo; // Agregar insumo al arreglo
		guardarInsumosEnArchivo();
		getch();

	}
}

void borrarInsumo() {

	Insumo insumo;
	int eIdInsumo;

	printf("Ingrese el ID del Insumo a borrar: ");
	scanf("%d", &eIdInsumo);

	int i;
	int index = buscarInsumo(eIdInsumo);
	if (index == -1) {
		printf("Error. No se encontró el ID del Insumo\n");
		getch();
	} else {
		// Mostrar datos del Insumo
		printf("Datos del Insumo:\n");
		printf("ID: %d\n", insumos[index].eIdInsumo);
		printf("Nombre: %s\n", insumos[index].sNombreInsumo);
		printf("Descripción: %s\n", insumos[index].sDescripcionInsumo);
		printf("Categoría: %s\n", insumos[index].sCategoriaInsumo);
		printf("Stock: %d\n", insumos[index].eStockInsumo);
		printf("Precio: %.2f\n", insumos[index].fPrecioInsumo);

		// Solicitar confirmación
		char cConfirmacion;
		printf("¿Está seguro de que desea borrar el registro del Insumo? (s/n): ");
		scanf(" %c", &cConfirmacion);
		if (cConfirmacion == 's') {
			// Borrar el registro del Insumo
			for (i = index; i < totalInsumos - 1; i++) {
				insumos[i] = insumos[i + 1]; // Desplazar insumos hacia la izquierda
			}
			totalInsumos--; // Reducir el total de insumos
			printf("El registro del Insumo fue borrado correctamente\n");
			guardarInsumosEnArchivo();
			getch();
		} else {
			printf("Operación detenida por el usuario\n");
			getch();
		}
	}
}

int validarDatos(const char* sNombreInsumo, const char* sDescripcionInsumo, const char* sCategoriaInsumo, int eStockInsumo, float fPrecioInsumo) {

	if (strlen(sNombreInsumo) < 3 || strlen(sNombreInsumo) > MAX_NOMBRE) {
		return 0; // Nombre debe tener entre 3 y 50 caracteres
	}
	if (strlen(sDescripcionInsumo) < 10 || strlen(sDescripcionInsumo) > MAX_DESCRIPCION) {
		return 0; // Descripción debe tener entre 10 y 255 caracteres
	}
	if (strlen(sCategoriaInsumo) < 3 || strlen(sCategoriaInsumo) > MAX_CATEGORIA) {
		return 0; // Categoría debe tener entre 3 y 30 caracteres
	}
	if (eStockInsumo < 0) {
		return 0; // Stock debe ser positivo
	}
	if (fPrecioInsumo < 0.0f) {
		return 0; // Precio debe ser positivo
	}
	return 1; // Todos los datos son válidos
}

// Función para buscar un insumo por ID
int buscarInsumo(int eIdInsumo) {

	int i;
	for (i = 0; i < totalInsumos; i++) {
		if (insumos[i].eIdInsumo == eIdInsumo) {
			return i; // Retorna el índice del insumo encontrado
		}
	}
	return -1; // Retorna -1 si no se encuentra el insumo
}

// Procedimiento para modificar un insumo
void modificarInsumo() {

	int eIdInsumo;

	printf("Ingrese el ID del Insumo a modificar: ");
	scanf("%d", &eIdInsumo);

	int index = buscarInsumo(eIdInsumo);
	if (index == -1) {
		printf("Error. El identificador del insumo no existe.\n");
		getch();
	} else {
		// Solicitar nuevos valores
		Insumo nuevoInsumo;
		printf("Ingrese el nuevo nombre del insumo: ");
		scanf(" %[^\n]", nuevoInsumo.sNombreInsumo);
		printf("Ingrese la nueva descripción del insumo: ");
		scanf(" %[^\n]", nuevoInsumo.sDescripcionInsumo);
		printf("Ingrese la nueva categoría del insumo: ");
		scanf(" %[^\n]", nuevoInsumo.sCategoriaInsumo);
		printf("Ingrese el nuevo stock del insumo: ");
		scanf("%d", &nuevoInsumo.eStockInsumo);
		printf("Ingrese el nuevo costo del insumo: ");
		scanf("%f", &nuevoInsumo.fPrecioInsumo);

		// Validar nuevos datos
		if (!validarDatos(nuevoInsumo.sNombreInsumo, nuevoInsumo.sDescripcionInsumo, nuevoInsumo.sCategoriaInsumo, nuevoInsumo.eStockInsumo, nuevoInsumo.fPrecioInsumo)) {
			printf("Error: Los nuevos datos ingresados no son válidos.\n");
			getch();
		} else {
			// Solicitar confirmación
			char cConfirmacion;
			printf("¿Está seguro de que desea modificar el insumo? (s/n): ");
			scanf(" %c", &cConfirmacion);
			if (cConfirmacion == 's') {
				// Modificar el insumo
				insumos[index] = nuevoInsumo;
				insumos[index].eIdInsumo = eIdInsumo; // Mantener el ID original
				guardarInsumosEnArchivo();
				printf("La modificación se realizó correctamente.\n");
				getch();
			} else {
				printf("La modificación fue cancelada.\n");
				getch();
			}
		}
	}
}

// *********************
// Santiago
// MÓDULO: Listar insumos
// PreC: N/A
// PosC: Se muestran los registros de insumos o un mensaje si no existen
// DE: N/A
// DS: Registros del Insumo
/*********************/
void listarInsumos() {

	int i;

	if (totalInsumos == 0) {
		printf("No hay registros de Insumos.\n");
		return;
	}

	printf("\n--- Lista de Insumos Registrados ---\n");

	for (i = 0; i < totalInsumos; i++) {
		printf("ID del Insumo: %d\n", insumos[i].eIdInsumo);
		printf("Nombre del Insumo: %s\n", insumos[i].sNombreInsumo);
		printf("Descripción: %s\n", insumos[i].sDescripcionInsumo);
		printf("Categoría: %s\n", insumos[i].sCategoriaInsumo);
		printf("Stock actual: %d\n", insumos[i].eStockActual);
		printf("Stock mínimo: %d\n", insumos[i].eStockMinimo);
		printf("Stock máximo: %d\n", insumos[i].eStockMaximo);
		printf("Costo: $%.2f\n", insumos[i].fCostoInsumo);
		printf("------------------------------\n");
		getch();
	}
}

// ============================
// Santiago
// MÓDULO: Consultar insumo por ID
// PreC: eldInsumo es un número entero, positivo, ingresado por el usuario
// PosC: Se muestra el registro del Insumo correspondiente o un mensaje de inexistencia
// DE: Identificador del Insumo (eldInsumo)
// DS: Registro del Insumo
// ============================
void consultarInsumoPorID() {
	int eldInsumo;
	int encontrado = 0;
	int i;

	printf("Ingrese el ID del Insumo a consultar: ");
	scanf("%d", &eldInsumo);

	if (eldInsumo <= 0) {
		printf("Error: El ID debe ser un número entero positivo.\n");
		return;
	}

	for (i = 0; i < totalInsumos; i++) {
		if (insumos[i].eIdInsumo == eldInsumo) {
			printf("\n--- Registro del Insumo ---\n");
			printf("ID del Insumo: %d\n", insumos[i].eIdInsumo);
			printf("Nombre del Insumo: %s\n", insumos[i].sNombreInsumo);
			printf("Descripción del Insumo: %s\n", insumos[i].sDescripcionInsumo);
			printf("Categoría del Insumo: %s\n", insumos[i].sCategoriaInsumo);
			printf("Stock actual: %d\n", insumos[i].eStockActual);
			printf("Stock mínimo: %d\n", insumos[i].eStockMinimo);
			printf("Stock máximo: %d\n", insumos[i].eStockMaximo);
			printf("Costo: $%.2f\n", insumos[i].fCostoInsumo);
			encontrado = 1;
			getch();
			break;
		}
	}

	if (!encontrado) {
		printf("El ID del Insumo no existe.\n");
		getch();
	}
}


/* ******
* Procedimiento: guardarInsumosEnArchivo
* Fecha: 19/06/2025
* Objetivo: Actualizar archivo
****** */
void guardarInsumosEnArchivo() {

	//Variables
	FILE *archivo;
	int i;

	archivo = fopen("Insumos.txt", "w");

	if (archivo == NULL) {

		return;

	}

	for (i = 0; i < totalInsumos; i++) {

		fprintf(archivo, "%d|%s|%s|%s|%d|%d|%d|%d|%.2f|%.2f\n",
		        insumos[i].eIdInsumo,
		        insumos[i].sNombreInsumo,
		        insumos[i].sDescripcionInsumo,
		        insumos[i].sCategoriaInsumo,
		        insumos[i].eStockInsumo,
		        insumos[i].eStockActual,
		        insumos[i].eStockMinimo,
		        insumos[i].eStockMaximo,
		        insumos[i].fPrecioInsumo,
		        insumos[i].fCostoInsumo
		       );
	}

	fclose(archivo);

}//guardarInsumosEnArchivo


/* ******
* Procedimiento: cargarInsumosDesdeArchivo
* Fecha: 19/06/2025
* Objetivo: Cargar insumos desde el archivo
****** */
void cargarInsumosDesdeArchivo() {

	//Variables
	FILE *archivo;

	archivo = fopen("Insumos.txt", "r");

	if (archivo == NULL) {

		return;

	}

	totalInsumos = 0;

	while (fscanf(archivo, "%d|%[^|]|%[^|]|%[^|]|%d|%d|%d|%d|%f|%f\n",
	              &insumos[totalInsumos].eIdInsumo,
	              insumos[totalInsumos].sNombreInsumo,
	              insumos[totalInsumos].sDescripcionInsumo,
	              insumos[totalInsumos].sCategoriaInsumo,
	              &insumos[totalInsumos].eStockInsumo,
	              &insumos[totalInsumos].eStockActual,
	              &insumos[totalInsumos].eStockMinimo,
	              &insumos[totalInsumos].eStockMaximo,
	              &insumos[totalInsumos].fPrecioInsumo,
	              &insumos[totalInsumos].fCostoInsumo
	             ) == 10) {

		totalInsumos++;

		if (totalInsumos >= MAX_INSUMOS) {

			break;

		}
	}

	fclose(archivo);

} //cargarInsumosDesdeArchivo
