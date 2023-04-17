#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

// representa la base de una jerarqu�a de expresiones
class Exp{
public:
	virtual ~Exp() {}
	virtual void print() = 0;				// imprime la expresi�n en formato algebraico
	virtual double evaluate(double X) = 0;	// evalua la expresion especializada con var = X
	virtual Exp *derivate() = 0;			// calcula y retorna la expresi�n derivada
	virtual Exp *clone() = 0;				// clona la expresion
};

// representa expresiones constantes
class ConstExp : public Exp{ // constant
public:
	ConstExp(double value_)	: value(value_){}
	void print(){
		cout << value;
	};
	double evaluate(double X)	{ /* ToDo */
		return value;
	}
	Exp *derivate(){ /* ToDo */
		ConstExp *e = new ConstExp(0);
		return e;
	}
	Exp *clone(){ /* ToDo */
		ConstExp *e = new ConstExp(value);
		return e;
	}
private:
	double value;
};

// representa expresiones binarias (+, -, *, /)
class BinaryExp : public Exp{ // PLUS, MINUS, MULT, DIV
public:
	BinaryExp(Exp *e1_, Exp *e2_): e1(e1_), e2(e2_){}
	~BinaryExp(){
		delete e1;
		delete e2;
	}
protected:
	Exp *e1;
	Exp *e2;
};

// representa expresiones unarias (sin, cos, tan)
class UnaryExp : public Exp{ // SIN, COS, TAN
public:
	UnaryExp(Exp *e1_) : e1(e1_) {}
	~UnaryExp(){
		delete e1;
	}
protected:
	Exp *e1;
};

// representa expresiones variables ( X )
class VariableExp : public Exp{ // VARIABLE
public:
	void print(){/* ToDo */
		cout << "X";
	};
	double evaluate(double X){ /* ToDo */
		return X;
	}
	Exp *derivate(){ /* ToDo */
		ConstExp *e = new ConstExp(1);
		return e;
	}
	Exp *clone(){ /* ToDo */
		VariableExp *e = new VariableExp();
		return e;
	}
};

class PlusExp : public BinaryExp{
public:
	PlusExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2) {}
	void print(){/* ToDo */
		e1->print();
		cout << "+";
		e2->print();
	};
	double evaluate(double X){ /* ToDo */
		return e1->evaluate(X) + e2->evaluate(X);
	}
	Exp *derivate(){ /* ToDo */
		PlusExp *e = new PlusExp(e1->derivate(), e2->derivate());
		return e;
	}
	Exp *clone(){ /* ToDo */
		PlusExp *e = new PlusExp(e1->clone(), e2->clone());
		return e;
	}
};

class MinusExp : public BinaryExp{
public:
	MinusExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2) {}
	void print(){/* ToDo */
		e1->print();
		cout << "-";
		e2->print();
	};
	double evaluate(double X){ /* ToDo */
		return e1->evaluate(X) - e2->evaluate(X);
	}
	Exp *derivate(){ /* ToDo */
		MinusExp *e = new MinusExp(e1->derivate(), e2->derivate());
		return e;
	}
	Exp *clone(){ /* ToDo */
		MinusExp *e = new MinusExp(e1->clone(), e2->clone());
		return e;
	}
};

class MultExp : public BinaryExp{
public:
	MultExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2) {}
	void print(){
		cout << "(";
		e1->print();
		cout << ").(";
		e2->print();
		cout << ")";
	};
	double evaluate(double X){ /* ToDo */
		return e1->evaluate(X) * e2->evaluate(X);
	}
	Exp *derivate(){// f*g -> f'*g + f*g'
		MultExp *t1 = new MultExp(e1->derivate(), e2->clone());
		MultExp *t2 = new MultExp(e1->clone(), e2->derivate());
		PlusExp *e = new PlusExp(t1, t2);
		return e;
	}
	Exp *clone(){ /* ToDo */
		MultExp *e = new MultExp(e1->clone(), e2->clone());
		return e;
	}
};

