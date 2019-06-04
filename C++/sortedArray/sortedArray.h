#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H

#include <ostream>//ostream

#include <iostream>

#include <algorithm>//std::swap

#include <iterator>//std::const_iterator

#include "voce.h"

#include <cstddef>//Won't compile on test server otherwise

/**
@file sortedArray.h
@brief Dichiarazione della classe sortedArray
**/

typedef unsigned int size;

/**
	Eccezione custom lanciata da copy constructor ed iterator constructor
	indica un errore nella creazione dell'oggetto
	
	@brief Eccezione: lanciata da costruttori
*/
struct constructor_Exception: std::exception {};
/**
	Eccezione custom lanciata dalla funzione add
	indica un errore nell'aggiutna di un elemento
	
	
	@brief Eccezione lanciata dalla classe add 
	
*/
struct add_element_exception: std::exception {};
/**
	Eccezione custom lanciata dalla funzione remove e dalla funzione empty
	nel caso in cui si cerchi di rimuovere un elemento non esistente oppure nel caso in cui si
	cerchi di rimuovere un elemento da un sortedArray vuoto
	
	@brief Eccezione lanciata dalla classe remove e empty
	
	
*/
struct remove_element_exception: std::exception {};
/**
	Eccezione custom lanciata dalla funzione getElement quando viene richiesto un elemento 
	non esistente
	
	@brief Eccezione custom lanciata dalla funzione get Element e []
	
*/
struct invalid_parameter_exception: std::exception {};
/**
	Eccezione custom lanciata dalla funzione filter quando si verifica un errore oppure si cerca di 
	filtrare un sortedArray vuoto
	
	@brief Eccezione custom lanciata dalla funzione filter
	
*/
struct filter_exception: std::exception {};

/** @brief  Array di dati generici ordinati

Classe che rappresenta un array di dati generici sempre ordinati
L'array garantisce sempre la presenza di "_size" elementi ordinati secondo
il parametro specificato dall'utente tramite "order"
Sono stati impllementati due iteratori (random,forward) entrambi di tipo const per prevenire
scritture che potrebbero risultare illecite
Il forward iterator restituisce gli elementi in ordine inverso.
 **/
