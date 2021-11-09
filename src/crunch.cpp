#include <iostream>
#include "common.h"
#include "error.h"
#include "buffer.h"
#include "symtab.h"
#include "icode.h"
#include "parser.h"

Icode *pIcode; // ptr to the intermediate code

int main(int argc, char *argv[])
{
	// validate
	if (argc != 3)
	{
		cerr << "Usage: crunch <source file> <icode file>" << endl;
		AbortTranslation(abortInvalidCommandLineArgs);
	}

	// create the inermediate code
	pIcode = new Icode(argv[2], Icode::output);

	// parse the file
	Parser parser(new SourceBuffer(argv[1]));
	parser.Parse();

	// clean
	delete pIcode;
}
