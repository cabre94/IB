#include <iostream>
#include <ctime>
#include <bitset>
#include <vector>

using namespace std;

/*
En esta version, voy a implementar una clase que emule una referencia a un bit
asi puedo implementar el operator[] non-const.
*/

template <class T>
class Vector{
public:
	Vector() : sz(0), v(nullptr) {}
	Vector(int sz_) : sz(sz_), v(new T[sz]) {}
	~Vector(){delete [] v;}

	Vector(const Vector &vec);
	Vector& operator=(const Vector& vec);

	T& operator[](int i){return v[i];}
	T  operator[](int i) const {return v[i];}
	
	int size(){return sz;}
private:
	int sz;
	T* v;
};

template<class T>
Vector<T>::Vector(const Vector &vec) : sz(vec.sz), v(new T[vec.sz]){
// Vector<T>::Vector(const Vector<T> &vec) : sz(vec.sz), v(new T[vec.sz]){
    for(int i=0; i < sz; i++)
        v[i] = vec.v[i];
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector &vec){
    T *aux = new T[vec.sz];
    for(int i=0; i < vec.sz; i++)
        aux[i] = vec.v[i];

    delete [] v;
    v = aux;
    sz = vec.sz;

    return *this;
}

template <class T>
ostream& operator<<(ostream &out, Vector<T> &vec){
    for(int i=0; i < vec.size()-1; i++)
        out << vec[i] << " - ";
    out << vec[vec.size()-1];
    return out;
}


/*
Especializacion para bools
- Voy a considerar que el primer elemento es el bit de mas a la derecha (o sea,
el bit menos significativo)
*/

template<>
class Vector<bool>{
public:
	Vector() : n_bits(0), sz(0), v(nullptr){}
	Vector(int sz_);
	~Vector(){delete [] v;};

	Vector(const Vector &);
	Vector &operator=(const Vector &);
	
	bool operator[] (int idx) const {return get(idx);}

	// No retorna realmente size, pero es lo que el usuario esperaria
	int size(){return n_bits;}

	class reference{	// Clase para emular una referencia a un bit
		friend class Vector<bool>;
		// reference();	// Left undefined?

		Vector<bool> *vec;	// Puntero al vector<bool> que queremos hacer referencia
		int idx;	// El indice de vec al que hacemos referencia
	public:
		// Un constructor a partir de un vector<bool> y el indice
		reference(Vector<bool>& vec_, int idx);
		reference(const reference&) = default;
		// ~reference(){};
		operator bool() const {return vec->get(idx);};	// For x = b[i];
		reference& operator=(bool x);	// For b[idx] = x;
		reference& operator=(const reference& x);	// For b[idx] = b[__j];

		// reference& flip();
		// bool operator~() const;
	};
	friend class reference;
	
	// Para cuando el [] esta a la izquierda de la igualdad
	// Esto nos retorna la referencia a un bit creada con el vector<bool> y el indice
	// Despues, el operator= de reference se encarga de modificar el bit
	// segun lo que haya a la derecha de la igualdad.
	reference operator[](int idx) {return reference(*this, idx);}

private:
	void set(int idx, bool value); 	// Setea el bit en idx
	bool get(int idx) const;		// Retorna el bit en idx

	// Cantidad de bits que tenemos en un unsigned long
	const unsigned int N = 8*sizeof(unsigned long);

	int n_bits;		// Cantidad de bits
	int sz;			// Tamaño de v
	unsigned long *v;
};

Vector<bool>::Vector(int n_bits_)
	: n_bits(n_bits_), sz(1+n_bits_/N), v(new unsigned long[sz]) {}

Vector<bool>::Vector(const Vector<bool> &vec)
	: n_bits(vec.n_bits), sz(vec.sz), v(new unsigned long[vec.sz]){
    for(int i=0; i < vec.sz; i++)
        v[i] = vec.v[i];
}

Vector<bool> &Vector<bool>::operator=(const Vector<bool> &vec){
    unsigned long* aux = new unsigned long[vec.sz];
    for(int i=0; i < vec.sz; i++)
        aux[i] = vec.v[i];

    delete [] v;
    v = aux;
    n_bits = vec.n_bits;
    sz = vec.sz;

    return *this;
}

