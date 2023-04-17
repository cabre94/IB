#include <iostream>

using namespace std;

class myUDT{
private:
    myUDT(){cout << "Constructor..." << endl;}
    ~myUDT(){cout << "Destructor..." << endl;}
};


int main(){

    myUDT instance; // Esto directamente no compila

    return 0;
}

// Con amor, Cabre.