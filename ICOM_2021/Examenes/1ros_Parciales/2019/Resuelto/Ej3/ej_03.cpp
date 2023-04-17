#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>

using namespace std;

// void grafenoFloodFill(STM_image &img, IslaGrafeno &isla, int i, int j, unsigned short threshold){


struct STM_image{
	unsigned int width;
	unsigned int height;
	vector<unsigned short> pixels;

	unsigned int ij2index(int i, int j){
		assert(i >= 0 && i < (int) width && j >= 0 && j < (int) height);
		// unsigned int pixelIndex = i * width + j;
		unsigned int pixelIndex = i * height + j;
		assert(pixelIndex < pixels.size());
		return pixelIndex;
	}
	unsigned short getPixel(int i, int j) {
		unsigned int pixelIndex = ij2index(i, j);
		return pixels[pixelIndex];
	}
	void setPixel(int i, int j, unsigned short value) {
		unsigned int pixelIndex = ij2index(i, j);
		pixels[pixelIndex] = value;
	}
};

struct Punto2D {
	int x, y;
};

struct IslaGrafeno {
	vector<Punto2D> puntos;
};

struct GrafenoAnalizer {
	GrafenoAnalizer(unsigned short threshold_){
		threshold = threshold_;
	}

	vector<IslaGrafeno> analize(STM_image img);
	// ...
	unsigned short threshold;
};

void grafenoFloodFill(STM_image &img, IslaGrafeno &isla, int i, int j, unsigned short threshold);


vector<IslaGrafeno> GrafenoAnalizer::analize(STM_image img){
	vector<IslaGrafeno> islas;

	for(int i=0; i < img.width; i++){
		for(int j=0; j < img.height; j++){
			if(img.getPixel(i,j) > threshold){
				IslaGrafeno isla;
				/* Si el valor del pixel es mayor que el threshold, llamo a mi funcion que deberia llenarme la isla de grafeno
				con los puntos. Para que isla lo llene con los puntos, se lo pasamos a grafenoFloodFill por referencia, si no,
				nos va a llenar de puntos una copia.*/
				grafenoFloodFill(img, isla, i, j, threshold);
				// Agregamos la isla que encontramos al vector de islas
				islas.push_back(isla);
			}
		}
	}

	return islas;
}

void grafenoFloodFill(STM_image &img, IslaGrafeno &isla, int i, int j, unsigned short threshold){
	if(img.getPixel(i,j) < threshold) // Pense que deberia volar a la mierda...
		return;
	else{
		// Agregamos el punto donde estamos a la isla de grafeno
		Punto2D p = {i, j};
		isla.puntos.push_back(p);

		// Ponemos el punto en cero para no volver en futuros llamados
		img.setPixel(i, j, 0);

		// Llamamos recursivavente a la funcion hacia las 4 direcciones
		grafenoFloodFill(img, isla, i, j+1, threshold);
		grafenoFloodFill(img, isla, i+1, j, threshold);
		grafenoFloodFill(img, isla, i, j-1, threshold);
		grafenoFloodFill(img, isla, i-1, j, threshold);
	}
}



// No hace falta hacer este main
int main(){
	srand(time(0));

	STM_image img;
	// Seria mas razonable que esto se haga en un constructor, pero prefiero no tocarlo
	img.height = 10;
	img.width = 20;
	img.pixels.resize(img.width * img.height);	// Esto lo llena de ceros
	for(int i = 0; i < img.width; i++){
		for(int j = 0; j < img.height; j++){
			// cout << i << " " << j << endl;
			img.setPixel(i, j, rand() % 128);	// Ponemos un poco de ruidito
		}
	}

	/* Ponemos a mano una isla */
	img.setPixel(2, 3, 1023);
	img.setPixel(2, 4, 1023);
	img.setPixel(3, 3, 1023);
	img.setPixel(3, 4, 1023);
	img.setPixel(4, 3, 1023);
	img.setPixel(4, 4, 1023);

	/* Ponemos a mano una segunda isla */
	img.setPixel(15, 7, 620);
	img.setPixel(15, 8, 620);
	img.setPixel(16, 7, 620);
	img.setPixel(16, 8, 620);
	img.setPixel(17, 7, 620);
	// img.setPixel(17, 8, 620);


	// Creamos el analizador de grafeno con un threshold
	GrafenoAnalizer analizer(256);

	// el metodo analize nos deberia retornar el vector de islas
	vector<IslaGrafeno> islas =  analizer.analize(img);

	// Y las printeamos a ver si son los puntos que que pusimos en la setPixel
	for(int i=0; i < islas.size(); i++){
		cout << "Isla " << i+1 << endl;
		for(int j = 0; j < islas[i].puntos.size(); j++){
			cout << "(" << islas[i].puntos[j].x << ", " << islas[i].puntos[j].y << ") ";
		}
		cout << endl;
	}

	return 0;
}