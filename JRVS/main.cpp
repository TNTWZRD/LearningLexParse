#include <iostream>
#include <string>

#include "src\utils\logManager.h"

using namespace std;

int main() {
	// Variables:
	static const string TITLE = "JRVS";
	logger::LogManager Log = logger::LogManager::get(logger::AllLogs::AllOn);

	// Do Stuff:

	Log.LOGCUSTOM(TITLE, "JRVS Process Started.");


	cout << endl;
	system("PAUSE");
	return 0;
}