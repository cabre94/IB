#include <iostream>

using namespace std;

class myUDT{
    void kk1(){}
    int kk2(){
        return 42;
    }
};

int main(){
    myUDT var;
    
	cout << "Tamaño de la variable myUDT: " << sizeof(var) << endl;
    
    return 0;
}

// https://www.stroustrup.com/bs_faq2.html#sizeof-empty

// Con amor, Cabre.