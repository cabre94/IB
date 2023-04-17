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
    ImagenGris(size_t ancho_, size_t alto_);       // ToDo
    Gris getPixel(int i, int j) const;             // ToDo
    void setPixel(int i, int j, Gris color);       // ToDo
    size_t getAncho() const;                       // ToDo
    size_t getAlto() const;                        // ToDo
    Punto2D centroide() const;                     // ToDo

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

class CamProcessor {
public:
    CamProcessor(const ImagenGris &back, Gris th) 
		: background(back), threshold(th) {}

    // Solicita el procesamiento de una nueva imagen proveniente
    // de la c�mara, el centroide de la imagen resta entre este nuevo frame
    // y el background ser� retornada como resultado del procesamiento
    Punto2D procFrame(const ImagenGris &frame){
        // ToDo
        return Punto2D{ 0, 0 };
    }
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

