#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "utils\logManager.h"
#include "utils\fileManager.h"
#include "utils\smallUtils.h"

using namespace std;

class JRVSParser {
public:
	JRVSParser(string fileName);

private:
	logger::LogManager    Log = logger::LogManager::get(); // New Log  Object
	fmanager::FileManager FMan;							   // New FMan Object
	vector<string> tokens;
	string OutFile = "logs/" + smallutils::replaceInString(smallutils::getISOTimeStamp(), ':', '-') + ".out";

	void _QuickLog(string out) { Log.LOGDEBUG(string("JRVSParser: " + string(out))); }
	void _Output(string out) { cout << ">>> " << out << endl; FMan.appendFile(OutFile, out); }

	string FILE;
	string INPUTFILE;

	void lex(string data);
	void parse(vector<string> tokens);
};

