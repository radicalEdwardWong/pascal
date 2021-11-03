#include <iostream>
#include <string.h>
#include "common.h"
#include "error.h"
#include "buffer.h"
#include "symtab.h"
#include "parser.h"

int main(int argc, char *argv[])
{
	extern int xrefFlag;

	// check cmdline args
	if ((argc != 2) && (argc != 3)) {
		cerr << "Usage: xref1 <source file> [-x]" << endl;
		AbortTranslation(abortInvalidCommandLineArgs);
	}

	// set cross-referencing flag
	xrefFlag = (argc == 3) && (strcmp(argv[2], "-x") == 0);

	// parse the file
	Parser parser(new SourceBuffer(argv[1]));

	parser.Parse();

	// print the cross-reference
	if (xrefFlag) {
		list.PutLine();
		list.PutLine("***** Cross-Reference *****");
		list.PutLine();
		globalSymtab.Print();
	}

	return 0;
}
