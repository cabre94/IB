#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <deque>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;


// define la abstracci�n de un Job. 
// Cada Job tendr� un nombre y un m�todo "run" que realiza el trabajo espec�fico.
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
        JobManager(){
            num_Jobs = 0;
        }
        // agrega un job a la cola de jobs pendientes
        void addJob(Job *job) {
            JOBS.push_back(job);
            num_Jobs++;
        }

        // remueve y retorna el job mas antiguo. Retorna nullptr si no hay mas jobs pendientes. 
        Job *getJob() {
            if (num_Jobs){
                num_Jobs--;
                Job* a = JOBS.front(); 
                JOBS.pop_front();
                return a;
            }
            return nullptr;
        }

    private:
        deque<Job*>  JOBS; // Puntero a Trabajos
        int num_Jobs;

};

// entidad que ejecuta jobs tomados desde un JobManager pasado en la construcci�n del objeto
class Worker {
    public:

        Worker(JobManager *jm) {
            JOB_M = jm;
            Job_now = nullptr;
        }

        // esta funci�n deber� tomar Jobs desde el JobManager e ir ejecutandolos
        // hasta que no existan mas Jobs que procesar.
        void start() { 
            while(true){
                Job_now = JOB_M -> getJob();
                if(Job_now == nullptr)
                    return;
                Job_now -> run();
            }    
        }

    private:
        JobManager* JOB_M;          // Su administrador correspondiente
        Job* Job_now;               // Trabajo actual     
};

///////////////////////////////////


// Job que aproxima e imprime el valor de Pi siguiendo la serie num�rica propuesta por Leibniz (ejercicio 3, pr�ctica 4)
// la cota de error deseado se pasa como argumento al constructor de la clase.
class PiJob : public Job {  
    public:
        PiJob(double error) : Job("Calcula Pi por Leibniz"), cotaError(error) {};

        void run() {
            int i = 1;
            double pi = 0, pi_anterior;
            
            do{
                pi_anterior = pi;
                pi += 4.0 /i - 4.0 /(2.0+ i);
                i  += 4;
            }while(fabs(pi - pi_anterior) > cotaError);
        }

    private:
        double cotaError;
};


// Job que aproxima e imprime el valor de la raiz cuadrada de un n�mero siguiendo el algoritmo del ejercicio 4 de la pr�ctica 4
// El valor y la cota de error deseado se pasa como argumento al constructor de la clase.
class SqrtJob : public Job {
    public:
        SqrtJob(double valor_, double error) : Job("Calculo aproximado de sqrt"), valor(valor_), cotaError(error) {};

        void run() {
            double X = 1, X_anterior;
            assert(X >= 0);
            if(valor == 0)
                return;
            
            do{     
                X_anterior = X;
                X = (X + valor/X)/2;
            }   while( fabs(X-X_anterior) > cotaError);
        }

    private:
        double valor;
        double cotaError;

};

// Job que se ejecuta durante una cantidad dada de tiempo (segundos) e imprime el valor del tiempo cada segundo
// La cantidad de segundos que durar� la ejecuci�n se pasa como argumento al constructor de la clase.
// ver aclaraci�n (2) en el pr�ctico.
class TimerJob : public Job {
    public:
        TimerJob(unsigned int t) : Job("Timer"), timeToRun(t) {};

        void run() {
            auto t0 = high_resolution_clock::now();
            auto t1 = high_resolution_clock::now();
            for (int i = 0; i < timeToRun; i++){
                t0 = high_resolution_clock::now();
                this_thread::sleep_for(milliseconds{1000});
                t1 = high_resolution_clock::now();
                cout << duration_cast<microseconds>(t1-t0).count() << " usecs\n";
            }
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

    return 0;
}

// Solo falta ver el thread 