class DivExp : public BinaryExp{
public:
	DivExp(Exp *e1, Exp *e2) : BinaryExp(e1, e2) {}
	void print(){
		cout << "(";
		e1->print();
		cout << ")/(";
		e2->print();
		cout << ")";
	};
	double evaluate(double X){ /* ToDo */
		return e1->evaluate(X) / e2->evaluate(X);
	}
	Exp *derivate(){// f/g -> (f'*g - f*g') / g^2
		MultExp *t1 = new MultExp(e1->derivate(), e2->clone());
		MultExp *t2 = new MultExp(e1->clone(), e2->derivate());
		MinusExp *num = new MinusExp(t1, t2);
		MultExp *den = new MultExp(e2->clone(), e2->clone());
		DivExp *e = new DivExp(num, den);
		return e;
	}
	Exp *clone(){
		DivExp *e = new DivExp(e1->clone(), e2->clone());
		return e;
	}
};

class SinExp : public UnaryExp{
public:
	SinExp(Exp *e1) : UnaryExp(e1) {}
	void print(){
		cout << "sin(";
		e1->print();
		cout << ")";
	};
	double evaluate(double X){
		return sin(e1->evaluate(X));
	}
	// Hay que definirla despues, porque necesitamos el CosExp, que esta declarado mas abajo
	// Este es uno de los casos en donde uno esta obligado a declarar la funcion miembro
	// y definirla despues
	Exp *derivate();
	Exp *clone(){ /* ToDo */
		SinExp *e = new SinExp(e1->clone());
		return e;
	}
};

class CosExp : public UnaryExp{
public:
	CosExp(Exp *e1) : UnaryExp(e1) {}
	void print(){
		cout << "cos(";
		e1->print();
		cout << ")";
	};
	double evaluate(double X){
		return cos(e1->evaluate(X));;
	}
	Exp *derivate(){ // cos(f(x)) -> -1 * sin(f(x)) * f'(x)
		SinExp *seno = new SinExp(e1->clone());
		MultExp *t = new MultExp(seno, e1->derivate());
		MultExp *e = new MultExp(new ConstExp(-1), t);
		return e;
	}
	Exp *clone(){ /* ToDo */
		CosExp *e = new CosExp(e1->clone());
		return e;
	}
};

class TanExp : public UnaryExp{
public:
	TanExp(Exp *e1) : UnaryExp(e1) {}
	void print(){
		cout << "tan(";
		e1->print();
		cout << ")";
	};
	double evaluate(double X){ /* ToDo */
		return tan(e1->evaluate(X));
	}
	Exp *derivate(){ // tan(f(x)) -> [ 1+tan²(f(x)) ] * f'(x) o
					 // tan(f(x)) -> [ 1/cos²(f(x)) ] * f'(x) o 
		MultExp *tan2 = new MultExp(new TanExp(e1->clone()), new TanExp(e1->clone()));
		PlusExp *t1 = new PlusExp(new ConstExp(1), tan2);
		MultExp *e = new MultExp(t1, e1->derivate());
		return e;
	}
	Exp *clone(){ /* ToDo */
		TanExp *e = new TanExp(e1->clone());
		return e;
	}
};

int main(){
	Exp *expr = new DivExp(
		new SinExp( // numerador
			new PlusExp(
				new MultExp(
					new ConstExp(3),
					new VariableExp()),
				new ConstExp(4))),
		new PlusExp( // denominador
			new ConstExp(2),
			new MultExp(
				new ConstExp(3),
				new CosExp(
					new DivExp(
						new VariableExp(),
						new PlusExp(
							new ConstExp(2),
							new VariableExp()))))));

	expr->print();

	double val = expr->evaluate(3.14);

	cout << "\nla Exp evaluada en 3.14 vale: " << val << endl;
	Exp *deriv = expr->derivate();

	deriv->print();

	val = deriv->evaluate(10);

    cout << "\nla Exp dereivada en 3.14 vale: " << val << endl;

	delete deriv;
	delete expr;

	return 0;
}

Exp *SinExp::derivate(){ // sin(f(x)) -> cos(f(x)) * f'(x)
	MultExp *e = new MultExp(new CosExp(e1->clone()), e1->derivate());
	return e;
}

// Con amor, Cabre.