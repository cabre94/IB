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
    // (queda recursivo)~
    OptionMenu(ifstream &in) {
      // ToDo
    }

    ~OptionMenu() {
        // ToDo
    }

    // debe visualizar la opcion del men� como
    // label : option1  option2  option3
    // donde label es la etiqueta de la opci�n y optionX son las etiquetas de las subopciones hijas
    void display() {
        // ToDo
    }

    // debe retornar la subopcion que tiene la etiqueta reqOption o nullptr si no existe esa subopcion
    OptionMenu *browse(const string &reqOption) {
        // ToDo
    }


private:
    string label;
    vector<OptionMenu *> suboptions;
};

class MenuBrowser {
public:
    // constructor que carga el men� de opciones desde el archivo fname
    // y hace que tanto root como current apunten a la opci�n ra�z del menu
    MenuBrowser(const char *fname){
        ifstream in(fname);
        assert(in);
        root = current = new OptionMenu(in);
    }
    ~MenuBrowser(){
        // ToDo
    }

    // m�todo que debe imprimir la opcion actual (current->display()), 
    // pedir la opcion deseada (cin >> opcion) e intentar navegar a esa subopci�n deseada
    // (current->browse(opcion)). 
    // Si esa opcion existe se debe cambiar current, 
    // si no existe se debe emitir un mensaje informandolo,
    // se debe imprimir nuevamente la opcion actual (current->display())
    // se debe reservar la opci�n "TOP" para que en caso de ser la opcion deseada, se haga que current sea nuevamente root.
    void prompt() {
        // ToDo
    }

private:
    OptionMenu *root;       // define la opci�n ra�z del sistema de men�s
    OptionMenu *current;    // opci�n activa
};

int main()
{
    MenuBrowser mb("menus.txt");

    while(true){
        mb.prompt();
    }
}
