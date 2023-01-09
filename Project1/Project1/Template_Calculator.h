#pragma once
////simple calculator sa vezbi
////izmenjeno malo da bi bilo prilagodjeno tome da se 
//#include "std_lib_facilities.h"
//#include "Template_Calculator.h"
//
//#pragma once
////simple calculator sa vezbi
////izmenjeno malo da bi bilo prilagodjeno tome da se 
//#include "std_lib_facilities.h"
//
////------------------------------------------------------------------------------
//
//template <typename T>class Token {
//public:
//	char kind;
//	T value;
//	Token(char ch) :kind(ch), value(T()) { };
//	Token(char ch, T val) : kind(ch), value(val) { };
//	Token(const Token &to) {
//		kind = to.kind;
//		value = to.value;
//	};
//};
//
//template <typename T>
//class Token_stream {
//private:
//	bool full;        // is there a Token in the buffer?
//	Token<T> buffer;     // here is where we keep a Token put back using vrati()
//	string izraz;
//	T nums[6];
//public:
//	Token_stream() :full(false), buffer(0), index(0), izraz("") {};
//	Token_stream(string izraz) :full(false), buffer(0), index(0), izraz(izraz) {};
//	Token<T> nabavi();
//	void vrati(Token<T> t);
//	int index;
//	T primary();
//	T term();
//	T expression();
//};
//
//template<typename T>
//T iskalkulisi(string izraz, T brojevi[6]);