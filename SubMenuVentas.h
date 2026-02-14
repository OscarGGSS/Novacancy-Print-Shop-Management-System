#ifndef SUBMENUVENTAS_H
#define SUBMENUVENTAS_H

//Bibliotecas
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "Tipos.h"
#include "NVInterfaz.h"
#include "NVFunciones.h"
#include <conio.h>
#include "SubMenuClientes.h"

//Prototipos
void SubMenuVentas(TaVentas *, int *, TaClientes, int);
int BuscarVenta(TaVentas, int, int, int);
void CargarVentas(TaVentas, int *);
void GuardarVentasEnArchivo(TaVentas *, int);
void MostrarResumenVenta(TrVenta);
void ValidarIdArchivo(int *, float *, char *, char *, int);

//Funciones RegistrarVenta:
void RegistrarVenta(TaVentas *, int *, TaClientes, int);
void CapturarProducto(TrProducto *, float *, float *);
void CapturarDatosVenta(TrVenta *);
void CapturarProductosVenta(TrVenta *, float *);
void GenerarIdVenta(TaVentas *, int, int *);
void GuardarNuevaVenta(TaVentas *, int *, TrVenta *);
void MostrarPreciosProducto(TrProducto, int);
TrProducto ProcesarProducto(TrProducto, TrVenta *, int, float, float, float *);
void ProcesarVenta(TrVenta *, int, float);

//Funciones CancelarVenta:
void CancelarVenta(TaVentas *, int *);
void CapturarDatosCancelacion(TrVenta *);
int ValidarIdVentaCancelacion(TaVentas, int, int *);

//Funciones ConsultarVentasPorFechas:
void ConsultarVentasPorFechas(TaVentas *, int);
int FiltrarMostrarVentasPorFecha(TaVentas *, int, TrFecha, TrFecha);
void MostrarDatosVenta(TaVentas *, int, int);
void PantallaConsultaFechas();
int ValidarFechaMenorOIgual(TrFecha, TrFecha);

//Funciones ConsultarVentaPorId:
void ConsultarVentaPorId(TaVentas *, int);
void MostrarDatosCancelacion(TrVenta);
int ValidarIdVentaConsulta(TaVentas, int);

//Funciones ReporteMensualVentas:
void ReporteMensualVentas(TaVentas *, int);
void ImprimirVentasPorPlataforma(TaVentas *, int, TePlataformas, int, int, int *, float *, int);
void MostrarFilaVentaPlataforma(TrVenta rVenta, int eRenglon, char *sCancelada);

/* ******
* Procedimiento: SubMenuVentas
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Mostrar el menú de ventas
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas), Arreglo de clientes (aClientes), total actual de clientes (eTotal)
******/
void SubMenuVentas(TaVentas *aVentas, int *eTotalVentas, TaClientes aClientes, int eTotalClientes) {
    
    //Variables
	int eOpcion;
   
    do {
    	
        Pantalla4();
        
        Centrar("VENTAS", 2);
        
        Mensaje(9, 49, "1. Registrar venta");
        Mensaje(10, 49, "2. Cancelar venta");
        Mensaje(11, 49, "3. Consultar venta (fechas)");
        Mensaje(12, 49, "4. Consultar venta (ID)");
        Mensaje(13, 49, "5. Reporte mensual");
        Mensaje(14, 49, "0. Regresar");

        Mensaje(16, 50, "Seleccione una opci%cn: ", 162);
        eOpcion = LeerEntero(16, 73, 1);
	
		switch (eOpcion) {
           
		    case 1: RegistrarVenta(aVentas, eTotalVentas, aClientes, eTotalClientes);
                	getch();
                	break;
            
			case 2: CancelarVenta(aVentas, eTotalVentas);
    				break;
                
            case 3: ConsultarVentasPorFechas(aVentas, *eTotalVentas);
    				break;
                
            case 4: ConsultarVentaPorId(aVentas, *eTotalVentas);
              	  	break;
                
            case 5: ReporteMensualVentas(aVentas, *eTotalVentas);
    				break;
                   
			case 0: break;
			
            default: Error(1); //Error (opción no válida)
                	 getch();
    
        }
        
    } while(eOpcion != 0);
    
} //SubMenuVentas

/* ******
* Función: BuscarVenta
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Buscar una venta por ID usando búsqueda binaria, opcionalmente ignorando ventas canceladas.
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas), ID a buscar (eIdBusqueda), filtro para ventas no canceladas (eCancelar)
* Retorna: Posición de la venta encontrada o -1 si no existe o está cancelada (según filtro)
****** */
int BuscarVenta(TaVentas aVentas, int eTotalVentas, int eIdBusqueda, int eCancelar) {
    
    //Variables
    int eMenor, eMayor, eMedio;
    
    if (eTotalVentas <= 0) {
    	
        return -1;
        
    }
    
    eMenor = 0;
    eMayor = eTotalVentas - 1;
    eMedio = (eMenor + eMayor) / 2;
    
    while (eMayor >= eMenor && eIdBusqueda != aVentas[eMedio].eIdVenta) {
        
        if (eIdBusqueda < aVentas[eMedio].eIdVenta) {
        	
            eMayor = eMedio - 1;
            
        } else {
        	
            eMenor = eMedio + 1;
            
        }
        
        eMedio = (eMenor + eMayor) / 2;
    }
    
    if (eMayor < eMenor) {
    	
        return -1;
        
    } else if (eCancelar == 1){
        
        if (aVentas[eMedio].eCancelada == 0) {
        	
            return eMedio;
            
        } else {
        	
            return -1;
            
        }
    }
    
    return eMedio;
    
} //BuscarVenta

