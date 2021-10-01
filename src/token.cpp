#include <stdio.h>
#include "token.h"

void strlwr(char *string) {
	char *ch = string;
	do {
		*ch = (char)tolower((int)*ch);
	} while (*ch++ != '\0');
}

/* extract an invalid character from the source */
void ErrorToken::Get(TextInBuffer &buffer)
{
	string[0] = buffer.Char();
	string[1] = '\0';
	buffer.GetChar();
}
