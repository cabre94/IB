#include <iostream>
#include <ctime>

using namespace std;

template <class T>
class Vector{
public:
	Vector() : elem(nullptr), sz(0) {}
	Vector(int s);
	~Vector();

	Vector(const Vector &v);
	Vector& operator=(const Vector& v);

	T& operator[](int i){return elem[i];}
	T  operator[](int i) const {return elem[i];}
	
	int size(){return sz;}
private:
	int sz;
	T* elem;
};

template<class T>
Vector<T>::Vector(int s) : sz(s), elem(new T[sz]) {}

template<class T>
Vector<T>::~Vector(){delete [] elem;}

template<class T>
Vector<T>::Vector(const Vector &vec) : sz(vec.sz), elem(new T[vec.sz]){
// Vector<T>::Vector(const Vector<T> &vec) : sz(vec.sz), elem(new T[vec.sz]){
    for(int i=0; i < sz; i++)
        elem[i] = vec.elem[i];
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector &vec){
    T *aux = new T[vec.sz];
    for(int i=0; i < vec.sz; i++)
        aux[i] = vec.elem[i];

    delete [] elem;
    elem = aux;
    sz = vec.sz;

    return *this;
}

template<class T>
void printVector(Vector<T>& v) {
	for(int i=0; i < v.size()-1; ++i)
		cout << v[i] << " - ";
	cout << v[v.size()-1] << endl;
}


/*
Especializacion para bools
	- Va por ese lado. El 16 probablemente debería ser un 32 o más genérico (8*sizeof(uint)).
Justo el operator[] yo no lo haría... El operator[](size_t) const es fácil, podés hacer 
que te retorne un unsigned char por copia. Pero el que no es const, te debería retornar
una referencia a un bit. Para eso tenés que hacer una clase que emule ser la referencia
a un bit y eso sea lo que te retorne (con todos los operadores que ameriten,
principalemente el de asignación, para poder hacer vecbool[0] = 1).
	- Las operaciones a memoria se hacen de word, en algunas arquitecturas trabajar de a bytes
es más costoso. Yo usaría unsigned long
- Como emular una referencia a un bit? Lo que deberías hacer es implementar este prototipo:
http://www.cplusplus.com/reference/bitset/bitset/reference/ Cómo implementarla? Deberías mantener un 
puntero al Vector y el índice. Con eso podés llamar a una setbit(size_t index, bool value) del vector
*/

template<>
class Vector<bool>{
public:
	Vector() : n_bits(0), sz(0), elem(nullptr) {}
	Vector(int sz_);
	~Vector(){delete [] elem;};

	Vector(const Vector &);
	Vector &operator=(const Vector &);
	
	int size(){return n_bits;}     // No retorna realmente size, pero es lo que el usuario esperaria
	
private:
	int n_bits;		// Cantidad de bits
	int sz;			// Tamaño de elem
	unsigned long *elem;
	const unsigned int N = 8*sizeof(unsigned long); // Cantidad de bits que tenemos en un unsigned long
};

Vector<bool>::Vector(int n_bits_) : n_bits(n_bits_), sz(1+n_bits_/N), elem(new unsigned long[sz]) {}

Vector<bool>::Vector(const Vector<bool> &vec) : n_bits(vec.n_bits), sz(vec.sz), elem(new unsigned long[vec.sz]){
    for(int i=0; i < vec.sz; i++)
        elem[i] = vec.elem[i];
}

Vector<bool> &Vector<bool>::operator=(const Vector<bool> &vec){
    unsigned long* aux = new unsigned long[vec.sz];
    for(int i=0; i < vec.sz; i++)
        aux[i] = vec.elem[i];

    delete [] elem;
    elem = aux;
    n_bits = vec.n_bits;
    sz = vec.sz;

    return *this;
}











int main(){
	srand(time(NULL));

    Vector<int> vec(10);
	for(int i=0; i < vec.size(); i++)
        vec[i] = rand() % 10;
	
	printVector(vec);

	// Copy constructor
	Vector<int> vec2 = vec;   
	printVector(vec2);
	
	// Copy assigment
    Vector<int> vec4;
    vec4 = vec2;                                
	printVector(vec4);
}