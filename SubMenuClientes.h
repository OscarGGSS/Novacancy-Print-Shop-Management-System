#ifndef SUBMENUCLIENTES_H
#define SUBMENUCLIENTES_H

//Bibliotecas
#include <stdio.h>
#include <stdlib.h> 
#include "NVInterfaz.h"
#include <conio.h>
#include "NVFunciones.h"

//Prototipos
void ActualizarArchivoClientes(TaClientes, int);
int BuscarCliente(TaClientes, int, int);
void CargarClientes(TaClientes, int *);
void ConsultarCliente(TaClientes, int);
void DesactivarCliente(TaClientes, int *);
void InsertarCliente(TaClientes, int *, TrCliente);
TrCliente LeerCliente();
void ListarClientes(TaClientes, int);
void ModificarCliente(TaClientes, int);
void MostrarCliente(TrCliente, int);
void SubMenuClientes(TaClientes, int *);
int ValidarIdCliente(TaClientes, int, int);

/* ******
* Procedimiento: SubMenuClientes
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Mostrar el menú de clientes
* Parámetros: Arreglo de clientes (aClientes), total actual de clientes (eTotal)
******/
void SubMenuClientes(TaClientes aClientes, int *eTotalClientes) {
	
	//Variables
    int eOpcion, eId;
	TrCliente rCliente;
	
    do {
    	
        Pantalla4();
        Centrar("CLIENTES", 2);

        Mensaje(9, 49, "1. Registrar cliente");
        Mensaje(10, 49, "2. Desactivar cliente");
        Mensaje(11, 49, "3. Modificar cliente");
        Mensaje(12, 49, "4. Consultar cliente (ID)");
        Mensaje(13, 49, "5. Listar clientes");
        Mensaje(14, 49, "0. Regresar");

        Mensaje(16, 50, "Seleccione una opci%cn: ", 162);
        eOpcion = LeerEntero(16, 73, 1);

        switch (eOpcion) {

            case 1: rCliente = LeerCliente();
                	InsertarCliente(aClientes, eTotalClientes, rCliente);
                	getch();
                	break;

            case 2: DesactivarCliente(aClientes, eTotalClientes);
					getch();
    				break;

            case 3: ModificarCliente(aClientes, *eTotalClientes);
                	getch();
                	break;

            case 4: ConsultarCliente(aClientes, *eTotalClientes);
                	getch();
                	break;

            case 5: ListarClientes(aClientes, *eTotalClientes);
                	getch();
                	break;

            case 0: break;

            default: Error(1); // Opción no válida
        }

    } while (eOpcion != 0);
    
} //SubMenuClientes

/******
* Procedimiento: ActualizarArchivoClientes
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Guardar en archivo el arreglo completo de clientes.
* Parámetros: Arreglo de clientes (aClientes), total actual de clientes (eTotal)
******/
void ActualizarArchivoClientes(TaClientes aClientes, int eTotal) {
	
	//Variables
    int eContador;
    FILE *pArchivo;
	
	pArchivo = fopen("Clientes.txt", "w");

    if (pArchivo != NULL) {

        for (eContador = 0; eContador < eTotal; eContador++) {
        	
            fprintf(pArchivo, "%d|%s|%s|%s|%s|%d\n",
                aClientes[eContador].eIdCliente,
                aClientes[eContador].sNombre,
                aClientes[eContador].sTelefono,
                aClientes[eContador].sDireccion,
                aClientes[eContador].sCorreo,
                aClientes[eContador].eActivo);
        }
        
        fclose(pArchivo);
    }
    
} //ActualizarArchivoClientes

/******
* Función: BuscarCliente
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Buscar un cliente por su ID usando búsqueda binaria.
* Parámetros: Arreglo de clientes (aClientes), total de clientes (eTotal), ID a buscar (eId)
* Retorna: Posición del cliente encontrado (eMedio) o -1 si no existe 
******/
int BuscarCliente(TaClientes aClientes, int eTotal, int eId) {
	
	//Variables
    int eMenor, eMayor, eMedio;

    if (eTotal == -1) {
    	
        return -1;
        
    } else {
    	
        eMenor = 0;
        eMayor = eTotal;
        eMedio = eTotal / 2;

        while (eMayor >= eMenor && eId != aClientes[eMedio].eIdCliente) {
        	
            if (eId < aClientes[eMedio].eIdCliente) {
            	
                eMayor = eMedio - 1;
                
            } else {
            	
                eMenor = eMedio + 1;
                
            }

            eMedio = (eMenor + eMayor) / 2;
        }

        if (eMayor < eMenor) {
        	
            return -1;
            
        } else {
        	
            return eMedio;
        }
    }
    
} //BuscarCliente

