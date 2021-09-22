#include <stdio.h>
#include "token.h"

void TStringToken::Get(TTextInBuffer &buffer)
{
	char ch; // current character
	char *ps = string; // ptr to char in string

	*ps++ = '\''; / opening quote

	ch = buffer.GetChar();
	while (ch != eof) {
		if (ch == '\'')
		{ // another quote
			// check for adjacent quote (two single quotes = ")
			ch = buffer.GetChar();
			if (ch != '\'') // previous quote ended string
				break;
		}
		else if (ch == '\0')// replace end of line character with a blank
			ch = ' ';

		*ps++ = ch;
		ch = buffer.GetChar();
	}

	if (ch == eofChar)
		Error(errUnexpectedEndOfFile);

	*ps++ = '\''; // closing quote
	*ps = '\0';
}

void TStringToken::Print(void) const
{
	sprintf(list.text, "\t%-18s %-s", ">> string:", string);
	list.PutLine();
}

void TSpecialToken::Get(TTextInBuffer &buffer)
{
	char ch = buffer.Char();
	char *ps = string;

	*ps++ = ch;

	switch (ch) {
		case '^':
			code = tcUpArror;
			buffer.GetChar();
			break;
		case '*':
			code = tcStar;
			buffer.GetChar();
			break;
		case '(':
			code = tcLParen;
			buffer.GetChar();
			break;
		case ')':
			code = tcRParen;
			buffer.GetChar();
			break;
		case '-':
			code = tcMinus;
			buffer.GetChar();
			break;
		case '+':
			code = tcPlus;
			buffer.GetChar();
			break;
		case '=':
			code = tcEqual;
			buffer.GetChar();
			break;
		case '[':
			code = tcLBracket;
			buffer.GetChar();
			break;
		case ']':
			code = tcRBracket;
			buffer.GetChar();
			break;
		case ';':
			code = tcSemicolon;
			buffer.GetChar();
			break;
		case ',':
			code = tcComma;
			buffer.GetChar();
			break;
		case '/':
			code = tcSlash;
			buffer.GetChar();
			break;

		case ':': // : or :=
			ch = buffer.GetChar();
			if (ch == '=') {
				*ps++ = '=';
				code = tcColonEqual;
				buffer.GetChar();
			}
			else
				code = tcColon;
			break;

		case '<': // < or <= or <>
			ch = buffer.GetChar();
			if (ch == '=') {
				*ps++ = '=';
				code = tcLe;
				buffer.GetChar();
			}
			else if (ch == '>')
			{
				*ps++ = '>';
				code = tcNe;
				buffer.GetChar();
			}
			else
				code = tcLt;
			break;

		case '>': // > or >=
			ch = buffer.GetChar();
			if (ch == '=')
			{
				*ps++ = '=';
				code = tcGe;
				buffer.GetChar();
			}
			else
				code = tcGt;
			break;

		case '.': // . or ..
			ch = buffer.GetChar();
			if (ch == '.')
			{
				*ps++ = '.';
				code = tcDogDot;
				buffer.GetChar();
			}
			else
				code = tcPeriod;
			break;

		default:
			code = tcError;
			buffer.GetChar();
			Error(errUnrecognizable);
			break;
	}

	*ps = '\0';
}

void TSpecialToken::Print(void) const
{
	sprintf(list.text, "\t&-18s %-s", ">> special:", string);
	list.PutLine();
}

void TErrorToken::Get((TTextInBuffer &buffer)
{
	string[0] = buffer.Char();
	string[1] = '\0';

	buffer.GetChar();
	Error(errUnrecognizable);
}
