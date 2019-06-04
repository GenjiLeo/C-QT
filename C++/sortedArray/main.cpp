#include "sortedArray.h"

#include "voce.h"

#include <iostream>

#include <cassert>

#include <string>

#include <cstddef>

//Equals
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
//Orders
struct order_int_increasing{
	
	bool operator()(int a, int b) const {
		
		return a<b;
	}
};

struct order_int_decreasing{
	
	bool operator()(int a, int b) const {
		
		return a>b;
	}
};

struct order_char_increasing{
	
	bool operator()(char a, char b) const {
		
		return a<b;
	}
};

struct order_char_decreasing{
	
	bool operator()(char a, char b) const {
		
		return a>b;
	}
};

struct order_voce_increasing{
	
	bool operator()(voce a, voce b) const{
		
		return a<b;
	}
};
struct order_voce_decreasing{
	
	bool operator()(voce a, voce b) const{
		
		return a>b;
	}
};


//Filters
struct is_odd{
	bool operator()(int a) const{
		
		return a%2;
	}
};

struct is_greater_than_5{
	bool operator()(int a) const{
		
		return a>5;
	}
};

struct is_vowel{

	bool operator()(char a) const {
		return ((a == 'a') || (a == 'e') || (a == 'i') || (a == 'o') || (a == 'u'));
	}
	
};

struct is_z{
	
	bool operator()(char a)const{
		return((a =='z'));
	}
};

struct is_Fraquelli{
	//The cool struct
	bool operator()(voce a) const{
		return a.cognome=="fraquelli";
	}
};

struct is_not_Fraquelli{
	
	bool operator()(voce a)const{
		return a.cognome!="fraquelli";
	}
};


void test_int(){
	
	typedef sortedArray<int,equal_int,order_int_increasing> sortedArray;
	const int val1=1;
	const int val2=2;
	const int val3=3;
	const int val4=4;
	const int val5=5;
	const int val6=6;
	const int val7=7;
	const int val8=8;
	const int val9=9;
	const int val10=10;
	
	sortedArray a;
	
	//Empty Print
	std::cout<<a<<std::endl;
	
	//add
	a.add(val1);
	a.add(val2);
	a.add(val1);
	a.add(val3);
	a.add(val4);
	a.add(val5);
	a.add(val10);
	a.add(val10);
	a.add(val10);
	a.add(val1);
	//Print 
	std::cout<<a<<std::endl;
	// 1-1-1-2-3-4-5-10-10-10
	//CConstructor
	sortedArray b(a);
	
	// std::cout<<b<<std::endl;
	
	//remove, one by one
	a.remove(val1);
	a.remove(val2);
	// a.remove(val1);
	a.remove(val3);
	a.remove(val4);
	a.remove(val5);
	a.remove(val10);
	// a.remove(val10);
	// a.remove(val10);
	// a.remove(val1);
	//a.remove(val1) will throw an exception since it's now empty
	//Is empty
	std::cout<<"It's empty: "<<a<<std::endl;
	
	//Assignment operator
	a=b;
	
	std::cout<<a<<std::endl;
	//Empty Function
	a.empty();
	
	std::cout<<"It's empty,again: "<<a<<std::endl;
	
	//swap
	a.swap(b);
	// /*
	std::cout<<"It's back to full: "<<a<<std::endl;
	
	//Filter
	a=a.filter(is_odd());
	
	std::cout<<"Only odd values: "<< a << std::endl;
	
	//getSize, should be 10
	std::cout<<"My size should be 10: " <<b.getSize()<<std::endl;
	
	//Exists
	std::cout<<"Value Exists: " << b.exists(val1) << std::endl;
	std::cout<<"Value not Exists: " << b.exists(val7)<<std::endl;
	
	//operator[]
	std::cout<<"Val number 2: "<<b[2]<<std::endl;
	
	//  Random Iterator
	sortedArray::const_iterator beginR=b.begin();
	sortedArray::const_iterator endR=b.end();
	
	std::cout<<"Forward 4 " <<*(beginR+4)<<std::endl;
	std::cout<<"Backward 4 " <<*(beginR-4)<<std::endl;
	
	std::cout<<"Accessing element N " << (beginR[3])<<std::endl;
	
	for(; beginR!=endR; ++beginR)
		std::cout<<"Random Iterator Begin Value " << * beginR <<std::endl;
	
	
	// Forward_but_backwards Iterator
	sortedArray::const_reverse_iterator begin=b.B_begin();
	sortedArray::const_reverse_iterator end=b.B_end();
	
	for(; begin!=end; ++begin)
		std::cout<<"Backwards Iterator Begin Value " << * begin <<std::endl;
	
	// Iterator CConstructor
	sortedArray iterated(b.begin(),b.end());
	std::cout<<iterated<<std::endl;
	// */
}