/* ******
* Procedimiento: CargarClientes
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Leer los clientes desde un archivo y cargarlos en memoria.
* Parámetros: Arreglo donde se cargan los clientes (aClientes), total de clientes leídos (eTotalClientes)
****** */
void CargarClientes(TaClientes aClientes, int *eTotalClientes) {
	
	//Variables
	int eContador, eLeidos;
	TrCliente rCliente;
	FILE *pArchivo;
	
    pArchivo = fopen("Clientes.txt", "r");
    
    if (pArchivo == NULL) {
    	
        *eTotalClientes = -1;

    } else {

	    eContador = 0;
	    
	    while (!feof(pArchivo) && eContador < MAX_CLIENTES) {
	
	        eLeidos = fscanf(pArchivo, "%d|%39[^|]|%19[^|]|%49[^|]|%29[^|]|%d\n",
	                         &rCliente.eIdCliente, rCliente.sNombre, rCliente.sTelefono,
	                         rCliente.sDireccion, rCliente.sCorreo, &rCliente.eActivo);
	                        
	        if (eLeidos == 6) {
	        	
	            aClientes[eContador] = rCliente;
	            eContador++;
	            
	        } else {
	        	
	            break;
	            
	        }
    	}
    
	    fclose(pArchivo);
	
	    *eTotalClientes = eContador;

    }
    
} //CargarClientes

/* ******
* Procedimiento: ConsultarCliente
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Mostrar los datos de un cliente específico a partir de su ID.
* Parámetros: Arreglo de clientes (aClientes), total de clientes (eTotal)
****** */
void ConsultarCliente(TaClientes aClientes, int eTotal) {
	
	//Variables
    int eId, ePos;

    Pantalla4();
    Centrar("Consultar cliente", 2);

    if (eTotal == -1) {
    	
        Centrar("No hay clientes. Pulse una tecla para regresar...", 26);
        getch();
        return;
        
    } else {

	    eId = ValidarIdCliente(aClientes, eTotal, 0);
	    
		if (eId == -1) {
	        
			return;
	        
	    } else {

		    ePos = BuscarCliente(aClientes, eTotal, eId);
		    
		    MostrarCliente(aClientes[ePos], 1);
		
			Centrar("Consulta finalizada. Pulse una tecla para regresar...", 26);
		
		} 
	}
} //ConsultarCliente

/* ******
* Procedimiento: DesactivarCliente
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Cambiar el estado de un cliente a inactivo.
* Parámetros: Arreglo de clientes (aClientes), total actual de clientes (eTotal)
****** */
void DesactivarCliente(TaClientes aClientes, int *eTotal) {
	
	//Variables
	int eId, ePos, eConfirmacion;
	char sMensaje[50];
	
    Pantalla4();
    Centrar("Desactivar cliente", 2);
		
	if (*eTotal == -1) {
	    	
	    Centrar("No hay clientes. Pulse una tecla para regresar...", 26);
	    getch();
	    return;
	
	} else {
		
		eId = ValidarIdCliente(aClientes, *eTotal, 1);
			            
		if(eId == -1){
	
			return;
				
		} else {

			ePos = BuscarCliente(aClientes, *eTotal, eId);
				
			MostrarCliente(aClientes[ePos], 0);
			
			sprintf(sMensaje, "   %cDesactivar cliente (s/n)?:", 168);
			eConfirmacion = LeerSN(20, 42, sMensaje); 

			if (eConfirmacion){
					
				aClientes[ePos].eActivo = 0;
	        	ActualizarArchivoClientes(aClientes, *eTotal);
	        	Centrar("El cliente fue desactivado correctamente. Pulse una tecla para regresar...", 26);
				
			} else {
				
				Centrar("Operacion anulada por el usuario. Pulse una tecla para regresar...", 26);

			}
		}
	}		   
} //DesactivarCliente