/* ******
* Procedimiento: CargarVentas
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Cargar el arreglo de ventas desde un archivo binario.
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas)
* ******/
void CargarVentas(TaVentas aVentas, int *eTotalVentas) {

	//Variables
	FILE *pArchivoVentas;
	
    pArchivoVentas = fopen("ventas.dat", "rb");
    
    if (pArchivoVentas != NULL) {
    	
        fread(eTotalVentas, sizeof(int), 1, pArchivoVentas);
        
        fread(aVentas, sizeof(TrVenta), *eTotalVentas, pArchivoVentas);
        
        fclose(pArchivoVentas);
        
    } else {
    	
        *eTotalVentas = 0; // archivo no existe, arreglo vacío
        
    }
    
} //CargarVentas

/* ******
* Procedimiento: GuardarVentasEnArchivo
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Guardar el arreglo de ventas en un archivo binario.
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas)
****** */
void GuardarVentasEnArchivo(TaVentas *aVentas, int eTotalVentas) {
    
    //Variables
	FILE *pArchivo = fopen("ventas.dat", "wb");
    
    if (pArchivo != NULL) {
    	
        fwrite(&eTotalVentas, sizeof(int), 1, pArchivo);
        fwrite(aVentas, sizeof(TrVenta), eTotalVentas, pArchivo);
        fclose(pArchivo);
        
    } else {
    	
        Error(2); //Error (al guardar ventas en archivo)
        getch();
        
    }

} //GuardarVentasEnArchivo

/* ******
* Procedimiento: MostrarResumenVenta
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Mostrar un resumen con los datos principales de una venta.
* Parámetros: Venta (rVenta)
****** */
void MostrarResumenVenta(TrVenta rVenta) {
    
    //Variables
	char sPlataforma[20];
    char sCancelada[3];

    if (rVenta.ePlataforma == MERCADOLIBRE) {
    	
        strcpy(sPlataforma, "MercadoLibre");
        
    } else if (rVenta.ePlataforma == SHOPIFY) {
    	
        strcpy(sPlataforma, "Shopify");
        
    } else if (rVenta.ePlataforma == INSTAGRAM) {
    	
        strcpy(sPlataforma, "Instagram");
        
    } else {
    	
        strcpy(sPlataforma, "Desconocido");
        
    }

    if (rVenta.eCancelada == 1) {
    	
        strcpy(sCancelada, "SI");
        
    } else {
    	
        strcpy(sCancelada, "NO");
        
    }

    Mensaje(10, 19, "ID Cliente:");
    Mensaje(10, 34, "%d", rVenta.eIdCliente);

    Mensaje(12, 15, "Fecha de venta:");
    Mensaje(12, 34, "%02d/%02d/%04d", rVenta.rFechaVenta.eDia, rVenta.rFechaVenta.eMes, rVenta.rFechaVenta.eAnio);

    Mensaje(14, 19, "Plataforma:");
    Mensaje(14, 34, "%s", sPlataforma);

    Mensaje(16, 21, "Subtotal:");
    Mensaje(16, 34, "$%.2f", rVenta.fSubtotal);

    Mensaje(18, 26, "IVA:");
    Mensaje(18, 34, "$%.2f", rVenta.fIva);

    Mensaje(20, 24, "Total:");
    Mensaje(20, 34, "$%.2f", rVenta.fTotal);
    
} //MostrarResumenVenta

/* ******
* Procedimiento: ValidarIdArchivo
* Autor: Zuri G
* Fecha: 18/06/2025
* Objetivo: Validar que un ID exista en un archivo y obtener su precio asociado.
* Parámetros: Dirección de ID a validar (pId), dirección del precio (pPrecio), nombre del archivo (sArchivo), tipo para etiqueta (sTipo), fila para mostrar mensajes (eFila)
****** */
void ValidarIdArchivo(int *pId, float *pPrecio, char *sArchivo, char *sTipo, int eFila) {

	//Variables
    int eValido, eIdLeido;
    char sNombre[50];
    float fPrecioLeido;
    FILE *archivo;
    char sEtiqueta[30];
    
    eValido = 0;
    
    sprintf(sEtiqueta, "ID del %s:", sTipo);
    Mensaje(eFila, 5, sEtiqueta);

    do {
    	
        BorrarZona(eFila, 20, 1, 10);
        BorrarZona(26, 20, 2, 80);

        GoToXY(eFila, 20);
        *pId = LeerEntero(eFila, 20, 6);

        archivo = fopen(sArchivo, "r");

        if (archivo == NULL) {
        	
            Mensaje(26, 2, "No se pudo abrir el archivo.");
            getch();
            return;
            
        }

        eValido = 0;

        while (fscanf(archivo, "%d|%[^|]|%f\n", &eIdLeido, sNombre, &fPrecioLeido) == 3) {  //entero | texto hasta ‘|’ | flotante + salto de línea.
            
			if (eIdLeido == *pId) {
                *pPrecio = fPrecioLeido;
                eValido = 1;
                break;
                
            }
        }

        fclose(archivo);

        if (!eValido) {
            Error(12);  // Error"ID no válido"
            getch();
        }

    } while (!eValido);
    
}//ValidarIdArchivo

/* ******
* Procedimiento: RegistrarVenta
* Autor: Zuri G
* Fecha: 15/06/2025 - 19/06/2025
* Objetivo: Registrar una o varias ventas nuevas con validación y captura de datos :)
* Parámetros: Arreglo de ventas (aVentas), total actual de ventas (eTotalVentas), arreglo de clientes (aClientes), total de clientes (eTotalClientes)
****** */

