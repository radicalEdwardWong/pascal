#include <stdio.h>
#include "common.h"
#include "error.h"
#include "parser.h"

void Parser::Parse(void)
{
	do {
		GetToken();

		if (token == tcEndOfFile) { // shouldn't see end of file
			Error(errUnexpectedEndOfFile);
			break;
		}

		// Enter each identifier into the symbol table
		// if it isn't already there
		if (token == tcIdentifier) {
			SymtabNode *pNode = globalSymtab.Search(pToken->String());
			if (!pNode)
				pNode = globalSymtab.Enter(pToken->String());
		}
	} while(token != tcPeriod);

	// print summary
	list.PutLine();
	sprintf(list.text, "%20d source lines.", currentLineNumber);
	list.PutLine();
	sprintf(list.text, "%20d syntax errors.", errorCount);
	list.PutLine();
}
