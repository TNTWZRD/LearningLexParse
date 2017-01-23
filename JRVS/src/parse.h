#pragma once

#include "utils\logManager.h"
#include "utils\fileManager.h"
#include "utils\smallUtils.h"

#include "jrvs.h"

using namespace std;

class ParseJARV {
private:
	logger::LogManager Log = logger::LogManager::get(logger::AllLogs::AllOn);
	vector<string>INData;

	void PARSE();
	void FindKeywords(string data, int lineNumber);

public:
	ParseJARV(vector<string> in);


};