void RegistrarVenta(TaVentas *aVentas, int *eTotalVentas, TaClientes aClientes, int eTotalClientes){
	
	//Variables
	TrVenta rVenta;
    int eSeguirVenta;
    float fSubtotal;
    char sMensaje[50];
	
    do {
    	
    	Pantalla4();	
    	Centrar("Registrar Venta", 2);

        if (*eTotalVentas == MAX_VENTAS - 1) {
            
			Error(3); //Error (No hay espacio)
            getch();
        	return;
        	
    	} else {

			fSubtotal = 0;
	
			rVenta.eIdCliente = ValidarIdCliente(aClientes, eTotalClientes, 1);
	
			if (rVenta.eIdCliente == -1) {
				
				return;
		
			} else {
		            	
			    CapturarDatosVenta(&rVenta);
		
				CapturarProductosVenta(&rVenta, &fSubtotal);
			
				ProcesarVenta(&rVenta, rVenta.eTotalProductos, fSubtotal);

				GuardarNuevaVenta(aVentas, eTotalVentas, &rVenta);
				
				Pantalla3();
		    	
				sprintf(sMensaje, " %cRegistrar otra venta? (s/n):", 168);	
				eSeguirVenta = LeerSN(14, 44, sMensaje);
				
			}
			
		}
    
	} while (eSeguirVenta);
    
    Centrar("Pulse una tecla para regresar...", 26);

}//RegistrarVenta

/* ******
* Procedimiento: CapturarProducto
* Autor: Zuri G
* Fecha: 16/06/2025 - 18/06/2025
* Objetivo: Capturar y validar los IDs de insumo y diseño, y obtener sus precios.
* Parámetros: Dirección del producto a llenar (pProducto), dirección del precio del insumo (pPrecioInsumo), dirección del precio del diseño (pPrecioDisenio) :c
****** */
void CapturarProducto(TrProducto *pProducto, float *pPrecioInsumo, float *pPrecioDisenio) {
	
	//Variables
    TrProducto rCopia;
    float fInsumo, fDisenio;

    BorrarZona(5, 20, 3, 3);  // Borra campos de ID
    BorrarZona(26, 1, 2, 70); // Borra posibles errores previos

    ValidarIdArchivo(&rCopia.eIdInsumo, &fInsumo, "Insumos.txt", "insumo", 5);
    ValidarIdArchivo(&rCopia.eIdDisenio, &fDisenio, "Disenos.txt", "diseno", 6);

    *pPrecioInsumo = fInsumo;
    *pPrecioDisenio = fDisenio;
    *pProducto = rCopia;

} //CapturarProducto

/******
* Procedimiento: CapturarDatosVenta
* Autor: Zuri G
* Fecha: 15/06/2025 - 18/06/2025
* Objetivo: Capturar la fecha y plataforma de una venta.
* Parámetros: Dirección del registro de venta a modificar (pVenta)
******/
void CapturarDatosVenta(TrVenta *pVenta) {
	
	//Variables
    int eOpcion;
    TrVenta rCopia = *pVenta;

    Mensaje(10, 10, "Fecha de la venta:");
    rCopia.rFechaVenta = LeerFecha(11, 10);

    Mensaje(16, 10, "[1- MERCADO LIBRE     2-SHOPIFY     3-INSTAGRAM]");
    Mensaje(17, 10, "Plataforma:");
    
    eOpcion = LeerEnteroEnRango(17, 22, 1, 3);
    
    rCopia.ePlataforma = (TePlataformas)(eOpcion - 1);

    *pVenta = rCopia;

} //CapturarDatosVenta

/* ******
* Procedimiento: CapturarProductosVenta
* Autor: Zuri G
* Fecha: 15/06/2025 - 18/06/2025
* Objetivo: Capturar varios productos para una venta y calcular subtotal.
* Parámetros: Dirección de a venta (pVenta), dirección del subtotal acumulado (pSubtotal)
****** */
void CapturarProductosVenta(TrVenta *pVenta, float *pSubtotal) {
	
	//Variables
    TrProducto rProducto;
    int eContador = 0;
    int eRenglon = 11;
    float fPrecioInsumo, fPrecioDisenio;
    int eSeguirProducto = 1;
    char sMensaje[60];

    PantallaProductos();

    while (eSeguirProducto && eContador < MAX_PRODUCTOS) {
        
		CapturarProducto(&rProducto, &fPrecioInsumo, &fPrecioDisenio);

        if (eRenglon > 20) {
            
			eRenglon = 12;
            
			BorrarZona(11, 3, 10, 114);
        }

        Mensaje(eRenglon, 12, "%d", eContador + 1);
        
        rProducto.eCantidad = LeerEnteroEnRango(eRenglon, 31, 1, 100);

        rProducto = ProcesarProducto(rProducto, pVenta, eContador, fPrecioInsumo, fPrecioDisenio, pSubtotal);
        eContador++;

        MostrarPreciosProducto(rProducto, eRenglon);

        eRenglon += 2;

        if (eContador < MAX_PRODUCTOS) {
            
			sprintf(sMensaje, "%cAgregar otro producto? (s/n):", 168);
            eSeguirProducto = LeerSN(26, 2, sMensaje);
            
        } else {
        	
            sprintf(sMensaje, "Se alcanz%c el m%cximo de productos por venta. Pulse una tecla para continuar...", 162, 160);
    		Centrar(sMensaje, 26);
    		getch();
            eSeguirProducto = 0;
            
        }
    }

    (*pVenta).eTotalProductos = eContador;
    
} //CapturarProductosVenta

