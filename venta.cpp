#include "venta.h"
#include "producto.h"

double calcularIVA(double subtotal)
{
    return subtotal * 0.12;
}

double calcularDescuento(
    double subtotal,
    int cantidadTotal)
{
    double descuento = 0;

    if(subtotal > 500)
    {
        descuento += subtotal * 0.05;
    }

    if(cantidadTotal % 5 == 0)
    {
        descuento += 25;
    }

    return descuento;
}

void crearVenta()
{
    Venta venta;

    venta.subtotal = 0;
    venta.iva = 0;
    venta.descuento = 0;
    venta.total = 0;

    int cantidadArticulos = 0;

    cout << "\n===== NUEVA VENTA =====\n";

    cout << "Numero venta: ";
    cin >> venta.numeroVenta;

    cout << "Mes (1-12): ";
    cin >> venta.mes;

    cout << "Cantidad de productos: ";
    cin >> venta.cantidadProductos;

    if(venta.cantidadProductos > 20)
    {
        cout << "\nMaximo permitido: 20 productos\n";
        return;
    }

    for(int i = 0; i < venta.cantidadProductos; i++)
    {
        int codigo;
        int cantidad;

        cout << "\nProducto #" << i + 1 << endl;

        cout << "Codigo: ";
        cin >> codigo;

        Producto p = buscarProducto(codigo);

        if(p.codigo == -1)
        {
            cout << "Producto no encontrado.\n";
            i--;
            continue;
        }

        cout << "Nombre: "
             << p.nombre << endl;

        cout << "Precio: Q"
             << p.precio << endl;

        cout << "Stock disponible: "
             << p.stock << endl;

        cout << "Cantidad: ";
        cin >> cantidad;

        if(cantidad > p.stock)
        {
            cout << "Stock insuficiente.\n";
            i--;
            continue;
        }

        venta.detalles[i].codigoProducto =
            codigo;

        venta.detalles[i].cantidad =
            cantidad;

        venta.detalles[i].precioUnitario =
            p.precio;

        venta.detalles[i].subtotal =
            cantidad * p.precio;

        venta.subtotal +=
            venta.detalles[i].subtotal;

        cantidadArticulos += cantidad;

        actualizarVentaProducto(
            codigo,
            cantidad
        );
    }

    venta.iva =
        calcularIVA(
            venta.subtotal
        );

    venta.descuento =
        calcularDescuento(
            venta.subtotal,
            cantidadArticulos
        );

    venta.total =
        venta.subtotal +
        venta.iva -
        venta.descuento;

    venta.total =
        round(
            venta.total * 100
        ) / 100;

    cout << "\n====================";

    cout << "\nSubtotal: Q"
         << venta.subtotal;

    cout << "\nIVA: Q"
         << venta.iva;

    cout << "\nDescuento: Q"
         << venta.descuento;

    cout << "\nTOTAL: Q"
         << venta.total;

    cout << "\n====================";

    ofstream archivo(
        "ventas.dat",
        ios::binary | ios::app
    );

    archivo.write(
        (char*)&venta,
        sizeof(Venta)
    );

    archivo.close();

    cout << "\nVenta guardada correctamente.\n";
}
