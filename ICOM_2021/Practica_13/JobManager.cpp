#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

// define la abstracción de un Job. 
// Cada Job tendrá un nombre y un método "run" que realiza el trabajo específico.
class Job {
    public:
        Job(const string &tname) : name(tname) {}
        virtual ~Job() {}

        virtual void run() = 0;

        string getName() { return name; }

    protected:
        string name;
};

// implementa un administrador de Jobs. 
// internamente mantiene los jobs registrados en una cola de punteros a Jobs.
class JobManager{
    public:
        // agrega un job a la cola de jobs pendientes
        void addJob(Job *job) {
            // ToDo
        }

        // remueve y retorna el job mas antiguo. Retorna nullptr si no hay mas jobs pendientes. 
        Job *getJob() {
            // ToDo
            return nullptr;
        }

    private:
        //  ToDo
};

// entidad que ejecuta jobs tomados desde un JobManager pasado en la construcción del objeto
class Worker {
    public:

        Worker(JobManager *jm) {
            // ToDo
        }

        // esta función deberá tomar Jobs desde el JobManager e ir ejecutandolos
        // hasta que no existan mas Jobs que procesar.
        void start() {
            // ToDo
        }

    private:
        // ToDo
};

///////////////////////////////////


// Job que aproxima e imprime el valor de Pi siguiendo la serie numérica propuesta por Leibniz (ejercicio 3, práctica 4)
// la cota de error deseado se pasa como argumento al constructor de la clase.
class PiJob : public Job {
    public:
        PiJob(double error) : Job("Calcula Pi por Leibniz"), cotaError(error) {}

        void run() {
            // ToDo
        }

    private:
        double cotaError;
};


// Job que aproxima e imprime el valor de la raiz cuadrada de un número siguiendo el algoritmo del ejercicio 4 de la práctica 4
// El valor y la cota de error deseado se pasa como argumento al constructor de la clase.
class SqrtJob : public Job {
    public:
        SqrtJob(double valor_, double error) : Job("Calculo aproximado de sqrt"), valor(valor_), cotaError(error) {}

        void run() {
            // ToDo
        }
    private:
        double valor;
        double cotaError;

};

// Job que se ejecuta durante una cantidad dada de tiempo (segundos) e imprime el valor del tiempo cada segundo
// La cantidad de segundos que durará la ejecución se pasa como argumento al constructor de la clase.
// ver aclaración (2) en el práctico.
class TimerJob : public Job {
    public:
        TimerJob(unsigned int t) : Job("Timer"), timeToRun(t) {}

        void run() {
            // ToDo
        }

    private:
        unsigned int timeToRun;
};


int main()
{
    JobManager jm;
    Worker w(&jm);

    PiJob pi1(0.1), pi2(0.00001);
    SqrtJob sq1(100, 0.0001), sq2(1524, 0.000001), sq3(49, 0.00001);
    TimerJob t1(5), t2(7);

    jm.addJob(&pi1);
    jm.addJob(&t1);
    jm.addJob(&pi2);
    jm.addJob(&sq1);
    jm.addJob(&sq2);
    jm.addJob(&sq3);
    jm.addJob(&t2);

    w.start();


}
