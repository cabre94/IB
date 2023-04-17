#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

class rata{
    public:
        rata(){};
        ~rata(){
            std::cout << "------------------------" << '\n';
            std::cout << "Se destruyó la rata." << '\n';
        };
        virtual void nace(void){
            std::cout << "Nace" ;
        }
        virtual void come(void){
            std::cout << "Figura::come" << '\n';
        }
        virtual void vive(void) {
            std::cout << "Figura::vive" << '\n';
        }
        virtual void muere(void){
            std::cout << "Figura::muere" << '\n';
        }
        virtual void quien_soy(void){
            std::cout << "Yo soy..." << '\n';
        }
};

class Rata_laboratorio : public rata{
    public:
        void come(void){
            std::cout << "químicos radioactivos" ;
        }
        void vive(void){
            std::cout << "tiene 2 colas y 3 ojos" ;
        }
        void quien_soy(void){
            std::cout << "Rata de laboratorio" ;
        }
        void muere(void){
            std::cout << "de un shock eléctrico" ;
        }

};

class Rata_alcantarilla : public rata{
    public:
        void come(void){
            std::cout << "basura" ;
        }
        void vive(void){
            std::cout << "se pelea con un murcielago por territorio" ;
        }
        void quien_soy(void){
            std::cout << "Rata de alcantarilla" ;
        }
        void muere(void){
            std::cout << "intoxicada" ;
        }
};

class Rata_domestica : public rata{
    public:
        void come(void){
            std::cout << "queso con huequitos" ;
        }
        void vive(void){
            std::cout << "le colocan un moñito con un vestidito" ;
        }
        void quien_soy(void){
            std::cout << "Rata domestica" ;
        }
        void muere(void){
            std::cout << "feliz" ;
        }
};
void que_le_pasa_a_una_rata(rata *r){
    std::cout << "------------------------" << '\n';
    r->nace();
    std::cout << " una " ;
    r->quien_soy();
    std::cout <<".\nCome " ;
    r->come();
    std::cout << " y " ;
    r->vive();
    std::cout << ".\nEntonces muere " ;
    r->muere();
    std::cout << "." << '\n';
}
int main(void)
{
    std::vector<rata *> holus;
    holus.push_back(new Rata_laboratorio);
    holus.push_back(new Rata_alcantarilla);
    holus.push_back(new Rata_domestica);

    for (size_t i = 0; i < 3; i++) {
        que_le_pasa_a_una_rata(holus[i]);
    }
    for (size_t i = 0; i < 3; i++) {
        delete holus[i];
    }

    return 0;
}
