#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Producto
{
    int codigo;
    char nombre[50];
    double precio;
    int stock;
    int vendidos;
    bool activo;
};

void menuProductos();

void registrarProducto();
void listarProductos();
void buscarProductoCodigo();
void buscarProductoNombre();

void actualizarStock();
void modificarPrecio();
void eliminarProducto();

void actualizarVentaProducto(
    int codigo,
    int cantidadVendida
);

Producto buscarProducto(int codigo);

#endif
