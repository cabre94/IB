#include <iostream>
#include <cstdint>
#include <cassert>
#include <new>
#include <algorithm>

using namespace std;

// Suponga que está diseñando una clase que será instanciada múltiples veces,
// pero que por diseño, nunca habrá más de N instancias simultáneas.
// Sobrecargue los operadores new y delete para esta clase para que utilicen
// un mecanismo eficiente de alocación (sin fragmentación y con costo
// constante).

// Para hacer una alocación con costo constante, vamos a implementar un
// buffer de tamaño suficiente para contener todas las posibles intancias
// de la clase y vamos a hacer una free list que mantenga los objetos libres
// disponibles. Esta free list opera como un stack. Al alocar se busca el
// espacio disponible primero en la lista y al liberar se pone ese lugar
// en la cabeza de la lista.
// La free list la vamos a hacer con índices sobre un arreglo, no con punteros.

class X {
    public:
        // Cantidad mácima de instancias de la clase
        static const size_t N = 10;

        // Vamos a permitir los operadores new y delete en sus versiones
        // que hacen throw bad_alloc y las que retornan nullptr sin excepciones
        void *operator new(size_t bytes);
        void operator delete(void *ptr);
        void* operator new(size_t, const nothrow_t&) noexcept;
        void operator delete(void*, const nothrow_t&);

        // Vamos a prohibir todas las versiones de new y delete que
        // permitirían alocar arreglos de más de una instancia
        void *operator new[](size_t bytes) = delete;
        void operator delete[](void *ptr) = delete;
        void* operator new[](size_t, const nothrow_t&) = delete;
        void operator delete[](void*, const nothrow_t&) = delete;
        void* operator new(size_t, void* ) = delete;
        void* operator new[](size_t, void*) = delete;
        void operator delete(void*, void*) = delete;
        void operator delete[](void*, void*) = delete;

        // Constructor que no dispara excepciones. Necesaria esta salvedad
        // para garantizar que el new sin excepciones realmente no tire
        // excepciones y retorne nullptr. (La versión del new que no throwea
        // puede llegar a throwear si el constructor lo hace)
        X() noexcept {
            cout << "X hello " << getId() << " @ " << this << endl;
        }

        // Método estático (de clase) para destruir un objeto
        // Es necesario porque el destructor es privado y es llamado
        // automáticamente por el operador delete (y cuando una variable
        // sale de scope). Así que llamaremos al delete desde una función
        // miembro estática que si puede acceder al destructor
        static void destroy(X *x) {
            delete x;
        }

        // Método que retorna cuál de las N instancias posibles es
        ssize_t getId() const;

    private:
        // Destructor privado. Al ser privado evita que se puedan instanciar
        // objetos (de stack, en arreglos, como miembros de otras clases
        // o derivados)
        ~X() {
            cout << "X bye " << getId() << " @ " << this << endl;
        }

        // Prohibo asignación y construcción copia y move
        X &operator=(X) = delete;
        X(const X&) = delete;
        X(X&&) = delete;

        // Miembro del objeto. Nada especial, una cantidad de bytes
        // Se puede probar poniendo OBJ_MEMBER_SIZE8 en 1 o 2,
        // siendo esto más chico que sizeof(ssize_t) utilizado para índice
        // también funciona
        static const size_t OBJ_MEMBER_SIZE8 = 2345;
        char member[OBJ_MEMBER_SIZE8];

        // Declaración del buffer estático (de clase, compartido por todos
        // los objetos) donde van a ser alocadas las intancias
        static uint8_t heapBuffer[];

        // Índice del primer elemento libre en la lista de objetos disponibles
        // Esto es un valor en [0:N). Si no hay instancias disponibles va tomar
        // el valor FL_INVALID (-1) (ver a continuación). 
        static ssize_t freeListHead;

        // Constante que dice que no hay más elementos en la lista
        // similar al NULL al final de un último elemento en una lista con punteros
        static const ssize_t FL_INVALID = -1;

