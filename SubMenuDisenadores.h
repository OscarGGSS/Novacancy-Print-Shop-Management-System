#ifndef SUBMENUDISENADORES_H
#define SUBMENUDISENADORES_H

//Bibliotecas
#include <stdio.h>
#include <string.h>
#include "NVInterfaz.h"
#include "Tipos.h"

//Prototipos 
void SubMenuDisenadores(TaDisenadores, int *);
void InsertarDisenador(TaDisenadores, int *, TrDisenador);
void BorrarDisenador(TaDisenadores, int *, int);
int BuscarDisenador(TaDisenadores, int, int);
void ConsultarDisenador(TaDisenadores, int, int);
void ModificarDisenador(TaDisenadores, int, int, TrDisenador);
TrDisenador LeerDisenador(int);
void GuardarDisenadoresEnArchivo(TaDisenadores, int);
void LeerDisenadoresDesdeArchivo(TaDisenadores, int *);

void SubMenuDisenadores(TaDisenadores aDisenadores, int *eTotal) {
    int eOpcion, eIdDisenador;
    TrDisenador rDisenador;

    do {
    	
    	// Limpia la pantalla y redibuja marco
        system("cls");
        AjustarTamanoConsola(120, 30);
        MarcoPantalla();
        Marco(3, 5, 22, 110);
        
        Mensaje(4, 10, "Programa de dise%cadores", 164);
        Mensaje(5, 10, "1. Agregar Dise%cador.", 164);
        Mensaje(6, 10, "2. Borrar Dise%cador.", 164);
        Mensaje(7, 10, "3. Modificar datos de Dise%cador.", 164);
        Mensaje(8, 10, "4. Mostrar Dise%cador.", 164);
        Mensaje(9, 10, "0. Salir");
        Mensaje(20, 10, "Recuerda que para guardar debes salir.");
        Mensaje(10, 10, "Elija una opci%cn: ", 162);
        scanf("%d", &eOpcion);
        
   

        switch (eOpcion) {
            case 1:
            	system("cls");
		        AjustarTamanoConsola(120, 30);
		        MarcoPantalla();
		        Marco(3, 5, 22, 110);
                system("cls");
                rDisenador = LeerDisenador(1);
                InsertarDisenador(aDisenadores, eTotal, rDisenador);
                break;

            case 2:
            	system("cls");
		        AjustarTamanoConsola(120, 30);
		        MarcoPantalla();
		        Marco(3, 5, 22, 110);
                Mensaje(20, 10, "Ingrese el id a borrar: ");
                scanf("%d", &eIdDisenador);
                BorrarDisenador(aDisenadores, eTotal, eIdDisenador);
                break;

            case 3:
            	system("cls");
		        AjustarTamanoConsola(120, 30);
		        MarcoPantalla();
		        Marco(3, 5, 22, 110);
                Mensaje(10, 10, "Ingrese el id a modificar: ");
                scanf("%d", &eIdDisenador);
                rDisenador = LeerDisenador(0);
                ModificarDisenador(aDisenadores, *eTotal, eIdDisenador, rDisenador);
                break;

            case 4:
                system("cls");
                AjustarTamanoConsola(120, 30);
                MarcoPantalla();
                Marco(3, 5, 22, 110);
                Mensaje(10, 10, "Ingrese el ID para consultar: ");
                scanf("%d", &eIdDisenador);
                ConsultarDisenador(aDisenadores, *eTotal, eIdDisenador);
                break;

            case 0:
                GuardarDisenadoresEnArchivo(aDisenadores, *eTotal);
                printf("Adi%cs\n", 162);
                break;

            default:
                printf("Opci%cn no v%clida\n", 162, 160);
        }

        fflush(stdin);
        getchar();

    } while (eOpcion != 0);
}


void InsertarDisenador(TaDisenadores aDisenadores, int *eTotal, TrDisenador rDisenador){
    int ePos, eRecorre;

    if (*eTotal == MAX - 1){
        Mensaje(20, 10, "No hay espacio en el arreglo");
    } 
    else if (*eTotal == -1 || rDisenador.eIdDisenador > aDisenadores[*eTotal].eIdDisenador){
        (*eTotal)++;
        aDisenadores[*eTotal] = rDisenador;

        Mensaje(21, 10, "Dise%cador con ID %d agregado correctamente.", 164, rDisenador.eIdDisenador);
    } 
    else {
        ePos = BuscarDisenador(aDisenadores, *eTotal, rDisenador.eIdDisenador);

        if (ePos != -1){
            Mensaje(20, 10, "El dise%cador: %d ya existe", 164, rDisenador.eIdDisenador);
        } 
        else {
            eRecorre = *eTotal;

            while (eRecorre >= 0 && rDisenador.eIdDisenador < aDisenadores[eRecorre].eIdDisenador){
                aDisenadores[eRecorre + 1] = aDisenadores[eRecorre];
                eRecorre--;
            }

            aDisenadores[eRecorre + 1] = rDisenador;
            (*eTotal)++;

            Mensaje(10, 10, "Dise%cador con ID %d agregado correctamente.  Presiona enter para continuar.", 164, rDisenador.eIdDisenador);
        }
    }
}


