#ifndef NVFUNCIONES_H
#define NVFUNCIONES_H

//Bibliotecas
#include <stdio.h>
#include <windows.h>
#include "NVInterfaz.h"
#include <conio.h>
#include "Tipos.h"
#include <string.h>

//Prototipos
void Error(int);
int LeerEntero(int, int, int);
int ValidarEntero(char *);
int ValidarBisiesto(int);
int DiasDelMes(int, int);
TrFecha LeerFecha(int, int);
int LeerEnteroEnRango(int, int, int, int);
char LeerCaracter(int, int);
int LeerSN(int, int, char *);
void LeerCadena(char *, int);


/* *********
   Procedimiento: Error
   Autor: Oscar
   Fecha:
   Objetivo:
   Compilador: Dev-C++ 5.11
   Version 1.0
********* */
void Error(int eCodigoError) {
	
	//Variables
    char cMensaje[100];

    switch (eCodigoError) {
        
		case 1: sprintf(cMensaje, "Error. Opci%cn no v%clida. Pulse una tecla para continuar ...", 162, 160);
				break;
            
        case 2: sprintf(cMensaje, "Error al guardar ventas en archivo.");
				break;
            
        case 3: sprintf(cMensaje, "Cambiar");
				break;
            
        case 4: sprintf(cMensaje, "Error. El ID no es v%clido. Pulse una tecla para continuar...", 160);
            	break;
        
		case 5: sprintf(cMensaje, "Cambiar", 162);
				break;
				
        case 6: sprintf(cMensaje, "Error. Entrada no v%clida.", 160);
				break;
            
        case 7: sprintf(cMensaje, "Error. El d%ca no es v%clido.", 161, 160);
				break;
            
        case 8: sprintf(cMensaje, "Error. El mes no es v%clido.", 160); 
          		break;
            
        case 9: sprintf(cMensaje, "Error. El a%co no es v%clido.", 164, 160); 
            	break;
            	
        case 10: sprintf(cMensaje, "Error. El d%ca no es v%clido para esta fecha.", 161, 160); 
            	 break;
            
        case 11: sprintf(cMensaje, "Error. El insumo no existe.");
            	 break;
            	 
        case 12: sprintf(cMensaje, "Error. El dise%co no existe.", 164);
            	 break;
            	 
        case 13: sprintf(cMensaje, "Error. S%clo se permite 's' y 'n'.", 162);
            	 break;
            	 
        case 14: sprintf(cMensaje, "Error.");
            	 break;
            	 
        case 15: sprintf(cMensaje, "Error. La fecha inicial debe ser < o = a la final.");
            	 break;
            	 
        case 16: sprintf(cMensaje, " ");
            	 break;
				     	
        default:
            sprintf(cMensaje, "Error desconocido.");
            break;
    }

    Centrar(cMensaje, 26);
    Beep(1000, 300);
    
} //Error

/* ******
* Función: LeerEntero
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Leer un entero
* Parámetros: Renglón (erenglon), columna (eColumna), el código de error (eError)
* Retorna: 1 cuando se lea con éxito
******/

int LeerEntero(int eRenglon, int eColumna, int eError) {
	
	//Variables
    int eValor;
    char cFin;

    while (1) {
    	
        if (scanf("%d%c", &eValor, &cFin) == 2 && cFin == '\n') {
        	
            return eValor;
            
        } else {

	        Error(eError);
	        fflush(stdin);
	        getch();
			BorrarZona(26, 20, 2, 80);
	        BorrarZona(eRenglon, eColumna, 1, 30);
	        GoToXY(eRenglon, eColumna);
	    
	    }
        
    }
    
} //LeerEntero

int ValidarEntero(char *cTexto) {
    
	int eContador;
	
	eContador = 0;
    
	if (cTexto[0] == '-'){
		
		eContador = 1;
		
	} else {

    	for (; cTexto[eContador] != '\0'; eContador++) {
    	
        	if (!isdigit(cTexto[eContador])) {
        	
            	return 0;

        	}
    	}
    
	}

    return (eContador > 0);
    
} //ValidarEntero

