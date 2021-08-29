#include <stdlib.h>
#include <iostream.h>
#include "error.h"

int errorCount = 0;

static char *abortMsg[] = {
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
void AbortTranslation(TAbortCode ac)
{
	cerr << "** Fatal translator error: " << abortMsg[~ac] << endl;
	exit(ac);
}
