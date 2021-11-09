#include <stdio.h>
#include "common.h"
#include "error.h"
#include "parser.h"

void Parser::Parse(void)
{
	// placeholder for the size of the crunched program
	pIcode->Put(0);

	// extract and put tokens
	do
	{
		GetToken();

		// Shouldn't see an end of file
		if (token == tcEndOfFile) {
			Error(errUnexpectedEndOfFile);
			break;
		}

		// enter each identifier, number, and string into the
		// symbol table if it isn't already in there, then
		// put the token
		switch (token) {
		case tcIdentifier:
		case tcNumber:
		case tcString:
		{
			SymtabNode *pNode = globalSymtab.Search(pToken->String());
			if (!pNode)
				pNode = globalSymtab.Enter(pToken->String());
			pIcode->Put(token, (short)pNode->NodeIndex());
			break;
		}
		default:
			pIcode->Put(token);
			break;
		}
	} while(token != tcPeriod);

	// remember the icode size at this point
	int programSize = pIcode->Size();

	// put symbol table
	pIcode->Put(globalSymtab.NodeCount());
	pIcode->Put(globalSymtab.Root());

	// put size at the head of the file
	pIcode->GoTo(0);
	pIcode->Put(programSize);

	// print the parser's summary
	list.PutLine();
	sprintf(list.text, "%20d source lines.", currentLineNumber);
	list.PutLine();
	sprintf(list.text, "%20d syntax errors.", errorCount);
	list.PutLine();
}
