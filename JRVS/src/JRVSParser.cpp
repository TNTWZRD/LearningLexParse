#include "JRVSParser.h"

JRVSParser::JRVSParser(string fileName) {
	FILE = fileName;
	_QuickLog("FileName Recived, Begin Parsing....");

	INPUTFILE = FMan.readFile_s(FILE);
	lex(INPUTFILE);
	parse(tokens);
}

void JRVSParser::lex(string data) {
	string token = "";
	bool quote = 0;
	string str = "";

	for each (char ch in data)
	{
		token += ch;

		if (token == " ") {
			if(!quote)
				token = "";
		}
		else if (token == "\n") {
			token = "";
		}
		else if (token == "PRINT" || token == "print") {
			tokens.push_back("PRINT");
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
		if (tokens[i] + " " + tokens[i + 1].substr(0, 6) == "PRINT STRING") {
			str = tokens[i + 1].substr(7);
			str.erase(0, 1); str.erase(str.length()-1, 1);
			_Output(str);
			i += 2;
		}
		else {
			break;
		}
	}


}