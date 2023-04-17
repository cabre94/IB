#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <queue>
#include <chrono>
#include <thread>

using namespace std;

// define la abstracci�n de un Job. 
// Cada Job tendr� un nombre y un m�todo "run" que realiza el trabajo espec�fico.
class Job {
public:
	Job(const string &tname) : name(tname) {}
	virtual ~Job() {}
	virtual void run() = 0;
	string getName(){return name;}
protected:
	string name;
};

// implementa un administrador de Jobs. 
// internamente mantiene los jobs registrados en una cola de punteros a Jobs.
class JobManager{
public:
	// agrega un job a la cola de jobs pendientes
	void addJob(Job *job){
		jobs.push(job);
	}
	// remueve y retorna el job mas antiguo. Retorna nullptr si no hay mas jobs pendientes. 
	Job *getJob(){
		if(jobs.empty())
			return nullptr;

		Job* last_job = jobs.front();
		jobs.pop();

		return last_job;
	}

private:
	std::queue<Job*> jobs;
};

// entidad que ejecuta jobs tomados desde un JobManager pasado en la construcci�n del objeto
class Worker {
public:

	Worker(JobManager *jm_) : jm(jm_) {}

	// esta funci�n deber� tomar Jobs desde el JobManager e ir ejecutandolos
	// hasta que no existan mas Jobs que procesar.
	void start(){
		Job *job = jm->getJob(); 

		while(job != nullptr){
			job->run();

			job = jm->getJob();
		}
	}

private:
	JobManager *jm;
	// ToDo
};

///////////////////////////////////


// Job que aproxima e imprime el valor de Pi siguiendo la serie num�rica propuesta por Leibniz (ejercicio 3, pr�ctica 4)
// la cota de error deseado se pasa como argumento al constructor de la clase.
class PiJob : public Job {
    public:
        PiJob(double error) : Job("Calcula Pi por Leibniz"), cotaError(error) {}

        void run(){
            int i = 0;
			double pi = 0, previo = 3;

			while(abs(pi - previo) > cotaError){
				previo = pi;

				pi += pow(-1, i) * (4.0/(2*i+1)); 

				i++;
			}

			cout << "Aproximacion de Pi usando metodo de Leibniz y cota ";
			cout << cotaError << endl;
			cout << pi << endl;
        }

    private:
        double cotaError;
};


// Job que aproxima e imprime el valor de la raiz cuadrada de un n�mero siguiendo el algoritmo del ejercicio 4 de la pr�ctica 4
// El valor y la cota de error deseado se pasa como argumento al constructor de la clase.
class SqrtJob : public Job {
public:
	SqrtJob(double valor_, double error) : Job("Calculo aproximado de sqrt"), valor(valor_), cotaError(error) {}

	void run(){
		int i = 1;
		double x_i = 1, x_f = (1+valor)/2;

		while(abs(x_f - x_i) > cotaError){
			x_i = x_f;
			x_f = (x_i + valor/x_i) / 2;
			i += 1;
		}

		cout << "Aproximacion de la raiz de " << valor << " con una cota ";
		cout << cotaError << endl;
		cout << x_f << endl;
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
	TimerJob(unsigned int t) : Job("Timer"), timeToRun(t) {}

	void run(){
		using namespace std::chrono;

		high_resolution_clock::time_point tic, tac;
		tic = high_resolution_clock::now();

		cout << 0 << " s\n";
		for(int i=1; i <= timeToRun; i++){
			this_thread::sleep_for(seconds{1});
			tac = high_resolution_clock::now();
			cout << duration_cast<seconds>(tac-tic).count() << " s\n";
		}
	}
private:
	unsigned int timeToRun;
};


int main(){
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
