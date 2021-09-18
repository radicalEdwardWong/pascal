#include "error.h"
#include "buffer.h"
#include "parser.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: tokenize1 <source file>" << endl;
		AbortTranslation(abortInvalidCommandLineArgs);
	}

	TParser parser(new TSourceBuffer(argv[1]));
	parser.Parse();
	return 0;
}