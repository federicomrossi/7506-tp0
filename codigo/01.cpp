#include <iostream>
#include <fstream>

using namespace std;



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
			PError::archivo_crear();
	}

	// Método que dado un archivo, inserta una linea de texto.
	static void insertarLinea(char* NOMBRE_ARCHIVO, char* TEXTO)
	{
		// Verificamos si existe el archivo
		ifstream entrada(NOMBRE_ARCHIVO);
		
		if(!entrada.is_open())
		{
			PError::archivo_abrir();
			return;
		}
		entrada.close();

		// Si existe, insertamos texto en linea
		ofstream salida(NOMBRE_ARCHIVO, ios::app);
		salida << TEXTO << endl;
		salida.close();
		cout << "Se ha registrado el texto en el archivo exitosamente." 
			 << endl;
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