#include <vector>
#include <array>
#include <iostream>
#include <fstream>

using namespace std;

// cada celda de un cuerpo escaneado esta represendado por un valor "resonante" representado por una
// intensidad: un valor entero, sin signo en el intervalo [0,255]
using Celda = unsigned char;

const unsigned int SCAN_LINE_SZ = 128;
const unsigned int LINES_PER_PLANE = 128;

// define una l�nea de scan (direcci�n X)
using ScanLine = array<Celda, SCAN_LINE_SZ>;

// define un plano de scan (direcci�n X,Y)
using ScanPlane = array<ScanLine, LINES_PER_PLANE>;

// define un vol�men de scan (direcci�n X,Y,Z)
using ScanBody = vector<ScanPlane>;

class ScanAnalyzer
{
public:
	// La estructura Sensitivity define la sensibilidad a ser aplicada en el analisis de una
	// imagen escaneada. La sensibilidad esta caracterizada por 2 par�metros
	struct Sensitivity
	{
		// definen el rango de detecci�n de los puntos (ver enunciado)
		Celda minValue;
		Celda maxValue;

		// define la minima proporcion [0, 1.0] de puntos de un plano (en Z) que deben ser sospechosos para que
		// el plano sea sospechoso (0: 0%, 1.0: 100%) (ver enunciado)
		double umbral;
	};

	// analiza la imagen 'image' y retorna un vector de todos los planos (identificado por �ndice de plano)
	// que son sospechosos dado la sensibilidad dada por 'params'
	vector<unsigned int> doWork(const ScanBody &image, const Sensitivity &params)
	{
		// vector para guardar los resultados
		vector<unsigned int> result;
		// en la imagen hay image.size() planos
		for (unsigned int i = 0; i < (unsigned int)(image.size()); i++)
		{
			if (planoSospechoso(image, params, i))
				result.push_back(i);
		}
		return result;
	}

private:
	/*Detección de un “punto sospechoso”: dado la imagen del cuerpo y un punto a través de su coordenada x, y, z 
	detecte si es sospechoso, considerando sospechoso aquellos puntos para los que todos los puntos adyacentes 
	directos (propio plano y plano superior e inferior) tienen valores dentro de un intervalo de nivel de resonancia 
	dado. */
	bool puntoSospechoso(const ScanBody &image, const Sensitivity &params, int x, int y, int z) // TODO
	{
		/* la declaración de dimensiones es
		using ScanLine = array<Celda, SCAN_LINE_SZ>;
		using ScanPlane = array<ScanLine, LINES_PER_PLANE>;
		using ScanBody = vector<ScanPlane>;
		ScanBody es un vector de planos ScanPlane, por lo tanto image[z] me devuelve el plano z de la imagen
		ScanPlane es un array de líneas ScanLine, por lo tanto image[z][y] me devuelve la línea y del plano z
		ScanLine es un array de celdas Celda, por lo tanto image [z][y][x] me devuelve la celda (punto) x, de
		la línea y, del plano z
		*/
		//entonces el objeto ScanBody image se indexa image[z][y][x], el orden de los índices es importante!
		//barro en +-1 en todas las coordenadas (a menos que me salga de la imagen)
		for (int i = z - 1; i <= (z + 1); i++)
		{
			if (i < 0 || i >= int(image.size()))
				continue;
			for (int j = y - 1; j <= (y + 1); j++)
			{
				if (j < 0 || j >= int(image[z].size()))
					continue;
				for (int k = x - 1; k <= (x + 1); k++)
				{
					if (k < 0 || k >= int(image[z][y].size()))
						continue;
					//para que el punto (x,y,z) sea sospechoso, el punto y todos sus vecinos tienen que ser sospechosos.
					//si alguno no da dentro del umbral, entonces el punto no va a ser sospechoso y no tiene sentido
					//seguir iterando alrededor de este punto.
					if (!(image[i][j][k] >= params.minValue && image[i][j][k] <= params.maxValue))
						return false;
				}
			}
		}

		//si todos los puntos cayeron en el umbral, entonces el punto es sospechoso
		return true;
	}

	/*Detección de “plano sospechoso”: Es aquel plano (en Z) que posee una proporción de puntos sospechosos mayor 
	a un valor determinado.*/
	bool planoSospechoso(const ScanBody &image, const Sensitivity &params, int z)
	{
		int cnt = 0;
		// x varía de 0 a SCAN_LINE_SZ
		for (unsigned int i = 0; i < SCAN_LINE_SZ; i++)
		{
			// y varía de 0 a LINES_PER_PLANE
			for (unsigned int j = 0; j < LINES_PER_PLANE; j++)
			{
				// z es argumento fijo de la función
				if (puntoSospechoso(image, params, i, j, z))
					cnt++;
			}
		}
		// casteo a double para precisión. Cada plano tiene LINES_PER_PLANE * SCAN_LINE_SZ puntos
		// result (la proporción) va a valer entre 0.0 y 1.0
		double result = double(cnt) / (LINES_PER_PLANE * SCAN_LINE_SZ);
		// retorno true si el resultado se pasa del umbral
		return (result >= params.umbral);
	}
};

// fake scan image generation
#define _USE_MATH_DEFINES
#include <math.h>

ScanBody genImage()
{
	const unsigned int BODY_LEN = 256;
	ScanBody img;
	for (unsigned int z = 0; z < BODY_LEN; z++)
	{
		ScanPlane sp;
		double modulador = sin(z * M_PI / BODY_LEN);
		modulador *= modulador;
		modulador *= modulador;
		for (unsigned int y = 0; y < LINES_PER_PLANE; y++)
		{
			for (unsigned int x = 0; x < SCAN_LINE_SZ; x++)
			{
				double xf = (x * M_PI / SCAN_LINE_SZ) - M_PI / 2;
				double yf = (y * M_PI / LINES_PER_PLANE) - M_PI / 2;
				double val = cos(xf) * cos(yf);
				val *= modulador;
				sp[y][x] = (unsigned char)(val * 255);
			}
		}
		img.push_back(sp);
	}
	return img;
}

int main()
{
	cout << "Generando imagen trucha...\n";
	ScanBody image = genImage();
	cout << "imagen generada...\n";

	ScanAnalyzer analyzer;
	ScanAnalyzer::Sensitivity s = {150, 200, 0.10};

	cout << "Procesando...\n";
	vector<unsigned int> planos = analyzer.doWork(image, s);
	cout << "Completed...\n";
	for (auto x : planos)
		cout << "El plano " << x << " es sospechoso\n";

	return 0;
}