#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class USUARIO
{
private:
    string usuario;
    string contraseña;

public:
    USUARIO();
    ~USUARIO();

    void abrirMenu(int opcion);
    void ingresar();
    void registrar();
};

class DESTINOSVUELOS
{
private:
    string destino;

public:
    DESTINOSVUELOS();
    ~DESTINOSVUELOS();

    void buscarDestinos();
    string getDestino() { return destino; }
};

class LISTAESPERA
{
public:
    LISTAESPERA();
    ~LISTAESPERA();

    void listaespera();
};

class SELECCIONASIENTOS
{
private:
    vector<int> asientosdisp;
    string nombrecomp;

public:
    SELECCIONASIENTOS();
    ~SELECCIONASIENTOS();

    void mostrarAsientosDisponibles();
    bool seleccionarAsiento();
    string getnombrereserva() { return nombrecomp; }
    void setnombrereserva(string n_nomresv) { nombrecomp = n_nomresv; }
    void mostrarDatosReservacion();
    void cancelarReserva(int numAsiento);
};

class MENUFINAL
{
private:
    int salir;

public:
    MENUFINAL();
    ~MENUFINAL();

    void salirmenu();
    void cancelarvuelo(vector<int> &asientosdisp);
};

USUARIO::USUARIO()
{
    usuario = "sin usuario";
    contraseña = "sin contraseña";
}

USUARIO::~USUARIO() {}

void USUARIO::abrirMenu(int opcion)
{
    cout << "Bienvenido a VolandoAndo!!" << endl;
    cout << "1. Ingresar" << endl;
    cout << "2. Registrarse" << endl;
    cout << "3. Cancelar vuelo" << endl;
    cout << "Seleccione una opción: ";
    cin >> opcion;

    if (opcion == 1)
    {
        ingresar();
    }
    else if (opcion == 2)
    {
        registrar();
    }
    else if (opcion == 3)
    {
        MENUFINAL cancelar;
        vector<int> asientosdisp;
        cancelar.cancelarvuelo(asientosdisp);
    }
    else
    {
        cout << "Opción inválida. Por favor, seleccione 1 o 2." << endl;
        abrirMenu(1);
    }
}

void USUARIO::ingresar()
{
    cout << "Ingrese su usuario: ";
    cin >> usuario;

    ifstream archivo("/Users/emisanzmor/Desktop/usuarios.txt");
    string u;

    while (getline(archivo, u))
    {
        if (u == usuario)
        {
            cout << "Ingrese su contraseña: ";
            cin >> contraseña;
            string c;
            getline(archivo, c);
            if (c == contraseña)
            {
                cout << "Bienvenido, " << usuario << endl;

                DESTINOSVUELOS destino;
                destino.buscarDestinos();
                break;
            }
            else
            {
                cout << "Contraseña incorrecta. Por favor, inténtelo de nuevo." << endl;
                return;
            }
        }
    }
    if (usuario != u)
    {
        cout << "No se encontró el usuario dentro del sistema." << endl;
    }
}

void USUARIO::registrar()
{
    cout << "Ingrese un nombre de usuario nuevo: ";
    cin >> usuario;

    ifstream archivo("/Users/emisanzmor/Desktop/usuarios.txt");
    string u;
    bool usuarioexiste = false;

    while (getline(archivo, u))
    {
        if (u == usuario)
        {
            usuarioexiste = true;
            break;
        }
    }

    if (usuarioexiste)
    {
        cout << "El usuario ya existe. Por favor, elija otro nombre de usuario." << endl;
        return;
    }

    cout << "Ingrese una contraseña: ";
    cin >> contraseña;

    ofstream archivosalida("/Users/emisanzmor/Desktop/usuarios.txt");
    if (archivosalida.is_open())
    {
        archivosalida << usuario << endl;
        archivosalida << contraseña << endl;
        archivosalida.close();
        cout << "Usuario registrado exitosamente." << endl;
        abrirMenu(0);
    }
    else
    {
        cout << "Error al abrir el archivo de usuarios." << endl;
    }
}

DESTINOSVUELOS::DESTINOSVUELOS() {}

DESTINOSVUELOS::~DESTINOSVUELOS() {}

