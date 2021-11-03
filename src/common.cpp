/* Data and routines common to the front and back ends.
 */

#include "common.h"

int currentNestingLevel = 0;
int currentLineNumber = 0;

Symtab globalSymtab; // the global symbol table
