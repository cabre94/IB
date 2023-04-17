#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


struct STM_image
{
    unsigned int width;
    unsigned int height;
    std::vector<unsigned short> pixels;

    unsigned int ij2index(int i, int j) {
        assert(i >= 0 && i < (int) width && j >= 0 && j < (int) height);
        // unsigned int pixelIndex = i * width + j;	// Esta linea esta mal
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

struct GrafenoAnalizer
{
    GrafenoAnalizer(unsigned int threshold_) {
        threshold = threshold_;
    }

    vector<IslaGrafeno> analize(STM_image img);   // implmentar

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