/* ******
* Función: ValidarBisiesto
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Verificar si un año es o no bisiesto
* Parámetros: Año (eAnio)
* Retorna: 1 si es bisiesto, 0 si no lo es
******/

int ValidarBisiesto(int eAnio) {
    
	if (eAnio % 4 == 0 && eAnio % 100 != 0) {
        
		return 1;
    
	}

    if (eAnio % 400 == 0) {
        
		return 1;
    
	}

    return 0;
    
} //ValidarBisiesto


/* ******
* Función: DiasDelMes
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Indica cuantos dias tiene un mes (tomando en cuenta años bisiestos)
* Parámetros: Año (eAnio), mes (eMes)
* Retorna: La cantidad de días que tiene el mes (eDia)
******/

int DiasDelMes(int eMes, int eAnio) {
    
    //Variables
    int eDias;

    if (eMes == 1 || eMes == 3 || eMes == 5 || eMes == 7 || eMes == 8 || eMes == 10 || eMes == 12) {
        
        eDias = 31;

    } else if (eMes == 4 || eMes == 6 || eMes == 9 || eMes == 11) {
        
        eDias = 30;

    } else if (eMes == 2) {
        
        if (ValidarBisiesto(eAnio) == 1) {
           
		    eDias = 29;
        
		} else {
            
			eDias = 28;
			
        }

    } else {
        
        eDias = 0;

    }

    return eDias;
    
} //DiasDelMes

/* ******
* Función: LeerFecha
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Lee y valida que una fecha sea correcta
* Parámetros: Renglon (eRen), columna (eCol) para escribir
* Retorna: Fecha valida (TrFecha)
******/

TrFecha LeerFecha(int eRen, int eCol) {
	
	//Variables	
    TrFecha rFecha;
    int eDiasMax;

    do {

		BorrarZona(eRen, eCol + 5, 1, 15);
        BorrarZona(26, 20, 1, 80);
        
		Mensaje(eRen, eCol, "D%ca: ", 161);
		GoToXY(eRen, eCol + 5);
		
		if (scanf("%d", &rFecha.eDia) != 1) { //que no quede vacío o se ingrese algo q no sea entero
            
			Error(6); //Error (entrada no válida)
			getch();
            fflush(stdin);
			rFecha.eDia = 0;
            continue;
            
        }

        if (rFecha.eDia < 1 || rFecha.eDia > 31) {  // validación día entre 1-31
            
            Error(7);
            getch();
            
        }
        
    } while (rFecha.eDia < 1 || rFecha.eDia > 31);

    do {
    	    
		BorrarZona(eRen + 1, eCol + 5, 1, 15);
        BorrarZona(26, 20, 1, 80);
        
		Mensaje(eRen + 1, eCol, "Mes:");
		GoToXY(eRen + 1, eCol + 5);
		
        if (scanf("%d", &rFecha.eMes) != 1) {
        	
            Error(6);  //Error (entrada no válida)
            getch();
            fflush(stdin);
            rFecha.eMes = 0;
            continue;
            
        }

        if (rFecha.eMes < 1 || rFecha.eMes > 12) { // validación mes entre 1-12
            
			BorrarZona(26, 20, 1, 80);
			Error(8);
			getch();
			
        }
        
    } while (rFecha.eMes < 1 || rFecha.eMes > 12);

    do {
    	
    	BorrarZona(eRen + 2, eCol + 5, 1, 15);
        BorrarZona(26, 20, 1, 80);
        
		Mensaje(eRen + 2, eCol, "A%co:", 164);
		GoToXY(eRen + 2, eCol + 5);
        
        if (scanf("%d", &rFecha.eAnio) != 1) {
        	
            Error(6);
            fflush(stdin);
            getch();
            rFecha.eAnio = 0;
            continue;
            
        }

        if (rFecha.eAnio < 2020 || rFecha.eAnio > 2100) {
        	
            Error(9);
            getch();
            
        }
        
    } while (rFecha.eAnio < 2020 || rFecha.eAnio > 2100);

    eDiasMax = DiasDelMes(rFecha.eMes, rFecha.eAnio);
    
    if (rFecha.eDia > eDiasMax) {
    	
    	Error(10);
    	getch();
        
        do {
        	
            BorrarZona(eRen, eCol + 5, 1, 15);
        	BorrarZona(26, 20, 1, 80);

			GoToXY(eRen, eCol + 5);
            
            if (scanf("%d", &rFecha.eDia) != 1) {
            	
                Error(6);
                getch();
                fflush(stdin);
                rFecha.eDia = 0;
                continue;
                
            }

            if (rFecha.eDia < 1 || rFecha.eDia > eDiasMax) {
            	
                Error(7);
                getch();
                
            }
            
        } while (rFecha.eDia < 1 || rFecha.eDia > eDiasMax);
    }

    return rFecha;
    
} //LeerFecha

