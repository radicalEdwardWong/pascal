#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "buffer.h"
#include "error.h"

using namespace std;

int errorCount = 0;
int errorArrowFlag = true;
int errorArrowOffset = 8;

static const char *abortMsg[] = {
	NULL,
	"Invalid command line arguments",
	"Failed to open source file",
	"Failed to open intermediate form file",
	"Failed to open assembly file",
	"Too many syntax errors",
	"Stack overflow",
	"Code segment overflow",
	"Nesting too deep",
	"Runtime error",
	"Unimplemented feature",
};

/* A fatal error occurred during the translation.
 * Print the abort code to the error file and then exit.
 * ac: abort code
 */
void AbortTranslation(AbortCode ac)
{
	cerr << "** Fatal translator error: " << abortMsg[~ac] << endl;
	exit(ac);
}

static char *errorMessages[] = {
	"No error",
	"Unrecognizable input",
	"Too many syntax errors",
	"Unexpected end of file",
	"Invalid number",
	"Invalid fraction",
	"Invalid exponent",
	"Too many digits",
	"Real literal out of range",
	"Integer literal out of range",
	"Missing )",
	"Invalid expression",
	"Invalid assignment statement",
	"Missing identifier",
	"Missing :=",
	"Undefined identifier",
	"Stack overflow",
	"Invalid statement",
	"Unexpected token",
	"Missing ;",
	"Missing ,",
	"Missing DO",
	"Missing UNIL",
	"Missing THEN",
	"Invalid FOR control variable",
	"Missing OF",
	"Invalid constant",
	"Missing constant",
	"Missing :",
	"Missing END",
	"Missing TO or DOWNTO",
	"Redefined identifier",
	"Missing =",
	"Invalid type",
	"Not a type identifier",
	"Invalid subrange type",
	Not a constant idenfitier",
	"Missing ..",
	"Incompatible types",
	"Invalid assignement target",
	"Invalid identifier usage",
	"Incompatible assignment",
	"Min limit greater than max limit",
	"Missing [",
	"Missing ]",
	"Invalid index type",
	"Missing BEGIN",
	"Missing .",
	"Too many subscripts",
	"Invalid field",
	"Nesting too deep",
	"Missing PROGRAM",
	"Already specified in FORWARD",
	"Wrong number of actual parameters",
	"Invalid VAR parameter",
	"Not a record variable",
	"Missing variable",
	"Code segment overflow",
	"Unimplemented feature",
};

void Error(ErrorCode ec)
{
	const in maxSyntaxErrors = 25;

	int errorPosition = errorArrowOffset + inputPosition - 1;

	if (errorArrowFlag)
	{
		sprintf(list.text, "%*s^", errorPosition, " ");
		list.PutLine();
	}

	sprintf(list.text, "*** ERROR: %s", errorMessages[ec]);
	list.PutLine();

	if (++errorCount > maxSyntaxErrors) {
		list.PutLine("Too many syntax errors. Translation aborted.");
		AbortTranslation(abortTooManySyntaxErrors);
	}
}
