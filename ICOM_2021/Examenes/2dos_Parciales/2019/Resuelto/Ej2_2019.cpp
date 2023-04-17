#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <vector>

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class OptionMenu {
public:
    OptionMenu(ifstream &in);                       ///ToDo
    ~OptionMenu();                                  ///ToDo
    void display();                                 ///ToDo
    OptionMenu *browse(const string &reqOption);    ///ToDo

private:
    string label;
    vector<OptionMenu *> suboptions;
};

class MenuBrowser {
public:
    // constructor que carga el men� de opciones desde el archivo fname
    // y hace que tanto root como current apunten a la opci�n ra�z del menu
    MenuBrowser(const char *fname) {
        ifstream in(fname);
        assert(in);
        root = current = new OptionMenu(in);
    }
    ~MenuBrowser(); ///ToDo
    void prompt();  ///ToDo

private:
    OptionMenu *root;       // define la opci�n ra�z del sistema de men�s
    OptionMenu *current;    // opci�n activa
};

int main()
{
    MenuBrowser mb("menus.txt");

    while(true){
        mb.prompt();
		break;
    }
}

/// Definiciones OptionMenu ------------------------------------------------------------------------------

/**
Debe crear la opcion leyendo el label y la cantidad de hijos desde el ifstream,
reservar espacio para las suboptions de acuerdo a la cantidad de hijos y
mandar a crear esos hijos desde el mismo ifstream y pushearlos en suboptions.
(queda recursivo)
**/
OptionMenu :: OptionMenu(ifstream &in){
    int i_aux;
    assert(in >> label);
    assert(in >> i_aux);
    suboptions.resize(i_aux);
    for(int i=0; i<i_aux; i++)
        suboptions[i] = new OptionMenu(in);
}

OptionMenu :: ~OptionMenu(){
    for(auto elem : suboptions)
        delete elem;
}

/**
Debe visualizar la opcion del men� como
label : option1  option2  option3
donde label es la etiqueta de la opci�n y optionX son las etiquetas
de las subopciones hijas
**/
void OptionMenu :: display(){
    cout << label << " : ";
    for(int i=0; i<suboptions.size(); i++)
        cout << suboptions[i]->label << " ";
}

/**
debe retornar la subopcion que tiene la etiqueta reqOption
o nullptr si no existe esa subopcion
**/

OptionMenu* OptionMenu :: browse(const string &reqOption){
    for(int i=0; i<suboptions.size(); i++)
        if(suboptions[i]->label == reqOption)
            return suboptions[i];
    return nullptr;
}

/// Definiciones MenuBrowser ------------------------------------------------------------------------
/**
M�todo que debe imprimir la opcion actual (current->display()),
pedir la opcion deseada (cin >> opcion) e intentar navegar a esa subopci�n deseada
(current->browse(opcion)).
Si esa opcion existe se debe cambiar current,
si no existe se debe emitir un mensaje informandolo,
se debe imprimir nuevamente la opcion actual (current->display())
se debe reservar la opci�n "TOP" para que en caso de ser la opcion deseada,
se haga que current sea nuevamente root.
**/
void MenuBrowser :: prompt(){
    string opcion;
    cout << "Opcion actual = ";
    current->display();
    cout << "\nIngrese una opcion = ";
    cin >> opcion;
    if(opcion == "TOP")
        current = root;
    else{
        OptionMenu *nuevaOpcion = current->browse(opcion);
        if(nuevaOpcion != nullptr)
            current = nuevaOpcion;
        else
            cout << "No existe esa opcion" << endl;
    }
    cout << "La opcion actualizada es =  ";
    current->display();
    cout << "\n\n";
}

MenuBrowser :: ~MenuBrowser(){
    delete root;
}