/* ******
* Procedimiento: InsertarCliente
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Agregar un nuevo cliente al arreglo y actualizar el archivo.
* Parámetros: Arreglo de clientes (aClientes), total actual de clientes (eTotal), cliente a insertar (rCliente)
****** */
void InsertarCliente(TaClientes aClientes, int *eTotal, TrCliente rCliente) {
    
    //Variables
    char sMensaje[50];
    
	if (*eTotal == MAX_CLIENTES - 1) {
        
		Centrar("No hay espacio para agregar un cliente. Pulse una tecla para regresar...", 26);
        return;
        
    } else if (*eTotal == -1) {
		
        *eTotal = 0;
        
    }
	
	rCliente.eIdCliente = *eTotal + 1;
	
	aClientes[*eTotal] = rCliente;
	(*eTotal)++;
	
	ActualizarArchivoClientes(aClientes, *eTotal);
	
	sprintf(sMensaje, "El cliente con ID %d se guard%c correctamente. Pulse una tecla para regresar...", rCliente.eIdCliente, 162);
	Centrar(sMensaje, 26);
    
} //InsertarCliente

/* ******
* Función: LeerCliente
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Capturar los datos de un nuevo cliente
* Retorna: Registro con los datos capturados del cliente (rCliente)
****** */
TrCliente LeerCliente() {
	
	//Variables
    TrCliente rCliente;
    
    Pantalla4();
	Centrar("Datos del cliente", 2);
	
    rCliente.eIdCliente = 0; //id temporal
    rCliente.eActivo = 1; //activo

    Mensaje(8, 13, "Nombre: ");
    LeerCadena(rCliente.sNombre, 40);

    Mensaje(10, 11, "Tel%cfono: ", 130);
    LeerCadena(rCliente.sTelefono, 20);

    Mensaje(12, 10, "Direcci%cn: ", 162);
    LeerCadena(rCliente.sDireccion, 50);

    Mensaje(14, 13, "Correo: ");
    LeerCadena(rCliente.sCorreo, 30);

    return rCliente;
    
} //LeerCliente

/******
* Procedimiento: ListarClientes
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Mostrar en pantalla la lista completa de clientes con su estado.
* Parámetros: Arreglo de clientes (aClientes), total de clientes (eTotal)
******/
void ListarClientes(TaClientes aClientes, int eTotal) {
    
    //Variables
	int eContador, eRenglon;

    Pantalla4();
    Centrar("Lista de clientes", 2);

	DibujarTabla(5, 13, 1, 3, 30);
	Mensaje(6, 28, "ID");
	Mensaje(6, 57, "NOMBRE");	
	Mensaje(6, 88, "ESTADO");
	
	eRenglon = 8;

    for (eContador = 0; eContador < eTotal; eContador++) {

        if (eRenglon > 22) {
        	
            Centrar("Pulse una tecla para continuar...", 26);
            getch();
            BorrarZona(8, 10, 15, 90);
            eRenglon = 8;
        }

        Mensaje(eRenglon, 28, "%d", aClientes[eContador].eIdCliente);
        Mensaje(eRenglon, 46, "%s", aClientes[eContador].sNombre);
        
        if (aClientes[eContador].eActivo == 1) {
        	
            Mensaje(eRenglon, 88, "ACTIVO");
            
        } else {
        	
            Mensaje(eRenglon, 88, "INACTIVO");
            
        }

        eRenglon++;
    }

    Centrar("Fin de listado. Pulse una tecla para regresar...", 26);

} //ListarClientes

/* ******
* Procedimiento: MostrarCliente
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Mostrar en pantalla los datos de un cliente.
* Parámetros: Cliente a mostrar (rCliente), indicador para mostrar estado (eEstado)
****** */
void MostrarCliente(TrCliente rCliente, int eEstado) {

	if (eEstado == 1){
		
		if (rCliente.eActivo == 1){
		
			Mensaje(10, 13, "Estado: ACTIVO");
	
		} else {
			
			Mensaje(10, 13, "Estado: INACTIVO");
		}
	
	}	
	
	Mensaje(12, 13, "Nombre: %s", rCliente.sNombre);
	Mensaje(14, 11, "Tel%cfono: %s", 130, rCliente.sTelefono);
	Mensaje(16, 10, "Direcci%cn: %s", 162, rCliente.sDireccion);
	Mensaje(18, 13, "Correo: %s", rCliente.sCorreo);
	    
} //MostrarCliente

