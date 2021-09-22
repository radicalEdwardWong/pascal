#include <stdio.h>
#include "token.h"

void strlwr(char *string) {
	char *ch = string;
	do {
		*ch = (char)tolower((int)*ch);
	} while (*ch++ != '\0');
}

void TWordToken::Get(TTextInBuffer &buffer)
{
	char ch = buffer.Char();
	char *ps = string;

	do {
		*ps++ = ch;
		ch = buffer.GetChar();
	} while ( (charCodeMap[ch] == ccLetter)
		|| (charCodeMap[ch] == ccDigit ) );

	*ps = '\0';

	strlwr(string);

	code = tcWord;
}

void TWordToken::Print(void) const
{
	sprintf(list.text, "\t%-18s %-s", ">> word:", string);
	list.PutLine();
}

/* extract an invalid character from the source */
void TErrorToken::Get(TTextInBuffer &buffer)
{
	string[0] = buffer.Char();
	string[1] = '\0';
	buffer.GetChar();
}
