#include "producto.h"

void registrarProducto()
{
    Producto p;

    cout << "\n--- REGISTRAR PRODUCTO ---\n";

    cout << "Codigo: ";
    cin >> p.codigo;

    cin.ignore();

    cout << "Nombre: ";
    cin.getline(p.nombre,50);

    try
{
    cout << "Precio: ";
    cin >> p.precio;

    if(cin.fail() || p.precio < 0)
    {
        throw "Precio invalido";
    }
}
catch(const char* mensaje)
{
    cout << mensaje << endl;

    cin.clear();
    cin.ignore(1000,'\n');

    return;
}

    try
{
    cout << "Stock: ";
    cin >> p.stock;

    if(cin.fail() || p.stock < 0)
    {
        throw "Stock invalido";
    }
}
catch(const char* mensaje)
{
    cout << mensaje << endl;

    cin.clear();
    cin.ignore(1000,'\n');

    return;
}

    p.vendidos = 0;
    p.activo = true;

    ofstream archivo("productos.dat",
                     ios::binary | ios::app);

    archivo.write(
        (char*)&p,
        sizeof(Producto)
    );

    archivo.close();

    cout << "\nProducto guardado correctamente.\n";
}

void listarProductos()
{
    Producto p;

    ifstream archivo(
        "productos.dat",
        ios::binary
    );

    if(!archivo)
    {
        cout << "\nNo existen productos.\n";
        return;
    }

    cout << "\n===== LISTA DE PRODUCTOS =====\n";

    while(
        archivo.read(
        (char*)&p,
        sizeof(Producto))
    )
    {
        if(p.activo)
        {
            cout << "\nCodigo: " << p.codigo;
            cout << "\nNombre: " << p.nombre;
            cout << "\nPrecio: Q" << p.precio;
            cout << "\nStock: " << p.stock;
            cout << "\nVendidos: " << p.vendidos;
            cout << "\n-------------------";
        }
    }

    archivo.close();
}

void buscarProductoCodigo()
{
    int codigoBuscado;

    cout << "\nCodigo a buscar: ";
    cin >> codigoBuscado;

    Producto p;
    bool encontrado = false;

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
        if(p.codigo == codigoBuscado
           && p.activo)
        {
            encontrado = true;

            cout << "\nProducto encontrado\n";

            cout << "Codigo: "
                 << p.codigo << endl;

            cout << "Nombre: "
                 << p.nombre << endl;

            cout << "Precio: Q"
                 << p.precio << endl;

            cout << "Stock: "
                 << p.stock << endl;

            break;
        }
    }

    archivo.close();

    if(!encontrado)
    {
        cout << "\nProducto no encontrado.\n";
    }
}

void buscarProductoNombre()
{
    char nombreBuscado[50];

    cin.ignore();

    cout << "\nNombre a buscar: ";
    cin.getline(nombreBuscado,50);

    Producto p;

    bool encontrado = false;

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
        if(strcmp(
            p.nombre,
            nombreBuscado) == 0
            && p.activo)
        {
            encontrado = true;

            cout << "\nProducto encontrado\n";

            cout << "Codigo: "
                 << p.codigo << endl;

            cout << "Nombre: "
                 << p.nombre << endl;

            cout << "Precio: Q"
                 << p.precio << endl;

            cout << "Stock: "
                 << p.stock << endl;

            break;
        }
    }

    archivo.close();

    if(!encontrado)
    {
        cout << "\nProducto no encontrado.\n";
    }
}
void menuProductos()
{
    int opcion;

    do
    {
        cout << "\n========================";
        cout << "\n MODULO PRODUCTOS";
        cout << "\n========================";

        cout << "\n1. Registrar";
        cout << "\n2. Listar";
        cout << "\n3. Buscar por codigo";
        cout << "\n4. Buscar por nombre";       
        cout << "\n5. Actualizar stock";
        cout << "\n6. Modificar precio";
        cout << "\n7. Eliminar producto";
        cout << "\n0. Regresar";

        cout << "\nOpcion: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1:
                registrarProducto();
                break;

            case 2:
                listarProductos();
                break;

            case 3:
                buscarProductoCodigo();
                break;

            case 4:
                buscarProductoNombre();
                break;
                
            case 5:
			    actualizarStock();
                break;

            case 6:
                modificarPrecio();
                break;

            case 7:
                eliminarProducto();
                break;
        }

    }while(opcion != 0);
}

