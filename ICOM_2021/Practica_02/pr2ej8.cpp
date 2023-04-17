#include <iostream>

using namespace std;

int main(){
    uint8_t r, g, b;

    int input;

    cout << "Ingrese rojo: ";
    cin >> input;
    r = input;

    cout << "Ingrese verde: ";
    cin >> input;
    g = input;

    cout << "Ingrese azul: ";
    cin >> input;
    b = input;

    cout << "r: " << hex << (int) r << ", g: " << (int) g << ", b: " << (int) b << endl;

    uint32_t rgb = r | (((uint32_t) g) << 8) | (((uint32_t) b) << 16);

    cout << "rgb: " << dec << rgb << " #" << hex << rgb << endl;

    // es lo mismo que multiplicar por las potencias de 2
    float rgbf = r + g * 256.0 + b * 65536.0;
    printf("en float: %.0f\n", rgbf);


    return 0;
}

// Este es de Tapia, no mio.