#include "JRVSParser.h"

JRVSParser::JRVSParser(string fileName) {
	FILE = fileName;
	_QuickLog("FileName Recived, Begin Parsing....");

	INPUTFILE = FMan.readFile_s(FILE);
	INPUTFILE += "\n";
	lex(INPUTFILE);
	
#if 0
	cout << "[";
	for each (string val in tokens){
		cout << " \"" << val << "\",";
	}
	cout << "]" << endl;
#else
	parse(tokens);
#endif
}

void JRVSParser::lex(string data) {
	string token, str, expr, var;
	bool quote = 0;
	bool varStarted = 0;
	bool isexpr = 0;

	for each (char ch in data)
	{
		token += ch;

		if (token == " ") {
			if(!quote)
				token = "";
		}
		else if (token == "\n") {
			token = "";
			if (expr != "" && isexpr == 1) {
				tokens.push_back("EXPR:" + expr);
				expr = "";
			}
			else if (expr != "" && isexpr == 0) {
				tokens.push_back("NUM:" + expr);
				expr = "";
			}
			else if (var != "") {
				tokens.push_back("VAR:" + var);
				var = "";
				varStarted = 0;
			}
			isexpr = 0;
		}
		else if (token == "=" && !quote) {
			if (var != "") {
				tokens.push_back("VAR:" + var);
				var = "";
				varStarted = 0;
			}
			tokens.push_back("EQUALS");
			token = "";
		}
		else if (token == "$" && !quote) {
			varStarted = 1;
			var += token;
			token = "";
		}
		if (varStarted == 1) {
			var += token;
			token = "";
		}
		else if (token == "INPUT" || token == "input") {
			tokens.push_back("INPUT");
			token = "";
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
		else if (token == "\"" || token == " \"") {
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
		if (tokens[i] + " " + tokens[i + 1].substr(0, 6) == "PRINT STRING") {
			doPrint(tokens[i + 1]);
			i += 2;
		}
		else if (tokens[i] + " " + tokens[i + 1].substr(0, 4) == "PRINT EXPR") {
			doPrint(tokens[i + 1]);
			i += 2;
		}
		else if (tokens[i] + " " + tokens[i + 1].substr(0, 3) == "PRINT NUM") {
			doPrint(tokens[i + 1]);
			i += 2;
		}
		else if (tokens[i] + " " + tokens[i + 1].substr(0, 3) == "PRINT VAR") {
			doPrint(getVariable(tokens[i + 1]));
			i += 2;
		}
		else if ((tokens[i].substr(0, 3) + " " + tokens[i + 1] + " " + tokens[i + 2].substr(0, 6)) == "VAR EQUALS STRING") {
			doAssign(tokens[i].substr(4), tokens[i + 2]);
			i += 3;
		}
		else if ((tokens[i].substr(0, 3) + " " + tokens[i + 1] + " " + tokens[i + 2].substr(0, 4)) == "VAR EQUALS EXPR") {
			doAssign(tokens[i].substr(4), "NUM:" + evalExpr(tokens[i + 2].substr(5)));
			i += 3;
		}
		else if ((tokens[i].substr(0, 3) + " " + tokens[i + 1] + " " + tokens[i + 2].substr(0, 3)) == "VAR EQUALS NUM") {
			doAssign(tokens[i].substr(4), tokens[i + 2]);
			i += 3;
		}
		else if ((tokens[i].substr(0, 3) + " " + tokens[i + 1] + " " + tokens[i + 2].substr(0, 3)) == "VAR EQUALS VAR") {
			doAssign(tokens[i].substr(4), getVariable(tokens[i+2]));
			i += 3;
		}
		else if (tokens[i] + " " + tokens[i + 1].substr(0, 6) + " " + tokens[i + 2].substr(0, 3) == "INPUT STRING VAR") {
			string in;
			_Output(fixString(tokens[i + 1]));
			getline(cin, in);
			symbols[tokens[i + 2].substr(4)] = "STRING:\"" + in + "\"";
			i += 3;
		}

	}

#if 1
	std::cout << "[";
	for (int i = 0; i < symbols.Size(); i++) {
		std::cout << " \"" << symbols.GetItemName(i) << "\"," << " \"" << symbols[i] << "\",";
	}
	std::cout << "]" << std::endl;
#endif

}

string JRVSParser::fixString(string in) {
	in = in.substr(8);
	in = in.erase(in.length() - 1, 1);
	return in;
}

void JRVSParser::doPrint(string toPrint) {

	if (toPrint.substr(0, 6) == "STRING") {
		toPrint = fixString(toPrint);
	}
	else if (toPrint.substr(0, 3) == "NUM") {
		toPrint = toPrint.substr(4);
	}
	else if (toPrint.substr(0, 4) == "EXPR") {
		toPrint = evalExpr(toPrint.substr(5));
	}

	_Output(toPrint);

}

void JRVSParser::doAssign(string key, string val) {
	symbols[key] = val;
}

string JRVSParser::getVariable(string name) {
	name = name.substr(4);
	if (symbols.IsItem(name))
		return symbols[name];
	else
		return "VARIABLE ERROR: undefined variable.";
}



string JRVSParser::evalExpr(string expr) {
	return smallutils::intToString(te_interp(expr.c_str(), 0));
}