void actualizarStock()
{
    int codigo;
    int nuevoStock;

    cout << "\nCodigo del producto: ";
    cin >> codigo;

    cout << "Nuevo stock: ";
    cin >> nuevoStock;

    fstream archivo(
        "productos.dat",
        ios::binary | ios::in | ios::out
    );

    Producto p;

    while(
        archivo.read(
            (char*)&p,
            sizeof(Producto))
    )
    {
        if(p.codigo == codigo && p.activo)
        {
            p.stock = nuevoStock;

            archivo.seekp(
                -sizeof(Producto),
                ios::cur
            );

            archivo.write(
                (char*)&p,
                sizeof(Producto)
            );

            cout << "\nStock actualizado.\n";

            archivo.close();
            return;
        }
    }

    cout << "\nProducto no encontrado.\n";

    archivo.close();
}

void modificarPrecio()
{
    int codigo;
    double nuevoPrecio;

    cout << "\nCodigo del producto: ";
    cin >> codigo;

    cout << "Nuevo precio: ";
    cin >> nuevoPrecio;

    fstream archivo(
        "productos.dat",
        ios::binary | ios::in | ios::out
    );

    Producto p;

    while(
        archivo.read(
            (char*)&p,
            sizeof(Producto))
    )
    {
        if(p.codigo == codigo && p.activo)
        {
            p.precio = nuevoPrecio;

            archivo.seekp(
                -sizeof(Producto),
                ios::cur
            );

            archivo.write(
                (char*)&p,
                sizeof(Producto)
            );

            cout << "\nPrecio actualizado.\n";

            archivo.close();
            return;
        }
    }

    cout << "\nProducto no encontrado.\n";

    archivo.close();
}


void eliminarProducto()
{
    int codigo;

    cout << "\nCodigo a eliminar: ";
    cin >> codigo;

    fstream archivo(
        "productos.dat",
        ios::binary | ios::in | ios::out
    );

    Producto p;

    while(
        archivo.read(
            (char*)&p,
            sizeof(Producto))
    )
    {
        if(p.codigo == codigo && p.activo)
        {
            p.activo = false;

            archivo.seekp(
                -sizeof(Producto),
                ios::cur
            );

            archivo.write(
                (char*)&p,
                sizeof(Producto)
            );

            cout << "\nProducto eliminado.\n";

            archivo.close();
            return;
        }
    }

    cout << "\nProducto no encontrado.\n";

    archivo.close();
    
    
}


Producto buscarProducto(int codigo)
{
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
        if(
            p.codigo == codigo &&
            p.activo
        )
        {
            archivo.close();
            return p;
        }
    }

    archivo.close();

    p.codigo = -1;

    return p;
}

void actualizarVentaProducto(
    int codigo,
    int cantidadVendida
)
{
    fstream archivo(
        "productos.dat",
        ios::binary |
        ios::in |
        ios::out
    );

    Producto p;

    while(
        archivo.read(
            (char*)&p,
            sizeof(Producto))
    )
    {
        if(
            p.codigo == codigo
            && p.activo
        )
        {
            p.stock -= cantidadVendida;

            p.vendidos += cantidadVendida;

            archivo.seekp(
                -sizeof(Producto),
                ios::cur
            );

            archivo.write(
                (char*)&p,
                sizeof(Producto)
            );

            break;
        }
    }

    archivo.close();
}

