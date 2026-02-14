#ifndef NVINTERFAZ_H
#define NVINTERFAZ_H

//Bibliotecas
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdarg.h>

//Prototipos
void AjustarTamanoConsola(int, int);
void BorrarZona(int, int, int, int);
void Centrar(char * , int);
void DibujarTabla(int, int, int, int, int);
void GoToXY(int, int);
void Linea(int, int);
void Marco(int, int, int, int);
void MarcoPantalla();
void Mensaje(int, int, const char *, ...);
void Pantalla2();
void Pantalla3();
void Pantalla4();
void Pantalla5();
void PantallaNoVacancy();
void PantallaProductos();
void TablaPlataforma();


void AjustarTamanoConsola(int ancho, int alto) {
	
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT rect = {0, 0, 1, 1};
    SetConsoleWindowInfo(hConsola, TRUE, &rect);

    COORD tamBuffer;
    tamBuffer.X = ancho;
    tamBuffer.Y = alto;
    SetConsoleScreenBufferSize(hConsola, tamBuffer);

    rect.Right = ancho - 1;
    rect.Bottom = alto - 1;
    SetConsoleWindowInfo(hConsola, TRUE, &rect);

    GoToXY(0, 0);
    
}//AjustarTamanoConsola

/* ******
* Procedimiento: BorrarZona
* Autor: Zuri G
* Fecha: 15/06/2025
* Objetivo: Borrar una zona de la pantalla
* Parámetros: Renglón de inicio (eRenIni), Columna de inicio (eColIni), # filas a borrar (eFilas), # columnas a borrar (eColumnas)
******/

void BorrarZona(int eRenIni, int eColIni, int eFilas, int eColumnas) {
	
	//Variables
    int eRen, eCol;
    
    for (eRen = eRenIni; eRen < eRenIni + eFilas; eRen++) {
    	
        for (eCol = eColIni; eCol < eColIni + eColumnas; eCol++) {
        	
            GoToXY(eRen, eCol);
            
            printf(" ");
            
        }
    }
    
} //BorrarZona

void Centrar(char *sCadena , int eRenglon){
	
	int eCol;
	
    eCol = (120 - (int)strlen(sCadena)) / 2;
    
    Mensaje(eRenglon, eCol, "%s", sCadena);
    
} //Centrar

/* ******
* Procedimiento: DibujarTabla
* Autor: Zuri G
* Fecha: 14/06/2025
* Objetivo: Dibujar una tabla
* Parámetros: Renglón de inicio (eRenIni), Columna de inicio (eColIni), # renglones (eRenglones), # columnas (eColumnas), ancho de la celda (eAnchoCelda)
******/

void DibujarTabla(int eRenIni, int eColIni, int eRenglones, int eColumnas, int eAnchoCelda){
    
    //Variables
    int eRecorreRen, eRecorreCol, eContador;

    GoToXY(eRenIni, eColIni);
    
	printf("%c", 218);

    for(eRecorreCol = 0; eRecorreCol < eColumnas; eRecorreCol++){
    	
        for(eContador = 0; eContador < eAnchoCelda; eContador++){
		
			printf("%c", 196);
        
    	}
    	
        if(eRecorreCol == eColumnas - 1){
	
            printf("%c", 191);
        
        } else{
        	
            printf("%c", 194);
            
    	}
    }

    for(eRecorreRen = 0; eRecorreRen < eRenglones; eRecorreRen++){

        GoToXY(eRenIni + 1 + eRecorreRen * 2, eColIni);
        printf("%c", 179);
        
        for(eRecorreCol = 0; eRecorreCol < eColumnas; eRecorreCol++){
        	
            for(eContador = 0; eContador < eAnchoCelda; eContador++){
			
				printf(" ");
				
			}
			
            printf("%c", 179);
        }

        if(eRecorreRen < eRenglones - 1){
        	
            GoToXY(eRenIni + 2 + eRecorreRen * 2, eColIni);
            printf("%c", 195);
            
            for(eRecorreCol = 0; eRecorreCol < eColumnas; eRecorreCol++){
            	
                for(eContador = 0; eContador < eAnchoCelda; eContador++){
				
					printf("%c", 196);
				
				}
				
                if(eRecorreCol == eColumnas - 1){
			
                    printf("%c", 180);
                    
            	} else {
            		
                    printf("%c", 197);
                    
            	}
            }
        }
    }

    GoToXY(eRenIni + eRenglones * 2, eColIni);
    printf("%c", 192);
    
    for(eRecorreCol = 0; eRecorreCol < eColumnas; eRecorreCol++){
    	
        for(eContador = 0; eContador < eAnchoCelda; eContador++){
        	
			printf("%c", 196);
			
		}
        
		if(eRecorreCol == eColumnas -1){
		
            printf("%c", 217);
            
        } else {

            printf("%c", 193);
            
    	}
    }
    
} //DibujarTabla

void GoToXY(int eRen, int eCol){
	
    COORD coordenada;
    HANDLE salida = GetStdHandle(STD_OUTPUT_HANDLE);
    
    coordenada.X = eCol;
    coordenada.Y = eRen;
    
    SetConsoleCursorPosition(salida, coordenada);
    
} //GoToXY

