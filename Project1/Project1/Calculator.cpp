//simple calculator sa vezbi
//izmenjeno malo da bi bilo prilagodjeno tome da se 
#include "std_lib_facilities.h"
#include "Calculator.h"

Token_stream ts;
double nums[6];
bool da_li_je_int;

Token::Token(char ch)    // make a Token from a char
	:kind(ch), value(0) { }

Token::Token(char ch, double val)     // make a Token from a char and a double
	: kind(ch), value(val) { }

Token::Token(const Token &t)
{
	kind = t.kind;
	value = t.value;
}

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
	:full(false), buffer(0), index(0), izraz("")    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream(string izraz)
	:full(false), buffer(0), index(0), izraz(izraz)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The vrati() member function puts its argument back into the Token_stream's buffer:
void Token_stream::vrati(Token t)
{
	if (full) error("vrati() into a full buffer");
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
	index--;			  // smanjujemo indeks za 1 jer smo se vratili char unazad
}

//------------------------------------------------------------------------------

Token Token_stream::nabavi()
{
	if (full) {       // do we already have a Token ready?
		// remove token from buffer
		full = false;
		index++;
		return buffer;
	}

	char ch = izraz[index];    // note that >> skips whitespace (space, newline, tab, etc.)
	index++;

	switch (ch) {
	case '(': case ')': case '+': case '-': case '*': case '/': case '\0':
		return Token(ch);        // let each character represent itself
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		//procitaj broj
		double val = double(ch) - double('0');
		char drugi = izraz[index];
		//ako je jednocifreni broj sa zarezom
		if (drugi == '.') {
			string ostatak = "0.";
			ostatak += izraz[index + 1];
			val += stod(ostatak);
			index += 2;
			//posle zareza moze biti samo jedna cifra
			if (izraz[index] == '0' || izraz[index] == '1' || izraz[index] == '2' || izraz[index] == '3' || izraz[index] == '4' || izraz[index] == '5' || izraz[index] == '6' || izraz[index] == '7' || izraz[index] == '8' || izraz[index] == '9') {
				throw exception("Bad token");
				return 999999999;
			}
		}
		//ako je dvocifreni broj
		else if (drugi != '*'&&drugi != '/'&&drugi != '+'&&drugi != '-'&&drugi != '('&&drugi != ')'&&drugi != '\0') {
			val *= 10;
			val += double(drugi) - double('0');
			index++;
			//ako udje u ovaj if onda je prosledjen trocifreni broj sto nije validno
			if (izraz[index] == '0' || izraz[index] == '1' || izraz[index] == '2' || izraz[index] == '3' || izraz[index] == '4' || izraz[index] == '5' || izraz[index] == '6' || izraz[index] == '7' || izraz[index] == '8' || izraz[index] == '9') {
				throw exception("Bad token");
				return 999999999;
			}
			else if (izraz[index] == '.') {
				//ako je dvocifreni broj sa zarezom
				string ostatak = "0.";
				ostatak += izraz[index + 1];
				val += stod(ostatak);
				index += 2;
				//posle zareza moze biti samo jedna cifra
				if (izraz[index] == '0' || izraz[index] == '1' || izraz[index] == '2' || izraz[index] == '3' || izraz[index] == '4' || izraz[index] == '5' || izraz[index] == '6' || izraz[index] == '7' || izraz[index] == '8' || izraz[index] == '9') {
					throw exception("Bad token");
					return 999999999;
				}
			}
		}
		//provera da li je broj jedan od ponudjenih
		bool dobar = false;
		for (int k = 0; k < 6; k++) {
			if (val == nums[k] && nums[k] != 9999) {
				dobar = true;
				nums[k] = 9999;
				break;
			}
		}
		if (dobar) {
			return Token('8', val);   // let '8' represent "a number"
		}
		else {
			return 999999999;
		}
	}
	default:
		throw exception("Bad token");
		return 999999999;
	}
}

// deal with numbers and parentheses
double Token_stream::primary()
{
	Token t = nabavi();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		double d = expression();
		t = nabavi();
		if (t.kind != ')') error("')' expected");
		t = nabavi();
		//ako je posle zagrade broj mnozimo
		if (t.kind == '8') {
			ts.vrati(t);
			d *= primary();
		}
		else {
			ts.vrati(t);
		}
		return d;
	}
	case '8':            // we use '8' to represent a number
		return t.value;  // return the number's value
	default:
		throw exception("primary expected");
		return 999999999;
	}
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double Token_stream::term()
{
	double left = primary();
	Token t = nabavi();        // nabavi the next token from token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = nabavi();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) throw exception("divide by zero");
			//ako su integeri i nisu deljivi nije validno
			if (fmod(left, d) != 0 && da_li_je_int) {
				throw domain_error("Not divisable");
				return 5555555;
			}
			left /= d;
			t = nabavi();
			break;
		}
		case '(':
			ts.vrati(t);
			left *= primary();
			t = nabavi();
			break;
		default:
			vrati(t);     // put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double Token_stream::expression()
{
	double left = term();      // read and evaluate a Term
	Token t = nabavi();        // nabavi the next token from token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term();    // evaluate Term and add
			t = nabavi();
			break;
		case '-':
			left -= term();    // evaluate Term and subtract
			t = nabavi();
			break;
		default:
			vrati(t);     // put t back into the token stream
			return left;       // finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

double iskalkulisi(string izraz, double brojevi[6], bool int_vrednosti)
try
{
	da_li_je_int = int_vrednosti;
	for (int i = 0; i < 6; i++) {
		nums[i] = brojevi[i];
	}
	double val = 0;
	ts = Token_stream(izraz);        // provides nabavi() and vrati() 
	while (ts.index < izraz.length()) {
		Token t = ts.nabavi();
		if (t.kind == '\0') return val;
		ts.vrati(t);
		val = ts.expression();
	}
	return val;
}
catch (std::domain_error e) {
	return 5555555;
}
catch (...) {
	return 999999999;
}