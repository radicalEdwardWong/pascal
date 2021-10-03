#include <iostream.h>
#include "error.h"
#include "buffer.h"
#include "parser.h"

void main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Usage: compact <source file>" << endl;
		AbortTranslation(abortInvalidCommandLineArgs);
	}

	// since we're outputting a compact version of the source...
	errorArrowFlag = false; // don't print arrows under syntax errors
	listFlag = false; // don't list the source file

	parser parser(new SourceBuffer(argc[1]));
	parser.Parse();
}
