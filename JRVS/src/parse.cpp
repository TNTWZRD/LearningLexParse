#include "parse.h"

// constructor
ParseJARV::ParseJARV(vector<string> in) {
	INData = in;
	PARSE();
}

// Main Parse Object
void ParseJARV::PARSE() {
	Log.LOGCUSTOM("ParseJARV", "PARSE() Called. Starting.....");

	int c = 0;
	for each (string value in INData)
	{
		if (value.length() != 0) {
			Log.LOGCUSTOM("ParseJARV", "Data: " + value);
			FindKeywords(value, c);
			c++;
		}
	}

}

void ParseJARV::FindKeywords(string data, int lineNumber) {
	size_t found;
	string keyword;
	int start, end;

	// Keyword print
	keyword = "print";
	found = data.find(keyword);
	if (found != string::npos) {
		// Found print
		start = found;
		found = data.find(';', found+1);
		if (found != string::npos) {
			// Found ';'
			end = found;
			found = data.find('"', start);
			if (found != string::npos) {
				// Found First "
				start = found+1;
				found = data.find('"', found+1);
				if (found != string::npos) {
					// Found Second "
					end = found;
					JRVS::JRVSPrint(data.substr(start, end-start));
				}
				else
					Log.LOGERROR("ParseJARV Line:" + smallutils::intToString(lineNumber) + ", Missing A '\"'.");
			}
			else
				Log.LOGERROR("ParseJARV Line:" + smallutils::intToString(lineNumber) + ", Could not find '\"'.");
		}
		else
			Log.LOGERROR("ParseJARV Line:" + smallutils::intToString(lineNumber) + ", Could not find ';'.");
	}

	// Keyword print
	keyword = "end;";
	found = data.find(keyword);
	if (found != string::npos)
		JRVS::JRVSPrint(">>>ENDOFFILE<<<");


}