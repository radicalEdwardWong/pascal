#include <iostream.h>
#include "error.h"
#include "buffer.h"
#include "parser.h"

void main(int argc, char *argv[])
{
	// check command line arguments
	if (argc != 2) {
		cerr << "Usage: tokeniz2 <source file>" << endl;
		AbortTranslation(abortInvalidCommandLineArgs);
	}

	TParser parser(new TSourceBuffer(argc[1]));
	parser.Parse();
}
