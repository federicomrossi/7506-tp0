#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;



/* *******************************************************************
 * 						FUNCIONES AUXILIARES
 * *******************************************************************/

 bool texto_esta_en_linea(string oracion, string texto)
{
	int i, j=0;

	for(i=0; oracion[i]; i++)
	{
		if(oracion[i] == texto [j])
		{ 
			if (!texto[++j] && 
				(!oracion[i+1] || oracion[i+1] == ' ')) 
				return true;
		}
		else
			j = 0;
	}

	return false;
}


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

	// Método que envía a la salida estandar las lineas contenidas
	// en el archivo de texto.
	static void leer(char* NOMBRE_ARCHIVO)
	{
		ifstream entrada(NOMBRE_ARCHIVO);

		// Verificamos si existe el archivo
		if(!entrada.is_open())
		{
			PError::archivo_abrir();
			return;
		}

		// Enviamos lineas a la salida estandar
		string linea;

		while(entrada.good())
		{
			getline(entrada,linea);
			cout << linea << endl;
		}

		entrada.close();
	}

	// Método que busca el TEXTO en el archivo con ruta NOMBRE_ARCHIVO
	// y envía las líneas que lo contienen a la salida estandar.
	static void buscar(char* NOMBRE_ARCHIVO, char* TEXTO)
	{
		ifstream entrada(NOMBRE_ARCHIVO);

		// Verificamos si existe el archivo
		if(!entrada.is_open())
		{
			PError::archivo_abrir();
			return;
		}

		// Buscamos e imprimimos las líneas que contienen al TEXTO.
		string linea;

		while(entrada.good())
		{
			getline(entrada,linea);
			
			if(texto_esta_en_linea(linea, TEXTO))
				cout << linea << endl;
		}

		entrada.close();
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

	if (!argv[2] || argv[2][2] || argv[2][0] != '-')
	{
		PError::parametros();
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

		// Muestra por pantalla las líneas de texto contenidas en el archivo
		// de text con ruta [NOMBRE_ARCHIVO].
		case 'l':	Archivo::leer(argv[1]);
					break;

		// Busca el [TEXTO] en cada línea del archivo de texto con ruta
		// [NOMBRE_ARCHIVO] y envía a la salida estandar las que la contienen.
		case 's':	if(!argv[3]) 
					{
						PError::parametros();
						break;
					}
					Archivo::buscar(argv[1], argv[3]);
					break;
		
		// Elimina el archivo con ruta [NOMBRE_ARCHIVO].
		case 'e':	Archivo::eliminar(argv[1]);
					break;

		// Caso por defecto
		default: PError::parametros();
				 break;
	}

	return 0;

}