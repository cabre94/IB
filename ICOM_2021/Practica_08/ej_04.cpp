#include <iostream>

using namespace std;


int CompareStrings(const char *str1, const char *str2){
    int i = 0;

    while(str1[i]){
        if(str1[i] > str2[i])
            return 1;
        else if(str1[i] < str2[i])
            return -1;
        i++;
    }

    if(str2[i])
        return -1;
    return 0;
}

int main(){

    char str1[64], str2[64];

    cout << "Ingresar primer string: " << endl;
    cin.getline(str1, sizeof(str1));
    cout << "Ingresar segundo string: " << endl;
    cin.getline(str2, sizeof(str2));

    cout << CompareStrings(str1, str2) << endl;

    return 0;
}

// Con amor, Cabre.