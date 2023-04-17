#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;

class TreeNode {
public:
    TreeNode(int v) : value(v), left(nullptr), right(nullptr) {};
    ~TreeNode();                /// ToDo
    void addNode(int v);        /// ToDo
    void print();               /// ToDo
    unsigned numNodes() const;  /// ToDo
    unsigned height() const;    /// ToDo
    bool exist(int v);          /// ToDo
private:
    int value;
    TreeNode *left;
    TreeNode *right;
};
int main()
{
    static const int NUM_VALUES = 5000;
    static const int MAX_VAL = 10000;
    int aux;
    srand(time(nullptr));
    aux = rand() % MAX_VAL;
    TreeNode t(aux);
    cout << "Raiz: " << aux << endl;

    for (int i = 0; i < NUM_VALUES; ++i){
        aux = rand() % MAX_VAL;
        //cout << "Ingreso: " << aux << endl;
        t.addNode(aux);
    }

    t.print();
    int n = t.numNodes();
    assert(n == NUM_VALUES);
    cout << "La altura es: " << t.height() << endl;
    int test[] = { 43, 21, 655, 125, 3211, 2244, 4432, 7621, 1234, 4367 };
    for (auto s : test)
        cout << "Existencia de " << s << " en el arbol:\t" << t.exist(s) << endl;
    return 0;
}

void TreeNode :: addNode(int v){
    if(v < value)
        if(!left)
            left = new TreeNode(v);
        else
            left->addNode(v);
    else
        if(!right)
            right = new TreeNode(v);
        else
            right->addNode(v);
}

void TreeNode :: print(){
    if(left)
        left->print();
    cout << value << endl;
    if(right)
        right->print();
}

TreeNode :: ~TreeNode(){
    delete left;
    delete right;
}

unsigned TreeNode :: numNodes() const{
    unsigned nroNodos = 0;
    if(left)
        nroNodos += (1 + left->numNodes());
    if(right)
        nroNodos += (1 + right->numNodes());
    return nroNodos;
}

unsigned TreeNode :: height() const{
    if(!left && !right)
        return 1;
    if(left && !right)
        return 1 + left->height();
    if(right && !left)
        return 1 + right->height();
    unsigned alt_left = 1 + left->height(), alt_right = 1 + right->height();
    return (alt_left > alt_right) ? alt_left : alt_right;
}

bool TreeNode :: exist(int v){
    if(value == v)
        return true;
    if(left && !right)
        return left->exist(v);
    if(right && !left)
        return right->exist(v);
    if(right && left)
        return left->exist(v) || right->exist(v);
    return false;
}
