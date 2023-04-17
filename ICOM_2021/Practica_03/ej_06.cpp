#include <iostream>

using namespace std;

int main(){
	char c;

	while( (c = cin.get()) != EOF){
		if(c == '('){
			while(c != EOF && c != ')'){
            	c = cin.get();
            }
            c = cin.get();
		}
        cout.put(c);
	}

    return 0;
}
