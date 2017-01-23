#include <iostream>
#include <sys/stat.h>
#include <conio.h>
#include <string>

#include "src\JRVSParser.h"
#include "src\utils\logManager.h"

using namespace std;

int main(int argc, char *argv[]) {
	logger::LogManager LOG = logger::LogManager::get();
	int MODE = 1; // 0 for Command Line, 1 for cin
	string File;

	if (argc != 2)
		MODE = 1;
	else if (argc == 2)
		MODE = 0;

	MODE = 2;
	File = "C:\\Users\\danie\\Documents\\Visual Studio 2015\\Projects\\JRVS\\JRVS\\testFile.jrvs";

	if (MODE == 0)
		File = argv[1];
	else if (MODE == 1) {
		cout << "Please Enter JRVS File Location: " << endl;
		getline(cin, File);
	}

	if (File.length() < 6) {
		LOG.LOGERROR("The File Name You Have Entered Is To Short!!!");
		char x; x = _getch();
	}
	else if (File.substr(File.length() - 5, 5) != ".jrvs")
		LOG.LOGERROR("File is not a .jrvs file!!");
	else {
		struct stat fileInfo;
		if (stat(File.c_str(), &fileInfo) != 0)
			LOG.LOGERROR("The Indicated File Does Not Exist!");
		else {
			// Parse And Compile COde Here:
			LOG.LOGCUSTOM("MAIN", "File Found, Begining Parsing....");

			JRVSParser::JRVSParser(File);

			LOG.LOGCUSTOM("MAIN", "File Processed, Quitting....");
		}
	}

	char x; x = _getch();
	return 0;
}