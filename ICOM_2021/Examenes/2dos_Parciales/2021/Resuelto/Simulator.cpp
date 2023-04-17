#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

// Define una variable de un modelo, por simplicidad se soporta un solo tipo de variable.
class Variable{
public:
	Variable(const string &vname, double initValue = 0) : varName(vname), varValue(initValue) {}
	double getValue() const {return varValue;} // TODO
	void setValue(double v) {varValue = v;} // TODO
	string getName() {return varName;}
private:
	string varName;
	double varValue;
};

// Define un administrador de variables. Todas las variables on pontencial intercambio
// entre modelos debe ser registrada en este Manager
class VarManager{
public:
	void registerVar(Variable *v){
		auto ret = vars.insert(pair<string, Variable *>(v->getName(), v) );
		assert(ret.second);
	}				  // TODO
	Variable *getVariable(const string &varName) const {
		for(auto it = vars.begin(); it != vars.end(); ++it){
			if(it->first == varName)
				return it->second;
		}
		throw string("No encontre la variable");
	} // TODO
	const list<const Variable *> getAllVariables(){
		list<const Variable *> var_list;

		for(auto it = vars.begin(); it != vars.end(); ++it){
			var_list.push_back(it->second);
		}

		return var_list;
	} // TODO
private:
	map<string, Variable *> vars;
};

// Define la interface que debe satisfacer todo modelo en la simulaci�n
class Model{
public:
	Model(const string &modelName) : name(modelName) {}
	virtual ~Model() {};
	// m�todo que d� oprtunidad al modelo a que registre todas las variables propiad
	virtual void create(VarManager &) = 0;
	// m�todo que d� la oportunidad de "attacharse" a variables de otros modelos, a trav�s del nombre
	virtual void connect(const VarManager &) = 0;
	// m�todo que d� la oportunidad de destruir/liberar todos los recursos con que cuenta el modelo
	virtual void destroy() = 0;
	// m�todo que solicita al modelo que avance un paso en la simulaci�n, actualizando sus variables propias
	virtual void doStep(uint64_t currT) = 0;
protected:
	string name; // nombtre del modelo
};

// modelo ejemplo que deber�a modelar un grifo    // TODO
class Grifo : public Model{
public:
	Grifo(const string &name) : Model(name){}
	~Grifo(){destroy();}
	void create(VarManager &varMan){
		varGrifo = new Variable("var" + name);
		varMan.registerVar(varGrifo);
	}
	void connect(const VarManager &varMan){
		Variable* var = varMan.getVariable("varTanque");
		cout << name << " usa " << var->getName() << endl;
	}
	void destroy(){delete varGrifo;}
	void doStep(uint64_t currT){
		varGrifo->setValue(varGrifo->getValue()+1);
		cout << name << endl;
	}
private:
	Variable* varGrifo;
};

// modelo ejemplo que deber�a modelar un tanque    // TODO
class Tanque : public Model{
public:
	Tanque(const string &name) : Model(name) {}
	~Tanque(){destroy();}
	void create(VarManager &varMan){
		varTanque = new Variable("var" + name);
		varMan.registerVar(varTanque);
	}
	void connect(const VarManager &varMan){
		Variable* var = varMan.getVariable("vargrifo");
		cout << name << " usa " << var->getName() << "?" << endl;
	}
	void destroy(){delete varTanque;}
	void doStep(uint64_t currT){
		varTanque->setValue(varTanque->getValue()+1);
	}
private:
	Variable* varTanque;
};

// // modelo ejemplo que deber�a modelar una bomba de riego   // TODO
// class BombaRiego : public Model{
// public:
// 	BombaRiego(const string &name) : Model(name) {}
// };

// // modelo ejemplo que deber�a modelar un aspersor  // TODO
// class AspersorRiego : public Model{
// public:
// 	AspersorRiego(const string &name) : Model(name) {}
// };

// // modelo ejemplo que satisface la interface Model, perop que solo monitorea el estado de todas las variables.
// // // TODO
// class FakeModelMonitor : public Model{
// public:
// 	FakeModelMonitor(const string &name) : Model(name) {}
// };

// Modela un contexto de simulaci�n, donde los modelos se registran y hay un scheduler que
// controla la evoluci�n sincr�nica de mos modelos.
class Simulator{
public:
	Simulator() : models{}, currTime(0), varMgr{}, sched{models} {}				  // TODO
	void registerModel(Model *m){
		models.push_back(m);
	} // TODO
	void prepare(){
		// sched = Scheduler(models);
		for(size_t i=0; i < models.size(); i++){
			models[i]->create(varMgr);
		}
	}				  // TODO

	void simulate(uint64_t duration){
		currTime += duration;
		sched.doStep(currTime);
	} // TODO

private:
	// controla la evoluci�n de todos los modelos en forma sincr�nica
	class Scheduler{
	public:
		Scheduler(vector<Model *> &models_) : models(models_) {} // TODO
		void doStep(uint64_t t){
			for(size_t i=0; i < models.size(); i++){
				models[i]->doStep(t);
			}
		} // TODO
	private:
		vector<Model *> &models;
		// const vector<Model *> &models;
	};
	vector<Model *> models;
	uint64_t currTime = 0;

	VarManager varMgr;
	Scheduler sched;
};

int main(){

	Simulator simulator;
	simulator.registerModel(new Grifo("grifo"));
	simulator.registerModel(new Tanque("Tanque"));
	// simulator.registerModel(new BombaRiego("Bomba"));
	// simulator.registerModel(new AspersorRiego("Aspersor1"));
	// simulator.registerModel(new AspersorRiego("Aspersor2"));
	// simulator.registerModel(new AspersorRiego("Aspersor3"));
	// simulator.registerModel(new AspersorRiego("Aspersor4"));
	// simulator.registerModel(new FakeModelMonitor("Monitor"));

	simulator.prepare();

	simulator.simulate(10000);

	return 0;
}
