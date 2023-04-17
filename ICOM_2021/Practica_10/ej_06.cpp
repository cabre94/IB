#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

/*
En esta version, implemento el Stack para que tenga un tamaño maximo definido
al crear el Stack. El tamaño maximo puede ser distinto para cada Stack.

Si tratamos de hacer un push cuando esta lleno o un pop cuando esta vacio,
lanzamos una excepcion.
*/

class Stack{
public:
	Stack(unsigned int size);
	~Stack();
	
	void push(char c); 	// coloca un nuevo carácter en la pila
	char pop();			// retira el elemento al tope del stack
	
	bool isEmpty();	// retorna true/false indicando si el stack está vacío
	void print();
private:
	char *v;
	size_t top;
	const unsigned int MAX_SIZE;

	// Struct para lanzar excepcion en caso de que este lleno y hagamos push
	struct overflow{};
	// Struct para lanzar excepcion en caso de que este vacio y hagamos pop
	struct underflow{};
};

int main(){
	srand(time(0));
	const char c[] = "abcdefghij";

	Stack s(20);

	for(int i=0; i < 10; i++)
		s.push(c[rand() % 10]);
	
	s.print();

	cout << "Saco un elemento: " << s.pop() << endl;
	cout << "Saco un elemento: " << s.pop() << endl;
	cout << "Saco un elemento: " << s.pop() << endl;
	
	s.print();

	return 0;
}


Stack::Stack(unsigned int size) : v(new char[size]), top(0), MAX_SIZE(size){}

Stack::~Stack(){
	delete [] v;
}

bool Stack::isEmpty(){
	return top == 0;
}

void Stack::print(){
	if(isEmpty()){
		cout << "Stack is Empty";
	}else{
		size_t i;
		for(i=0; i < top-1; i++)
			cout << v[i] << " -> ";
		cout << v[top-1] << endl;
	}
}

void Stack::push(char c){
	if(top == MAX_SIZE)
		throw overflow{};
	v[top++] = c;
}

char Stack::pop(){
	if(isEmpty())
		throw underflow{};
    return v[--top];
}

// Con amor, Cabre.