void Vector<bool>::set(int idx, bool value){
	// - idx/N es indice del vector de unsigned long que tenemos que modificar
	// - (idx % N) es el bit del elemento idx/N que queremos setear
	// Lo que hacemos es shiftear un 1 (de tipo unsigned long, por eso el UL)
	// para dejarlo en la posicion del bit que queremos setear
	// El OR bitwise deja tal cual los bits comparados con 0 y pone un 1 los
	// comparados con 1. 0010 | 0100 -> 0110.	0110 | 0100 -> 0110
	if(value)
		v[idx/N] |= 1UL << (idx % N);
	// El AND deja mantine los comparados con 1 y deja un 0 los comparados con 0
	// 0110 & 1101 -> 0100.		0100 | 1101 -> 0100
	else
		v[idx/N] &= ~(1UL << (idx % N));
}

bool Vector<bool>::get(int idx) const {
	// - idx/N es indice del vector de unsigned long que tenemos que modificar
	// - (idx % N) es el bit del elemento idx/N que queremos. >> (idx % N) corre
	// ese bit a la primera posicion (lo pone como el bit menos significativo).
	// Por ultimo, hacemos un AND bit-wise contra un 1 (eso no da el valor del
	// ultimo bit) y lo convertimos a bool.
	return (bool) ( (v[idx/N] >> (idx % N)) & 1UL);
}

ostream& operator<<(ostream &out, Vector<bool> &vec){
	// Solamente porque me gusta mas como se ve, voy a printear los bits de a 8
	
	// Primero printeo los ceros a la izquierda (me da toc que uno que distinto)
	for(int i=0; i < (8 - vec.size() % 8); i++)
		out << '0';
	
	// Printeamos los bits dejando un espacio cada 8
	for(int i = vec.size()-1; i >= 0; i--){
		if(vec[i])
			out << '1';
		else
			out << '0';

		if((i % 8 == 0) && (i != 0))
			out << " ";
	}

    return out;
}

/*
Class Vector<bool>::reference
Me guie mucho viendo el codigo de la stl para std::bitset::reference
*/

// Creamos una referencia a partir del vector<bool> y el indice
Vector<bool>::reference::reference(Vector<bool>& vec_, int idx_){
	vec = &vec_;
	idx = idx_;
}

// For b[idx] = x;
// Basicamente llama a la set del puntero a Vector<bool> que mantenemos.
Vector<bool>::reference& Vector<bool>::reference::operator=(bool x){
	vec->set(idx, x);
	return *this;
}

// For b[idx] = b[__j];
// No me queda claro porque hace falta este operador. Yo hubiera creido que
// b[__j] retorna un bool y con eso se llama al operator=(bool x).
Vector<bool>::reference& Vector<bool>::reference::operator=(const reference& x){
	vec->set(idx, x.vec->get(x.idx));
	return *this;
}


int main(){
	srand(time(0));

    // Vector<int> vec(10);
	// for(int i=0; i < vec.size(); i++)
    //     vec[i] = rand() % 10;
	
	// // printVector(vec);
	// cout << vec << endl;

	// // Copy constructor
	// Vector<int> vec2 = vec;
	// vec2[3] = 42;
	// // printVector(vec2);
	// cout << vec2 << endl;
	
	// // Copy assigment
    // Vector<int> vec4;
    // vec4 = vec2;                                
	// vec4[3] = 4;
	// // printVector(vec4);
	// cout << vec4 << endl;

	Vector<bool> vec_b(65);

    for(int i=0; i < vec_b.size(); i++)
		// vec_b.set(i, rand() % 2);
		vec_b[i] = rand() % 2;
	
	cout << vec_b << endl;

	for(int i=0; i < vec_b.size()/2; ++i)
		vec_b[i] = true;
	// Copy constructor
	Vector<bool> vec2 = vec_b;
	// printVector(vec2);
	cout << vec2 << endl;
	
	for(int i=vec2.size()/2; i < vec2.size(); ++i)
		vec2[i] = false;
	// Copy assigment
    Vector<bool> vec4;
    vec4 = vec2;                                
	vec4[3] = 4;
	// printVector(vec4);
	cout << vec4 << endl;
	
	return 0;
}