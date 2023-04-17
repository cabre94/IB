/*
date: 16-09-2020
File: ej_.cpp
Author : Facundo Martin Cabrera
Email: cabre94@hotmail.com facundo.cabrera@ib.edu.ar
GitHub: https://github.com/cabre94
GitLab: https://gitlab.com/cabre94
Description:
*/

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <sstream>

class Traveler{
private:
    std::string str;
    
public:
    Traveler(std::string str_);	//Ordinary constructor
    Traveler(const Traveler &t);	//Copy constructor
    Traveler(Traveler &&t);	//Move constructor
    Traveler &operator=(const Traveler &);	//Copy assignment
    Traveler &operator=(Traveler &&);	// Move assignment
    ~Traveler(){}
};

Traveler::Traveler(std::string str_) : str(str_) {
    std::cout << "Traveler - Ordinary Constructor" << this << std::endl;
}

Traveler::Traveler(const Traveler &t) : str(t.str){
    std::cout << "Traveler - Copy constructor " << this << std::endl;
}

Traveler::Traveler(Traveler &&t) : str(std::move(t.str)) {
    std::cout << "Traveler - Move constructor " << this << std::endl;
}

Traveler &Traveler::operator=(const Traveler &t){
    std::cout << "Traveler - Copy assigment " << this << std::endl;
    str = t.str;
    return *this;
}

Traveler &Traveler::operator=(Traveler &&t){
    std::cout << "Traveler - Move assigment " << this << std::endl;
    str = t.str;
    return *this;
}



class Pager{
private:
    std::string str;
    
public:
    Pager(std::string str_);	//Ordinary constructor
    Pager(const Pager &t);	//Copy constructor
    Pager(Pager &&t);	//Move constructor
    Pager &operator=(const Pager &);	//Copy assignment
    Pager &operator=(Pager &&);	// Move assignment
    ~Pager(){}
};

Pager::Pager(std::string str_) : str(str_) {
    std::cout << "Pager - Ordinary Constructor " << this << std::endl;
}

Pager::Pager(const Pager &t) : str(t.str){
    std::cout << "Pager - Copy constructor " << this << std::endl;
}

Pager::Pager(Pager &&t) : str(std::move(t.str)) {
    std::cout << "Pager - Move constructor " << this << std::endl;
}

Pager &Pager::operator=(const Pager &t){
    std::cout << "Pager - Copy assigment " << this << std::endl;
    str = t.str;
    return *this;
}

Pager &Pager::operator=(Pager &&t){
    std::cout << "Pager - Move assigment " << this << std::endl;
    str = t.str;
    return *this;
}


class BusinessTraveler : public Traveler{
private:
    Pager p;
public:
    BusinessTraveler() : p{""}, Traveler{""} {}
    BusinessTraveler(std::string str1, std::string str2) : p{str1}, Traveler{str2} {}

    BusinessTraveler(const BusinessTraveler &bt);	//Copy constructor
    BusinessTraveler(BusinessTraveler &&bt);	//Move constructor
    BusinessTraveler &operator=(const BusinessTraveler &);	//Copy assignment
    BusinessTraveler &operator=(BusinessTraveler &&);	// Move assignment
    ~BusinessTraveler(){}

};

// BusinessTraveler::BusinessTraveler(const BusinessTraveler &bt) p(bt.p), Traveler()    {}
BusinessTraveler::BusinessTraveler(const BusinessTraveler &bt) : Traveler(bt), p(bt.p){
    std::cout << "BusinessTraveler - Copy Constructor " << this << std::endl;
}

BusinessTraveler::BusinessTraveler(BusinessTraveler &&bt) : Traveler(std::move(bt)), p(std::move(bt.p)){
    std::cout << "BusinessTraveler - Move constructor " << this << std::endl;
}

BusinessTraveler &BusinessTraveler::operator=(const BusinessTraveler &bt){
    std::cout << "BusinessTraveler - Copy assigment " << this << std::endl;
    Traveler::operator=(bt);
    p = bt.p;
    return *this;
}

BusinessTraveler &BusinessTraveler::operator=(BusinessTraveler &&bt){
    std::cout << "BusinessTraveler - Move assigment " << this << std::endl;
    Traveler::operator=(std::move(bt));
    p = std::move(bt.p);
    return *this;
}





int main(int argc, const char** argv){

    BusinessTraveler kk("Boca", "Juniors");

    BusinessTraveler kk2 = kk;
    BusinessTraveler kk3 = std::move(kk);
    


    return 0;
}