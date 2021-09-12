#include <stdio.h>
#include "token.h"

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

	for (char &ch:string)
    {
          ch = tolower(ch);
    }

	code = tcWord;
}

void TWordToken::Print(void) const
{
	sprintf(list.text, "\t%-18s %-s", ">> word:", string);
	list.PutLine();
}

void TNumberToken::Get(TTextInBuffer &buffer)
{
	const int maxDigitCount = 4;
	char ch = buffer.Char(); // char from input
	char *ps = string;
	int digitCount = 0;
	int countErrorFlag = false; // true if too mangy digits, else false

	value.integer = 0;
	do {
		*ps++ = ch;

		if (++digitCount <= maxDigitCount)
			value.integer = (10 * value.integer) + (ch - '0');
		else // too many digits
			countErrorFlag = true;

		ch = buffer.GetChar();
	} while (charCodeMap[ch] == ccDigit);

	*ps = '\0';
	code = countErrorFlag ? tcError : tcNumber;
}

void TNumberToken::Print(void) const
{
	sprintf(list.text, "\t%-18s =%d", ">> number:", value.integer);
	list.PutLine();
}

void TSpecialToken::Get(TTextInBuffer &buffer)
{
	char ch = buffer.Char();
	char *ps = string;

	*ps++ = ch;
	*ps = '\0';
	buffer.GetChar();

	code = (ch == '.') ? tcPeriod : tcError;
}

void TSpecialToken::Print(void) const
{
	sprintf(list.text, "\t%-18s %-s", ">> special:", string);
	list.PutLine();
}

/* extract an invalid character from the source */
void TErrorToken::Get(TTextInBuffer &buffer)
{
	string[0] = buffer.Char();
	string[1] = '\0';
	buffer.GetChar();
}