void DESTINOSVUELOS::buscarDestinos()
{
    cout << "Por favor ingrese su destino: ";
    cin >> destino;
    ifstream archivo("/Users/emisanzmor/Library/Mobile Documents/com~apple~TextEdit/Documents/destinos.txt");
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo de vuelos. Intente nuevamente." << endl;
        return;
    }

    string palabraclave = destino;
    string linea;
    bool encontrado = false;

    while (getline(archivo, linea))
    {
        if (linea.find(palabraclave) != string::npos)
        {
            LISTAESPERA lista;
            lista.listaespera();
            cout << linea << endl;
            SELECCIONASIENTOS selecciona;
            selecciona.seleccionarAsiento();
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado)
    {
        cout << "No se encontró el destino. Por favor, ingréselo nuevamente." << endl;
        buscarDestinos();
    }
}

LISTAESPERA::LISTAESPERA() {}

LISTAESPERA::~LISTAESPERA() {}

void LISTAESPERA::listaespera()
{
    cout << "Gracias por reservar con nosotros...Espere un momento" << endl;
    cout << "..." << endl;
    cout << "..." << endl;
    cout << "..." << endl;
    cout << "..." << endl;
    cout << "..." << endl;
    cout << "..." << endl;
}

SELECCIONASIENTOS::SELECCIONASIENTOS()
{
    for (int i = 1; i <= 40; ++i)
    {
        asientosdisp.push_back(i);
    }
}

SELECCIONASIENTOS::~SELECCIONASIENTOS() {}

void SELECCIONASIENTOS::mostrarAsientosDisponibles()
{
    cout << "Asientos disponibles: ";
    for (int num : asientosdisp)
    {
        cout << num << " ";
    }
    cout << endl;
}

bool SELECCIONASIENTOS::seleccionarAsiento()
{
    mostrarAsientosDisponibles();

    int seleccion;
    cout << "Ingrese el número del asiento que desea reservar: ";
    cin >> seleccion;
    cout << "Ingrese su nombre completo: ";
    cin >> nombrecomp;

    auto it = find(asientosdisp.begin(), asientosdisp.end(), seleccion);
    if (it != asientosdisp.end())
    {
        asientosdisp.erase(it);
        cout << "Asiento reservado exitosamente. Gracias por volar con VolandoAndo!!" << endl;

        mostrarDatosReservacion();
        return true;
    }
    else
    {
        cout << "El asiento seleccionado ya fue reservado. Por favor elija otro." << endl;
        return seleccionarAsiento();
    }
}

void SELECCIONASIENTOS::mostrarDatosReservacion()
{
    cout << "Estimado usuario: " << getnombrereserva() << ", su reservación ha sido completada exitosamente. Se le enviará vía correo electrónico su voucher para viajar." << endl;

    MENUFINAL menu;
    menu.salirmenu();
}

void SELECCIONASIENTOS::cancelarReserva(int numAsiento)
{
    auto it = find(asientosdisp.begin(), asientosdisp.end(), numAsiento);
    if (it != asientosdisp.end())
    {
        asientosdisp.erase(it);
        cout << "Cancelación exitosa, asiento liberado" << endl;
    }
    else
    {
        cout << "El asiento ingresado no está reservado." << endl;
    }
}

MENUFINAL::MENUFINAL() {}

MENUFINAL::~MENUFINAL() {}

void MENUFINAL::salirmenu()
{
    cout << "¿Desea salir del sitio?" << endl;
    cout << "1. SI" << endl;
    cout << "2. NO" << endl;
    cin >> salir;

    if (salir == 1)
    {
        cout << "Saliendo del sitio..." << endl;
    }
    else if (salir == 2)
    {
        USUARIO abrir;
        abrir.abrirMenu(0);
    }
    else
    {
        cout << "Opción inválida." << endl;
    }
}

void MENUFINAL::cancelarvuelo(vector<int> &asientosdisp)
{
    cout << "¿De verdad desea cancelar su vuelo?" << endl;
    cout << "1. SI" << endl;
    cout << "2. NO" << endl;
    cin >> salir;
    if (salir == 1)
    {
        cout << "Cancelando sus boletos. Espere un segundo..." << endl;
        int asientocancel;
        cout << "Ingrese el número del asiento que desea cancelar: ";
        cin >> asientocancel;

        SELECCIONASIENTOS selecciona;
        selecciona.cancelarReserva(asientocancel);
    }
    else if (salir == 2)
    {
        USUARIO abrir;
        abrir.abrirMenu(0);
    }
    else
    {
        cout << "Opción inválida." << endl;
    }
}

int main()
{
    USUARIO usuario;
    usuario.abrirMenu(0);

    return 0;
}