void BorrarDisenador(TaDisenadores aDisenadores, int *eTotal, int eIdDisenador){
	
	//Variables 
	
	int ePos, eRecorre;
	
	//Marco
	AjustarTamanoConsola(120, 30);
    MarcoPantalla();
    Marco(3, 5, 22, 110);
    
	
	if (*eTotal == -1){
		
		Mensaje(20, 10, "El arreglo est%c vac%co", 160, 161);
		
	} else {
		
		ePos = BuscarDisenador(aDisenadores, *eTotal, eIdDisenador);
		
		if (ePos == -1){
		
			Mensaje(20, 10, "El dise%cador: %d no existe", 164,  eIdDisenador);
		
		} else {
		
			for (eRecorre = ePos; eRecorre <= *eTotal -1; eRecorre ++){
			
				aDisenadores[eRecorre] = aDisenadores[eRecorre + 1];
				
			}
		
			(*eTotal)--;
			
			Mensaje(10, 10, "Dise%cador con ID %d borrado correctamente.  Presiona enter para continuar.", 164, eIdDisenador);
			
		}
		
	}
	
}

int BuscarDisenador (TaDisenadores aDisenadores, int eTotal, int eIdDisenador){
	
	//Varaibles 
	
	int eMenor, eMayor, eMedio;
	
	if (eTotal == -1){
		
		return -1;
		
	} else {
		
		eMenor = 0;
		eMayor = eTotal;
		eMedio = eTotal / 2; 
		
	
		while (eMayor >= eMenor && eIdDisenador != aDisenadores[eMedio].eIdDisenador){
	 	
	 		if (eIdDisenador < aDisenadores[eMedio].eIdDisenador){
	 			
	 			eMayor = eMedio - 1;
	 		
			} else {
		 	
			 	eMenor = eMedio + 1;
		 	
			}
		 
		 	eMedio = (eMenor + eMayor) / 2;
	 	
		} 
	 
	 	if (eMayor < eMenor){
	 	
	 		return -1;
	 	
	 	} else {
	 	
	 		return eMedio;
	 	
	 	}
	 	
	}
	
} //BuscarDise�ador

void ConsultarDisenador(TaDisenadores aDisenadores, int eTotal, int eIdDisenador){
	
	//Variables 
	int ePos;
	
	
	AjustarTamanoConsola(120, 30);
    MarcoPantalla();
    Marco(3, 5, 22, 110);
	
	if (eTotal == -1){
		
		printf("No existe el id: %d");
		
	} else{
	 	
		ePos = BuscarDisenador(aDisenadores, eTotal, eIdDisenador);
	
		if(ePos == -1){
			
			printf("No existe el ID: %d", ePos);
			
			return;
			
		}else{
			
			
			Mensaje(7, 10, "ID: %d", aDisenadores[ePos].eIdDisenador);
			Mensaje(8, 10, "Nombre: %s", aDisenadores[ePos].sNombre);
			Mensaje(9, 10, "Domicilio: Calle: %s", aDisenadores[ePos].rDomicilio.sCalle);
			Mensaje(10, 10, "Nucmero exterior: %s", aDisenadores[ePos].rDomicilio.sNoExterior);
			Mensaje(11, 10, "Nucmero inteior: %s", aDisenadores[ePos].rDomicilio.sNoInterior);
			Mensaje(12, 10, "Colonia: %s", aDisenadores[ePos].rDomicilio.sColonia);
			Mensaje(13, 10, "Codigo postal: %s", aDisenadores[ePos].rDomicilio.sCP);
			Mensaje(14, 10, "Delegacion: %s", aDisenadores[ePos].rDomicilio.sDelegacion);
			Mensaje(15, 10, "Telefono: %s", aDisenadores[ePos].sTelefono);
			Mensaje(16, 10, "Fecha de nacimiento: %02d/%02d/%04d",
            aDisenadores[ePos].rFechaNac.eDia,
            aDisenadores[ePos].rFechaNac.eMes,
            aDisenadores[ePos].rFechaNac.eAnio);
			
		}
		
		
	}
	
	
	
}

void ModificarDisenador(TaDisenadores aDisenadores, int eTotal, int eIdDisenador, TrDisenador rDisenadorNuevo){
    int ePos = BuscarDisenador(aDisenadores, eTotal, eIdDisenador);

    if (ePos != -1){
        BorrarDisenador(aDisenadores, &eTotal, eIdDisenador);
        rDisenadorNuevo.eIdDisenador = eIdDisenador;
        InsertarDisenador(aDisenadores, &eTotal, rDisenadorNuevo);
        // Quita el mensaje y pausa aqu?
    } else {
        Mensaje(20, 10, "El dise%cador con ID %d no existe.", 164, eIdDisenador);

    }
}