        // Función auxiliar que va a ser llamada desde las dos versiones
        // de operator new, la que throwea bad_alloc y la nothrow
        static void *new_helper(size_t bytes);

        // Miembro estático auxiliar que tiene un constructor.
        // Al ser un miembro estático, es construido antes inclusive
        // de que se llame a main. Así nos garantizamos que su constructor
        // sea llamado al origen de los tiempos y nos va a permitir inicializar
        // la free list
        static struct HeapInitializer {
            HeapInitializer();
        } heapInitializer;

};

// unnamed namespace, sus internals son solo visibles desde este archivo.
namespace {

// Definición de una unión entre un índice y un objeto de la clase X
// Por qué hace falta? Cuando el espacio de un objeto no esté en uso,
// o sea libre, vamos a poner ahí el índice del siguiente libre.
// Qué pasaría si el sizeof(X) es menor que sizeof(ssize_t)?
// Respuesta: estaríamos pisando memoria. Así que nos tenemos que garantizar
// poder guardar un índice. Con una unión logramos esto. El tamaño de la unión
// va a ser el máximo entre sizeof(X) y sizeof(ssize_t).
union Link {
    X x;
    ssize_t next_free_idx;
};

// Ponemos un puntero a link, que va a ser nuestro heap.
// Originalmente en nullptr. El contructor de heapInitializer lo va
// a apuntar a un buen lugar (al primer libre)
// Es conveniente para no hacer casts en todas la funciones
Link *heap = nullptr;

} // unnamed namespace

// Este es el buffer para tener todos los objetos permitidos
// Lo hacemos de los bytes suficientes para guardar N Links
// Esto es por si sizeo(X) es menor que sizeof(ssize_t)
uint8_t X::heapBuffer[X::N * sizeof(Link)];

// Originalmente el índice el primer objeto disponible está en inválido (-1)
// El con
ssize_t X::freeListHead = X::FL_INVALID;

// Definición del miembro estático heapInitializer
X::HeapInitializer X::heapInitializer;

// Constructor del miembro estático heapInitializer
// Al ser un miembro estático, es construido antes inclusive
// de que se llame a main. Así nos garantizamos que su constructor
// sea llamado al origen de los tiempos y nos va a permitir inicializar
// la free list
// La idea es contruir una lista (también se puede ver como un stack)
// de los buffers de objetos disponibles
X::HeapInitializer::HeapInitializer()
{
    // Inicializamos el puntero heap a la cabeza de buffer para contener
    // todas las instancias. Lo hacemos como un Link por el tema de tamaños
    // de X vs el del índice (ssize_t)
    heap = (Link *) X::heapBuffer;

    // Recorremos todos los links menos el último de nuestro buffer
    // y decimos que el próximo siguiente es el siguiente
    for( size_t i = 0; i < N-1; ++i )
        heap[i].next_free_idx = i + 1;

    // El siguiente del último es inválido. Significa que no hay más en la
    // lista de elementos libres
    heap[N-1].next_free_idx = FL_INVALID;
    
    // Ponemos que la cabeza de elementos libres es el primero
    X::freeListHead = 0;

    // De esta manera, la cabeza de la free list tiene el índice del
    // primer elemento. Los otros tienen el índice del siguiente y
    // el último tiene un índice inválido (FL_INVALID == -1)
}

// Versión del operator new que throwea bad_alloc
// Llama al helper y si retorna nullptr throwea bad_alloc
void *X::operator new(size_t bytes)
{
    // cout << "X::new ";

    void *ptr = new_helper(bytes);

    if( ptr == nullptr )
        throw bad_alloc{};

    return ptr;
}

// Versión del operator new que no throwea y retorna nullptr si falla
void *X::operator new(size_t bytes, const nothrow_t&) noexcept
{
    // cout << "X::new nothrow ";
    return new_helper(bytes);
}