/* ******
* Función: LeerEnteroEnRango
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Lee y valida que un entero este en un rango
* Parámetros: Renglon (eRen), columna (eCol), límite inferior y superior del rango (eMin, eMax)
* Retorna: El valor en el rango (eValor)
******/
int LeerEnteroEnRango(int eRen, int eCol, int eMin, int eMax){
	
	//Variables
    int eValor;
    
    do {
    	
		BorrarZona(26, 20, 1, 80);
    	BorrarZona(eRen, eCol, 1, 20);
    	
    	GoToXY(eRen, eCol);
        eValor = LeerEntero(eRen, eCol, 6);
        
        if (eValor < eMin || eValor > eMax) {
        	
            Error(6);
            getch();
            
        }
        
    } while (eValor < eMin || eValor > eMax);
    
    return eValor;
    
} //LeerEnteroEnRango

/* ******
* Función: LeerCaracter
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Lee y valida un caracter cualquiera
* Parámetros: Renglon (eRen), columna (eCol)
* Retorna: El caracter (cCaracter)
******/
char LeerCaracter(int eRenglon, int eColumna) {
	
	//Variables
    char cCaracter, cFin;

    while (1) {
        
        BorrarZona(eRenglon, eColumna, 1, 43);
        
        GoToXY(eRenglon, eColumna);

        if (scanf(" %c%c", &cCaracter, &cFin) == 2 && cFin == '\n') {
            
			return cCaracter;
			
        } else {

	        Error(14);
	        fflush(stdin);
	        getch();
	        BorrarZona(26, 57, 1, 6);
    	
		}	
	}
	
} //LeerCaracter

/* ******
* Función: LeerSN
* Autor: Zuri G
* Fecha: 16/06/2025
* Objetivo: Lee y valida que un caracter sea 's', 'S', 'n' o 'N'
* Parámetros: Renglon (eRen), columna (eCol), mensaje (sMensaje)
* Retorna: 1 si es 's' o 'S' y 0 si es 'n' o 'N'
******/

int LeerSN(int eRen, int eCol, char *sMensaje) {
	
	//Variables
    char cRespuesta;
    
    while (1) {
        
        Mensaje(eRen, eCol, sMensaje);
        
        cRespuesta = LeerCaracter(eRen, eCol + 31);
        
        if (cRespuesta == 'S' || cRespuesta == 's') {
        	
            return 1;
            
        } else if (cRespuesta == 'N' || cRespuesta == 'n') {
        	
            return 0;
            
        } else {

            Error(13);
            getch();  
            BorrarZona(26, 43, 1, 33);
           
        }
    }
    
} //LeerSN

void LeerCadena(char *sCadena, int eLongitudMax) {

    fgets(sCadena, eLongitudMax, stdin);
    
	size_t len = strlen(sCadena);
    
	if(len > 0 && sCadena[len-1] == '\n') {
        
		sCadena[len-1] = '\0';
    }
    
} //LeerCadena

#endif
