#include <iostream>

using namespace std;

void fun();

int main(){
	fun();
	return 0;
}

void fun(){
    int a[3][3] = { 0 };
    int *pFilas[3] = { &a[0][0], &a[1][0], &a[2][0] };
    pFilas[0][0] = pFilas[1][0] = pFilas[2][0] = 1;
    
    for(int i=0; i < 3; i++){
        for(int j=0; j < 3; j++){
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

// Con amor, Cabre.