#ifndef TIPOS_H
#define TIPOS_H

//Constantes
#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_VENTAS 100
#define IVA 0.16f
#define MAX_CADENA 50
#define MAX 50
#define MAX_NOMBRE 50
#define MAX_DESCRIPCION 255
#define MAX_CATEGORIA 30
#define MAX_INSUMOS 100

//Tipos
typedef struct rFecha {
	
    int eDia;
    int eMes;
    int eAnio;
    
} TrFecha; //TrFecha

typedef enum ePlataformas {
	
    MERCADOLIBRE,
    SHOPIFY,
    INSTAGRAM
    
} TePlataformas; //TePlataformas

typedef struct rProducto {
	
	int eIdProducto;
    int eIdInsumo;
    int eIdDisenio;
    int eCantidad;
    float fPrecioDisenio;
    float fPrecioInsumo;
    float fPrecio;
    
} TrProducto; //TrProducto

typedef TrProducto TaProductos[MAX_PRODUCTOS];

typedef struct rVenta {
	
    int eIdVenta;
    int eIdCliente;
    TePlataformas ePlataforma;
    TrFecha rFechaVenta;
    int eTotalProductos;
    TaProductos aProductos;
    float fSubtotal;
    float fIva;
    float fTotal;
    int eCancelada;
    TrFecha rFechaCancelacion;
    char sMotivoCancelacion[130];
    
} TrVenta; //TrVenta

typedef TrVenta TaVentas[MAX_VENTAS];

typedef struct rCliente {
	
	int eIdCliente;
	char sNombre [40];
	char sTelefono[20];
	char sDireccion[50];
	char sCorreo[30];
	int eActivo;
	
} TrCliente;

typedef TrCliente TaClientes[MAX_CLIENTES];

typedef struct rDomicilio {
	
	char sCalle [40];
	char sNoExterior[4];
	char sNoInterior[4];
	char sColonia [30];
	char sCP[6];
	char sDelegacion[20];
	
} TrDomicilio; 

typedef struct rDisenador {
	
	int eIdDisenador;
	char sNombre [40];
	char sTelefono [15];
	TrDomicilio rDomicilio;
	TrFecha rFechaNac;
	
} TrDisenador;

typedef TrDisenador TaDisenadores [MAX];

typedef struct rDiseno {
	
	int eIdDisenos;
	char sNombre [40];
	int ePrecio;
    int eIdDisenador;
	
} TrDiseno;

typedef TrDiseno TaDisenos [MAX];

// Estructura para insumos
typedef struct {
    int eIdInsumo;
    char sNombreInsumo[MAX_NOMBRE];
    char sDescripcionInsumo[MAX_DESCRIPCION];
    char sCategoriaInsumo[MAX_CATEGORIA];
    int eStockInsumo;
    int eStockActual;
    int eStockMinimo;
    int eStockMaximo;
    float fPrecioInsumo;
    float fCostoInsumo;
} Insumo;

#endif
