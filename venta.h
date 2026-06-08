#ifndef VENTA_H
#define VENTA_H

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct DetalleVenta
{
    int codigoProducto;
    int cantidad;
    double precioUnitario;
    double subtotal;
};

struct Venta
{
    int numeroVenta;
    
    int mes;

    int cantidadProductos;

    DetalleVenta detalles[20];

    double subtotal;
    double iva;
    double descuento;
    double total;
};

double calcularIVA(double subtotal);

double calcularDescuento(
    double subtotal,
    int cantidadTotal
);

void crearVenta();

#endif
