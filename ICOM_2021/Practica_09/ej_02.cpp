#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Noiserer{
public:
	Noiserer (double minV_, double maxV_){
		minV = minV_;
		maxV = maxV_;
	}
	double operator()(double v){
		// Numero aleatorio entre minV y maxV
		double noise = minV + ((double) rand() / RAND_MAX) * (maxV-minV);
		return v + noise;
	}
private:
	double minV, maxV;
};

int main(){
	srand(time(0));

	std::vector<double> in (10, 0.0);
	std::vector<double> out(in.size());

	transform(in.begin(), in.end(), out.begin(), Noiserer(-1,1));

	cout << "Inicial\tCon ruido" << endl;
	for(int i=0; i < in.size(); i++)
		cout << in[i] << '\t' << out[i] << endl;

	return 0;
}

// Con amor, Cabre.