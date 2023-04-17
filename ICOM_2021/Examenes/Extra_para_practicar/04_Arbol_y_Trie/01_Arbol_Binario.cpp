/*
date: 27-10-21
File: 01_Arbol_Binario.cpp
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description:
*/

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class TreeNode{
public:
	TreeNode(int v) : value(v), left(nullptr), right(nullptr){};
	~TreeNode() { delete left; delete right;}
	void addNode(int v); 		// ToDo
	void print(); 				// ToDo
	unsigned numNodes() const; 	// ToDo
	unsigned height() const; 	// ToDo
	bool exist(int v); 			// ToDo
private:
	int value;
	TreeNode *left;
	TreeNode *right;

	void printBT(const string& prefix, bool isLeft);
};

int main(){
	static const int NUM_VALUES = 10;
	static const int MAX_VAL = 20;

	srand(time(nullptr));

	TreeNode t(rand() % MAX_VAL);
	for (int i = 0; i < NUM_VALUES; ++i)
		t.addNode(rand() % MAX_VAL);

	t.print();
	
	int n = t.numNodes();
	assert(n == NUM_VALUES+1);

	cout << "La altura es: " << t.height() << endl;

	// int test[] = {43, 21, 655, 125, 3211, 2244, 4432, 7621, 1234, 4367};
	int test[] = {4, 8, 15, 16, 23, 42};
	for (auto s : test)
		cout << "Existencia de " << s << " en el arbol: " << t.exist(s) << endl;

	return 0;
}

// Definiciones
void TreeNode::addNode(int v){
	if(v < value){
		if(left == nullptr)
			left = new TreeNode(v);
		else
			left->addNode(v);
	}else{
		if(right == nullptr)
			right = new TreeNode(v);
		else
			right->addNode(v);
	}
}

void TreeNode::print(){
	printBT("", false);
}

unsigned TreeNode::numNodes() const{
	if(this == nullptr)
		return 0;
	return 1 + left->numNodes() + right->numNodes();
}

unsigned TreeNode::height() const{
	cout << value << endl;	// Esto se va a romper
	height();				// Esto tambien
	if(this == nullptr)
		return 0;
	unsigned h_l = left->height();
	unsigned h_r = right->height();
	return 1 + ((h_l > h_r) ? h_l : h_r);
}

bool TreeNode::exist(int v){
	if(this == nullptr)
		return false;
	if(value == v)
		return true;
	if(v < value)
		return left->exist(v);
	return right->exist(v);
}

// Me copie y adapte esta version de la print sacada de internet que me gusto
void TreeNode::printBT(const std::string& prefix, bool isLeft){
    if(this != nullptr){
        cout << prefix;

        cout << (isLeft ? "├─" : "└─" );

        // print the value of the node
        cout << this->value << endl;

        // enter the next tree level - left and right branch
		left->printBT(prefix + (isLeft ? "│   " : "    "), true);
		right->printBT(prefix + (isLeft ? "│   " : "    "), false);
    }
}