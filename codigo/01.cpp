#include <iostream>
#include <fstream>

using namespace std;

class PError
{
public:

	static void parametros()
	{
		cout << "Los parámetros ingresados no son válidos" << endl;
	}
};

class Archivo
{
public:
	
	// Método que crea un archivo
	static void crear(char* NOMBRE_ARCHIVO)
	{
		ofstream salida(NOMBRE_ARCHIVO);

		if(salida.good())
		{
			cout << "Se ha creado el archivo exitosamente." << endl;
			salida.close();
		}
		else
			cout << "Ha ocurrido un error al intentar crear el archivo." << endl;
	}

	// Método que dado un archivo, inserta una linea de texto.
	static void insertarLinea(char* NOMBRE_ARCHIVO, char* TEXTO)
	{
		ofstream salida(NOMBRE_ARCHIVO, ios::in | ios::trunc);
		if(!salida.good())
		{
			cout << "No se ha podido abrir el archivo especificado." << endl;
			return;
		}

		salida << TEXTO << endl;
	}
};



int main(int argc, char *argv[]) {

	if (!argv[2] || argv[2][2])
	{
		cout << "Los parámetros ingresados son válidos" << endl;
		return 0;
	}

	switch(argv[2][1])
	{
		// Crea el archivo de texto en la ruta [NOMBRE_ARCHIVO].
		case 'c':	Archivo::crear(argv[1]);	
					break;

		// Registra el [TEXTO] en una línea del archivo de texto con ruta
		// [NOMBRE_ARCHIVO].
		case 'r':	if(!argv[3]) 
					{
						PError::parametros();
						break;
					}

					Archivo::insertarLinea(argv[1], argv[3]);
					break;

		// case "-l":
		// 			break;
		// case "-s":
		// 			break;
		
		// case "-e":
		// 			break;

		default: PError::parametros();
				 break;
	}

	return 0;

}