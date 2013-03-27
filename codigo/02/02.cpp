#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib> // para usar atoi()
#include <sstream>

using namespace std;

static const char* separadorRegistro = ",";



/* *******************************************************************
 * 							FUNCIONES AUXILIARES
 * *******************************************************************/





/* *******************************************************************
 * 									CLASES
 * *******************************************************************/


class PError
{
public:

	// Imprime mensaje de error relacionado al ingreso inválido de parámetros
	static void parametros()
	{
		cout << "PError-01: Los parámetros ingresados no son válidos" << endl;
	}

	// Imprime mensaje de error para error al crear archivo.
	static void archivo_crear()
	{
		cout << "PError-02: Ha ocurrido un error al intentar crear el archivo."
			 << endl;
	}

	// Imprime mensaje de error para archivos que no se han podido abrir.
	static void archivo_abrir()
	{
		cout << "PError-03: No se ha podido abrir el archivo especificado." 
			 << endl;
	}
};



class Archivo
{
public:
	
	// Método que crea un archivo de registros variables
	static void crear(char* NOMBRE_ARCHIVO)
	{
		ofstream salida(NOMBRE_ARCHIVO, ios::binary);

		if(salida.good())
		{
			cout << "Se ha creado el archivo exitosamente." << endl;
			salida.close();
		}
		else
			PError::archivo_crear();
	}

	// Método que dado un archivo, inserta un nuevo registro variable.
	static void agregarRegistro(char* NOMBRE_ARCHIVO, char* TEXTO)
	{
		// Verificamos si existe el archivo
		ifstream entrada(NOMBRE_ARCHIVO);
		
		if(!entrada.is_open())
		{
			PError::archivo_abrir();
			return;
		}
		entrada.close();

		// Si existe, insertamos texto en línea
		ofstream salida(NOMBRE_ARCHIVO, ios::out | ios::binary | ios::app);

		if(salida.is_open())
		{
			// Tomamos la longitud del TEXTO y lo convertimos en tipo almacenable
			ifstream::pos_type longitudTEXTO = 
				(ifstream::pos_type) strlen(TEXTO);
			stringstream s_longitudTEXTO;
			s_longitudTEXTO << longitudTEXTO;

			// Almacenamos el registro en archivo
			salida.write(s_longitudTEXTO.str().c_str(), 
				(ifstream::pos_type) sizeof(s_longitudTEXTO.str().c_str()));
			salida.write(separadorRegistro, 
				(ifstream::pos_type) sizeof(separadorRegistro));
			salida.write(TEXTO, (ifstream::pos_type) longitudTEXTO);
		}

		salida.close();

		cout << "Se ha agregado el registro en el archivo exitosamente." 
			 << endl;
	}

	// Método que envía a la salida estandar las lineas contenidas
	// en el archivo de texto.
	static void leerRegistros(char* NOMBRE_ARCHIVO)
	{
		// ifstream entrada(NOMBRE_ARCHIVO);

		// // Verificamos si existe el archivo
		// if(!entrada.is_open())
		// {
		// 	PError::archivo_abrir();
		// 	return;
		// }

		// // Enviamos lineas a la salida estandar
		// string linea;

		// while(entrada.good())
		// {
		// 	getline(entrada,linea);
		// 	cout << linea << endl;
		// }

		// entrada.close();

		ifstream entradan(NOMBRE_ARCHIVO, ios::in | ios::binary);

		char* v1 = new char[4];
		char* v2 = new char[4];
		
		entradan.read(v1, 4);
		entradan.read(v2, 4);
		char* v3 = new char[atoi(v1)];
		entradan.read(v3, atoi(v1));

		cout << "v1: " << atoi(v1) << endl;
		cout << "v2: " << v2 << endl;
		cout << "v3: " << v3 << endl;


		entradan.close();
		delete[] v1;
		delete[] v2;
		delete[] v3;
	}

	// Método que elimina el archivo con ruta NOMBRE_ARCHIVO.
	static void eliminar(char* NOMBRE_ARCHIVO)
	{
		remove(NOMBRE_ARCHIVO);
		cout << "Se ha eliminado el archivo " << NOMBRE_ARCHIVO << endl;
	}
};



/* *******************************************************************
 * 							PROGRAMA PRINCIPAL
 * *******************************************************************/


int main(int argc, char *argv[]) {

	// Comprobamos que halla especificación de parametro de acción
	if (!argv[2])
	{
		PError::parametros();
		return 0;
	}

	// Crea el archivo de texto en la ruta [NOMBRE_ARCHIVO].
	else if(!strcmp(argv[2], "-c"))
		Archivo::crear(argv[1]);

	else if(!strcmp(argv[2], "-rt"))
		Archivo::agregarRegistro(argv[1], argv[3]);

	// Elimina el archivo con ruta [NOMBRE_ARCHIVO]
	else if(!strcmp(argv[2], "-e"))
		Archivo::eliminar(argv[1]);
	
	// Caso por defecto
	else
		PError::parametros();

	return 0;
}