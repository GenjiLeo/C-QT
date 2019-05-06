#include "graph.h"

#include "voce.h"

#include <iostream>

#include <cassert>

#include <string>

#include <cstddef>

struct equal_int {

  bool operator()(int a, int b) const {

    return (a == b);

  }
};

struct equal_char {

  bool operator()(char a, char b) const {

    return (a == b);

  }

};

struct equal_voce {

  bool operator()(voce a, voce b) const {

    return (a == b);

  }

};

void test_int() {
  typedef grafo < int, equal_int > grafo;
  //Costruttore Vuoto
  grafo testEmpty;
  assert(testEmpty.getSize() == 0);	
  testEmpty.add(1);
  assert(testEmpty.getSize() == 1);
  std::cout << testEmpty << std::endl; //Printa size,nodi,matrice
  testEmpty.setEdge(1, 1, 1);

  testEmpty.add(2);
  testEmpty.add(3);
  testEmpty.add(4);
  testEmpty.add(5);
  testEmpty.add(6);
  assert(testEmpty.getSize() == 6);
  std::cout << testEmpty;
  //Test aggiunta doppi
  //try{ testEmpty.add(1); } catch(...){}; //Try/catch previene leaks

  //CopyConstructor
  grafo testEmpty2;
  grafo testEmpty3(testEmpty2);
  assert(testEmpty3.getSize() == 0);
  std::cout << testEmpty3;
  //CopyConstructor con Elementi
  grafo grafo_elementi;
  grafo_elementi.add(1);
  grafo_elementi.add(2);
  grafo_elementi.add(3);
  grafo_elementi.add(4);
  grafo grafo_elementi_copy(grafo_elementi);
  assert(grafo_elementi_copy.getSize() == 4);
  std::cout << "Grafo Elementi: " << std::endl;
  std::cout << grafo_elementi_copy;
  // testAssegnamento
  grafo testAssegnamenti;
  testAssegnamenti = grafo_elementi;
  assert(testAssegnamenti.getSize() == 4);
  std::cout << "Grafo testAssegnamenti: " << std::endl;
  std::cout << testAssegnamenti;
  //testRimozione
  grafo testRimozione;
  testRimozione = testAssegnamenti;
  testRimozione.remove(2);
  assert(testRimozione.getSize() == 3);
  std::cout << "Grafo testRimozione: " << std::endl;
  std::cout << testRimozione;
  //Test testRimozione di elemento assente
  // try{ testRimozione.remove(10); } catch(...){}; //Try/catch previene leaks
  //Test testRimozione elemento 0-esimo
  testRimozione.remove(1);
  std::cout << testRimozione;
  //Test testRimozione elemento ultimo
  testRimozione.remove(4);
  std::cout << testRimozione;
  //Test testRimozione rimanenti
  testRimozione.remove(3);
  std::cout << testRimozione;
  //Operator() ritorna matrice
  grafo testTonde(testAssegnamenti);
  //setEdge utilizza gli Identificatori della matrice
  testTonde.setEdge(1, 1, 1);
  testTonde.setEdge(1, 2, 1);
  testTonde.setEdge(2, 1, 1);
  testTonde.setEdge(4, 4, 1);
  std::cout << testTonde;
  //Operator() Utilizza gli indici numerici della matrice!
  std::cout << testTonde(0, 0) << std::endl;
  std::cout << testTonde(1, 0) << std::endl;
  std::cout << testTonde(0, 1) << std::endl;
  std::cout << testTonde(3, 3) << std::endl;

  //Operator[] ritorna nodi
  // Utilizza gli indici numerici dei nodi!
  grafo testQuadre;
  testQuadre.add(1);
  testQuadre.add(52);
  testQuadre.add(2);
  testQuadre.add(4);
  std::cout << testQuadre;
  std::cout << "Print degli Identificatori" << std::endl;
  std::cout << testQuadre[0] << std::endl;
  std::cout << testQuadre[1] << std::endl;
  std::cout << testQuadre[2] << std::endl;
  std::cout << testQuadre[3] << std::endl;
  //swap
  std::cout << "Swap del grafo quadro con testTonde" << std::endl;
  testQuadre.swap(testTonde);
  std::cout << "testQuadre diventa testTonde: " << testQuadre;
  std::cout << "testTonde diventa testQuadre: " << testTonde;
  //getSize(void)
  grafo testSize;
  assert(testSize.getSize() == 0);
  testSize.add(1);
  assert(testSize.getSize() == 1);
  testSize.add(2);
  assert(testSize.getSize() == 2);
  testSize.add(3);
  assert(testSize.getSize() == 3);
  testSize.add(4);
  assert(testSize.getSize() == 4);
  //setEdges(id,id,value) set degli archi
  //hasEdges(void) count di archi validi
  testSize.setEdge(1, 1, 1);
  testSize.setEdge(2, 1, 1);
  testSize.setEdge(1, 2, 1);
  testSize.setEdge(3, 1, 1);
  testSize.setEdge(4, 4, 1);
  testSize.setEdge(2, 4, 1);
  std::cout << "Grafo Size: conto degli archi" << std::endl;
  std::cout << testSize.hasEdges() << std::endl;
  std::cout << testSize;
  assert(testSize.hasEdges() == 6);
  //hasEdge(id,id) ritorna il valore dell'arco
  assert(testSize.hasEdge(1, 1) == 1);
  assert(testSize.hasEdge(1, 3) == 0);

  //Esistenza
  grafo testEsistenza;
  testEsistenza.add(1);
  testEsistenza.add(13242);
  testEsistenza.add(19);
  testEsistenza.add(11);
  testEsistenza.add(2);
  //exists(id) ritorna l'esistenza di un nodo
  assert(testEsistenza.exists(1) == 1);
  assert(testEsistenza.exists(2) == 1);
  assert(testEsistenza.exists(11) == 1);
  assert(testEsistenza.exists(24) == 0);
  //std::cout<<"Asserts passed"<<std::endl;

  //getNode(id) ritorna la posizione dell'id, se esistente
  std::cout << "Presenza dei nodi con id 1,2, 123: " << std::endl;
  std::cout << testEsistenza.getNode(1) << std::endl;
  std::cout << testEsistenza.getNode(2) << std::endl;
  std::cout << testEsistenza.getNode(123) << std::endl;
  //setNode(id,id) trasforma il primo valore nel secondo,se esistente
  std::cout<<testEsistenza;
  testEsistenza.setNode(1, 3);

  testEsistenza.setNode(2, 4);
  

  //try{testEsistenza.setNode(123,5);} catch(...){}; //SetElementException

  //iterators
  grafo testIteratore;
  testIteratore.add(1234);
  testIteratore.add(2);
  testIteratore.add(3);
  testIteratore.add(4);
  testIteratore.add(5);
  testIteratore.add(75);
  testIteratore.add(42);
  testIteratore.add(44);
  testIteratore.add(96);
  testIteratore.setEdge(1234, 2, 1);
  testIteratore.setEdge(3, 3, 1);

  grafo::const_iterator begin = testIteratore.begin();
  grafo::const_iterator end = testIteratore.end();

  std::cout << "Grafo testIteratore" << std::endl;
  std::cout << testIteratore;

  std::cout << "Utilizzo degli iteratori sul Grafo testIteratore: " << std::endl;
  for (; begin != end; ++begin)
    std::cout << "begin:" << * begin << std::endl;

}