/* ******
* Procedimiento: ModificarCliente
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Modificar los datos de un cliente existente.
* Parámetros: Arreglo de clientes (aClientes), total actual de clientes (eTotal)
****** */
void ModificarCliente(TaClientes aClientes, int eTotal) {
	
	//Variables
    int eId, ePos, eConfirmacion;
    TrCliente rNuevo;
    char sMensaje[50];

    Pantalla4();
    Centrar("Modificar datos del cliente", 2);

    if (eTotal == -1) {

        Centrar("No hay clientes. Pulse una tecla para regresar...", 26);
        getch();
        return;
    
    } else {

	    eId = ValidarIdCliente(aClientes, eTotal, 1);
	    
		if (eId == -1) {
	        
			return;
	        
	    } else {

		    ePos = BuscarCliente(aClientes, eTotal, eId);
		    
		    MostrarCliente(aClientes[ePos], 0);
			sprintf(sMensaje, "    %cModificar cliente (s/n)?:", 168);
			eConfirmacion = LeerSN(20, 42, sMensaje);

			if (eConfirmacion){
					
				rNuevo = LeerCliente();
				rNuevo.eIdCliente = eId;  // conservar ID original
			
		    	aClientes[ePos] = rNuevo;

		   		ActualizarArchivoClientes(aClientes, eTotal);
	        	
				sprintf(sMensaje, "Cliente con ID %d modificado correctamente. Pulse una tecla para regresar...", eId);
				Centrar(sMensaje, 26);
			
			} else {
				
				sprintf(sMensaje, "Operaci%cn anulada por el usuario. Pulse una tecla para regresar...", 162);
				Centrar(sMensaje, 26);
		
			} 
		}
	}
} //ModificarCliente

/******
* Funcion: ValidarIdCliente
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Solicitar un ID de cliente y validar su existencia y estado si se requiere.
* Parámetros: Arreglo de clientes (aClientes), total de clientes (eTotal), validar si está activo (eValidarActivo)
* Retorna: ID válido del cliente o -1 si se cancela (eId)
******/
int ValidarIdCliente(TaClientes aClientes, int eTotal, int eValidarActivo) {
    
    //Variables
    char sEntrada[10];
    int eId, ePos;
	char sMensaje[50];
	
    do {
    	
        BorrarZona(26, 20, 2, 80);
        BorrarZona(8, 36, 2, 15);
        
        Centrar("Pulse 'x' para regresar.", 26);
        
		Mensaje(8, 10, "Ingrese el ID del cliente: ");
        LeerCadena(sEntrada, 9);

        if (sEntrada[0] == 'x' || sEntrada[0] == 'X') {
            
            BorrarZona(26, 20, 2, 80);
            sprintf(sMensaje, "Operaci%cn anulada por el usuario. Pulse una tecla para regresar...", 162);
            Centrar(sMensaje, 26);
            return -1;
        
		} else {

	        eId = atoi(sEntrada);
	
	        if (eId <= 0) {
	        	
	            Error(6);
	            getch();
	            ePos = -1;
	            
	        } else {
	        	
	            ePos = BuscarCliente(aClientes, eTotal, eId);
	
	            if (ePos == -1) {
	            	
	                BorrarZona(26, 20, 2, 80);
	                Centrar("El ID no existe.", 26);
	                getch();
	                
	            } else if (eValidarActivo == 1 && aClientes[ePos].eActivo == 0) {
	            	
	                BorrarZona(26, 20, 2, 80);
	                sprintf(sMensaje, "El cliente con ID %d est%c inactivo.", eId, 160);
	                Centrar(sMensaje, 26);
	                getch();
	                ePos = -1;
            	
				}	
	        }
	        
	    }

    } while (ePos == -1);

    BorrarZona(26, 20, 2, 80);
    return eId; 
	  
} //ValidarIdCliente

#endif