/******
* Procedimiento: GenerarIdVenta
* Autor: Zuri G
* Fecha: 16/06/2025 - 18/06/2025
* Objetivo: Generar un nuevo ID único para una venta.
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas), dirección para almacenar nuevo ID (pIdVentaNuevo)
******/
void GenerarIdVenta(TaVentas *aVentas, int eTotalVentas, int *pIdVentaNuevo) {
	
	//Variables
    int eMaxId, eContador;
    
    eMaxId = 0;
    
    for (eContador = 0; eContador < eTotalVentas; eContador++) {
    	
        if ((*aVentas)[eContador].eIdVenta > eMaxId) {
        	
            eMaxId = (*aVentas)[eContador].eIdVenta;
            
        }
    }
    
    *pIdVentaNuevo = eMaxId + 1;
    
} //GenerarIdVenta

/* ******
* Procedimiento: GuardarNuevaVenta
* Autor: Zuri G
* Objetivo: Asignar ID a una venta, agregarla al arreglo y guardar en archivo.
* Parámetros: Arreglo de ventas (aVentas), dirección del total de ventas (eTotalVentas), dirección de la venta a guardar (pVenta)
****** */
void GuardarNuevaVenta(TaVentas *aVentas, int *eTotalVentas, TrVenta *pVenta) {
	
	//Variables
    int eIdActual;
    char sMensaje[50];
    
    GenerarIdVenta(aVentas, *eTotalVentas, &eIdActual);
    
    (*pVenta).eIdVenta = eIdActual;    
    
    (*aVentas)[*eTotalVentas] = *pVenta;
    
	(*eTotalVentas)++;
    
    GuardarVentasEnArchivo(aVentas, *eTotalVentas);
    
    BorrarZona(26, 1, 2, 45);
    
    Mensaje(26, 2, "La venta se registr%c correctamente.", 162);
    sprintf(sMensaje, "ID de la venta: %d", eIdActual);
    Centrar(sMensaje, 26);
    
	getch(); 
    
} //GuardarNuevaVenta

/* ******
* Procedimiento: MostrarPreciosProducto
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Mostrar los precios y el importe de un producto en pantalla.
* Parámetros: Producto a mostrar (rProducto), fila para mostrar (eRenglon)
****** */
void MostrarPreciosProducto(TrProducto rProducto, int eRenglon) {
	
	//Variables
    float fImporte;

    fImporte = rProducto.fPrecio * rProducto.eCantidad;

    Mensaje(eRenglon, 47, "$%.2f", rProducto.fPrecioDisenio);
    Mensaje(eRenglon, 68, "$%.2f", rProducto.fPrecioInsumo);
    Mensaje(eRenglon, 87, "$%.2f", rProducto.fPrecio);
    Mensaje(eRenglon, 105, "$%.2f", fImporte);

} //MostrarPreciosProducto

/* ******
* Función: ProcesarProducto
* Autor: Zuri G
* Fecha: 17/06/2025 - 187/06/2025
* Objetivo: Calcular precio final, importe y actualizar la venta con el producto procesado.
* Parámetros: Producto a procesar (rProducto), dirección de la venta (pVenta), índice del producto (eContador), precio de insumo (fPrecioInsumo), precio de diseño (fPrecioDisenio), 
			dirección del subtotal acumulado (pSubtotal)
* Retorna: Producto "procesado" [con precios y datos actualizados (rProducto)]
****** */
TrProducto ProcesarProducto(TrProducto rProducto, TrVenta *pVenta, int eContador, float fPrecioInsumo, float fPrecioDisenio, float *pSubtotal) {
    //Variables
    float fPrecioFinal, fImporte;
	
	rProducto.fPrecioInsumo = fPrecioInsumo;
    rProducto.fPrecioDisenio = fPrecioDisenio;

    fPrecioFinal = fPrecioInsumo + fPrecioDisenio;
    rProducto.fPrecio = fPrecioFinal;

    fImporte = fPrecioFinal * rProducto.eCantidad;
    *pSubtotal += fImporte;

    rProducto.eIdProducto = eContador + 1;

    (*pVenta).aProductos[eContador] = rProducto;

    return rProducto;
    
} //ProcesarProducto

/******
* Procedimiento: ProcesarVenta
* Autor: Zuri G
* Fecha: 17/06/2025 - 1/06/2025
* Objetivo: Calcular totales e inicializar datos de la venta.
* Parámetros: Dirección de venta (pVenta), número de productos (eContador), subtotal acumulado (fSubtotal)
******/
void ProcesarVenta(TrVenta *pVenta, int eContador, float fSubtotal) {
	
	//Variables
    TrVenta rCopia = *pVenta;

    rCopia.eTotalProductos = eContador;
    rCopia.fSubtotal = fSubtotal;
    rCopia.fIva = fSubtotal * 0.16f;
    rCopia.fTotal = rCopia.fSubtotal + rCopia.fIva;
    rCopia.eCancelada = 0;
    rCopia.rFechaCancelacion.eDia = 0;
    rCopia.rFechaCancelacion.eMes = 0;
    rCopia.rFechaCancelacion.eAnio = 0;
    rCopia.sMotivoCancelacion[0] = '\0';

    // Actualiza el contenido al q apunta
    *pVenta = rCopia;

    Mensaje(22, 95, "Subtotal: $%.2f", rCopia.fSubtotal);
    Mensaje(23, 100, "IVA: $%.2f", rCopia.fIva);
    Mensaje(26, 98, "Total: $%.2f", rCopia.fTotal);
    
} //ProcesarVenta

