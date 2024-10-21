#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// ALGORITMO DE ORDENAMIENTO RELACIONADO A QUICKSORT

// Convierte los meses obtenidos en texto a números
int obtenerMes(const std::string &mes)
{
    if (mes == "Jan")
        return 1;
    if (mes == "Feb")
        return 2;
    if (mes == "Mar")
        return 3;
    if (mes == "Apr")
        return 4;
    if (mes == "May")
        return 5;
    if (mes == "Jun")
        return 6;
    if (mes == "Jul")
        return 7;
    if (mes == "Aug")
        return 8;
    if (mes == "Sep")
        return 9;
    if (mes == "Oct")
        return 10;
    if (mes == "Nov")
        return 11;
    if (mes == "Dec")
        return 12;
    return 0; // Si no encuentra el mes
}

// Se crea la función compararFechas para ordenar las líneas del archivo por fecha de mes y día
bool compararFechas(const std::string &linea1, const std::string &linea2)
{
    std::string mes1 = linea1.substr(0, 3); // Sustrae los primeros 3 caracteres de cada línea, que son el mes.
    std::string mes2 = linea2.substr(0, 3);
    int dia1 = std::stoi(linea1.substr(4, 2)); // Sustrae los caracteres 4 y 5 que son el día.
    int dia2 = std::stoi(linea2.substr(4, 2));

    if (obtenerMes(mes1) != obtenerMes(mes2))
        return obtenerMes(mes1) < obtenerMes(mes2);
    else
        return dia1 < dia2;
}

// Función para convertir una fecha en formato "MMM DD" a un número para comparar fácilmente
int convertirFecha(const std::string &linea)
{
    std::string mes = linea.substr(0, 3);    // Sustrae los primeros tres caracteres que son el mes.
    int dia = std::stoi(linea.substr(4, 2)); // Convierte los caracteres 4 y 5 en el día.
    return obtenerMes(mes) * 100 + dia;      // Formato MMDD para comparar fácilmente.
}

int main()
{
    // Se crea un vector para almacenar los datos del archivo "bitacora.txt"
    std::vector<std::string> datos;

    // Se abre el archivo "bitacora.txt"
    std::ifstream archivo("bitacora.txt");

    // Comprobación de si el archivo está abierto correctamente
    if (!archivo.is_open())
    {
        std::cout << "No se pudo abrir el archivo correctamente." << std::endl;
        return 1;
    }

    // Se lee línea por línea el archivo y se almacenan los datos en el vector
    std::string linea;
    while (std::getline(archivo, linea))
    {
        datos.push_back(linea);
    }
    archivo.close(); // Se cierra el archivo

    // Se ordenan los datos por fecha usando la función compararFechas
    std::sort(datos.begin(), datos.end(), compararFechas);

    // Crear un archivo de salida para almacenar los datos ordenados
    std::ofstream archivoSalida("bitacora_ordenada.txt");
    if (!archivoSalida.is_open())
    {
        std::cout << "No se pudo crear el archivo de salida." << std::endl;
        return 1;
    }

    // Escribir todos los registros ordenados en el archivo de salida
    for (const auto &registro : datos)
    {
        archivoSalida << registro << std::endl;
    }
    archivoSalida.close();

    // Solicita al usuario las fechas de inicio y fin de búsqueda
    std::string fechaInicio, fechaFin;
    std::cout << "Ingrese la fecha de inicio (formato MMM DD): ";
    std::getline(std::cin, fechaInicio);
    std::cout << "Ingrese la fecha de fin (formato MMM DD): ";
    std::getline(std::cin, fechaFin);

    // Convierte las fechas ingresadas por el usuario al formato MMDD
    int fechaInicioNum = convertirFecha(fechaInicio);
    int fechaFinNum = convertirFecha(fechaFin);

    // Despliega los registros que están dentro del rango de fechas ingresadas por el usuario
    bool registrosEncontrados = false;
    for (const auto &registro : datos)
    {
        int fechaRegistro = convertirFecha(registro);
        if (fechaRegistro >= fechaInicioNum && fechaRegistro <= fechaFinNum)
        {
            std::cout << registro << std::endl; // Imprime los registros en pantalla
            registrosEncontrados = true;
        }
    }

    if (!registrosEncontrados)
    {
        std::cout << "No se encontraron registros en el rango de fechas proporcionado." << std::endl;
    }

    std::cout << "Registros ordenados y almacenados en 'bitacora_ordenada.txt'." << std::endl;

    return 0;
}