void test_char(){
	
	typedef sortedArray<char,equal_char,order_char_increasing> sortedArray;
	const char val1='a';
	const char val2='b';
	const char val3='c';
	const char val4='d';
	const char val5='e';
	const char val6='f';
	const char val7='g';
	const char val8='h';
	const char val9='i';
	const char val10='z';
	
	sortedArray a;
	
	//Empty Print
	std::cout<<a<<std::endl;
	
	//add
	a.add(val1);
	a.add(val2);
	a.add(val1);
	a.add(val3);
	a.add(val4);
	a.add(val5);
	a.add(val10);
	a.add(val10);
	a.add(val10);
	a.add(val1);
	//Print 
	std::cout<<a<<std::endl;
	// 1-1-1-2-3-4-5-10-10-10
	//CConstructor
	sortedArray b(a);
	
	// std::cout<<b<<std::endl;
	
	//remove, one by one
	a.remove(val1);
	a.remove(val2);
	// a.remove(val1);
	a.remove(val3);
	a.remove(val4);
	a.remove(val5);
	a.remove(val10);
	// a.remove(val10);
	// a.remove(val10);
	// a.remove(val1);
	//a.remove(val1) will throw an exception since it's now empty
	//Is empty
	std::cout<<"It's empty: "<<a<<std::endl;
	
	//Assignment operator
	a=b;
	
	std::cout<<a<<std::endl;
	//Empty Function
	a.empty();
	
	std::cout<<"It's empty,again: "<<a<<std::endl;
	
	//swap
	a.swap(b);
	// /*
	std::cout<<"It's back to full: "<<a<<std::endl;
	
	//Filter
	a=a.filter(is_vowel());
	
	std::cout<<"Only vowel values: "<< a << std::endl;
	
	//getSize, should be 10
	std::cout<<"My size should be 10: " <<b.getSize()<<std::endl;
	
	//Exists
	std::cout<<"Value Exists: " << b.exists(val1) << std::endl;
	std::cout<<"Value not Exists: " << b.exists(val7)<<std::endl;
	
	//operator[]
	std::cout<<"Val number 2: "<<b[2]<<std::endl;
	
	//  Random Iterator
	sortedArray::const_iterator beginR=b.begin();
	sortedArray::const_iterator endR=b.end();
	
	std::cout<<"Forward 4 " <<*(beginR+4)<<std::endl;
	std::cout<<"Backward 4 " <<*(beginR-4)<<std::endl;
	
	std::cout<<"Accessing element N " << (beginR[3])<<std::endl;
	
	for(; beginR!=endR; ++beginR)
		std::cout<<"Random Iterator Begin Value " << * beginR <<std::endl;
	
	
	// Forward_but_backwards Iterator
	sortedArray::const_reverse_iterator begin=b.B_begin();
	sortedArray::const_reverse_iterator end=b.B_end();
	
	for(; begin!=end; ++begin)
		std::cout<<"Backwards Iterator Begin Value " << * begin <<std::endl;
	
	// Iterator CConstructor
	sortedArray iterated(b.begin(),b.end());
	std::cout<<iterated<<std::endl;
	// */
	
  
}

