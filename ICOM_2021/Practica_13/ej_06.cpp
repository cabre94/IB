#include <iostream>
#include <ctime>
#include <queue>
// https://www.cplusplus.com/reference/queue/queue/

template<class T>
class Queue {
public:
	// coloca un nuevo elemento en la cola
	void put(T e){
		elts.push(e);
	}
	// retira el elemento más antiguo de la cola
	T get(){
		T oldest_elem = elts.front();
		elts.pop();
		return oldest_elem;
	};
	// retorna la cantida de elementos contenidos
	unsigned int size(){
		return elts.size();
	}
private:
	std::queue<T> elts; // a definir
};


int main(){
	srand(time(0));

	Queue<int> queue_int;
	int x;

	for(int i=0; i < 5; ++i){
		x = rand() % 100;
		queue_int.put(x);
		std::cout << "Agregue " << x << std::endl;
	}

	while(queue_int.size()){
		std::cout << "Saco " << queue_int.get();
		std::cout << ". La cola quedo con " << queue_int.size() << " elementos." << std::endl;
	}

	return 0;
}