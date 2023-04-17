#include <iostream>

using namespace std;

class MyString{
public:
	MyString();
	MyString(const char *str);
	MyString(const MyString &str);
	~MyString();
	char operator[](int i) const;
	char &operator[](int i);
	MyString operator+(MyString &str);
	MyString &operator=(const MyString &str);
	int getLength() const;



	// void print();
	void print() const;
private:
	char *s;
	int length;
};



void f(const MyString s){
	s.print();

}


int main(){

	MyString kk("maskk");

	// kk.print();

	// f(kk);

	// MyString kk2 = kk;
	// MyString kk2(kk);
	// MyString kk2{kk};

	MyString kk3("kk3");
	kk3 = kk;
	kk3.operator=(kk);

	// a = b = c;
	// a.operator=(b.operator=(c))

	try{
		kk3 = kk;
	}
	catch(...){
		kk3.print();
	}
	








	// MyString s1("hola mundo");
	// MyString s2(s1);
	// MyString s3;

	// s3 = s1 + s2;

	// cout << "s1:\t";
	// s1.print();
	// cout << "s2:\t";
	// s2.print();
	// cout << "s3 = s1+s2:\t";
	// s3.print();

	// s3[4] = 'X';
	// cout << "Despues de la sentencia s3[4] = 'X' s3 como:\t";
	// s3.print();

	// char c = s3[2];
	// cout << "El elemento s3[2] es: ";
	// cout << c << endl;

	return 0;
}

MyString::MyString(){
	s = nullptr;
	length = 0;
}


MyString::MyString(const char *str){
	// Primero calculamos el largo del arreglo nativo str
	int len = 0;
	while(str[len] != 0)
		len++;
	length = len;	// Lo guardamos en MyString

	s = new char[length];	// Allocamos la memoria para esos caracteres. No necesitamos el 0
							// porque en nuestra clase ya tenemos el largo del string
	for(int i=0; i < length; i++) // Copiamos caracter a caracter
		s[i] = str[i];
}

MyString::MyString(const MyString &str){
	length = str.getLength();	// Copiamos el largo

	s = new char[length];
	for(int i=0; i < length; i++)
		s[i] = str.s[i];
}

MyString::~MyString(){
	delete [] s;
}

char MyString::operator[](int i) const{
	return s[i];
}

char& MyString::operator[](int i){
	return s[i];
}

MyString MyString::operator+(MyString &str){
	MyString res;

	res.length = length + str.getLength();
	res.s = new char[res.length];

	int i = 0;
	for( ; i < length; i++)		// Copiamos el primer strings
		res.s[i] = s[i];
	for(int j=0; j < str.getLength(); j++)	// Y a continuacion el segundo
		res.s[i+j] = str.s[j];

	return res;
}

MyString &MyString::operator=(const MyString &str){
	char *aux = new char[str.getLength()]; 	// Se puede hacer como esta comentado abajo, pero esta forma es mejor, porque si por X motivo
												// falla la alocacion (tira bad_alloc) y ya destruiste el contenido, cagaste. Con esto solo lo
												// destruis una vez que te aseguraste de haberlo copiado.
	for(int i=0; i < str.getLength(); i++)		// Copiamos cada uno de los elementos
		aux[i] = str.s[i];
	
	// Ahora si, como estamos seguros de que pudimos copiar el string, liberamos la memoria del string actual
	// y reemplazamos el puntero por el auxiliar, donde ya esta todo copiado.
	length = str.getLength();
	delete [] s;
	s = aux;
	
	return *this;	// Retornamos una referencia, asi que pedimos el contenido de this
	/*
	delete [] s;

	length = str.getLength();
	s = new char[length];

	for(int i=0; i < length; i++)
		s[i] = str.s[i];
	
	return *this;
	*/
}

int MyString::getLength() const{
	return length;
}

void MyString::print() const{
	cout << s << endl;
}

// Con amor, Cabre.