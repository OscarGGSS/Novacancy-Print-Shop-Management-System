#ifndef SUBMENUDISENOS_H
#define SUBMENUDISENOS_H

//Bibliotecas
#include <stdio.h>
#include <string.h>
#include "NVInterfaz.h"
#include "Tipos.h"

//Prototipos 
void SubMenuDisenos(TaDisenos, int *);
void InsertarDiseno(TaDisenos, int *, TrDiseno);
void BorrarDiseno(TaDisenos, int *, int);
int BuscarDiseno(TaDisenos, int, int);
void ConsultarDiseno(TaDisenos aDisenos, int eTotal, int eIdDisenos);
void ModificarDiseno(TaDisenos, int, int, TrDiseno);
TrDiseno LeerDiseno(int);
void GuardarDisenosEnArchivo(TaDisenos, int);
void LeerDisenosDesdeArchivo(TaDisenos, int *);

void SubMenuDisenos(TaDisenos aDisenos, int *eTotal) {
    
	int eOpcion, eIdDisenos;
    TrDiseno rDiseno;

    do {
    	
    	// Limpia la pantalla y redibuja marco
        system("cls");
        AjustarTamanoConsola(120, 30);
        MarcoPantalla();
        Marco(3, 5, 22, 110);
        
        Mensaje(4, 10, "Programa de dise%co", 164);
        Mensaje(5, 10, "1. Agregar Dise%co.", 164);
        Mensaje(6, 10, "2. Borrar Dise%co.", 164);
        Mensaje(7, 10, "3. Modificar datos de Dise%co.", 164);
        Mensaje(8, 10, "4. Mostrar Dise%co.", 164);
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
                rDiseno = LeerDiseno(1);
                InsertarDiseno(aDisenos, eTotal, rDiseno);
                break;

            case 2:
            	system("cls");
		        AjustarTamanoConsola(120, 30);
		        MarcoPantalla();
		        Marco(3, 5, 22, 110);
                Mensaje(15, 10, "Ingrese el id a borrar: ");
                scanf("%d", &eIdDisenos);
                BorrarDiseno(aDisenos, eTotal, eIdDisenos);
                break;

            case 3:
            	system("cls");
		        AjustarTamanoConsola(120, 30);
		        MarcoPantalla();
		        Marco(3, 5, 22, 110);
                Mensaje(10, 10, "Ingrese el id a modificar: ");
                scanf("%d", &eIdDisenos);
                rDiseno = LeerDiseno(0);
                ModificarDiseno(aDisenos, *eTotal, eIdDisenos, rDiseno);
                
                
                break;

            case 4:
                system("cls");
                AjustarTamanoConsola(120, 30);
                MarcoPantalla();
                Marco(3, 5, 22, 110);
                Mensaje(10, 10, "Ingrese el ID para consultar: ");
                scanf("%d", &eIdDisenos);
                ConsultarDiseno(aDisenos, *eTotal, eIdDisenos);
                break;

            case 0:
                GuardarDisenosEnArchivo(aDisenos, *eTotal);
                printf("Adi%cs\n", 162);
                break;

            default:
                printf("Opci%cn no v%clida\n", 162, 160);
        }

        fflush(stdin);
        getchar();

    } while (eOpcion != 0);
}


void InsertarDiseno(TaDisenos aDisenos, int *eTotal, TrDiseno rDiseno){
    int ePos, eRecorre;

    if (*eTotal == MAX - 1){
        Mensaje(20, 10, "No hay espacio en el arreglo");
    } 
    else if (*eTotal == -1 || rDiseno.eIdDisenos > aDisenos[*eTotal].eIdDisenos){
        (*eTotal)++;
        aDisenos[*eTotal] = rDiseno;

        Mensaje(21, 10, "Dise%co con ID %d agregado correctamente.", 164, rDiseno.eIdDisenos);
    } 
    else {
        ePos = BuscarDiseno(aDisenos, *eTotal, rDiseno.eIdDisenos);

        if (ePos != -1){
            Mensaje(20, 10, "El dise%co: %d ya existe", 164, rDiseno.eIdDisenos);
        } 
        else {
            eRecorre = *eTotal;

            while (eRecorre >= 0 && rDiseno.eIdDisenos < aDisenos[eRecorre].eIdDisenos){
                aDisenos[eRecorre + 1] = aDisenos[eRecorre];
                eRecorre--;
            }

            aDisenos[eRecorre + 1] = rDiseno;
            (*eTotal)++;

            Mensaje(10, 10, "Dise%co con ID %d agregado correctamente.  Presiona enter para continuar.", 164, rDiseno.eIdDisenos);
        }
    }
}