TrDisenador LeerDisenador(int leeId){
	
	//Variables 
	TrDisenador rDisenador;
	int eCalif;
	
	AjustarTamanoConsola(120, 30);
    MarcoPantalla();
    Marco(3, 5, 22, 110);
	
	Mensaje(4, 10,"Ingrese los siguientes datos del Dise%cador: ", 164);
	
	if (leeId){
		
		Mensaje(5, 10, "Id: ");
		scanf("%d", &rDisenador.eIdDisenador);
	}
	
	Mensaje(6, 10, "Ingrese el nombre: ");
	fflush(stdin);
	gets(rDisenador.sNombre);

	Mensaje(7, 10, "Ingrese el domicilio: ");
	Mensaje(8, 10, "Calle: ");
	fflush(stdin);
	gets(rDisenador.rDomicilio.sCalle);
	
	Mensaje(9, 10, "No. Exterior:");
	fflush(stdin);
	gets(rDisenador.rDomicilio.sNoExterior);
	
	Mensaje(10, 10, "No. Interior: ");
	fflush(stdin);
	gets (rDisenador.rDomicilio.sNoInterior);
	
	Mensaje(11, 10, "Colonia: ");
	fflush(stdin);
	gets(rDisenador.rDomicilio.sColonia);
	
	Mensaje(12, 10, "C%cdigo Postal: ", 162);
	fflush(stdin);
	gets(rDisenador.rDomicilio.sCP);
	
	Mensaje(13, 10, "Delegaci%cn: ", 162);
	fflush(stdin);
	gets(rDisenador.rDomicilio.sDelegacion);
	
	Mensaje(14, 10, "Tel%cfono: ", 130);
	fflush(stdin);
	gets (rDisenador.sTelefono);
	
	Mensaje(15, 10, "Fecha de nacimiento: ");
	
	Mensaje(16, 10, "D%ca: ", 161);
	scanf ("%d", &rDisenador.rFechaNac.eDia);
	
	Mensaje(17, 10, "Mes: ");
	scanf ("%d", &rDisenador.rFechaNac.eMes);
	
	Mensaje(18, 10, "A%co: ", 164);
	scanf ("%d", &rDisenador.rFechaNac.eAnio);
	
	system("cls");
	
	AjustarTamanoConsola(120, 30);
    MarcoPantalla();
    Marco(3, 5, 22, 110);
    
	
	return rDisenador;
	
	
	
}

void GuardarDisenadoresEnArchivo(TaDisenadores aDisenadores, int eTotal) {
    FILE *archivo = fopen("Disenadores.txt", "w");
    
    int i;

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para guardar.\n");
        return;
    }

    for (i = 0; i <= eTotal; i++) {
        fprintf(archivo,
            "ID: %d\nNombre: %s\nTelefono: %s\n"
            "Calle: %s\nNo. Exterior: %s\nNo. Interior: %s\nColonia: %s\nCP: %s\nDelegacion: %s\n"
            "Fecha Nac: %02d/%02d/%04d\n\n",
            aDisenadores[i].eIdDisenador, aDisenadores[i].sNombre, aDisenadores[i].sTelefono,
            aDisenadores[i].rDomicilio.sCalle, aDisenadores[i].rDomicilio.sNoExterior,
            aDisenadores[i].rDomicilio.sNoInterior, aDisenadores[i].rDomicilio.sColonia,
            aDisenadores[i].rDomicilio.sCP, aDisenadores[i].rDomicilio.sDelegacion,
            aDisenadores[i].rFechaNac.eDia, aDisenadores[i].rFechaNac.eMes,
            aDisenadores[i].rFechaNac.eAnio
        );
    }

    fclose(archivo);
    Centrar("Datos guardados correctamente ", 4);
}

void LeerDisenadoresDesdeArchivo(TaDisenadores aDisenadores, int *eTotal) {
    FILE *archivo = fopen("Disenadores.txt", "r");
    TrDisenador r;
    *eTotal = -1;

    if (archivo == NULL) return;

    while (fscanf(archivo, 
            "ID: %d\nNombre: %[^\n]\nTelefono: %[^\n]\n"
            "Calle: %[^\n]\nNo. Exterior: %[^\n]\nNo. Interior: %[^\n]\nColonia: %[^\n]\nCP: %[^\n]\nDelegacion: %[^\n]\n"
            "Fecha Nac: %d/%d/%d\n\n",
            &r.eIdDisenador, r.sNombre, r.sTelefono,
            r.rDomicilio.sCalle, r.rDomicilio.sNoExterior, r.rDomicilio.sNoInterior,
            r.rDomicilio.sColonia, r.rDomicilio.sCP, r.rDomicilio.sDelegacion,
            &r.rFechaNac.eDia, &r.rFechaNac.eMes, &r.rFechaNac.eAnio
        ) == 12) {
        (*eTotal)++;
        aDisenadores[*eTotal] = r;
    }

    fclose(archivo);
}

#endif
