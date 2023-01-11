//Autor: Mila Milovic SV22-2021
//Datum poslednje izmene: 09.01.2023.
#pragma once
//simple calculator sa vezbi, deklaracije klasa i funkcije
//izmenjeno malo da bi bilo prilagodjeno tome da se radi sa stringovima
//funkcionalnost deljenja je razlicita za int u odnosu na double vrednosti
//takodje je izmenjeno da racuna da je (4+1)7 = 35 tj ako nema operacije mnozi se
#include "std_lib_facilities.h"

//------------------------------------------------------------------------------

class Token {
public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	Token(char ch);
	Token(char ch, double val);
	Token(const Token &t);
};

//------------------------------------------------------------------------------

class Token_stream {
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token_stream(string izraz);   // make a Token_stream that reads from string
	Token nabavi();      // nabavi a Token (nabavi() is defined elsewhere)
	void vrati(Token t);    // put a Token back
	double index;
	double expression();    // declaration so that primary() can call expression()
	double primary();
	double term();
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using vrati()
	string izraz;
};

double iskalkulisi(string izraz, double brojevi[6], bool int_vrednosti);