void Linea(int eColIni, int eColFin){
	
    int eCol;
    
    for(eCol = eColIni; eCol <= eColFin; eCol++){
        
		printf("%c", 196);
    
    }
    
} //Linea

/* ******
* Procedimiento: Marco
* Autor: infosauridos
* Fecha: 12/06/2025
* Objetivo: Dibujar un marco en la pantalla con valores personalizados
* Parámetros: Renglón de inicio (eRenIni), Columna de inicio (eColIni), Renglón de fin (eRenFin), Columna de fin (eColFin)
******/

void Marco(int eRenIni, int eColIni, int eRenFin, int eColFin){
    
    //Variables
    int eRen, col;
    
    GoToXY(eRenIni, eColIni);
    printf("%c", 218);


    for (col = eColIni + 1; col < eColFin; col++){
    	
        GoToXY(eRenIni, col);
        printf("%c", 196); 
        
    }

    GoToXY(eRenIni, eColFin);
    printf("%c", 191);
    
    for (eRen = eRenIni + 1; eRen < eRenFin; eRen++){
    	
        GoToXY(eRen, eColIni);
        printf("%c", 179);
        
        GoToXY(eRen, eColFin);
        printf("%c", 179);
        
    }
    
    GoToXY(eRenFin, eColIni);
    printf("%c", 192);

    for (col = eColIni + 1; col < eColFin; col++){
    	
        GoToXY(eRenFin, col);
        printf("%c", 196);
        
    }
    
    GoToXY(eRenFin, eColFin);
    printf("%c", 217);
    
} //Marco

void MarcoPantalla(){
	
	//Variables
    int eRen;
    
	GoToXY(1,0);
    
	printf("%c", 218);
    
    Linea(2, 119);
    
	printf("%c\n", 191);
    
	for(eRen = 2; eRen <= 29; eRen++){
        
		GoToXY(eRen, 0);
		printf("%c", 179);
        
		GoToXY(eRen, 119);
		printf("%c", 179);
    
	}
    
    GoToXY(29, 0);
    printf("%c", 192);
    
    Linea(2, 119);
    
    printf("%c\n", 217);
    
} //MarcoPantalla

/* ******
* Procedimiento: Mensaje
* Autor: Infosauridos
* Fecha: 12/06/2025
* Objetivo: Mostrar un mensaje con formato (utilizando vprintf y número variables de argumentos)
* Parámetros: Renglón (eRenglon), Columna (eColumna), una cadena de formato, parámetros variables 
******/

void Mensaje(int eRenglon, int eColumna, const char *pFormato, ...){
	
    GoToXY(eRenglon, eColumna);
    va_list args;
    va_start(args, pFormato);
    vprintf(pFormato, args);
    va_end(args);
    
} //Mensaje

/* ******
* Procedimientos: Pantalla2, Pantalla3, Pantalla4, Pantalla5, PantallaNoVacancy
* Autor: Infosauridos
* Fecha: 17/06/2025
* Objetivo: Mostrar diferentes pantallas con diseño específico mediante marcos y colores.
******/

void Pantalla2(){
	
	system("cls");
	system("color 3F");
    MarcoPantalla();
    Marco(2, 1, 24, 118);
    
} //Pantalla2

void Pantalla3() {
	
    system("cls");
    system("color 3F");
    MarcoPantalla();
    Marco(3, 1, 24, 118);
    
} //Pantalla3

void Pantalla4() {
	
	system("cls");
	system("color 3F");
    MarcoPantalla();
    Marco(4, 1, 24, 118);
    
} //Pantalla4

void Pantalla5(){
	
	system("cls");
	system("color 3F");
    MarcoPantalla();
    Marco(5, 1, 24, 118);
    
} //Pantalla5()

void PantallaNoVacancy() {
	
    system("cls");
    system("color 0F");
    Centrar("NO VACANCY", 3);
    MarcoPantalla();
    Marco(4, 1, 24, 118);
    
} //PantallaNoVacancy


/* ******
* Procedimiento: PantallaProductos
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Mostrar la pantalla para agregar productos a la venta
******/

void PantallaProductos(){
	
	Pantalla3();
	Centrar("PRODUCTOS", 1);
	DibujarTabla(8, 3, 1, 6, 18);  
	Mensaje(9, 12, "#");
	Mensaje(9, 28, "Cantidad: ");
	Mensaje(9, 44, "Precio Dise%co", 164);
	Mensaje(9, 63, "Precio Insumo");
	Mensaje(9, 83, "Precio Total");
	Mensaje(9, 104, "Importe");
	
} //PantallaProductos

/* ******
* Procedimiento: TablaPlataforma
* Autor: Zuri G
* Fecha: 17/06/2025
* Objetivo: Dibujar la tabla para los reportes mensuales
* Parámetros: n/a
******/

void TablaPlataforma(){
	
	DibujarTabla(8, 12, 1, 5, 18);

    Mensaje(9, 17, "ID Venta");
    Mensaje(9, 39, "Fecha");
    Mensaje(9, 55, "ID Cliente");
    Mensaje(9, 74, "Cancelada");
    Mensaje(9, 96, "Total");
    
} //TablaPlataforma

#endif
