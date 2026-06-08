#include "reportes.h"
#include "producto.h"

void productosMenorStock()
{
    Producto p;

    ifstream archivo(
        "productos.dat",
        ios::binary
    );

    cout << "\n=== PRODUCTOS CON STOCK BAJO ===\n";

    while(
        archivo.read(
        (char*)&p,
        sizeof(Producto))
    )
    {
        if(
            p.activo &&
            p.stock <= 10
        )
        {
            cout << "\nCodigo: "
                 << p.codigo;

            cout << "\nNombre: "
                 << p.nombre;

            cout << "\nStock: "
                 << p.stock;

            cout << "\n----------------";
        }
    }

    archivo.close();
}

void productosMasVendidos()
{
    Producto p;

    ifstream archivo(
        "productos.dat",
        ios::binary
    );

    cout << "\n=== PRODUCTOS MAS VENDIDOS ===\n";

    while(
        archivo.read(
        (char*)&p,
        sizeof(Producto))
    )
    {
        if(p.activo)
        {
            cout << "\nCodigo: "
                 << p.codigo;

            cout << "\nNombre: "
                 << p.nombre;

            cout << "\nVendidos: "
                 << p.vendidos;

            cout << "\n----------------";
        }
    }

    archivo.close();
}

void ordenarPrecioAsc()
{
    Producto productos[100];

    int n = 0;

    Producto p;

    ifstream archivo(
        "productos.dat",
        ios::binary
    );

    while(
        archivo.read(
        (char*)&p,
        sizeof(Producto))
    )
    {
        if(p.activo)
        {
            productos[n] = p;
            n++;
        }
    }

    archivo.close();

    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(
                productos[j].precio >
                productos[j+1].precio
            )
            {
                Producto aux =
                    productos[j];

                productos[j] =
                    productos[j+1];

                productos[j+1] =
                    aux;
            }
        }
    }

    cout << "\n=== ORDENADOS POR PRECIO ===\n";

    for(int i=0;i<n;i++)
    {
        cout << productos[i].nombre
             << " - Q"
             << productos[i].precio
             << endl;
    }
}

void ordenarStockAsc()
{
    Producto productos[100];

    int n = 0;

    Producto p;

    ifstream archivo(
        "productos.dat",
        ios::binary
    );

    while(
        archivo.read(
        (char*)&p,
        sizeof(Producto))
    )
    {
        if(p.activo)
        {
            productos[n] = p;
            n++;
        }
    }

    archivo.close();

    for(int i=0;i<n-1;i++)
    {
        int menor = i;

        for(int j=i+1;j<n;j++)
        {
            if(
                productos[j].stock <
                productos[menor].stock
            )
            {
                menor = j;
            }
        }

        Producto aux =
            productos[i];

        productos[i] =
            productos[menor];

        productos[menor] =
            aux;
    }

    cout << "\n=== ORDENADOS POR STOCK ===\n";

    for(int i=0;i<n;i++)
    {
        cout << productos[i].nombre
             << " - "
             << productos[i].stock
             << endl;
    }
}

void menuReportes()
{
    int opcion;

    do
    {
        cout << "\n=== REPORTES ===";

        cout << "\n1. Menor stock";
        cout << "\n2. Mas vendidos";
        cout << "\n3. Ordenar precio";
        cout << "\n4. Ordenar stock";
        cout << "\n0. Regresar";

        cout << "\nOpcion: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1:
                productosMenorStock();
                break;

            case 2:
                productosMasVendidos();
                break;

            case 3:
                ordenarPrecioAsc();
                break;

            case 4:
                ordenarStockAsc();
                break;
        }

    }while(opcion != 0);
}
