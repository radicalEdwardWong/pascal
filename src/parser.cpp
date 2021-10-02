#include <stdio.h>
#include "common.h"
#include "error.h"
#include "parser.h"

void Parser::Parse(void)
{
	int currIsDelimiter;
	int prevIsDelimiter = true;

	do {
		GetToken();

		if (token == tcEndOfFile) {
			Error(errUnexpectedEndOfFile);
			break;
		}

		if (token != tcError) {
			currIsDelimiter = pToken->IsDelimiter();

			if (!prevIsDelimiter && !currIsDelimiter) {
				pCompact->PutBlank();
			}
			pCompact->Put(pToken->String());

			prevIsDelimiter = currIsDelimiter;
		}
		else
			Error(errUnrecognizable);
	} while (token != tcPeriod);

	pCompact->PutLine();
}
