//simple calculator sa vezbi
//izmenjeno malo da bi bilo prilagodjeno tome da se 
#include "std_lib_facilities.h"
#include "Calculator.h"

Token_stream ts;
int nums[6];

Token::Token(char ch)    // make a Token from a char
	:kind(ch), value(0) { }

Token::Token(char ch, int val)     // make a Token from a char and a double
	:kind(ch), value(val) { }

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
		int val = int(ch)-int('0');
		char drugi = izraz[index];
		if (drugi != '*'&&drugi != '/'&&drugi != '+'&&drugi != '-'&&drugi != '('&&drugi != ')'&&drugi != '\0') {
			val *= 10;
			val += int(drugi) - int('0');
			index++;
			//ako udje u ovaj if onda je prosledjen trocifreni broj sto nije validno
			if (izraz[index] == '0' || izraz[index] == '1' || izraz[index] == '2' || izraz[index] == '3' || izraz[index] == '4' || izraz[index] == '5' || izraz[index] == '6' || izraz[index] == '7' || izraz[index] == '8' || izraz[index] == '9') {
				error("Bad token");
				return 999999999;
			}
		}
		//provera da li je broj jedan od ponudjenih
		bool dobar = false;
		for (int k = 0; k < 6; k++) {
			if (val == nums[k] && nums[k]!=9999) {
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
		error("Bad token");
		return 999999999;
	}
}

// deal with numbers and parentheses
int Token_stream::primary()
{
	Token t = nabavi();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		int d = expression();
		t = nabavi();
		if (t.kind != ')') error("')' expected");
		d *= primary();
		return d;
	}
	case '8':            // we use '8' to represent a number
		return t.value;  // return the number's value
	default:
		error("primary expected");
		return 999999999;
	}
}

//------------------------------------------------------------------------------

// deal with *, /, and %
int Token_stream::term()
{
	int left = primary();
	Token t = nabavi();        // nabavi the next token from token stream

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = nabavi();
			break;
		case '/':
		{
			int d = primary();
			if (d == 0) error("divide by zero");
			if (left%d != 0) {
				error("Not divisable");
				return 999999999;
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
int Token_stream::expression()
{
	int left = term();      // read and evaluate a Term
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

int iskalkulisi(string izraz, int brojevi[6])
try
{
	for (int i = 0; i < 6; i++) {
		nums[i] = brojevi[i];
	}
	int val;
	ts = Token_stream(izraz);        // provides nabavi() and vrati() 
	// cin >> val >> c;
	// cout << val << endl << c;
	while (ts.index < izraz.length()) {
		Token t = ts.nabavi();
		if (t.kind == '\0') return val;
		ts.vrati(t);
		val = ts.expression();
	}
	return val;
}
catch (...) {
	return 999999999;
}