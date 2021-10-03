#include <iostream>
#include <string.h>
#include "complist.h"

using namespace std;

void CompactListBuffer::PutBlank(void)
{
	if (++textLength >= maxCompactTextLength - 1)
		PutLine();
	else
		*pText++ = ' ';
}

void CompactListBuffer::Put(const char *pString)
{
	int tokenLength = strlen(pString);

	if (textLength + tokenLength >= maxCompactTextLength - 1) 
		PutLine();

	strcpy(pText, pString);
	pText += tokenLength;
	textLength += tokenLength;
}

void CompactListBuffer::PutLine(void)
{
	if (textLength > 0) {
		*pText = '\0';
		cout << text << endl;

		pText = text;
		textLength = 0;
	}
}
