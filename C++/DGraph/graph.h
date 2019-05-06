#ifndef GRAPH_H
#define GRAPH_H

#include <ostream>//ostream

#include <iostream>

#include <algorithm>//std::swap

#include <iterator>//std::const_iterator

#include "voce.h"

#include <cstddef>//Won't compile on test server otherwise

/**
@file graph.h
@brief Dichiarazione della classe grafo
**/


typedef unsigned int size;

/**
	Eccezione custom lanciata da operator() e operator[] 
	rappresenta un errore avvenuto nella ricerca di un Id
	
	@brief Eccezione custom lanciata da operator() e operator[] 
	rappresenta un errore avvenuto nella ricerca di un Id
*/
struct IdNotFoundException : std::exception {};
/**
	Eccezione custom lanciata dalla funzione add
	rappresenta un errore (in genere un duplicato) nell'aggiunta di un nodo
	
	@brief Eccezione custom lanciata dalla funzione add
	rappresenta un errore (un duplicato) nell'aggiunta di un nodo
*/
struct AddElementException : std::exception {};
/**
	Eccezione custom lanciata dalla funzione remove
	rappresenta un errore (un elemento non trovato) nella rimozione 
	di un nodo
	
	@brief Eccezione custom lanciata dalla funzione remove
	rappresenta un errore (un elemento non trovato) nella rimozione 
	di un nodo
*/
struct RemoveElementException : std::exception {};
/**
	Eccezione custom lanciata dalla funzione setNode,setEdge
	rappresenta un errore(un elemento non trovato) nella modifica
	del valore
	
	@brief Eccezione custom lanciata dalla funzione setNode,setEdge
	rappresenta un errore(un elemento non trovato) nella modifica
	del valore
	
*/
struct SetElementException : std::exception {};


/** @brief Grafo di nodi templati,
gestiti tramite matrice di adiacenza.


 Grafo di nodi templati,
gestiti tramite matrice di adiacenza.
Implementiamo un const iterator.
Implementiamo un template di Equal per la gestione delle classi

Nella classe sono contenuti:
un indicatore della dimensione
un insieme di nodi(identificatori) templati
una matrice di booleani(basati sui nodi) che indicano gli archi
una templatura di Equals
**/
template <typename T , typename Eql>
class grafo {
  
  size _size;
  bool** matrix;
  T* nodes;
  Eql equalVal;


	/**
		Metodo che permette la corretta inizializzazione della memoria.
	*/
  void init(const size sz) {
    
      matrix = new bool*[sz]();
      nodes = new T[sz]();
      for (size i = 0; i < sz; ++i) {
        matrix[i] = new bool[sz]();
   
      }
      _size = sz;

    
  }

  /**
          Metodo che permette il corretto rilascio della memoria.
          invocato dal distruttore e in alcune altre occasioni(add/remove)
  */
  void clear() {
		T tmp;
      for (size i = 0; i < this->getSize(); ++i){
		  //delete nodes;
		  delete[] matrix[i];
	  }
	  delete[] nodes;
      delete[] matrix;
      //delete[] nodes;
  
  };

 public:
	/**
       Costruttore vuoto, fondamentale.
    */
  grafo() {

    _size = 0;
    matrix = 0;
    nodes = 0;
    //init(_size); //Non fa molto
  };

  /**
          Copy Constructor, fondamentale.
          Attraverso init allochiamo la memoria necessaria a costruire
          il nostro nuovo grafo.
          @param other un grafo dal quale costruire l'attuale

  */
	grafo(const grafo& other) {
    
      init(other.getSize());
      for (size i = 0; i < _size; ++i){
		  nodes[i] = other.nodes[i];
		  for(size j=0; j< _size; ++j)
			  matrix[i][j] = other.matrix[i][j];
	  }
  };

