#include "scanner.h"

CharCode charCodeMap[128];

TextScanner::TextScanner(TextInBuffer *pBuffer)
	: pTextInBuffer(pBuffer)
{
	int i;

	// initialize character code map
	for (i = 0; i <= 127; ++i) charCodeMap[i] = ccError;
	for (i = 'a'; i <= 'z'; ++i) charCodeMap[i] = ccLetter;
	for (i = 'A'; i <= 'Z'; ++i) charCodeMap[i] = ccLetter;
	for (i = '0'; i <= '9'; ++i) charCodeMap[i] = ccDigit;
	charCodeMap['+'] = charCodeMap['-'] = ccSpecial;
	charCodeMap['*'] = charCodeMap['/'] = ccSpecial;
	charCodeMap['='] = charCodeMap['^'] = ccSpecial;
	charCodeMap['.'] = charCodeMap[','] = ccSpecial;
	charCodeMap['<'] = charCodeMap['>'] = ccSpecial;
	charCodeMap['('] = charCodeMap[')'] = ccSpecial;
	charCodeMap['['] = charCodeMap[']'] = ccSpecial;
	charCodeMap['{'] = charCodeMap['}'] = ccSpecial;
	charCodeMap[':'] = charCodeMap[';'] = ccSpecial;
	charCodeMap[' '] = charCodeMap['\t'] = ccWhiteSpace;
	charCodeMap['\n'] = charCodeMap['\0'] = ccWhiteSpace;
	charCodeMap['\''] = ccQuote;
	charCodeMap[eofChar] = ccEndOfFile;
}

void TextScanner::SkipWhiteSpace(void)
{
	char ch = pTextInBuffer->Char();

	do {
		if (charCodeMap[ch] == ccWhiteSpace) {
			ch = pTextInBuffer->GetChar();
		}
		else if (ch == '{') {
			do {
				ch = pTextInBuffer->GetChar();
			} while ((ch != '}') && (ch != eofChar));

			if (ch != eofChar)
				ch = pTextInBuffer->GetChar();
			else
				Error(errUnexpectedEndOfFile);
		}
	} while ((charCodeMap[ch] == ccWhiteSpace) || (ch == '{'));
}

Token *TextScanner::Get(void)
{
	Token *pToken;

	SkipWhiteSpace();

	switch (charCodeMap[pTextInBuffer->Char()]) {
		case ccLetter:
			pToken = &wordToken;
			break;
		case ccDigit:
			pToken = &numberToken;
			break;
		case ccQuote:
			pToken = &stringToken;
			break;
		case ccSpecial:
			pToken = &specialToken;
			break;
		case ccEndOfFile:
			pToken = &eofToken;
			break;
		default:
			pToken = &errorToken;
			break;
	}

	pToken->Get(*pTextInBuffer);

	return pToken;
}
