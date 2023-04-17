#include <iostream>

using namespace std;

void ej2(){
	int acum2 = 0, acum3 = 0, acum4 = 0, acum5 = 0;

	for (int i = 1; i <= 1000; i++)	{
		if (i % 2 == 0)
			acum2 += i;
		if (i % 3 == 0)
			acum3 += i;
		if (i % 4 == 0)
			acum4 += i;
		if (i % 5 == 0)
			acum5 += i;
	}

	cout << "Suma de los multiplos de 2: " << acum2 << endl;
	cout << "Suma de los multiplos de 3: " << acum3 << endl;
	cout << "Suma de los multiplos de 4: " << acum4 << endl;
	cout << "Suma de los multiplos de 5: " << acum5 << endl;
}

int main(){

	ej2();

	return 0;
}

// Con amor, Cabre.