  /**
          Destroyer, fondamentale.
          Attraverso la funzione clear rilascia la memoria assegnata al grafo.
  */
  ~grafo() { clear(); };
  /**
          Operatore di assegnamento.
          @param other grafo dal quale costruire l'attuale
          @return il nuovo grafo.
  */
  grafo& operator=(const grafo& other) {
    
      grafo tmp(other);
      (*this).swap(tmp);
    
    return *this;
  };
  /**
          Metodo che permette l'accesso alla MATRICE del grafo.
          Svolto come tale in quanto impossibile ridefinire [][].
          @param indice che rappresenta il nodo di partenza
          @param indice che rappresenta il nodo di arrivo
          @return valore che rappresenta la presenza di un arco tra i due valori
		  @throw IdNotFoundException nel caso in cui si vada OutOfBounds
  */
  bool& operator()(size i, size j) const {
    // will be used to access the matrix
  
      if ((i < _size) & (j < _size))
        return matrix[i][j];
      else
		 throw IdNotFoundException();
   
  };

  /**
          Metodo che permette l'accesso all'insieme dei nodi.
          @param indice che rappresenta il nodo a quale si vuole accedere
          @return valore che rappresenta l'identificatore del nodo
		  @throw IdNotFoundException nel caso in cui si vada OutOfBounds
  */
  T& operator[](size i) const {
    
      if (i < _size)
        return nodes[i];
      else
		throw IdNotFoundException();

  }
	/**
		OverRide della funzione standard swap
		scambia I valori di due grafi
	*/
  void swap(grafo& other) {
    
      std::swap(_size, other._size);
      std::swap(matrix, other.matrix);
      std::swap(nodes, other.nodes);
    
   // return *this;
  };
  /**
          Metodo che ritorna la dimensione della matrice
          @return dimensione della matrice
  */
  size getSize(void) const { return _size; };
  /**
          Metodo che ritorna il conteggio di archi presenti nella matrice
          @return conteggio archi
  */
  size hasEdges(void) const {
    size counter = 0;

    for (size i = 0; i < _size; ++i)
      for (size j = 0; j < _size; ++j)
        if (matrix[i][j]) ++counter;
    return counter;
  }
  /**
          Metodo che ritorna l'esistenza di un identificatore
          @param id Identificatore da cercare
          @return esistenza di id
  */
  bool exists(const T& id) {
    bool found = 0;

    for (size i = 0; i < _size; ++i)
      if (equalVal(nodes[i],id)) found = 1;

    return found;
  };


  /**
          Metodo che aggiunge un nuovo nodo, se non gia esistente.
          Con l'aggiunta del nodo aggiungiamo una fila/colonna alla matrice e
          ne aumentiamo la dimensione.
          @param nodo da aggiungere.
		  @throw AddElementException nel caso in cui il nodo da aggiungere non sia valido
  */
  void add(const T& id) {
    
      if (!(exists(id))) {
    
        size tmpSz = _size + 1;
        bool** tmpMatrix = 0;
        T* tmpNodes = new T[tmpSz]();

        for (size i = 0; i < _size; ++i) tmpNodes[i] = nodes[i];

      
        tmpNodes[tmpSz - 1] = id;

        tmpMatrix = new bool*[tmpSz]();
        for (size i = 0; i < tmpSz; ++i) tmpMatrix[i] = new bool[tmpSz]();

        for (size i = 0; i < _size; ++i)
          for (size j = 0; j < _size; ++j) tmpMatrix[i][j] = matrix[i][j];

        clear();

        _size = tmpSz;
        matrix = tmpMatrix;
        nodes = tmpNodes;
      } else {
		//Non lasciamo aggiungere due volte lo stesso elemento
		std::cerr<<"Add Error"<<std::endl;
		throw AddElementException();
		
      }
    
  };

