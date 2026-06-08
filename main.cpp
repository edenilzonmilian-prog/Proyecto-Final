#include <iostream>
#include "producto.h"
#include "venta.h"
#include "reportes.h"

using namespace std;

int main()
{
    cout << "====================================\n";
    cout << "Sistema de Ventas e Inventario\n";
    cout << "Estudiante: Hans Douglas Edenilzon Alvar\n";
    cout << "====================================\n";

    int opcion;

    do
    {
        cout << "\nMENU PRINCIPAL";
        cout << "\n1. Gestion de Productos";
        cout << "\n2. Ventas";
        cout << "\n3. Reportes";
        cout << "\n0. Salir";

        cout << "\nOpcion: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1:
                menuProductos();
                break;
            case 2:
                crearVenta();
                break;
            case 3:
                menuReportes();
                break;
        }

    }while(opcion != 0);

    return 0;
}
