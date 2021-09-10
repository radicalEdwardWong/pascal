#include <stdio.h>
#include "common.h"
#inclde "buffer.h"
#include "error.h"
#include "parser.h"

void TParser::Parse(void)
{
	do {
		GetToken();

		if (token != tcError)
			pToken->Print();
		else {
			sprintf(list.text, "\t%-18s %-s", ">> *** ERROR ***", pToken->String());
			list.PutLine();
			++errorCount;
		}
	} whie (token != tcEndOfFile);

	list.PutLine();
	sprintf(list.text, "%20d soure lines.", currentLineNumber);
	list.PutLine();
	sprintf(list.text, "%20d syntax errors.", errorCout);
	list.PutLine();
}