void test_voce(){
  
	typedef sortedArray<voce,equal_voce,order_voce_increasing> sortedArray;
	const voce val1("aaaaaaaa","aaaaaaaaa","aaaaaaaa");
	const voce val2("leonardo","fraquelli","zzzzzzzz");
	const voce val3("pippofoo","fraquelli","fraquesti");
	const voce val4("zorro","fraquelli","zzzzzzzz");
	const voce val5("kj","is","god");
	const voce val6("zaabbbbz","bbbabbbaa","aaaabbba");
	const voce val7("unused","is","unused");
	const voce val8("foo","bar","ca");
	const voce val9("r","u","Here");
	const voce val10("zzzzzzzz","zzzzzzzz","zzzzzzzz");
	
	sortedArray a;
	
	//Empty Print
	std::cout<<a<<std::endl;
	
	//add
	a.add(val1);
	a.add(val2);
	a.add(val1);
	a.add(val3);
	a.add(val4);
	a.add(val5);
	a.add(val10);
	a.add(val10);
	a.add(val10);
	a.add(val1);
	//Print 
	std::cout<<a<<std::endl;
	// 1-1-1-2-3-4-5-10-10-10
	//CConstructor
	sortedArray b(a);
	
	// std::cout<<b<<std::endl;
	
	//remove, one by one
	a.remove(val1);
	a.remove(val2);
	// a.remove(val1);
	a.remove(val3);
	a.remove(val4);
	a.remove(val5);
	a.remove(val10);
	// a.remove(val10);
	// a.remove(val10);
	// a.remove(val1);
	//a.remove(val1) will throw an exception since it's now empty
	//Is empty
	std::cout<<"It's empty: "<<a<<std::endl;
	
	//Assignment operator
	a=b;
	
	std::cout<<a<<std::endl;
	//Empty Function
	a.empty();
	
	std::cout<<"It's empty,again: "<<a<<std::endl;
	 
	//swap
	a.swap(b);
	
	std::cout<<"It's back to full: "<<a<<std::endl;
	
	//Filter
	a=a.filter(is_Fraquelli());
	
	std::cout<<"Only Fraquelli values: "<< a << std::endl;
	
	//getSize, should be 10
	std::cout<<"My size should be 10: " <<b.getSize()<<std::endl;
	
	//Exists
	std::cout<<"Value Exists: " << b.exists(val1) << std::endl;
	std::cout<<"Value not Exists: " << b.exists(val7)<<std::endl;
	
	//operator[]
	std::cout<<"Val number 2: "<<b[2]<<std::endl;
	
	//  Random Iterator
	sortedArray::const_iterator beginR=b.begin();
	sortedArray::const_iterator endR=b.end();
	
	std::cout<<"Forward 4 " <<*(beginR+4)<<std::endl;
	std::cout<<"Backward 4 " <<*(beginR-4)<<std::endl;
	
	std::cout<<"Accessing element N " << (beginR[3])<<std::endl;
	
	for(; beginR!=endR; ++beginR)
		std::cout<<"Random Iterator Begin Value " << * beginR <<std::endl;
	
	
	// Forward_but_backwards Iterator
	sortedArray::const_reverse_iterator begin=b.B_begin();
	sortedArray::const_reverse_iterator end=b.B_end();
	
	for(; begin!=end; ++begin)
		std::cout<<"Backwards Iterator Begin Value " << * begin <<std::endl;
	
	// Iterator CConstructor
	sortedArray iterated(b.begin(),b.end());
	std::cout<<iterated<<std::endl;
	// */
	
	
}

int main(){

  test_int();

  test_char();

  test_voce();
  
  // sortedArray<int,equal_int,order_int_increasing> first;
  // first.add(1);
  // first.add(2);
  // first.add(3);
  
  // sortedArray<int,equal_int,order_int_decreasing> second=createArray(first);
  // std::cout<<second;
  
  // const voce v1("aaa","aaa","aaa");
  // const voce v2("aaa","aaa","aaz");
  // bool t=v1>v2;
  // std::cout<< t <<std::endl;;
	
  
  return 0;
}