  /**
          Metodo che permette di rimuovere un nodo dall'insieme
          rimuovendo il nodo eliminiamo tutti gli archi da esso uscenti,
          e da esso entranti.
          @param nodo da rimuovere
		  @throw RemoveElementException nel caso in cui si cerchi di rimuovere un elemento non valido
  */
  void remove(const T& id) {

      if (exists(id)) {
       // std::cout << "Removing:" <<id << std::endl;
        size tmpSz = _size - 1;
        bool** tmpMatrix = 0;
        T* tmpNodes = new T[tmpSz]();

        int position = 0;
        for (size i = 0; i < _size; ++i)
          if (equalVal(nodes[i],id)) position = i;

        tmpMatrix = new bool*[tmpSz]();
        for (size i = 0; i < tmpSz; ++i) tmpMatrix[i] = new bool[tmpSz]();

        size mov = 0;
        size mov2 = 0;
       
        for (size i = 0; i < tmpSz; ++i) {
          if (i == position & (i+mov)<tmpSz) ++mov;
          tmpNodes[i] = nodes[i + mov];
        }
        mov = 0;
       
        for (size i = 0; i < tmpSz; ++i) {
          mov = 0;
          mov2 = 0;
          if (i == position & (i+mov)<tmpSz) mov = 1;
          for (size j = 0; j < tmpSz; ++j) {
            if (j == position & (j+mov2)<tmpSz) mov2 = 1;
            tmpMatrix[i][j] = matrix[i + mov][j + mov2];
          }
        }
        clear();
        _size = tmpSz;
        matrix = tmpMatrix;
        nodes = tmpNodes;
      } else {
		std::cerr<<"RemoveError";
        throw RemoveElementException();
      }
  
    
		
    
  };
  /**
          Metodo che ritorna la posizione di un nodo all'interno dell'insieme
     nodes.
	 Un valore di -1 indica un Nodo non trovato
	 
          @param identificatore da cercare
          @return posizione dell'identificatore, se presente.
  */
  int getNode(const T& id) {
    int position = -1;
    for (size i = 0; i < _size; ++i)
      if (equalVal(nodes[i],id)) position = i;
	
    return position;
  };
  /**
          Metodo che permette la modifica dell'identificatore di un nodo.
          @param valore da sostituire
          @param valore sostituente
		  @throw SetElementException nel caso in cui L'id non sia valido
  */
  void setNode(const T& oldVal, const T& id) {
 
      if (exists(oldVal)) {
        //std::cout << "Old Val Exists" << std::endl;
        if (!(exists(id))) {
          size position = getNode(oldVal);
          nodes[position] = id;
         
        } else{
          std::cerr << "Id already taken" << std::endl;
		  throw SetElementException();
		}
      } else {// Non consideriamo un errore se cerchiamo di modificare qualcosa che non c'è
        std::cerr << "Couldn't Find the Id you were looking for" << std::endl;
		throw SetElementException();
	  }
    
  };
  /**
          Metodo che permette la modifica di un arco.
          permette di creare e rimuovere archi.
          @param nodo di uscita
          @param nodo di entrata
          @param True per creare un arco, false per rimuoverlo
		  @throw SetElementException nel caso in cui non sia presente uno dei due nodi
  */
  void setEdge(const T& first, const T& second, bool val) {

		if (exists(first) & exists(second))
		  matrix[getNode(first)][getNode(second)] = val;
		else
		  throw SetElementException();	
	
  };
  /**
          Metodo per identificare la presenza di un arco.
          @param nodo di uscita
          @param nodo di entrata
          @return presenza o meno di un arco
  */
  bool hasEdge(const T& first, const T& second) {

	bool returnVal=false;
  	 if (exists(first) & exists(second))
      		returnVal= matrix[getNode(first)][getNode(second)];
    	else
      		std::cout << "One of the Id's doesn't exist";

	return returnVal;
  };



	/**
		Classe rappresentante un forward const_iterator
		Iteriamo con un puntatore all'array generico nodes 
		Utilizziamo un indice numerico per indicar su quale cella dell'array nodes è 			posizionato l'iteratore
		
		@brief Classe rappresentante un forward const_iterator
	*/
  class const_iterator {
    //
   public:
    typedef std::forward_iterator_tag iterator_category; //categoria di iteratore
    typedef T value_type; //valore puntato
    typedef ptrdiff_t difference_type; //tipo usato per differenziare tra due pointer
    typedef const T* pointer; //puntatore al tipo puntato
    typedef const T& reference; //reference al tipo puntato