/* ******
* Procedimiento: CancelarVenta
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Cancelar una venta existente con confirmación y guardar cambios ><
* Parámetros: Arreglo e ventas (aVentas), dirección del total de ventas (eTotalVentas)
****** */
void CancelarVenta(TaVentas *aVentas, int *eTotalVentas) {
	
	//Variables
    int eIdBusqueda, eContador, ePos, eConfirmacion;
	TrVenta rVenta;
	char sMensaje[50];
	
    Pantalla4();
    Centrar("Cancelar Venta", 2);
	
	if(*eTotalVentas == 0){
		
		Centrar("No hay ventas. Pulse una tecla para regresar...", 26);
		getch();
	
	} else{
		
	    ePos = ValidarIdVentaCancelacion(*aVentas, *eTotalVentas, &eIdBusqueda);
		
		if (ePos == -1){
		
			return;
	
		} else {
	
    			rVenta = (*aVentas)[ePos];
				MostrarResumenVenta(rVenta);
				
				sprintf(sMensaje, " %cCancelar esta venta? (s/n)?:", 168);
				eConfirmacion = LeerSN(22, 44, sMensaje);
				
				if (eConfirmacion) {
					
				    BorrarZona(5, 2, 19, 117);
				
				    CapturarDatosCancelacion(&rVenta);
				    rVenta.eCancelada = 1;
				
				    (*aVentas)[ePos] = rVenta;
				    GuardarVentasEnArchivo(aVentas, *eTotalVentas);
				
				    Centrar("Venta cancelada correctamente. Pulse una tecla para regresar...", 26);
	                
	            } else {
	            	
	                sprintf(sMensaje, "Operaci%cn anulada por el usuario. Pulse una tecla para regresar...", 162);
            		Centrar(sMensaje, 26);
	                
	            }

            getch();
        }
    }

} //CancelarVenta

/* ******
* Procedimiento: CapturarDatosCancelacion
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Capturar el motivo y fecha de cancelación de una venta.
* Parámetros: Dirección del registro de venta a modificar (pVenta)
****** */
void CapturarDatosCancelacion(TrVenta *pVenta) {
    //Variables
	int eContador;

	BorrarZona(26, 40, 1, 45);
    Mensaje(6, 5, "Motivo de cancelaci%cn: ", 162);

    for (eContador = 0; eContador < 130; eContador++) {
    	
        (*pVenta).sMotivoCancelacion[eContador] = '\0';
    }

    fflush(stdin);
    gets((*pVenta).sMotivoCancelacion);

    Mensaje(9, 5, "Fecha de cancelaci%cn", 162);
    (*pVenta).rFechaCancelacion = LeerFecha(10, 5);

} //CapturarDatosCancelacion

/* ******
* Función: ValidarIdVentaCancelacion
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Validar el ID de una venta para cancelación, asegurando que exista y esté activa.
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas), dirección para almacenar ID validado (pIdVenta)
* Retorna: Posición de la venta en el arreglo o -1 si el usuario 'x' o no existe
****** */
int ValidarIdVentaCancelacion(TaVentas aVentas, int eTotalVentas, int *pIdVenta) {
    
    //Variables
    char sEntrada[10];
    int eId, ePos;
	char sMensaje[50];
	
    do {
    	
		BorrarZona(26, 20, 2, 80);
        BorrarZona(8, 34, 2, 7);
        
        Centrar("Pulse 'x' para regresar.", 26);
        
        Mensaje(8, 15, "ID de la venta:    ");
        LeerCadena(sEntrada, 9);

        if (sEntrada[0] == 'x' || sEntrada[0] == 'X') {
            
            BorrarZona(26, 20, 2, 80);
            sprintf(sMensaje, "Operaci%cn anulada por el usuario. Pulse una tecla para regresar...", 162);
            Centrar(sMensaje, 26);
            getch();
            return -1;
        
		} else {

	        eId = atoi(sEntrada);

	        if (eId <= 0) {
	        	
	            Error(6);
	            getch();
	            ePos = -1;
	            
	        } else {
	        	
	            ePos = BuscarVenta(aVentas, eTotalVentas, eId, 1);

	            if (ePos == -1) {
	            	
	                BorrarZona(26, 20, 2, 80);
	                sprintf(sMensaje, "No se encontr%c una venta [activa] con ID %d.", 162, eId);
	                Centrar(sMensaje, 26);
	                getch();
	                
	            }	
	        }
	    }

    } while (ePos == -1);

    *pIdVenta = eId;
    BorrarZona(26, 20, 2, 80);
    return ePos;   

} //ValidarIdVentaCancelacion

