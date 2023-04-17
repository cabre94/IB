#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <vector>
#include <fstream>

#include <iostream>

using namespace std;

using Gris = unsigned char;

struct Punto2D{
    unsigned int x;
    unsigned int y;
};

class ImagenGris{
public:
    ImagenGris(const string &fname){
        loadFrom(fname);
    }
	// No aclaran que hay que hacer con esto, pero asumo que la dejo vacia
    ImagenGris(size_t ancho_, size_t alto_) : ancho(ancho_), alto(alto_){
		pixels.clear();
		pixels.reserve(ancho * alto);
	}
    Gris getPixel(int i, int j) const {return pixels[i*ancho+j];}
    void setPixel(int i, int j, Gris color) {pixels[i*ancho+j] = color;}
    size_t getAncho() const {return ancho;}
    size_t getAlto() const {return alto;}
    Punto2D centroide() const;

    void loadFrom(const string &fname){
        ifstream f(fname);
        assert(f);
        f >> ancho >> alto;
        pixels.clear();
        pixels.reserve(ancho * alto);
        int c;
        while (f >> c)
            pixels.push_back(Gris(c));
        assert(ancho * alto == pixels.size());
    }

private:
    size_t ancho, alto;
    vector<Gris> pixels;
};

class CamProcessor{
public:
    CamProcessor(const ImagenGris &back, Gris th) 
		: background(back), threshold(th) {}

    // Solicita el procesamiento de una nueva imagen proveniente
    // de la c�mara, el centroide de la imagen resta entre este nuevo frame
    // y el background ser� retornada como resultado del procesamiento
    Punto2D procFrame(const ImagenGris &frame);
private:
    const ImagenGris background;   // imagen gris de fondo
    Gris threshold;                 // umbral de detecci�n
};


class FakeCam{
    public:
        FakeCam() : fnames({ "image1.img", "image2.img", "image3.img", "image4.img" }) {}

        void nextFrame(ImagenGris &img){
            img.loadFrom(fnames[frame % fnames.size()]);
            frame++;
        }

    private:
        vector<string> fnames;
        int frame = 0;
};

int main(){
    ImagenGris img("bg.img");
    CamProcessor vigia(img, 10);

    FakeCam cam;

    while(true){
        cam.nextFrame(img);
        Punto2D c = vigia.procFrame(img);
        cout << "x: " << c.x << "  y: " << c.y << endl;
    }

	return 0;
}




// 
Punto2D ImagenGris::centroide() const{
	unsigned int cm_i = 0, cm_j = 0;

	for(size_t i=0; i < alto; i++){
		for(size_t j=0; j < ancho; j++){
			Gris pxl = getPixel(i, j);	// Obtenemos el valor del pixel
			cm_i += i * (unsigned int) pxl;
			cm_j += j * (unsigned int) pxl;
		}
	}
	// Al dividir por un entero deberia hacer la division entera
	cm_i = cm_i / alto;
	cm_j = cm_j / ancho;
	
	return Punto2D {cm_i, cm_j};
}

// Solicita el procesamiento de una nueva imagen proveniente
// de la c�mara, el centroide de la imagen resta entre este nuevo frame
// y el background ser� retornada como resultado del procesamiento
Punto2D CamProcessor::procFrame(const ImagenGris &frame){
	assert(background.getAlto() == frame.getAlto());
	assert(background.getAncho() == frame.getAncho());

	// Imagen donde vamos a guardar la resta
	ImagenGris mrf(background.getAlto(), background.getAncho());

	Gris resta;	// Pixel de la resta

	for(size_t i=0; i < mrf.getAlto(); i++){
		for(size_t j=0; j < mrf.getAncho(); j++){
			resta = (Gris) abs(background.getPixel(i,j) - frame.getPixel(i,j));

			// Dependiendo de si la resta es menor o mayor que el threshold
			// seteamos 0 o resta en la imagen mrf.
			if(resta < threshold)
				mrf.setPixel(i, j, 0);
			else
				mrf.setPixel(i, j, resta);
		}
	}

	// Retornamos el centroide
	return mrf.centroide();
}