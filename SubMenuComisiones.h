#ifndef SUBMENU_COMISIONES_H
#define SUBMENU_COMISIONES_H

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tipos.h"
#include "NVInterfaz.h"
#include "NVFunciones.h"
#include <conio.h>

// Prototipos
void SubMenuComisiones(TaDisenadores, int *, TaDisenos, int *, TaVentas *, int);
void ReporteMensualComisiones(TaDisenadores, int, TaDisenos, int, TaVentas *, int);
void ImprimirComisionesDisenador(TaDisenadores, int, TaDisenos, int, TaVentas *, int, int, int);
void MostrarFilaComision(int, char *, float, int);

void SubMenuComisiones(TaDisenadores aDisenadores, int *eTotalDisenadores, TaDisenos aDisenos, int *eTotalDisenos, TaVentas *aVentas, int eTotalVentas)
{

    int eOpcion;

    do
    {

        system("cls");
        AjustarTamanoConsola(120, 30);
        MarcoPantalla();
        Marco(3, 5, 22, 110);

        Centrar("COMISIONES", 2);

        Mensaje(9, 49, "1. Mostrar Reporte de Comisiones");
        Mensaje(10, 49, "0. Regresar");

        Mensaje(16, 50, "Seleccione una opci%cn: ", 162);
        eOpcion = LeerEntero(16, 73, 1);
        switch (eOpcion)
        {

        case 1:
            ReporteMensualComisiones(aDisenadores, *eTotalDisenadores, aDisenos, *eTotalDisenos, aVentas, eTotalVentas);
            getch();

            break;

        case 0:
            break;

        default:
            Error(1); // Error (opci�n no v�lida)
            getch();
        }

    } while (eOpcion != 0);

} // SubMenuComisiones

void ReporteMensualComisiones(TaDisenadores aDisenadores, int eTotalDisenadores, TaDisenos aDisenos, int eTotalDisenos, TaVentas *aVentas, int eTotalVentas)
{

    char sPeriodo[15];
    char sNombreDisenador[50];
    int eMes, eAnio;
    float fTotalVentas;

    fTotalVentas = 0;

    Pantalla5();
    system("color 2F");
    Centrar("No vacancy", 1);
    Centrar("Subsistema de Comisiones", 2);
    Centrar("Reporte Mensual de Comisiones", 3);

    if (eTotalVentas == 0)
    {

        Centrar("No hay ventas. Pulse una tecla para regresar...", 26);
    }
    else
    {

        Centrar("Ingrese el mes: ", 13);
        scanf("%d", &eMes);
        //eMes = LeerEnteroEnRango(13, 68, 1, 31);

        Mensaje(15, 52, "Ingrese el a%co: ", 164);
        scanf("%d", &eAnio);
        //eAnio = LeerEnteroEnRango(15, 68, 2020, 2100);

        BorrarZona(13, 48, 4, 25);

        sprintf(sPeriodo, "Periodo: %02d/%04d", eMes, eAnio);
        Centrar(sPeriodo, 4);

        ImprimirComisionesDisenador(aDisenadores, eTotalDisenadores, aDisenos, eTotalDisenos, aVentas, eTotalVentas, eMes, eAnio);

        Centrar("Se ha completado el reporte. Pulse una tecla para regresar...", 26);
    }

    getch();
}

void ImprimirComisionesDisenador(TaDisenadores aDisenadores, int eTotalDisenadores, TaDisenos aDisenos, int eTotalDisenos, TaVentas *aVentas, int eTotalVentas, int eMes, int eAnio)
{

    int eRenglon = 6;
    float fVentasTotales;
    int eIdDisenador, i, e, f, g;
    char sNombreDisenador[50];

    BorrarZona(6, 5, 20, 110);

    Mensaje(10, 5, "ID Dise%cn", 164);
    Mensaje(10, 21, "Nombre Dise%cn", 164);
    Mensaje(10, 59, "Ventas Totales", 164);
    Mensaje(10, 90, "Comisi%cn Total", 164);
    
    for (i = 0; i <= eTotalDisenadores; i++)
    {
        fVentasTotales = 0.0f; // Reiniciar el total de ventas para cada diseñador
        for (e = 0; e <= eTotalVentas; e++)
        {

            if ((*aVentas)[e].eCancelada == 0)
            {
                

                if ((*aVentas)[e].rFechaVenta.eMes == eMes && (*aVentas)[e].rFechaVenta.eAnio == eAnio )
                    
                { 
                    // Coincide la fecha

                    for (f = 0; f <= (*aVentas)[e].eTotalProductos; f++)
                    {

                        for (g = 0; g <= eTotalDisenos; g++)
                        {

                            if (aDisenos[g].eIdDisenos == (*aVentas)[e].aProductos[f].eIdDisenio &&
                                aDisenos[g].eIdDisenador == aDisenadores[i].eIdDisenador)
                            {
                                fVentasTotales += (*aVentas)[e].fSubtotal; //((*aVentas)[e].aProductos[f].fPrecioDisenio) * (*aVentas)[e].aProductos[f].eCantidad;
                            }
                        }
                    }
                }
            }
        }
        MostrarFilaComision(aDisenadores[i].eIdDisenador, aDisenadores[i].sNombre, fVentasTotales, 15 + i);
    }
}

void MostrarFilaComision(int eIdDisenador, char *sNombreDisenador, float fVentasTotales, int eRenglon)
{

    float fComisionTotal = fVentasTotales * 0.10f; // Asumiendo una comisi�n del 10%

    Mensaje(eRenglon, 5, "%3d", eIdDisenador);        // 3 espacios para ID
    Mensaje(eRenglon, 21, "%-30s", sNombreDisenador); // Nombre alineado a la izquierda
    Mensaje(eRenglon, 59, "$%.2f", fVentasTotales);   // Números alineados a la derecha
    Mensaje(eRenglon, 90, "$%.2f", fComisionTotal);   // Lo mismo para comisión
}

#endif // SUBMENU_COMISIONES_H