// Helper de alocación utilizado por las dos versiones de operator new.
// Retorna nullptr si no hay 
inline void *X::new_helper(size_t bytes)
{
    // Me aseguro que me manden a alocar lo que espero...
    // Brujas no hay, pero...
    assert(bytes == sizeof(X));

    // cout << "X::new_helper, flh: " << freeListHead << endl;
    
    // Inicializo lo que voy a retornar con nullptr
    Link *pl = nullptr;

    // Si la cabeza de la lista no es inválida (o sea, quedan elementos libres)
    if( freeListHead != FL_INVALID ) {
        // El link que tengo que devolver es el de índice freeListHead,
        // el primero libre en lista de libres
        pl = heap + freeListHead;

        // Actualizo la cabeza de la lista de libres con el siguiente
        freeListHead = pl->next_free_idx;
    }

    // Retorno. nullptr si no había disponibles o el primero disponible.
    return pl;
}

// Operator delete. Tengo que poner el objeto que estoy destruyendo
// a la cabeza de lista de espacio libre de objetos
void X::operator delete(void *p)
{
    // cout << "X::delete, flh: " << freeListHead << endl;
    
    // Casteo el objeto a liberar a un Link
    Link *pl = (Link *) p;

    // Pongo como siguiente disponible a este objeto el que estaba en la
    // cabeza de la lista de libre
    pl->next_free_idx = freeListHead;

    // Pongo como índice de la cabeza de libres a este objeto liberado
    freeListHead = pl - heap;
}

// Función que me da el índice de un objeto.
// La diferencia "en Links" entre el objeto y el inicio del buffer
inline ssize_t X::getId() const {
    return (Link *) this - heap;
}

// Este destructor nunca es llamado, solo por completitud
void X::operator delete(void* p, const nothrow_t& nt)
{
    // cout << "X::op delete nt, flh: " << freeListHead << endl;
    return operator delete(p);
}

// Ejercito el alocador
int main()
{
    // Arreglo de punteros a X
    const int MAX_REQ = 70;
    X *ptrs[MAX_REQ];

    // Imprimo
    cout << "sizeof Link: " << sizeof(Link) << endl;
    cout << "sizeof X: " << sizeof(X) << endl;
    cout << "sizeof ssize_t: " << sizeof(ssize_t) << endl;

    // Esto da un error porque el destructor es privado
    // X xinstance; //! Error porque ~X es privado

    // Cantidad de iteraciones del loop de prueba
    const int NUM_PRUEBAS = 3;

    // Loop de prueba
    for( int i = 0; i < NUM_PRUEBAS; ++i ) {
        int k;
        // Try/catch para agarrar el bad_alloc de la versión que throwea
        try {
            // Loop de alocación por prueba
            for( k = 0; k < MAX_REQ; ++k ) {
                ptrs[k] = new X;

                // Todo esto está prohibido porque el destructor es privado
                // y/o los operadores de asignación están deleted
                // if( k > 0 ) {
                //     *ptrs[k+1] = *ptrs[k-1];
                //     *ptrs[k] = move(*ptrs[k-1]);
                // }

                // Descomentar lo siguiente y comentar la línea de arriba
                // para probar la version nothrow
                // ptrs[k] = new (nothrow) X;
                // if( ! ptrs[k] )
                //     break;
            }
        } catch( const exception &e ) {
            // Atrapamos cualquier excepción de la STL
            cout << "Exception: " << e.what() << endl;
        }

        // A cuánto llegamos en el loop de alocación
        cout << "Allocamos: " << k << endl;

        // Mezclamos el arreglo de punteros allocados para liberarlos
        // en un orden aleatorio
        random_shuffle(ptrs, &ptrs[k]);

        // Libero todos los puntero alocados utilizando la va función destroy.
        // No puedo utilizar delete simplemente porque el destructor es privado
        while( k-- )
            X::destroy(ptrs[k]);
    }

    // That's all folks...

    return 0;
}