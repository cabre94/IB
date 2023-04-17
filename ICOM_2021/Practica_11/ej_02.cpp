#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


struct STM_image{
    unsigned int width;
    unsigned int height;
    std::vector<unsigned short> pixels;

    unsigned int ij2index(int i, int j){
        assert(i >= 0 && i < (int) width && j >= 0 && j < (int) height);
        // unsigned int pixelIndex = i * width + j;
        unsigned int pixelIndex = i * height + j;
        assert(pixelIndex < pixels.size());
        return pixelIndex;
    }

    unsigned short getPixel(int i, int j){
        unsigned int pixelIndex = ij2index(i, j);
        return pixels[pixelIndex];
    }

    void setPixel(int i, int j, unsigned short value){
        unsigned int pixelIndex = ij2index(i, j);
        pixels[pixelIndex] = value;
    }
};

struct Punto2D{
    int x, y;
};

struct IslaGrafeno{
    vector<Punto2D> puntos;
};

struct GrafenoAnalizer{
    GrafenoAnalizer(unsigned int threshold_) {
        threshold = threshold_;
    }

    vector<IslaGrafeno> analize(STM_image img);   // implmentar

	void grafenoFloodFill(STM_image &img, IslaGrafeno &isla, int i, int j, unsigned short threshold);

    unsigned short threshold;
};

STM_image stmLoadImage(const string &fname)
{
    STM_image img;
    ifstream ifile(fname);
    assert(ifile);

    ifile >> img.width >> img.height;
    unsigned short pixel;
    img.pixels.reserve(img.width * img.height);
    
    while (ifile >> pixel)
        img.pixels.push_back(pixel);

    assert(img.pixels.size() == img.width * img.height);
    
    return img;
}

int main()
{
    STM_image img = stmLoadImage("image0.img");
    GrafenoAnalizer gfa(500);

    vector<IslaGrafeno> islas = gfa.analize(img);

    cout << "cantidad de islas: " << islas.size() << endl;
    for( size_t i = 0; i < islas.size(); ++i )
        cout << "isla " << i << ": size: " << islas[i].puntos.size() << endl;

    return 0;
}


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

void GrafenoAnalizer::grafenoFloodFill(STM_image &img, IslaGrafeno &isla, int i, int j, unsigned short threshold){
	if(i < 0 || i >= (int) img.width)	// Chequeamos estar dentro de la imagen
		return;
	if(j < 0 || j >= (int) img.height)
		return;
	if(img.getPixel(i,j) < threshold)
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