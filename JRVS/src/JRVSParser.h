#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "utils\logManager.h"
#include "utils\fileManager.h"
#include "utils\smallUtils.h"
#include "utils\tinyexpr.h"

using namespace std;

class JRVSParser {
public:
	JRVSParser(string fileName);

private:
	logger::LogManager    Log = logger::LogManager::get(); // New Log  Object
	fmanager::FileManager FMan;							   // New FMan Object

	vector<string> tokens;
	smallutils::AssocArray<string> symbols;

	string OutFile = "logs/" + smallutils::replaceInString(smallutils::getISOTimeStamp(), ':', '-') + ".out";

	void _QuickLog(string out) { Log.LOGDEBUG(string("JRVSParser: " + string(out))); }
	void _Output(string out) { std::cout << ">>> " << out << std::endl; FMan.appendFile(OutFile, out); }

	string FILE;
	string INPUTFILE;

	void lex(string data);
	void parse(vector<string> tokens);

	string fixString(string in);
	
	void doPrint(string toPrint);
	void doAssign(string key, string val);
	string getVariable(string name);

	string evalExpr(string expr);
};

