#include "jrvs.h"



JRVS::JRVS() {}

void JRVS::JRVSPrint(string data) {
	fmanager::FileManager fman;
	logger::LogManager Log = logger::LogManager::get(logger::AllLogs::AllOn);

	fman.appendFile("logs/" + smallutils::replaceInString(smallutils::getISOTimeStamp(), ':', '-') + ".out", data);
	cout << ">>> " << data << endl;
	Log.LOGCUSTOM("JRVS", "JRVSPrint: " + data);
}
