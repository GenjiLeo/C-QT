#ifndef VOCE_H
#define VOCE_H

#include <string> // std::string
#include <ostream> // std::ostream

/**
	Struct che rappresenta una voce di una rubrica. Una voce
	e' una terna di valori: <cognome, come, numero_tel>. I valori
	sono di tipo stringa.

	@brief Struct che rappresenta una voce di una rubrica.
*/
struct voce {
	std::string nome;
	std::string cognome;
	std::string ntel;

	/**
		Costruttore di default. Necessario se vogliamo poter
		costruire una voce senza valori particolari. In particolare
		e' l'unico costruttore usabile per poter istanziare un array di voci.
	*/
	voce();

	/**
		Costruttore secondario per avere una voce con dei valori 
		particolari.
		@param n nome del contatto
		@param c cognome del contatto
		@param nt numero telefonico del contatto
	*/
	voce(const std::string &n,
			 const std::string &c,
			 const std::string &nt); 

	/* NOTA: i seguenti metodi fondamentali (assegnamento, copy constructor e distruttore)
	         in questo caso possono non essere definiti in quanto la struct non contiene 
	         puntatori. L'assegnamento, il copy constructor e il distruttore di default 
	         gestiscono correttamente questi dati. Nulla vieta di definirli esplicitamente.
	*/  
	
	/**
		Copy constructor
		@param other voce da usare per creare this
	*/
	voce(const voce &other);

	/**
		Operatore di assegnamento
		@param other voce da cui copiare i dati
	*/
	voce &operator=(const voce &other);

	/**
		Distruttore
	*/
	~voce();

	/**
		Scambia il contenuto di due oggetti voce
		@param other voce il cui contenuto e' scambiato con quello di this
	*/
	void swap(voce &other);

	/**
		Operatore di uguaglianza. Due oggetti voce sono uguali sse
		hanno uguale nome, cognome e ntel
		@param other voce da confrontare con this
		@return true sse le due voci contengono gli stessi valori
	*/
	bool operator==(const voce &other) const;
};

/**
	Ridefinizione dell'operatore << per scivere il contenuto della voce su stream
	@param os stream di output su cui mandare la voce
	@param v voce da spedire sullo stream
	@return il riferimento allo stream di output
*/
std::ostream &operator<<(std::ostream &os,const voce &v);

/*
// Esempio di ridefinizione di un possibile operatore di stream di input 
// per un oggetto voce 
std::istream&operator>>(std::istream &is, voce&v) {

	is >> v.nome; // usiamo l'operatore di stream di input per le stringhe c++
	is >> v.cognome;
	is >> v.ntel;

	return is;
}
*/
#endif 


