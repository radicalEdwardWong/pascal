/* Print the contents of the source file in a format that
 * include paeg headings, line numbers, and nesting levels.
 */

#include <iostream>
#include "error.h"
#include "buffer.h"

using namespace std;

int main(int argc, char *argv[])
{
	char ch; // character fetched from source

	if (argc != 2) {
		cerr << "Usage: list <source file>" << endl;
		AbortTranslation(abortInvalidCommandLineArgs);
	}

	TSourceBuffer source(argv[1]);

	do
	{
		ch = source.GetChar();

	} while (ch != eofChar);
}