/* ******
* Procedimiento: ConsultarVentasPorFechas
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Permitir consulta de ventas entre dos fechas especificadas.
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas)
****** */
void ConsultarVentasPorFechas(TaVentas *aVentas, int eTotalVentas) {
	
	//Variables
	TrFecha rFechaInicio, rFechaFin;
    int eEncontrado, eRenglon;
	
    Pantalla2();
    Centrar("Consulta de Ventas por fechas", 1);
	
    if (eTotalVentas == 0) {
        
		Centrar("No hay ventas. Pulse una tecla para regresar...", 26);
		getch();
    
	} else {
		
		do {
            
            BorrarZona(5, 10, 3, 6);
            BorrarZona(5, 32, 3, 6);
            
			Mensaje(4, 5, "Fecha Inicial");
            rFechaInicio = LeerFecha(5, 5);

            Mensaje(4, 28, "Fecha Final");
            rFechaFin = LeerFecha(5, 28);

            if (!ValidarFechaMenorOIgual(rFechaInicio, rFechaFin)) {
                
				Error(15);
				getch();
				
			}

		} while (!ValidarFechaMenorOIgual(rFechaInicio, rFechaFin));

        PantallaConsultaFechas();

        eEncontrado = FiltrarMostrarVentasPorFecha(aVentas, eTotalVentas, rFechaInicio, rFechaFin);

        if (eEncontrado == 0) {
        	
            Centrar("No se encontraron ventas en el rango especificado. Pulse una tecla para regresar...", 26);
            getch();
            
        } else {
        	
            Centrar("Consulta finalizada. Pulse una tecla para regresar...", 26);
            getch();
            
        }
    }

} //ConsultarVentasPorFechas

/* ******
* Función: FiltrarMostrarVentasPorFecha
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Filtrar ventas entre dos fechas y mostrarlas en pantalla.
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas), fecha inicio (rFechaInicio), fecha fin (rFechaFin)
* Retorna: 1 si encontró ventas :D, 0 si no encontró ninguna D:
****** */
int FiltrarMostrarVentasPorFecha(TaVentas *aVentas, int eTotalVentas, TrFecha rFechaInicio, TrFecha rFechaFin) {
    
    //Variables
	int eContador, eFechaMaOIInicio, eFechaMeOIFin, eEncontrado, eRenglon;
	TrFecha rFechaVenta;
	
	eEncontrado = 0;
	eRenglon = 11;
	
    for (eContador = 0; eContador < eTotalVentas; eContador++) {
    	
        rFechaVenta = (*aVentas)[eContador].rFechaVenta;

        eFechaMaOIInicio = 0;
        
        if (rFechaVenta.eAnio > rFechaInicio.eAnio) {
            eFechaMaOIInicio = 1;
        } else if (rFechaVenta.eAnio == rFechaInicio.eAnio) {
            if (rFechaVenta.eMes > rFechaInicio.eMes) {
                eFechaMaOIInicio = 1;
            } else if (rFechaVenta.eMes == rFechaInicio.eMes) {
                if (rFechaVenta.eDia >= rFechaInicio.eDia) {
                    eFechaMaOIInicio = 1;
                }
            }
        }

        eFechaMeOIFin = 0;
        if (rFechaVenta.eAnio < rFechaFin.eAnio) {
            eFechaMeOIFin = 1;
        } else if (rFechaVenta.eAnio == rFechaFin.eAnio) {
            if (rFechaVenta.eMes < rFechaFin.eMes) {
                eFechaMeOIFin = 1;
            } else if (rFechaVenta.eMes == rFechaFin.eMes) {
                if (rFechaVenta.eDia <= rFechaFin.eDia) {
                    eFechaMeOIFin = 1;
                }
            }
        }

        if (eFechaMaOIInicio && eFechaMeOIFin) {
            MostrarDatosVenta(aVentas, eContador, eRenglon);
            eEncontrado = 1;
            eRenglon++;

            if (eRenglon >= 23) {
                Centrar("Pulse una tecla para continuar...", 26);
                getch();
                BorrarZona(12, 3, 12, 112);
                eRenglon = 11;
            }
        }
    }

    return eEncontrado;
    
} //FiltrarMostrarVentasPorFecha

/* ******
* Procedimiento: MostrarDatosVenta
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Mostrar los datos resumidos de una venta en un renglon
* Parámetros: Arreglo de ventas (aVentas), indice de venta (eIndice), renglón en pantalla (eRenglon)
* Retorna: Nada
****** */
void MostrarDatosVenta(TaVentas *aVentas, int eIndice, int eRenglon) {
	
	//Variables
    char sPlataforma[20];
    char sCancelada[5];
    TrVenta rVenta = (*aVentas)[eIndice];

    if (rVenta.ePlataforma == MERCADOLIBRE) {
    	
        strcpy(sPlataforma, "MercadoLibre");
        
    } else if (rVenta.ePlataforma == SHOPIFY) {
    	
        strcpy(sPlataforma, "Shopify");
        
    } else if (rVenta.ePlataforma == INSTAGRAM) {
    	
        strcpy(sPlataforma, "Instagram");
        
    } else {
    	
        strcpy(sPlataforma, "Desconocido");
        
    }

    if (rVenta.eCancelada == 1) {
    	
        strcpy(sCancelada, "SI");
        
    } else {
    	
        strcpy(sCancelada, "NO");
        
    }

    Mensaje(eRenglon + 1, 8, "%02d/%02d/%04d", rVenta.rFechaVenta.eDia, rVenta.rFechaVenta.eMes, rVenta.rFechaVenta.eAnio);
    Mensaje(eRenglon + 1, 32, "%d", rVenta.eIdVenta);
    Mensaje(eRenglon + 1, 51, "%d", rVenta.eIdCliente);
    Mensaje(eRenglon + 1, 64, "%s", sPlataforma);
    Mensaje(eRenglon + 1, 88, "%s", sCancelada);
    Mensaje(eRenglon + 1, 104, "$%.2f", rVenta.fTotal);
    
} //MostrarDatosVenta

