#include <stdio.h>
#include "common.h"
#include "error.h"
#include "parser.h"

void TParser::Parse(void)
{
	// Loop to extract and print tokens
	// until the end of the source file.
	do {
		GetToken();
		if (token != tcError)
			pToken->Print();
	} while (token != tcEndOfFile);

	list.PutLine();
	sprintf(list.text, "%20d source lines.", currentLineNumber);
	list.PutLine();
	sprintf(list.text, "%20d syntax errors.", errorCount);
	list.PutLine();
}
