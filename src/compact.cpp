#include <iostream>
#include "error.h"
#include "buffer.h"
#include "parser.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Usage: compact <source file>" << endl;
		AbortTranslation(abortInvalidCommandLineArgs);
	}

	// since we're outputting a compact version of the source...
	errorArrowFlag = false; // don't print arrows under syntax errors
	listFlag = false; // don't list the source file

	Parser parser(new SourceBuffer(argv[1]));
	parser.Parse();
}
