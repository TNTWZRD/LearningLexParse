#include "main.h" // Store includes here

using namespace std;

int main() {
	// Variables:
	static const string TITLE = "JRVS";
	logger::LogManager Log = logger::LogManager::get(logger::AllLogs::AllOn);
	fmanager::FileManager fman;

	// Do Stuff:
	Log.LOGCUSTOM(TITLE, "JRVS Process Started.");
	
	Log.LOGDEBUG("Found \"input/main.jrvs\" And Created New ParseJARV Object.");
	ParseJARV parseJARV = ParseJARV(fman.readFile_v("input/main.jrvs"));

	Log.LOGCUSTOM(TITLE, "JRVS Process Finnished.");

	cout << endl;
	system("PAUSE");
	return 0;
}