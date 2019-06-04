#include "voce.h"
#include <algorithm> // std::swap
#include <iostream>
#include <iterator>
voce::voce() 
	: nome(""), cognome(""), ntel("") {
}

voce::voce(const std::string &n,
			 const std::string &c,
			 const std::string &nt) :
	nome(n), cognome(c), ntel(nt) {}

voce::voce(const voce &other) :
	nome(other.nome), 
	cognome(other.cognome), 
	ntel(other.ntel) { }

voce& voce::operator=(const voce &other) {
	if(this != &other) {
		voce tmp(other);
		tmp.swap(*this);
		//nome = other.nome;
		//cognome = other.cognome;
		//ntel = other.ntel;
	}

	return *this;
}

voce::~voce() {
	
}

void voce::swap(voce &other) {
	std::swap(nome,other.nome);
	std::swap(cognome,other.cognome);
	std::swap(ntel,other.ntel);
}

bool voce::operator==(const voce &other) const {
	return (this->nome == other.nome && 
			 this->cognome == other.cognome && 
			 this->ntel == other.ntel);
			 
}
//Totally inefficient
bool voce::operator>(const voce&other) const{

	std::string::const_iterator begin=nome.begin();
	std::string::const_iterator end=nome.end();
	std::string::const_iterator beginO=other.nome.begin();
	std::string::const_iterator endO=other.nome.end();
	
	for(;(*begin)!=(*beginO) && (begin<end) && (beginO<endO);++begin,++ beginO)
		if(*begin > *beginO)
			return 1;
		else
			if(*begin < *beginO)
				return 0;
	
	std::string::const_iterator beginC=cognome.begin();
	std::string::const_iterator endC=cognome.end();
	std::string::const_iterator beginCO=other.cognome.begin();
	std::string::const_iterator endCO=other.cognome.end();
	
	// std::cout<<"Passed";
	
	for(;(*beginC)!=(*beginCO) && (beginC<endC) && (beginCO<endCO);++beginC,++beginCO)
		if(*beginC > *beginCO)
			return 1;
		else
			if(*beginC < *beginCO)
				return 0;	
	std::string::const_iterator beginT=ntel.begin();
	std::string::const_iterator endT=ntel.end();
	std::string::const_iterator beginTO=other.ntel.begin();
	std::string::const_iterator endTO=other.ntel.end();
	
	for(;(*beginT)!=(*beginTO) && (beginT<endT) && (beginTO<endTO);++beginT,++beginTO)
		if(*beginT > *beginTO)
			return 1;
		else
			if(*beginT < *beginTO)
				return 0;
	
	return 0;
}

bool voce::operator<(const voce &other) const{

	std::string::const_iterator begin=nome.begin();
	std::string::const_iterator end=nome.end();
	std::string::const_iterator beginO=other.nome.begin();
	std::string::const_iterator endO=other.nome.end();
	
	for(;(*begin)!=(*beginO) && (begin<end) && (beginO<endO);++begin,++ beginO)
		if(*begin < *beginO)
			return 1;
		else
			if(*begin > *beginO)
				return 0;
	
	std::string::const_iterator beginC=cognome.begin();
	std::string::const_iterator endC=cognome.end();
	std::string::const_iterator beginCO=other.cognome.begin();
	std::string::const_iterator endCO=other.cognome.end();
	
	// std::cout<<"Passed";
	
	for(;(*beginC)!=(*beginCO) && (beginC<endC) && (beginCO<endCO);++beginC,++beginCO)
		if(*beginC < *beginCO)
			return 1;
		else
			if(*beginC > *beginCO)
				return 0;	
	std::string::const_iterator beginT=ntel.begin();
	std::string::const_iterator endT=ntel.end();
	std::string::const_iterator beginTO=other.ntel.begin();
	std::string::const_iterator endTO=other.ntel.end();
	
	for(;(*beginT)!=(*beginTO) && (beginT<endT) && (beginTO<endTO);++beginT,++beginTO)
		if(*beginT < *beginTO)
			return 1;
		else
			if(*beginT > *beginTO)
				return 0;
	
	return 0;
	
	
	
	
}

std::ostream &operator<<(
	std::ostream &os,const voce &v) {

	os << "[" << v.nome <<" , " 
		<< v.cognome << " , " 
		<< v.ntel << "]";

	return os;
}




