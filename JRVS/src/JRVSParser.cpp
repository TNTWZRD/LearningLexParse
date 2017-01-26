#include "JRVSParser.h"

JRVSParser::JRVSParser(string fileName) {
	FILE = fileName;
	_QuickLog("FileName Recived, Begin Parsing....");

	INPUTFILE = FMan.readFile_s(FILE);
	INPUTFILE += "<EOF>";
	lex(INPUTFILE);
	parse(tokens);
}

void JRVSParser::doPrint(string toPrint) {

	if (toPrint.substr(0, 6) == "STRING") {
		toPrint = toPrint.substr(8);
		toPrint = toPrint.erase(toPrint.length() - 1, 1);
	}
	else if (toPrint.substr(0, 4) == "EXPR") {
		toPrint = evalExpr(toPrint.substr(5));
	}
	else if (toPrint.substr(0, 3) == "NUM") {
		toPrint = toPrint.substr(4);
	}

	_Output(toPrint);

}

string JRVSParser::evalExpr(string expr) {
	return smallutils::intToString(te_interp(expr.c_str(), 0));
}

void JRVSParser::lex(string data) {
	string token, str, expr;
	bool quote = 0;
	bool isexpr = 0;

	for each (char ch in data)
	{
		token += ch;

		if (token == " ") {
			if(!quote)
				token = "";
		}
		else if (token == "\n" || token == "<EOF>") {
			token = "";
			if (expr != "" && isexpr == 1) {
				tokens.push_back("EXPR:"+expr);
				expr = "";
			}
			else if (expr != "" && isexpr == 0) {
				tokens.push_back("NUM:" + expr);
				expr = "";
			}
			isexpr = 0;
		}
		else if (token == "PRINT" || token == "print") {
			tokens.push_back("PRINT");
			token = "";
		}
		else if (token == "0" || token == "1" || token == "2" || token == "3" || token == "4" || token == "5" || token == "6" || token == "7" || token == "8" || token == "9") {
			expr += token;
			token = "";
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^" || token == "%") {
			isexpr = 1;
			expr += token;
			token = "";
		}
		else if (token == "\"") {
			if (quote == 0) {
				quote = 1;
			}
			else if (quote == 1) {
				tokens.push_back("STRING:"+str+"\"");
				str = "";
				quote = 0;
				token = "";
			}
		}
		else if(quote == 1) {
			str += token;
			token = "";
		}
	}
}

void JRVSParser::parse(vector<string> tokens) {
	int i = 0;
	string str;
	while (i < tokens.size()) {
		if (tokens[i] + " " + tokens[i + 1].substr(0, 6) == "PRINT STRING" || tokens[i] + " " + tokens[i + 1].substr(0, 4) == "PRINT EXPR" || tokens[i] + " " + tokens[i + 1].substr(0, 3) == "PRINT NUM") {
			
			doPrint(tokens[i+1]);
			
			i += 2;
		}
		else {
			break;
		}
	}


}