void BorrarDiseno(TaDisenos aDisenos, int *eTotal, int eIdDisenos){
	
	//Variables 
	
	int ePos, eRecorre;
	
	//Marco
	AjustarTamanoConsola(120, 30);
    MarcoPantalla();
    Marco(3, 5, 22, 110);
    
	
	if (*eTotal == -1){
		
		Mensaje(20, 10, "El arreglo est%c vac%co", 160, 161);
		
	} else {
		
		ePos = BuscarDiseno(aDisenos, *eTotal, eIdDisenos);
		
		if (ePos == -1){
		
			Mensaje(20, 10, "El dise%co: %d no existe", 164,  eIdDisenos);
		
		} else {
		
			for (eRecorre = ePos; eRecorre <= *eTotal -1; eRecorre ++){
			
				aDisenos[eRecorre] = aDisenos[eRecorre + 1];
				
			}
		
			(*eTotal)--;
			
			Mensaje(10, 10, "Dise%co con ID %d borrado correctamente.  Presiona enter para continuar.", 164, eIdDisenos);
			
		}
		
	}
	
}

int BuscarDiseno (TaDisenos aDisenos, int eTotal, int eIdDisenos){
	
	//Varaibles 
	
	int eMenor, eMayor, eMedio;
	
	if (eTotal == -1){
		
		return -1;
		
	} else {
		
		eMenor = 0;
		eMayor = eTotal;
		eMedio = eTotal / 2; 
		
	
		while (eMayor >= eMenor && eIdDisenos != aDisenos[eMedio].eIdDisenos){
	 	
	 		if (eIdDisenos < aDisenos[eMedio].eIdDisenos){
	 			
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

void ConsultarDiseno(TaDisenos aDisenos, int eTotal, int eIdDisenos){
	
	//Variables 
	int ePos;
	
	

	
	if (eTotal == -1){
		
		printf("No existe el id: %d");
		
	} else{
	 	
		ePos = BuscarDiseno(aDisenos, eTotal, eIdDisenos);
	
		if(ePos == -1){
			
			printf("No existe el ID: %d", ePos);
			
			return;
			
		}else{
			
			
			Mensaje(7, 10, "ID: %d", aDisenos[ePos].eIdDisenos);
			Mensaje(8, 10, "Nombre: %s", aDisenos[ePos].sNombre);
			Mensaje(9, 10, "Precio: $%d", aDisenos[ePos].ePrecio);
            Mensaje(10, 10, "ID del Dise%cador: %d", 164, aDisenos[ePos].eIdDisenador);

			
		}
		
		
	}
	
	
	
}

void ModificarDiseno(TaDisenos aDisenos, int eTotal, int eIdDisenos, TrDiseno rDisenadorNuevo){
    int ePos = BuscarDiseno(aDisenos, eTotal, eIdDisenos);
    

    if (ePos != -1){
        BorrarDiseno(aDisenos, &eTotal, eIdDisenos);
        rDisenadorNuevo.eIdDisenos = eIdDisenos;
        InsertarDiseno(aDisenos, &eTotal, rDisenadorNuevo);
        // Quita el mensaje y pausa aqu?
    } else {
        Mensaje(10, 10, "El dise%cador con ID %d no existe.", 164, eIdDisenos);

    }
}


TrDiseno LeerDiseno(int leeIdDisenos){
	
	//Variables 
	TrDiseno rDiseno;
	int eCalif;
	
	AjustarTamanoConsola(120, 30);
    MarcoPantalla();
    Marco(3, 5, 22, 110);
	
	Mensaje(4, 10,"Ingrese los siguientes datos del Dise%cador: ", 164);
	
	if (leeIdDisenos){
		
		Mensaje(5, 10, "Id: ");
		scanf("%d", &rDiseno.eIdDisenos);
	}
	
	Mensaje(6, 10, "Ingrese el nombre: ");
	fflush(stdin);
	gets(rDiseno.sNombre);

	Mensaje(7, 10, "Ingrese el precio del dise%co: $", 164);
	scanf("%d", &rDiseno.ePrecio);

    Mensaje(8, 10, "Ingrese el ID del Dise%cador: ", 164);
	scanf("%d", &rDiseno.eIdDisenador);
	
	return rDiseno;
	
	
	
}

void GuardarDisenosEnArchivo(TaDisenos aDisenos, int eTotal) {
    int i;
    FILE *archivo = fopen("Disenos.txt", "w");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para guardar.\n");
        return;
    }

    for (i = 0; i <= eTotal; i++) {
        fprintf(archivo, "%d|%s|%d|%d\n",
            aDisenos[i].eIdDisenos,
            aDisenos[i].sNombre,
            aDisenos[i].ePrecio,
            aDisenos[i].eIdDisenador);
    }

    fclose(archivo);
    Centrar("Datos guardados correctamente ", 4);
}



void LeerDisenosDesdeArchivo(TaDisenos aDisenos, int *eTotal) {
    FILE *archivo = fopen("Disenos.txt", "r");
    TrDiseno r;
    *eTotal = -1;

    if (archivo == NULL) return;

    while (fscanf(archivo, "%d|%[^|]|%d|%d\n", &r.eIdDisenos, r.sNombre, &r.ePrecio, &r.eIdDisenador) == 4) {
        (*eTotal)++;
        aDisenos[*eTotal] = r;
    }

    fclose(archivo);
}


#endif
