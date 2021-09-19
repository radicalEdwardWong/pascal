#include <string.h>
#include <stdio.h>
#include "token.h"

const int minResWordLen = 2;
const int maxResWordLen = 9;

struct TResWord {
	const char *pString;
	TTokenCode code;
};

static TResWord rw2[] = {
	{"do", tcDO}, {"if", tcIF}, {"in", tcIN}, {"of", tcOF},
	{"or", tcOR}, {"to", tcTO}, {NULL},
};

static TResWord rw3[] = {
	{"and", tcAND}, {"div", tcDIV}, {"end", tcEND}, {"for", tcFOR},
	{"mod", tcMOD}, {"nil", tcNIL}, {"not", tcNOT}, {"set", tcSET},
	{"var", tcVAR}, {NULL},
};

static TResWord rw4[] = {
	{"case", tcCASE}, {"els", tcELSE}, {"file", tcFILE},
	{"goto", tcGOTO}, {"then", tcTHEN}, {"type", tcTYPE},
	{"with", tcWITH}, {NULL},
};

static TResWord rw5[] = {
	{"array", tcARRAY}, {"begin", tcBEGIN}, {"const", tcCONST},
	{"label", tcLABEL}, {"until", tcUNTIL}, {"while", tcWHILE},
	{NULL},
};

static TResWord rw6[] = {
	{"downto", tcDOWNTO}, {"packed", tcPACKED}, {"record", tcRECORD},
	{"repeat", tcREPEAT}, {NULL},
};

static TResWord rw7[] = {
	{"program", tcPROGRAM}, {NULL},
};

static TResWord rw8[] = {
	{"function", tcFUNCTION}, {NULL},
};

static TResWord rw9[] = {
	{"procedure", tcPROCEDURE}, {NULL},
};

static TResWord *rwTable[] = {
	NULL, NULL, rw2, rw3, rw4, rw5, rw6, rw7, rw8, rw9,
};

void TWordToken::Get(TTextInBuffer &buffer)
{
	extern TCharCode charCodeMap[];
	char ch = buffer.Char();
	char *ps = string;

	do {
		*ps++ = ch;
		ch = buffer.GetChar();
	} while( (charCodeMap[ch] == ccLetter)
		|| (charCodeMap[ch] == ccDigit));

	*ps = '\0';
	strlwr(string);

	CheckForReservedWord();
}

void TWordToken::CheckForReservedWord(void)
{
	int len = strlen(string);
	TResWord *prw;

	code = tcIdentifier;

	if ((len >= minResWordLen) && (len <= maxResWordLen)) {
		for (prw = rwTable[len]; prw->pString; ++prw) {
			if (strcmp(string, prw->pString) == 0) {
				code = prw->code;
				break;
			}
		}
	}
}

void TWordToken::Print(void) const
{
	if (code == tcIdentifier)
	{
		sprintf(list.text, "\t%-18s %-s", ">> identifier:", string);
	}
	else
	{
		sprintf(list.text, "\t%-18s %-s", ">> reserved word:", string);
	}

	list.PutLine();
}
