#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <vector>

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class OptionMenu{
public:
	// debe crear la opcion leyendo el label y la cantidad de hijos desde el ifstream
	// reservar espacio para las suboptions de acuerdo a la cantidad de hijos y
	// mandar a crear esos hijos desde el mismo ifstream y pushearlos en suboptions.
	// (queda recursivo)
	OptionMenu(ifstream &in){
		int n_suboptions;
		// Leemos el label y la cantidad de subopciones
		in >> label >> n_suboptions;
		// Ahora tenemos que allocar las subopciones y guardarlas en el vector
		for(int i=0; i < n_suboptions; i++)
			suboptions.push_back(new OptionMenu(in));
	}
	~OptionMenu(){
		// Tenemos que hacer el delete de cada elemento de vector
		for(int i=0; i < suboptions.size(); i++)
			delete suboptions[i];
	}
	// debe visualizar la opcion del men� como
	// label : option1  option2  option3
	// donde label es la etiqueta de la opci�n y optionX son las etiquetas de las subopciones hijas
	void display(){
		cout << label << " : ";
		for(int i=0; i < suboptions.size(); i++)
			cout << suboptions[i]->label << " ";
		cout << endl;
	}
	// debe retornar la subopcion que tiene la etiqueta reqOption o nullptr si no existe esa subopcion
	OptionMenu *browse(const string &reqOption){
		// Buscamos el label ingresado en las subopciones
		for(int i=0; i < suboptions.size(); i++){
			if(suboptions[i]->label == reqOption)
				return suboptions[i];
		}
		// Si llegamos aca, la opcion no existe, retornamos nullptr
		return nullptr;
	}

private:
	string label;
	vector<OptionMenu *> suboptions;
};

class MenuBrowser{
public:
	// constructor que carga el men� de opciones desde el archivo fname
	// y hace que tanto root como current apunten a la opci�n ra�z del menu
	MenuBrowser(const char *fname){
		ifstream in(fname);
		assert(in);
		root = current = new OptionMenu(in);
	}
	~MenuBrowser(){
		// Deleteamos root y esto deberia ir borrando todo recursivamente
		delete root;
	}

	// m�todo que debe imprimir la opcion actual (current->display()),
	// pedir la opcion deseada (cin >> opcion) e intentar navegar a esa subopci�n deseada
	// (current->browse(opcion)).
	// Si esa opcion existe se debe cambiar current,
	// si no existe se debe emitir un mensaje informandolo,
	// se debe imprimir nuevamente la opcion actual (current->display())
	// se debe reservar la opci�n "TOP" para que en caso de ser la opcion deseada, se haga que current sea nuevamente root.
	void prompt(){
		// Imprimimos el menu actual y sus opciones
		current->display();
		
		string in_option;	// Aca guardamos la opcion que vamos a pedir
		bool valid_option = false;	// Para saber si la opcion fue valida

		while(!valid_option){
			cin >> in_option;	// pedimos una opcion al usuario

			// Si la opcion es TOP, volvemos a root.
			if(in_option == "TOP"){
				current = root;
				valid_option = true;
			}else{
				// Ahora buscamos la opcion que se ingreso en las subopciones disponibles
				OptionMenu* browsed_option = current->browse(in_option);
				// Si es nullptr, avisamos que la opcion que se busco no existe y volvemos
				// a imprimir las opciones actuales. Se ejecuta otra iteracion del while
				if(browsed_option == nullptr){
					cout << "Opcion no valida" << endl;
					current->display();
				}else{
					// Si no es nullptr, actualizamos el puntero current
					current = browsed_option;
					valid_option = true;
				}
			}
		}

	}

private:
	OptionMenu *root;	 // define la opci�n ra�z del sistema de men�s
	OptionMenu *current; // opci�n activa
};

int main(){
	MenuBrowser mb("menus.txt");

	while(true){
		mb.prompt();
	}

	return 0;
}