void test_char() {
  typedef grafo < char, equal_char > grafo;
  //Costruttore Vuoto
  grafo testEmpty;
  assert(testEmpty.getSize() == 0);
  testEmpty.add('a');
  assert(testEmpty.getSize() == 1);
  std::cout << testEmpty << std::endl;
  testEmpty.setEdge('a', 'a', 1);

  testEmpty.add('b');
  testEmpty.add('c');
  testEmpty.add('d');
  testEmpty.add('e');
  testEmpty.add('f');
  assert(testEmpty.getSize() == 6);
  std::cout << testEmpty;
  //Test aggiunta doppi
  //try{ testEmpty.add('a'); } catch(...){}; //Try/catch previene leaks

  //CopyConstructor
  grafo testEmpty2;
  grafo testEmpty3(testEmpty2);
  assert(testEmpty3.getSize() == 0);
  std::cout << testEmpty3;
  //CopyConstructor con Elementi
  grafo grafo_elementi;
  grafo_elementi.add('a');
  grafo_elementi.add('b');
  grafo_elementi.add('c');
  grafo_elementi.add('d');
  grafo grafo_elementi_copy(grafo_elementi);
  assert(grafo_elementi_copy.getSize() == 4);
  std::cout << "Grafo Elementi: " << std::endl;
  std::cout << grafo_elementi_copy;
  // Assegnamento
  grafo testAssegnamenti;
  testAssegnamenti = grafo_elementi;
  assert(testAssegnamenti.getSize() == 4);
  std::cout << "Grafo testAssegnamenti: " << std::endl;
  std::cout << testAssegnamenti;

  //testRimozione
  grafo testRimozione;
  testRimozione = testAssegnamenti;
  testRimozione.remove('b');
  assert(testRimozione.getSize() == 3);
  std::cout << "Grafo testRimozione: " << std::endl;
  std::cout << testRimozione;
  //Test testRimozione di elemento assente
  // try{ testRimozione.remove('z'); } catch(...){}; //Try/catch previene leaks
  //Test testRimozione elemento 0-esimo
  testRimozione.remove('a');
  std::cout << testRimozione;
  //Test testRimozione elemento ultimo
  testRimozione.remove('d');
  std::cout << testRimozione;
  //Test testRimozione rimanenti
  testRimozione.remove('c');
  std::cout << testRimozione;

  //Operator() ritorna matrice
  grafo testTonde(testAssegnamenti);
  //setEdge utilizza gli Identificatori della matrice
  testTonde.setEdge('a', 'a', 1);
  testTonde.setEdge('a', 'b', 1);
  testTonde.setEdge('b', 'a', 1);
  testTonde.setEdge('d', 'd', 1);
  std::cout << testTonde;
  //Operator() Utilizza gli indici numerici della matrice!

  std::cout << testTonde(0, 0) << std::endl;
  std::cout << testTonde(1, 0) << std::endl;
  std::cout << testTonde(0, 1) << std::endl;
  std::cout << testTonde(3, 3) << std::endl;

  //Operator[] ritorna nodi
  // Utilizza gli indici numeri dei nodi!
  grafo testQuadre;
  testQuadre.add('a');
  testQuadre.add('y');
  testQuadre.add('b');
  testQuadre.add('d');
  std::cout << testQuadre;
  std::cout << "Print degli Identificatori" << std::endl;
  std::cout << testQuadre[0] << std::endl;
  std::cout << testQuadre[1] << std::endl;
  std::cout << testQuadre[2] << std::endl;
  std::cout << testQuadre[3] << std::endl;

  //swap
  std::cout << "Swap del grafo quadro con testTonde" << std::endl;
  testQuadre.swap(testTonde);
  std::cout << "testQuadre diventa testTonde: " << testQuadre;
  std::cout << "testTonde diventa testQuadre: " << testTonde;

  //getSize(void)
  grafo testSize;
  assert(testSize.getSize() == 0);
  testSize.add('a');
  assert(testSize.getSize() == 1);
  testSize.add('b');
  assert(testSize.getSize() == 2);
  testSize.add('c');
  assert(testSize.getSize() == 3);
  testSize.add('d');
  assert(testSize.getSize() == 4);
  //setEdges(id,id,value) set degli archi
  //hasEdges(void) count di archi validi
  testSize.setEdge('a', 'a', 1);
  testSize.setEdge('b', 'a', 1);
  testSize.setEdge('a', 'b', 1);
  testSize.setEdge('c', 'a', 1);
  testSize.setEdge('d', 'd', 1);
  testSize.setEdge('b', 'd', 1);
  std::cout << "Grafo Size: conto degli archi" << std::endl;
  std::cout << testSize.hasEdges() << std::endl;
  std::cout << testSize;
  assert(testSize.hasEdges() == 6);
  //hasEdge(id,id) ritorna il valore dell'arco
  assert(testSize.hasEdge('a', 'a') == 1);
  assert(testSize.hasEdge('a', 'c') == 0);

  //exists returns the existence of a node
  grafo testEsistenza;
  testEsistenza.add('a');
  testEsistenza.add('v');
  testEsistenza.add('f');
  testEsistenza.add('r');
  testEsistenza.add('b');

  assert(testEsistenza.exists('a') == 1);
  assert(testEsistenza.exists('b') == 1);
  assert(testEsistenza.exists('r') == 1);
  assert(testEsistenza.exists('P') == 0);

  //std::cout<<"Asserts passed"<<std::endl;
  //getNode(id) ritorna la posizione dell'id, se esistente
  std::cout << "Presenza dei nodi con id a,b, p	: " << std::endl;

  std::cout << testEsistenza.getNode('a') << std::endl;
  std::cout << testEsistenza.getNode('b') << std::endl;
  std::cout << testEsistenza.getNode('p') << std::endl;

  std::cout << "testEsistenza done" << std::endl;
  //setNode(id,id) cambia il primo valore nel secondo,se esistente
  testEsistenza.setNode('a', 'c');
  testEsistenza.setNode('b', 'd');

  //try{testEsistenza.setNode(123,5);} catch(...){}; //SetElementException

  //iterators
  grafo testIteratore;
  testIteratore.add('O');
  testIteratore.add('b');
  testIteratore.add('c');
  testIteratore.add('d');
  testIteratore.add('e');
  testIteratore.add('I');
  testIteratore.add('L');
  testIteratore.add('C');
  testIteratore.add('V');
  testIteratore.setEdge('V', 'C', 1);
  testIteratore.setEdge('d', 'd', 1);

  grafo::const_iterator begin = testIteratore.begin();

  grafo::const_iterator end = testIteratore.end();
  std::cout << "Grafo testIteratore" << std::endl;
  std::cout << testIteratore;

  std::cout << "Utilizzo degli iteratori sul grafo testIteratore" << std::endl;
  for (; begin != end; ++begin)
    std::cout << "begin:" << * begin << std::endl;

}