/* ******
* Procedimiento: PantallaConsultaFechas
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Mostrar encabezados y estructura de la tabla para consulta de ventas por fechas.
****** */
void PantallaConsultaFechas(){
	    
		DibujarTabla(9, 3, 1, 6, 18);
		    
		Mensaje(10, 10, "Fecha ");
		Mensaje(10, 46, "ID Cliente", 164);
		Mensaje(10, 64, "Plataforma");
		Mensaje(10, 84, "Cancelada");
		Mensaje(10, 105, "Total");
		Mensaje(10, 28, "ID Venta");
		
} //PantallaConsultaFechas

/* ******
* Función: ValidarFechaMenorOIgual
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Verificar si una fecha es menor o igual a otra.
* Parámetros: Fecha inicial (rFecha1), Fecha final (rFecha2)
* Retorna: 1 si rFecha1 <= rFecha2, oooo 0 en caso contrario :p
****** */
int ValidarFechaMenorOIgual(TrFecha rFecha1, TrFecha rFecha2) {
    
	if (rFecha1.eAnio < rFecha2.eAnio){
	
		return 1;
		
	} else if (rFecha1.eAnio > rFecha2.eAnio){
	
		return 0;
		
	} else if (rFecha1.eMes < rFecha2.eMes){
		
		return 1;
	
	} else if (rFecha1.eMes > rFecha2.eMes){
	
		return 0;
		
	} else if (rFecha1.eDia <= rFecha2.eDia){
		
		return 1;
	
	} else {
		
    	return 0;
    	
	}
	
} //ValidarFechaMenorOIgual

/*******
* Procedimiento: ConsultarVentaPorId
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Consultar y mostrar una venta por su ID
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas)
****** */
void ConsultarVentaPorId(TaVentas *aVentas, int eTotalVentas) {
	
	//Variables
    int eContador2, ePos;
    char sPlataforma[5];
    char sCancelada[5];
    char sTemp[32];
    TrVenta rVenta;

    Pantalla2();
    Centrar("Consulta de Venta por ID", 1);

    if (eTotalVentas == 0) {
    	
        Centrar("No hay ventas. Pulse una tecla para regresar...", 26);
        
    } else {
    	
        ePos = ValidarIdVentaConsulta(*aVentas, eTotalVentas);
        rVenta = (*aVentas)[ePos];

        if (rVenta.eCancelada == 1) {
    		
			MostrarDatosCancelacion(rVenta);
			
		}
		
		MostrarResumenVenta(rVenta);

        Centrar("Consulta finalizada. Pulse una tecla para regresar...", 26);
    }

    getch();
    
} //ConsultarVentaPorId

/* ******
* Procedimiento: MostrarDatosCancelacion
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Mostrar motivo y fecha de cancelación de una venta
* Parámetros: Registro de venta (rVenta)
****** */
void MostrarDatosCancelacion(TrVenta rVenta) {
	
	//Variables
    int eContador;
    char sTemp[33]; // 32 caracteres + '\0'

    Mensaje(8, 23, " VENTA:    CANCELADA");
    Mensaje(8, 64, "Motivo de cancelaci%cn:", 162);

    for (eContador = 0; eContador < 4; eContador++) {
        
		strncpy(sTemp, rVenta.sMotivoCancelacion + (eContador * 32), 32);
        sTemp[32] = '\0';

        if (strlen(sTemp) > 0) {
            
			Mensaje(10 + eContador, 64, "%s", sTemp);
        
		}
    }

    Mensaje(16, 64, "Fecha de cancelaci%cn:", 162);
    Mensaje(18, 64, "%02d/%02d/%04d", rVenta.rFechaCancelacion.eDia, rVenta.rFechaCancelacion.eMes, rVenta.rFechaCancelacion.eAnio);
        
} //MostrarDatosCancelacion

/* ******
* Funcin: ValidarIdVentaConsulta
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Validar existencia de ID de venta para consulta
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas)
* Retorna: Posición en arreglo de la venta válida
****** */
int ValidarIdVentaConsulta(TaVentas aVentas, int eTotalVentas) {
    
    //Variables
	int eId, ePos;

    while (1) {
    	
        Mensaje(6, 15, "ID de la venta:    ");
        eId = LeerEntero(5, 31, 6);

        ePos = BuscarVenta(aVentas, eTotalVentas, eId, 0);

        if (ePos == -1) {
        	
            Centrar("ID no encontrado. Intenta de nuevo.", 26);
            getch();
            BorrarZona(5, 67, 1, 15);
            BorrarZona(26, 20, 1, 80);
            
        } else {
        	
            return ePos;
            
        }
    }
    
} //ValidarIdVentaConsulta

