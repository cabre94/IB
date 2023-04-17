#include <iostream>

using namespace std;

struct RGB{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	// Ahora los metodos
	int compositeColor(){
		int R,G,B;
		R = red;
		G = green << 8;
		B = blue << 16;
		return R+G+B;
	}
	bool setFromComposite(int color){
		if(color < 0 || color > 0xffffff)
			return false;
		else{
			red = color % 256;
			green = (color >> 8) % 256;
			blue = (color >> 16);
			return true;
		}
	}
	bool setFromComponents(int R, int G, int B){
		if(R<0 || G<0 || B<0 || R>255 || G>255 || B>255)
			return false;
		else{
			red = R;
			green = G;
			blue = B;
			return true;
		}
	}
	void print(){
		cout << "Las componentes en RGB son:\n";
		cout << "R: " << (int) red   << "\n";
		cout << "G: " << (int) green << "\n";
		cout << "B: " << (int) blue  << "\n";
		return;
	}
};

int main(){
	int input,R,G,B;
	RGB Color;

	cout << "Ingresar color (valido de 0 a 16777215 (0xFFFFFF))\n";
	cin >> input;
	
	if(Color.setFromComposite(input)){
		cout << "El color ingresado es valido y se guardo correctamente.\n";
		cout << "El color ingresado es: " << Color.compositeColor() << ".\n";
		Color.print();
	}
	else
		cout << "El color ingresado no es valido.\n";

	cout << "\n\nAhora probamos con un segundo color, ingresando las componentes RGB.\n";
	cout << "Ingrese la componente R del color (0-255):\n";
	cin >> R;
	cout << "Ingrese la componente G del color (0-255):\n";
	cin >> G;
	cout << "Ingrese la componente B del color (0-255):\n";
	cin >> B;
	
	if(Color.setFromComponents(R,G,B)){
		cout << "Las componentes ingresadas son validas y el color se guardo correctamente.\n";
		cout << "El color ingresado es: " << Color.compositeColor() << ".\n";
		Color.print();
	}
	else
		cout << "Alguna de las componentes no ingresadas no es valida.\n";
	
    return 0;
}

// Con amor, Cabre.