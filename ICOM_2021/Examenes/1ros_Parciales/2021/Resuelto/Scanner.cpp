#include <vector>
#include <array>
#include <iostream>
#include <fstream>

using namespace std;

// cada celda de un cuerpo escaneado esta represendado por un valor "resonante" representado por una
// intensidad: un valor entero, sin signo en el intervalo [0,255]
using Celda = unsigned char;


const unsigned int SCAN_LINE_SZ    = 128;
const unsigned int LINES_PER_PLANE = 128;


// define una l�nea de scan (direcci�n X)
using ScanLine  = array<Celda,    SCAN_LINE_SZ>;

// define un plano de scan (direcci�n X,Y)
using ScanPlane = array<ScanLine, LINES_PER_PLANE>;

// define un vol�men de scan (direcci�n X,Y,Z)
using ScanBody  = vector<ScanPlane>;

class ScanAnalyzer {
    public:
        // La estructura Sensitivity define la sensibilidad a ser aplicada en el analisis de una
        // imagen escaneada. La sensibilidad esta caracterizada por 2 par�metros
        struct Sensitivity {
            // definen el rango de detecci�n de los puntos (ver enunciado)
            Celda  minValue;
            Celda  maxValue;

            // define la minima proporcion [0, 1.0] de puntos de un plano (en Z) que deben ser sospechosos para que
            // el plano sea sospechoso (0: 0%, 1.0: 100%) (ver enunciado)
            double umbral; 
        };

        // analiza la imagen 'image' y retorna un vector de todos los planos (identificado por �ndice de plano)
        // que son sospechosos dado la sensibilidad dada por 'params'
		vector<unsigned int> doWork(const ScanBody& image, const Sensitivity& params);          // TODO

    private:
		bool puntoSospechoso(const ScanBody& image, const Sensitivity& params, int x, int y, int z);  // TODO
		bool planoSospechoso(const ScanBody& image, const Sensitivity& params, int z);               // TODO

		// Funcion auxiliar para ver si un (x,y,z) esta dentro de la imagen
		// bool validIdx(int x, int y, int z);
};


// fake scan image generation
#define _USE_MATH_DEFINES
#include <math.h>

ScanBody genImage()
{
	const unsigned int BODY_LEN = 256;
	ScanBody img;
	for (unsigned int z = 0; z < BODY_LEN; z++) {
		ScanPlane sp;
		double modulador = sin(z * M_PI / BODY_LEN);
		modulador *= modulador;
		modulador *= modulador;
		for (unsigned int y = 0; y < LINES_PER_PLANE; y++) {
			for (unsigned int x = 0; x < SCAN_LINE_SZ; x++) {
				double xf = (x * M_PI / SCAN_LINE_SZ) - M_PI / 2;
				double yf = (y * M_PI / LINES_PER_PLANE) - M_PI / 2;
				double val = cos(xf) * cos(yf);
				val *= modulador;
				sp[y][x] = (unsigned char) (val*255);
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
	ScanAnalyzer::Sensitivity  s = { 150, 200, 0.10 };

	cout << "Procesando...\n";
	vector<unsigned int> planos = analyzer.doWork(image, s);
	cout << "Completed...\n";
	for (auto x : planos)
		cout << "El plano " << x << " es sospechoso\n";


	return 0;
}

// bool validIdx(int i, int j, int k){
// 	if(i < 0 || i>=)

// }

bool ScanAnalyzer::puntoSospechoso(const ScanBody& image, const Sensitivity& params, int x, int y, int z){

	for(int k=z-1; k <= z+1; k++){
		if(k < 0 || k >= image.size())
			continue;
		for(int j=y-1; j <= y+1; j++){
			if(j < 0 || j >= LINES_PER_PLANE)
				continue;
			for(int i=x-1; i <= x+1; i++){
				if(i < 0 || i >= SCAN_LINE_SZ)
					continue;
				// Chequeamos si el punto es sospechoso. Con uno que no lo sea ya alcanza para cortar la funcion
				if(image[k][j][i] < params.minValue || image[k][j][i] > params.maxValue)
					return false;
			}
		}
	}
	
	return true;
}

bool ScanAnalyzer::planoSospechoso(const ScanBody& image, const Sensitivity& params, int z){
	int count = 0;

	for(unsigned int j=0; j < LINES_PER_PLANE; j++){
		for(unsigned int i=0; i < SCAN_LINE_SZ; i++){
			if(puntoSospechoso(image, params, i, j, z))
				count++;
		}
	}

	double ratio = (double) count / (LINES_PER_PLANE*SCAN_LINE_SZ);

	return ratio > params.umbral;
}

vector<unsigned int> ScanAnalyzer::doWork(const ScanBody& image, const Sensitivity& params){
	vector<unsigned int> res;

	for(unsigned int z=0; z < image.size(); z++){
		if(planoSospechoso(image, params, z))
			res.push_back(z);
	}

	return res;
}