/* *****
* Procedimiento: ReporteMensualVentas
* Autor: Zuri G
* Fecha: 18/06/2025
* Objetivo: Mostrar reporte de ventas por plataforma en mes y año indicados
* Parámetros: Arreglo de ventas (aVentas), total de ventas (eTotalVentas)
****** */
void ReporteMensualVentas(TaVentas *aVentas, int eTotalVentas) {
	
	//Variables
	char sPeriodo[15];
	int eVentasTotales, eVentasML, eVentasShopify, eVentasInstagram, eMes, eAnio;
	float fTotalVentas, fTotalML, fTotalShopify, fTotalInstagram;

	eVentasML = 0;
	eVentasShopify = 0;
	eVentasInstagram = 0;
	fTotalML = 0;
	fTotalShopify = 0;
	fTotalInstagram = 0;
	
    Pantalla5();
    Centrar("No vacancy", 1);
    Centrar("Subsistema de Ventas", 2);
    Centrar("Reporte Mensual de Ventas", 3);

	if(eTotalVentas == 0){
		
		Centrar("No hay ventas. Pulse una tecla para regresar...", 26);

	} else {
		
	    Centrar("Ingrese el mes: ", 13);
	    eMes = LeerEnteroEnRango(13, 68, 1, 31);
	
	    Mensaje(15, 52, "Ingrese el a%co: ", 164);
	    eAnio = LeerEnteroEnRango(15, 68, 2020, 2100);
	
	    BorrarZona(13, 48, 4, 25);
	
	    sprintf(sPeriodo, "Periodo: %02d/%04d", eMes, eAnio);
	    Centrar(sPeriodo, 4);
	
	    ImprimirVentasPorPlataforma(aVentas, eTotalVentas, MERCADOLIBRE, eMes, eAnio, &eVentasML, &fTotalML, 0);
	    ImprimirVentasPorPlataforma(aVentas, eTotalVentas, SHOPIFY, eMes, eAnio, &eVentasShopify, &fTotalShopify, 0);
	    ImprimirVentasPorPlataforma(aVentas, eTotalVentas, INSTAGRAM, eMes, eAnio, &eVentasInstagram, &fTotalInstagram, 1);
	
	    eVentasTotales = eVentasML + eVentasShopify + eVentasInstagram;
	    fTotalVentas = fTotalML + fTotalShopify + fTotalInstagram;
	
	    Mensaje(23, 27, "# VENTAS TOTALES: %d", eVentasTotales);
	    Mensaje(23, 58, "TOTAL VENTAS DEL PERIODO: $%.2f", fTotalVentas);
	
	    Centrar("Se ha completado el reporte. Pulse una tecla para regresar...", 26);
	}
	
    getch();
    
} //ReporteMensualVentas

/******
* Procedimiento: ImprimirVentasPorPlataforma
* Autor: Zuri G
* Fecha: 18/06/2025
* Objetivo: Mostrar ventas y totales filtrados por plataforma, mes y año
* Parámetros: Arreglo de ventas (aVentas), número de ventas (eTotalVentas), plataforma a filtrar (ePlataforma), mes (eMes), año (eAnio), 
			  cantidad de ventas filtradas (eVentas), total acumulado (fTotal), indicador de última plataforma (eUltimaPlataforma)
******/
void ImprimirVentasPorPlataforma(TaVentas *aVentas, int eTotalVentas, TePlataformas ePlataforma, int eMes, int eAnio, int *eVentas, 
								  float *fTotal, int eUltimaPlataforma){
    
    //Variables
    int eContador, eRenglon;
    char sCancelada[3];
    TrFecha rFechaVenta;
    TrVenta rVenta;

    *eVentas = 0;
    *fTotal = 0;
	eRenglon = 11;

	BorrarZona(11, 12, 12, 100);
	BorrarZona(6, 45, 2, 30);
	
    if (ePlataforma == MERCADOLIBRE){
    	
        Centrar("MERCADOLIBRE", 7);
        
    } else if (ePlataforma == SHOPIFY) {
    	
        Centrar("SHOPIFY", 7);
        
    } else if (ePlataforma == INSTAGRAM) {
    	
        Centrar("INSTAGRAM", 7);
    }

    TablaPlataforma();

    for (eContador = 0; eContador < eTotalVentas; eContador++) { //recorre las ventas

        rVenta = (*aVentas)[eContador]; //toma la venta donde esta el contador
        rFechaVenta = rVenta.rFechaVenta; //toma su fecha

        if (rVenta.ePlataforma == ePlataforma && rFechaVenta.eMes == eMes && rFechaVenta.eAnio == eAnio) { //mostrar si coincide plataforma,mes y año

            if (eRenglon > 19) { //imprime hasta la linea 19
            	
                Centrar("Pulse una tecla para continuar...", 26);
                getch();
                BorrarZona(11, 12, 12, 100);
                eRenglon = 11;
            }
			
			if (rVenta.eCancelada == 1) {
            	
                strcpy(sCancelada, "SI");
                
            } else {
            	
                strcpy(sCancelada, "NO");
                
            }

            MostrarFilaVentaPlataforma(rVenta, eRenglon, sCancelada);
			
            *fTotal += rVenta.fTotal;
            *eVentas += 1;
            eRenglon++;
        }
    }

    Mensaje(21, 75, "# Ventas: %d", *eVentas);
    Mensaje(21, 92, "Total: $%.2f", *fTotal);

    if (!eUltimaPlataforma) { //si no es la última plataforma...
    	
        Centrar("Pulse una tecla para continuar...", 26);
        getch();
        
    }
    
} //ImprimirVentasPorPlataforma

/* *******
* Procedsimiento: MostrarFilaVentaPlataforma
* Autor: Zuri G
* Fecha: 18/06/2025
* Objetivo: Mostrar fila resumen de venta con plataforma y estado cancelación
* Parámetros: Venta (rVenta), renglón para mostrar (eRenglon), texto cancelación (sCancelada)
****** */
void MostrarFilaVentaPlataforma(TrVenta rVenta, int eRenglon, char *sCancelada) {
	
	//Variables
    TrFecha rFechaVenta = rVenta.rFechaVenta;

    Mensaje(eRenglon, 21, "%d", rVenta.eIdVenta);
    Mensaje(eRenglon, 37, "%02d/%02d/%04d", rFechaVenta.eDia, rFechaVenta.eMes, rFechaVenta.eAnio);
    Mensaje(eRenglon, 59, "%d", rVenta.eIdCliente);
    Mensaje(eRenglon, 78, "%s", sCancelada);
    Mensaje(eRenglon, 96, "$%.2f", rVenta.fTotal);
    
} //MostrarFilaVentaPlataforma

#endif