	/**
		Costruttore vuoto, fondamentale
	*/
    const_iterator() : ptr(0),position(0) {
    }

	/**
		Copy Constructor, fondamentale
		@param iteratore da usare per costruire l'iteratore
	*/
    const_iterator(const const_iterator& other) : ptr(other.ptr),position(other.position) {
    }

	/**
		Operatore di assegnamento.
		@param iteratore da usare per riceverei valori da assegnare
		@return l'iteratore modificato
	*/
    const_iterator& operator=(const const_iterator& other) {
      ptr = other.ptr;
	  position=other.position;
      return *this;
    }

	/**
		Destroyer, fondamentale
	*/
    ~const_iterator() { ptr = 0; position=0;}

 
	/**
		Operazione di Dereferenziamento.
		Operatore che ritorna il dato riferito dall'iteratore)
		@return il dato riferito.
	*/
    reference operator*() const { return (*ptr)[position]; }

  
	/**
		Operatore che ritorna il puntatore al dato riferito
		@return puntatore al dato riferito
	*/
    pointer operator->() const { return &((*ptr)[position]); }

   /**
	Operatore di post-incremento
	@return posizione successiva dell'iteratore
   */
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      position++;
      return tmp;
    }

   /**
	Operazione di pre-incremento
	@return posizione successiva dell'iteratore
   */
    const_iterator& operator++() {
      position++;
      return *this;
    }


	/**
		Operatore di uguaglianza
		@param iteratore con cui eseguiamo il confronto
		@return risultato del confronto
	*/
    bool operator==(const const_iterator& other) const {
      return ((ptr == other.ptr) &&	(position==other.position));
    }

  /**
	Operatore di disuguaglianza
	@param iteratore con cui eseguiamo il confronto
	@return risultato del confronto
  */
    bool operator!=(const const_iterator& other) const {
      return !(*this==other);
    }

   private:
    /*
		Dati utilizzati per iterare sull'array
	*/
    const grafo<T,Eql> *ptr;
	size position;

    friend class grafo;

    // Costruttore privato di inizializzazione usato dalla classe container
    // tipicamente nei metodi begin e end
    const_iterator(const grafo *p, size posit) : ptr(p),position(posit) {

    }

  };  

  // Ritorna l'iteratore all'inizio della sequenza dati
  const_iterator begin() const { return const_iterator(this,0); }

  // Ritorna l'iteratore alla fine della sequenza dati
  const_iterator end() const { return const_iterator(this,_size); }
};



/**
	@brief Ridefinizione dell'operatore << per scrivere:
	Dimensione del Grafo
	Identificatori del Grafo
	Matrice di Adiacenza

	Ridefinizione dell'operatore << per scrivere:
	Dimensione del Grafo
	Identificatori del Grafo
	Matrice di Adiacenza
	NOTA:
		La matrice è particolarmente intrusiva con Identificatori "Grandi"
		è stata lasciata per facilitare la lettura in fase di testing.
	
	@param os stream di output
	@param g grafo da inviare su os
	@return riferimento a os
*/
template <typename T,typename Eql>
std::ostream& operator<<(std::ostream& os, grafo<T,Eql>& g) {
  if (g.getSize() > 0) {
    os << "Size: " << g.getSize() << std::endl;
    os << "Node values:" << std::endl;
    for (size i = 0; i < g.getSize(); ++i) os << g[i] << " ";
    os << "" << std::endl;
	//Start Matrix
    os << "Matrix" << std::endl;
    os << "   ";
    for (int i = 0; i < g.getSize(); i++) {
      os << g[i] << " | ";
    }
    os << std::endl;
    for (int i = 0; i < g.getSize(); i++) {
      os << g[i] << "| ";
      for (int j = 0; j < g.getSize(); j++) {
        if (g(i, j)) {
          os << "X";
          os << " | ";
        } else {
          os << "O";
          os << " | ";
        }
      }
      os << std::endl;
    }
	//End Matrix
    os << std::endl;
  } else
    os << "Matrix is of size 0" << std::endl;
  return os;
};

#endif