void test_voce() {
  const voce v1("Leonardo", "Fraquelli", "820651");
  const voce v2("Luigi", "Celona", "123456");
  const voce v3("Gianluigi", "Ciocca", "654321");
  const voce v4("Alex", "Honnold", "000001");
  const voce v5("Marco", "Bedolini", "100000");
  const voce v6("Foo", "Bar", "010101");
  const voce v7("Pippo", "Paolo", "420609");
  const voce v8("Emilio", "Brambilla", "906024");
  const voce v9("Palminof", "Leprecauno", "123123");

  typedef grafo < voce, equal_voce > grafo;
  //Costruttore Vuoto
  grafo testEmpty;
  assert(testEmpty.getSize() == 0);
  testEmpty.add(v1);
  assert(testEmpty.getSize() == 1);
  std::cout << testEmpty << std::endl; //Printa nodi,size,matrice
  testEmpty.setEdge(v1, v1, 1);

  testEmpty.add(v2);
  testEmpty.add(v3);
  testEmpty.add(v6);
  testEmpty.add(v4);
  testEmpty.add(v5);
  assert(testEmpty.getSize() == 6);
  std::cout << testEmpty;
  //Test aggiunta doppi
  //try{ testEmpty.add(v1); } catch(...){}; //Try/catch previene leaks

  //CopyConstructor
  grafo testEmpty2;
  grafo testEmpty3(testEmpty2);
  assert(testEmpty3.getSize() == 0);
  std::cout << testEmpty3;
  //CopyConstructor con Elementi
  grafo grafo_elementi;
  grafo_elementi.add(v1);
  grafo_elementi.add(v2);
  grafo_elementi.add(v3);
  grafo_elementi.add(v4);
  grafo grafo_elementi_copy(grafo_elementi);
  assert(grafo_elementi_copy.getSize() == 4);
  std::cout << "Grafo Elementi: " << std::endl;
  std::cout << grafo_elementi_copy;
  // Assegnamento
  grafo testAssegnamenti;
  testAssegnamenti = grafo_elementi;
  assert(testAssegnamenti.getSize() == 4);
  std::cout << "Grafo testAssegnamenti: " << std::endl;
  std::cout << testAssegnamenti;

  //testRimozione
  grafo testRimozione;
  testRimozione = testAssegnamenti;
  testRimozione.remove(v2);
  assert(testRimozione.getSize() == 3);
  std::cout << "Grafo testRimozione: " << std::endl;
  std::cout << testRimozione;
  //Test testRimozione di elemento assente
  // try{ testRimozione.remove(v9); } catch(...){}; //Try/catch previene leaks
  //Test testRimozione elemento 0-esimo
  testRimozione.remove(v1);
  std::cout << testRimozione;
  //Test testRimozione elemento ultimo
  testRimozione.remove(v3);
  std::cout << testRimozione;
  //Test testRimozione rimanenti
  testRimozione.remove(v4);
  std::cout << testRimozione;

  //Operator() ritorna matrice
  grafo testTonde(testAssegnamenti);
  //setEdge utilizza gli Identificatori della matrice
  testTonde.setEdge(v1, v1, 1);
  testTonde.setEdge(v1, v2, 1);
  testTonde.setEdge(v2, v1, 1);
  testTonde.setEdge(v3, v3, 1);
  std::cout << testTonde;
  //Operator() Utilizza gli indici numerici di matrix!

  std::cout << testTonde(0, 0) << std::endl;
  std::cout << testTonde(1, 0) << std::endl;
  std::cout << testTonde(0, 1) << std::endl;
  std::cout << testTonde(3, 3) << std::endl;

  //Operator[] ritorna nodi
  // Utilizza gli indici numeri di nodes!
  grafo testQuadre;
  testQuadre.add(v1);
  testQuadre.add(v5);
  testQuadre.add(v2);
  testQuadre.add(v3);
  std::cout << testQuadre;
  std::cout << "Print degli Identificatori" << std::endl;
  std::cout << testQuadre[0] << std::endl;
  std::cout << testQuadre[1] << std::endl;
  std::cout << testQuadre[2] << std::endl;
  std::cout << testQuadre[3] << std::endl;

  //swap
  std::cout << "Swap del grafo quadro con testTonde" << std::endl;
  testQuadre.swap(testTonde);
  std::cout << "testQuadre diventa testTonde: " << testQuadre;
  std::cout << "testTonde diventa testQuadre: " << testTonde;

  //getSize(void)
  grafo testSize;
  assert(testSize.getSize() == 0);
  testSize.add(v1);
  assert(testSize.getSize() == 1);
  testSize.add(v2);
  assert(testSize.getSize() == 2);
  testSize.add(v3);
  assert(testSize.getSize() == 3);
  testSize.add(v4);
  assert(testSize.getSize() == 4);
  //setEdges(id,id,value) set degli archi
  //hasEdges(void) count di archi validi
  testSize.setEdge(v1, v1, 1);
  testSize.setEdge(v2, v1, 1);
  testSize.setEdge(v1, v2, 1);
  testSize.setEdge(v3, v1, 1);
  testSize.setEdge(v3, v3, 1);
  testSize.setEdge(v2, v3, 1);
  std::cout << "Grafo Size: conto degli archi" << std::endl;
  std::cout << testSize.hasEdges() << std::endl;
  std::cout << testSize;
  assert(testSize.hasEdges() == 6);
  //hasEdge(id,id) ritorna il valore dell'arco
  assert(testSize.hasEdge(v1, v1) == 1);
  assert(testSize.hasEdge(v1, v3) == 0);

  //exists ritorna l'esistenza del nodo
  grafo testEsistenza;
  testEsistenza.add(v1);
  testEsistenza.add(v6);
  testEsistenza.add(v5);
  testEsistenza.add(v7);
  testEsistenza.add(v2);

  assert(testEsistenza.exists(v1) == 1);
  assert(testEsistenza.exists(v2) == 1);
  assert(testEsistenza.exists(v6) == 1);
  assert(testEsistenza.exists(v4) == 0);

  std::cout << "Asserts passed" << std::endl;
  //getNode(id) ritorna la posizione dell'id, se esistente
  std::cout << "Presenza dei nodi con id v1,v2,v4: " << std::endl;
  std::cout << testEsistenza.getNode(v1) << std::endl;
  std::cout << testEsistenza.getNode(v2) << std::endl;
  std::cout << testEsistenza.getNode(v4) << std::endl;
  //setNode(id,id) cambia il primo valore nel secondo,se esistente
  testEsistenza.setNode(v1, v3);
  testEsistenza.setNode(v2, v4);
  //try{testEsistenza.setNode(v9,v2);} catch(...){}; //SetElementException

  //iterators
  grafo testIteratore;
  testIteratore.add(v1);
  testIteratore.add(v2);
  testIteratore.add(v3);
  testIteratore.add(v5);
  testIteratore.add(v4);
  testIteratore.add(v6);
  testIteratore.add(v7);
  testIteratore.add(v9);
  testIteratore.add(v8);
  testIteratore.setEdge(v8, v3, 1);
  testIteratore.setEdge(v3, v3, 1);

  grafo::const_iterator begin = testIteratore.begin();
  grafo::const_iterator end = testIteratore.end();

  std::cout << "Grafo testIteratore" << std::endl;
  std::cout << testIteratore;

  std::cout << "Utilizzo degli iteratori sul grafo testIteratore" << std::endl;
  for (; begin != end; ++begin)
    std::cout << "begin value: " << * begin << std::endl;
}

int main() {

  test_int();

  test_char();

  test_voce();
  
  // grafo<int,equal_int> intG;
  // grafo<int,equal_char> charG;
  // charG.swap(intG);
  
  return 0;
}