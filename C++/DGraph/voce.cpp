#include "voce.h"
#include <algorithm> // std::swap

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

std::ostream &operator<<(
	std::ostream &os,const voce &v) {

	os << "[" << v.nome <<" , " 
		<< v.cognome << " , " 
		<< v.ntel << "]";

	return os;
}




