#include <iostream>
#include <ctime>

using namespace std;

typedef void (*FunPtr_t)(void);

void fun1(){ cout << "Fun1" << endl;}

void fun2(){ cout << "Fun2" << endl;}

void fun3(){ cout << "Fun3" << endl;}

void fun4(){ cout << "Fun4" << endl;}

void fun5(){ cout << "Fun5" << endl;}


int main(){
    srand(time(0));

    FunPtr_t funs[5] = {fun1, fun2, fun3, fun4, fun5};
    
    for(int i=0; i<10; i++){
        int idx = rand()%5;
        funs[idx]();
    }

    return 0;
}

// Con amor, Cabre.