template < typename T, typename Eql, typename order >
  class sortedArray {

    T * data; //Puntatore all'array di tipo T 
    size _size; //Dimensione dell'array
    Eql equalVal; //Funtore di confronto
    order orderBy; //Funtore di ordinamento

    /**
            Metodo che permette il corretto rilascio della memoria.
            invocato dal distruttore e in alcune altre occasioni(add/remove/empty)
			
			@brief Metodo per il corretto rilascio della memoria.
    */
    void clear() {
      _size = 0;
      delete[] data;

      data = 0;

    };
	
	/**
			Metodo per l'inizializzazione e la ri-allocazione della memoria
			Svuota sempre l'array prima di ogni ri-allocazione.
			
			@brief Metodo per la corretta inizializzazione e ri-allocazione della memoria
	*/
    void update(T * newArray, size newSize) {
	clear();
      _size = newSize;
      data = newArray;

    }

    public:
      /**
       Costruttore vuoto, fondamentale.
	   
	   @brief Costruttore di default
    */
      sortedArray() {
        data = 0;
        _size = 0;
      }

	/**
		@brief Copy Constructor
		Copy constructor, fondamentale
		Permette di istanziare un sortedArray da un altro.
		@param other sortedArray da cui inizializzare il nuovo
		@throw constructor_Exception se vi sono problemi durante la copia
	*/
    sortedArray(const sortedArray & other) {
      data = 0;
      _size = 0;

      //try
      try {
        for (size i = 0; i < other._size; ++i)
          add(other.data[i]);
      } catch (...) {
        clear();
        throw constructor_Exception();
      }
      //catch clear

    }
	/**
		@brief Costruttore basato su iteratori generici
		
		Costruttore che inizializza un nuovo sortedArray basandosi su due iterator
		@param begin iteratore che indica l'inizio della struttura su cui iterare
		@param end iteratore che indica la fine della struttura su cui iterare
		@throw constructor_Exception se vi sono problemi durante la copia
	*/

    template < typename IT >
      sortedArray(IT begin, IT end) {
        data = 0;
        _size = 0;
        //TryCatch
        try {
          for (; begin != end; ++begin) {
            add(static_cast < T > ( * begin));
          }
        } catch (...) {
          clear();
          throw constructor_Exception();
        }
      }
	/**
		@brief Distruttore della classe
		
		Distruttore della classe, libera la memoria invocando clear()
		
	*/
      ~sortedArray() {
        clear();
      }
	/**
		@brief Operatore di assegnamento
		
		Operatore di assegnamento, fondamentale
		@param other sortedArray sorgente
		@return Riferimento a this
		
	*/
    sortedArray & operator = (const sortedArray & other) {

      sortedArray tmp(other);
      ( * this).swap(tmp);

    }
	/** 
		@brief overload della funzione swap
		
		Overload della funzione std swap
		@param other sortedArray con cui eseguire lo swap
		@return Riferimento a this
	*/
    sortedArray swap(sortedArray & other) {

      if ( & other != this) {
        sortedArray tmp(other);
        std::swap(data, tmp.data);
        std::swap(_size, tmp._size);
      }

      return *this;
    }
	/**
		@brief funzione per permettere l'aggiunta di un dato di tipo T
		
		funzione per permettere l'aggiunta di un dato di tipo T,
		il dato viene inserito su un array(standard) nell'ordine desiderato.
		il sortedArray rilascia poi i dati correntemente contenuti e punta ai nuvoi dati
		
		@param id valore di tipo T
		@throw add_element_exception nel caso in cui si verifichino degli errori durante l'aggiunta
	*/
    void add(const T & id) {  
	  try {
        T* tempArray = new T[_size + 1]();

        bool insrt = false;
        for (size i = 0; i <= _size; ++i)
          if (!insrt) {
            if (_size == 0 || i == _size)
              tempArray[i] = id;
            else {
              if (orderBy(id, data[i])) {
                tempArray[i] = id;
                insrt = true;
              } else
                tempArray[i] = data[i];
            }
          }
        else { //already Inserted
          tempArray[i] = data[i - 1];
        }

        update(tempArray, _size + 1);
      }catch (...) {
        clear();

        throw add_element_exception();
      }
    }
	/**
		@brief Funzione per la rimozione di un elemento
		
		Funzione per la rimozione di un elemento, simile all'utilizzo della add:
		Viene creato un array(standard) nel quale sono copiati i valori da NON rimuovere
		il sortedArray rilascia poi i nostri dati attuali per puntare ai nuovi dati.
		
		@param id dato di tipo T da rimuovere
		@throw remove_element_exception nel caso in cui l'array sia vuoto o nel caso in cui si verifichino degli errori
	*/
    void remove(const T & id) {
      int count = 0;
      if (_size == 0)
        throw remove_element_exception();
      try {
        for (size i = 0; i < _size; ++i)
          if (equalVal(id, data[i]))
            ++count;

        size length = _size - count;
        T * tempArray = new T[length]();
        int j = 0;
        for (size i = 0;
          (i + j < _size) && i < length; ++i) {
          //Se ci sono N elementi da rimuovere dobbiamo spostarci di N elementi	
          while (equalVal(id, data[i + j]))
            ++j;
          tempArray[i] = data[i + j];
        }

        update(tempArray, _size - count);

      } catch (...) {
        clear();
        throw remove_element_exception();
      }
    }
	/**
		@brief Funzione per svuotare l'array
		
		Funzione per svuotare l'array
		Inizialmente terribilmente complicata, la funzione al momento lavora come una
		clear pubbica
		
		@throw remove_element_exception se l'array è vuoto
	*/
    void empty() {
      if (_size == 0)
        throw remove_element_exception();
	else	
		clear();
	/*
      // T temp;
	  try{
		  int count = 0;
		  int j = 0;
		  for (size i = 1; i < _size; i++) {
			if (equalVal(data[i], data[i - j])) {
			  ++count;
			  ++j;
			}
			else j=0;
		  }
		  // std::cout<<"Count ? " <<count<<std::endl;
		  
		  size length = _size - count;
		  std::cout << length << std::endl;

		  T * tempArray = new T[count]();
		  j = 1;
		  tempArray[0] = data[0];
		  for (size i = 1;
			(i + j < _size) && i < count; ++i) {
				// std::cout<<"giro: "<< i <<std::endl;
			while (equalVal(data[i], data[i+j]) || equalVal(data[i + j], tempArray[i - 1])){
				
			  ++j;
			}
			tempArray[i] = data[i + j];
		  }
		  // std::cout<<"Temp Array:"<<std::endl;
		  // for(int i=0; i<count;++i)
		  // std::cout<<tempArray[i]<<std::endl;
		  for (size i = 0; i < count; ++i)
			remove(tempArray[i]);
		
      //TempArray va rimosso poichè i suoi dati puntati NON sono assegnati a nulla
      delete[] tempArray;
	  }
	  catch(...){
		  throw remove_element_exception();
		  */
	  
    }
	/**
		@brief Funzione per generare un sortedArray filtrato
		
		Funzione che genera un sortedArray filtrato basandosi sull'attuale e su un funtore
		generico F
		
		@param filterFunction funtore per il filtraggio di elementi
		@return un sortedArray basato sull'array originale che rispetti il funtore
		@throw filter_exception nel caso in cui l'array sia vuoto oppure vi sia un errore
	
	*/
    template < typename F >
      sortedArray filter(const F filterFunction) const {
        if (_size == 0)
          throw filter_exception();

        int count = 0;
        for (size i = 0; i < _size; ++i)
          if (!filterFunction(data[i]))
            ++count;
        size length = _size - count;
		try{
			T * tempArray = new T[length];

			int j = 0;
			for (size i = 0;
			  (i + j < _size) && i < length; ++i) {
			  while (!filterFunction(data[i + j]))
				++j;
			  tempArray[i] = data[i + j];
			}
		
		
        sortedArray tmp;
        for (size i = 0; i < length; ++i)
          tmp.add(tempArray[i]);
	  
	  
		delete[] tempArray;
        return tmp;
		}
		catch(...){
			throw filter_exception();
		}
		
      }
	/**
		@brief Funzione per accedere alla dimensione dell'array
		
		Funzione per accedere alla dimensione dell'array
		
	*/
    int getSize() const {
      return _size;
    }
	
	/**
		@brief Funzione per accedere all'elemento i-esimo dell'array
		
		 Funzione per accedere all'elemento i-esimo dell'array
		 Fallisce se non esiste i
		 @param i indice dell'elemento da accedere
		 @throw invalid_parameter_exception nel caso in cui i sia out of bounds o non valido
		 @return elemento i-esimo di tipo T
	*/
    T getElement(const size i) const {
      if (i < _size)
        return data[i];
      else throw invalid_parameter_exception(); 
    }
	/**
		@brief Funzione per verificare l'esistenza di un elemento di tipo T
		
		 Funzione per verificare l'esistenza di un elemento di tipo T
		 @param id parametro da ricercare
		 @return esistenza del parametro
	*/
    bool exists(const T & id) const {
      bool retVal = false;
      for (size i = 0; i < _size; ++i)
        if (equalVal(id, data[i]))
          retVal = true;

      return retVal;
    }
	/**
		@brief Operatore per l'accesso a un elemento i-esimo
		
		Operatore per l'accesso a un elemento i-esimo
		Funziona nello stesso modo di getElement
		
		@param indice a cui accedere
		@throw invalid_parameter_exception nel caso in cui sz non esista
		@return elemento di tipo T 
		
		
	*/
    T & operator[](const size sz) const {
      if (sz < _size)
        return data[sz];
      else
        throw invalid_parameter_exception(); //throw error

    }

    /**
		@brief classe che rappresenta un const_random_iterator
		
		Classe che rappresenta un const_random_iterator
		La gestione dell'iteratore è lasciata all'utente, non vengono perciò eseguiti
		controlli di correttezza
	 */

    class const_iterator {
      //	
      public:
      typedef std::random_access_iterator_tag iterator_category;
      typedef T value_type;
      typedef ptrdiff_t difference_type;
      typedef const T * pointer;
      typedef const T & reference;

      const_iterator() {
        ptr = NULL;
      }

      const_iterator(const const_iterator & other) {
        ptr = other.ptr;
      }

      const_iterator & operator = (const const_iterator & other) {
          ptr = other.ptr;
          return *this;
        }

        ~const_iterator() {}

      // Ritorna il dato riferito dall'iteratore (dereferenziamento)
      reference operator * () const {
        return *ptr;
      }

      // Ritorna il puntatore al dato riferito dall'iteratore
      pointer operator -> () const {
        return ptr;
      }

      // Operatore di accesso random
      reference operator[](int index) {
        return ptr[index];
      }

      // Operatore di iterazione post-incremento
      const_iterator operator++(int) {
        const_iterator tmp( * this);
        ptr++;

        return tmp;
      }

      // Operatore di iterazione pre-incremento
      const_iterator & operator++() {
        ++ptr;

        return *this;
      }

      // Operatore di iterazione post-decremento
      const_iterator operator--(int) {
        const_iterator tmp( * this);
        ptr--;

        return tmp;
      }

      // Operatore di iterazione pre-decremento
      const_iterator & operator--() {
        --ptr;

        return *this;
      }

      // Spostamentio in avanti della posizione
      const_iterator operator + (int offset) {
        ptr += offset;

        return *this;
      }

      // Spostamentio all'indietro della posizione
      const_iterator operator - (int offset) {
        ptr -= offset;

        return *this;
      }

      // Spostamentio in avanti della posizione
      const_iterator & operator += (int offset) {
        ptr += offset;

        return *this;
      }

      // Spostamentio all'indietro della posizione
      const_iterator & operator -= (int offset) {
        ptr -= offset;

        return *this;
      }

      // Numero di elementi tra due iteratori
      difference_type operator - (const const_iterator & other) {
        if (other.ptr > ptr)
          return other.ptr - ptr;
        else
          return ptr - other.ptr;
      }

      // Uguaglianza
      bool operator == (const const_iterator & other) const {
        return (ptr == other.ptr);
      }

      // Diversita'
      bool operator != (const const_iterator & other) const {
        return (ptr != other.ptr);
      }

      // Confronto
      bool operator > (const const_iterator & other) const {
        return (ptr > other.ptr);
      }

      bool operator >= (const const_iterator & other) const {
        return (ptr >= other.ptr);
      }

      // Confronto
      bool operator < (const const_iterator & other) const {
        return (ptr < other.ptr);
      }

      // Confronto
      bool operator <= (const const_iterator & other) const {
        return (ptr <= other.ptr);
      }

      private:
        //Dati membro
        T * ptr;
      // La classe container deve essere messa friend dell'iteratore per poter
      // usare il costruttore di inizializzazione.
      friend class sortedArray; // !!! Da cambiare il nome!

      // Costruttore privato di inizializzazione usato dalla classe container
      // tipicamente nei metodi begin e end
      const_iterator(T * p) {
        ptr = p;
      }

      // !!! Eventuali altri metodi privati

    }; // classe const_iterator

    // Ritorna l'iteratore all'inizio della sequenza dati
    const_iterator begin() const {
      return const_iterator(data);
    }

    // Ritorna l'iteratore alla fine della sequenza dati
    const_iterator end() const {
      return const_iterator(data + _size);
    }

    /**
		@brief classe che rappresenta un const_forward_iterator
		
		Classe che rappresenta un const_forward_iterator
		Questo iteratore itera sul sortedArray in direzione opposta(end to start)
		La gestione dell'iteratore è lasciata all'utente, non vengono perciò eseguiti
		controlli di correttezza
	 */

    class const_reverse_iterator {
      //	
      public:
        typedef std::forward_iterator_tag iterator_category;
      typedef T value_type;
      typedef ptrdiff_t difference_type;
      typedef
      const T * pointer;
      typedef
      const T & reference;

      const_reverse_iterator(): ptr(0) {

      }

      const_reverse_iterator(const const_reverse_iterator & other): ptr(other.ptr) {

      }

      const_reverse_iterator & operator = (const const_reverse_iterator & other) {
          ptr = other.ptr;
          return *this;
        }

        ~const_reverse_iterator() {
          ptr = 0;
        }

      // Ritorna il dato riferito dall'reverse_iteratore (dereferenziamento)
      reference operator * () const {
        return *ptr;
      }

      // Ritorna il puntatore al dato riferito dall'reverse_iteratore
      pointer operator -> () const {
        return ptr;
      }

      // Operatore di iterazione post-incremento
      const_reverse_iterator operator++(int) {
        const_reverse_iterator tmp( * this);
        ptr--;
        return tmp;
      }

      // Operatore di iterazione pre-incremento
      const_reverse_iterator & operator++() {
        --ptr;
        return *this;
      }

      // Uguaglianza
      bool operator == (const const_reverse_iterator & other) const {
        return ptr == other.ptr;
      }

      // Diversita'
      bool operator != (const const_reverse_iterator & other) const {
        return ptr != other.ptr;
      }

      private:
        T * ptr;

      // La classe container deve essere messa friend dell'reverse_iteratore per poter
      // usare il costruttore di inizializzazione.
      friend class sortedArray;

      // Costruttore privato di inizializzazione usato dalla classe container
      // tipicamente nei metodi begin e end
      const_reverse_iterator(T * p): ptr(p) {}

    }; // classe const_reverse_iterator

    // Ritorna l'reverse_iteratore all'inizio della sequenza dati
    const_reverse_iterator B_begin() const {
      return const_reverse_iterator(data + _size - 1);
    }

    // Ritorna l'reverse_iteratore alla fine della sequenza dati
    const_reverse_iterator B_end() const {
      return const_reverse_iterator(data - 1);
    }
  };

/**
	@brief Ridefinizione dell'operatore << per scrivere il sortedArray
	
	
	Ridefinizione dell'operatore << per scrivere il sortedArray
	viene indicata la dimensione prima di scrivere, riga per riga, tutti gli elementi dell'array
	
	@param os stream di output
	@param g sortedArray da inviare su os
	@return riferimento a os
*/
template < typename T, typename Eql, typename order >
  std::ostream & operator << (std::ostream & os, sortedArray < T, Eql, order > & g) {

    os << "Printing Array of size:" << g.getSize() << std::endl;

    for (size i = 0; i < g.getSize(); ++i) {
      os << "Elemento numero: " << i + 1 << ": ";
      os << g.getElement(i) << std::endl;

    }

    return os;

  };
  

// }

#endif